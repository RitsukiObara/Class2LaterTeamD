//============================================
//
// 時間処理[time.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "game_timer.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"

#include "pause.h"

//--------------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------------
CGameTime* CGameTime::m_pGameTimer = nullptr;		// ゲームタイマーの情報

//--------------------------------------------------
// マクロ定義
//--------------------------------------------------
#define TIME_POS			(D3DXVECTOR3(500.0f, 50.0f, 0.0f))		// ゲームタイマーの点のサイズ
#define TIME_SIZE			(D3DXVECTOR3(25.0f, 40.0f, 0.0f))		// ゲームタイマーの点のサイズ
#define TIME_DOT_SIZE		(D3DXVECTOR3(8.0f, 8.0f, 0.0f))			// ゲームタイマーの点のサイズ
#define TIME_WIDTH_SHIFT	(50.0f)									// ゲームタイマーのずらす横幅

//========================
// コンストラクタ
//========================
CGameTime::CGameTime() : CTime(CObject::TYPE_TIME, CObject::PRIORITY_UI)
{
	// 全ての値を初期化する
	m_StartTime = 0;		// 開始時刻
	m_PauseTime = 0;		// ポーズ中の時間
	m_bGoal = false;		// ゴール状況
}

//========================
// デストラクタ
//========================
CGameTime::~CGameTime()
{

}

//========================
// 初期化処理
//========================
HRESULT CGameTime::Init(void)
{
	// 全ての値を初期化する
	m_StartTime = 0;		// 開始時刻
	m_bGoal = false;		// ゴール状況
	m_PauseTime = 0;		// ポーズ中の時間

	if (FAILED(CTime::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CGameTime::Uninit(void)
{
	// タイムの終了処理
	CTime::Uninit();

	// ゲームタイマーを NULL にする
	m_pGameTimer = nullptr;
}

//========================
// 更新処理
//========================
void CGameTime::Update(void)
{
	if (CGame::GetPause() != nullptr)
	{ // ポーズの情報がある場合

		if (CGame::GetPause()->GetPause() == true &&
			CGame::GetState() == CGame::STATE_PLAY)
		{ // ポーズ中かつ、プレイ中の場合

			// ポーズ中の処理
			PauseProcess();
		}
		else
		{ // 上記以外

			if (CGame::GetState() != CGame::STATE_START)
			{ // スタート状態または、カウントダウン状態以外の場合

				// 通常の更新処理
				Basic();
			}
		}
	}
	else
	{ // 上記以外

		if (CGame::GetState() != CGame::STATE_START)
		{ // スタート状態または、カウントダウン状態以外の場合

			// 通常の更新処理
			Basic();
		}
	}
}

//========================
// 描画処理
//========================
void CGameTime::Draw(void)
{
	// 描画処理
	CTime::Draw();
}

//========================
// タイムの開始処理
//========================
void CGameTime::TimeStart(void)
{
	// 現在の時刻を取得する
	m_StartTime = timeGetTime();
}

//========================
// 通常の更新処理
//========================
void CGameTime::Basic(void)
{
	if (CGame::GetState() == CGame::STATE_GOAL)
	{ // ゴール状態の場合

		// ゴール状況を true にする
		m_bGoal = true;
	}

	if (m_bGoal == false)
	{ // ゴール状況が false の場合

		// 計算処理
		Calculate();

		// 1桁ごとのテクスチャの設定処理
		SetTexture();
	}
}

//========================
// ポーズ中の処理
//========================
void CGameTime::PauseProcess(void)
{
	// ローカル変数宣言
	DWORD NowTime = timeGetTime();		// 現在の時刻
	DWORD TotalTime = GetTotalTime();	// 合計時間

	// ポーズ中の時間を設定する
	m_PauseTime = (NowTime - m_StartTime) - TotalTime;
}

//========================
// 計算処理
//========================
void CGameTime::Calculate(void)
{
	// ローカル変数宣言
	DWORD NowTime;				// 現在の時刻

	// 現在時刻を取得する
	NowTime = timeGetTime();

	// 経過した秒数を測る
	SetTotalTime((NowTime - m_StartTime) - m_PauseTime);

	if (GetTotalTime() >= MAX_TIME)
	{ // 経過時間が 最大数 を超えた場合

		// 経過時間を補正する
		SetTotalTime(MAX_TIME);
	}

	// 数値の設定処理
	SetNumber();
}

//========================
// 取得処理
//========================
CGameTime* CGameTime::Get(void)
{
	if (m_pGameTimer != nullptr)
	{ // ゲームタイマーが NULL じゃなかった場合

		// ゲームタイムを返す
		return m_pGameTimer;
	}
	else
	{ // 上記以外

		// 生成して返す
		return m_pGameTimer = CGameTime::Create();
	}
}

//========================
// 生成処理
//========================
CGameTime* CGameTime::Create(void)
{
	if (m_pGameTimer == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		m_pGameTimer = new CGameTime;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return nullptr;
	}

	if (m_pGameTimer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(m_pGameTimer->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		m_pGameTimer->SetData(TIME_POS, NONE_D3DXVECTOR3, TIME_SIZE, TIME_DOT_SIZE, TIME_WIDTH_SHIFT);

		// 現在時刻を設定する
		m_pGameTimer->m_StartTime = timeGetTime();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 時間のポインタを返す
	return m_pGameTimer;
}