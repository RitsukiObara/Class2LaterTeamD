//============================================
//
// ゲームのメイン処理[game.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "map.h"
#include "skybox.h"
#include "rat.h"
#include "Cat.h"
#include "game_timer.h"
#include "edit.h"
#include "weapon_selectUI.h"
#include "block.h"
#include "countdown.h"
#include "item.h"
#include "resurrection_fan.h"
#include "player.h"
#include "entry.h"

#include "obstacle_manager.h"
#include "chara_infoUI.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define TRANS_COUNT		(80)	// 遷移カウント

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// ポーズの情報
CPlayer* CGame::m_apPlayer[MAX_PLAY] = {};				// プレイヤーの情報
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// ゲームの進行状態
int CGame::m_nFinishCount = 0;								// 終了カウント

// デバッグ版
#ifdef _DEBUG
CEdit* CGame::m_pEdit = nullptr;							// エディットの情報
bool CGame::m_bEdit = false;								// エディット状況
#endif

//=========================================
// コンストラクタ
//=========================================
CGame::CGame() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pPause = nullptr;			// ポーズ
	m_nFinishCount = 0;			// 終了カウント
	m_GameState = STATE_START;	// 状態

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// ネズミの情報
	}

// デバッグ版
#ifdef _DEBUG
	m_pEdit = nullptr;			// エディット
	m_bEdit = false;			// エディット状況
#endif
}

//=========================================
// デストラクタ
//=========================================
CGame::~CGame()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CGame::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// テキスト読み込み処理
	CElevation::TxtSet();

	// メッシュの読み込み処理
	//CMesh::TxtSet();

	// マップの情報をロードする
	CManager::Get()->GetFile()->Load(CFile::TYPE_OBSTACLE);
	CManager::Get()->GetFile()->Load(CFile::TYPE_CARROUTE);
	CManager::Get()->GetFile()->Load(CFile::TYPE_BLOCK);

	// マップの設定処理
	CManager::Get()->GetFile()->SetMap();

	// カウントダウンの生成処理
	CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(200.0f, 250.0f, 0.0f));

	// メッシュのテキスト読み込み
	//CMesh::TxtSet();

	// スカイボックスの生成処理
	CSkyBox::Create();

	//マップの生成
	CMap::Create();

#ifdef _DEBUG	//障害物テスト用

	// ルンバの生成処理
	CObstacle::Create(D3DXVECTOR3(-600.0f, 0.0f, -400.0f), CObstacle::TYPE_ROOMBA);

	// ひもの生成処理
	CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), CObstacle::TYPE_HIMO);

	// スピーカーの生成処理
	CObstacle::Create(D3DXVECTOR3(-250.0f, 200.0f, 900.0f), CObstacle::TYPE_SPEAKER);

	// リードの生成処理
	CObstacle *pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), CObstacle::TYPE_LEASH);
	pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	// 画鋲の生成処理
	CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, -120.0f), CObstacle::TYPE_PIN);

	// 扇風機の生成処理
	CObstacle::Create(D3DXVECTOR3(0.0f, 200.0f, 900.0f), CObstacle::TYPE::TYPE_FAN);

	// コップの生成処理
	CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, 100.0f), CObstacle::TYPE::TYPE_CUP);

#endif // _DEBUG

	// ネコのインデックスを取得する
	int nCat = CEntry::GetCatIdx();

	// ネズミの生成
	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		if (nCntPlay == nCat)
		{ // ネコ担当のプレイヤーの場合

			// プレイヤーの生成
			m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(500.0f * nCntPlay - 500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_CAT);
		}
		else
		{ // 上記以外

			// プレイヤーの生成
			m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(500.0f * nCntPlay - 500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_RAT);
		}
	}

	// 生成処理
	CGameTime::Create();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CCharaInfoUI::Create(D3DXVECTOR3(160.0f + (nCnt * 320.0f), 650.0f, 0.0f), nCnt, m_apPlayer[nCnt]->GetType());
	}

	//// 武器選択UIを生成
	//CWeaponSelectUI::Create();

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
	m_GameState = STATE_START;		// 状態

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CGame::Uninit(void)
{
	// ポインタを NULL にする
	m_pPause = nullptr;			// ポーズ

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// ネズミの情報
	}

	// 終了カウントを初期化する
	m_nFinishCount = 0;

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CGame::Update(void)
{

// デバッグ版
#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_8) == true)
	{ // 8キーを押したとき
		m_GameState = STATE_CAT_WIN;		// ねこのかち
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
	{ // 9キーを押したとき
		m_GameState = STATE_RAT_WIN;		// ねずみのかち
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F7) == true)
	{ // F7キーを押した場合

		// エディット状況を入れ替える
		m_bEdit = m_bEdit ? false : true;

		if (m_bEdit == true)
		{ // エディット状況が true の場合

			if (m_pEdit == nullptr)
			{ // エディット状況が NULL の場合

				// エディットの生成処理
				m_pEdit = CEdit::Create();
			}
		}
		else
		{ // 上記以外

			if (m_pEdit != nullptr)
			{ // エディット状況が NULL じゃない場合

				// 終了処理
				m_pEdit->Uninit();
				m_pEdit = nullptr;
			}
			else
			{ // 上記以外

				// 停止
				assert(false);
			}
		}
	}

#endif

	switch (m_GameState)
	{
	case CGame::STATE_START:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_PLAY:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_RAT_WIN:

		// 遷移処理
		Transition();

		break;

	case CGame::STATE_CAT_WIN:

		// 遷移処理
		Transition();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

#ifdef _DEBUG

	if (m_bEdit == true)
	{ // エディット状況が true の場合

		if (m_pEdit != nullptr)
		{ // エディットが NULL じゃない場合

			// エディットの更新処理
			m_pEdit->Update();
		}

		for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
		{
			// 死亡判別処理
			CObject::DeathDecision(nCnt);
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F9) == true)
		{ // F9キーを押した場合

			// 情報をセーブする
			CManager::Get()->GetFile()->Save(CFile::TYPE_OBSTACLE);		// 障害物
			CManager::Get()->GetFile()->Save(CFile::TYPE_BLOCK);		// ブロック
		}
	}
	else
	{ // 上記以外

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // レンダラーが NULL じゃない場合

			// レンダラーの更新
			CManager::Get()->GetRenderer()->Update();
		}
	}

#else

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// レンダラーの更新
		CManager::Get()->GetRenderer()->Update();
	}

#endif
		
	CManager::Get()->GetDebugProc()->Print("状態：%d", m_GameState);
}

//======================================
//描画処理
//======================================
void CGame::Draw(void)
{

}

//======================================
// 情報の設定処理
//======================================
void CGame::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);

	if (m_pPause == nullptr)
	{ // ポーズへのポインタが NULL の場合

		// ポーズの生成処理
		m_pPause = CPause::Create();
	}

	// スタート状態にする
	m_GameState = STATE_START;

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
}

//======================================
// ポーズ処理
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true)
	{ // Pキーを押した場合

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // フェード無し状態かつ、終了以外の場合

			if (m_pPause->GetPause() == false)
			{ // ポーズが false だった場合

				// ポーズ状況を true にする
				m_pPause->SetPause(true);
			}
			else
			{ // ポーズが true だった場合

				// ポーズ状況を false にする
				m_pPause->SetPause(false);
			}

			// 決定音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// 遷移処理
//======================================
void CGame::Transition(void)
{
	// 終了カウントを加算する
	m_nFinishCount++;

	if (m_nFinishCount % TRANS_COUNT == 0)
	{ // 終了カウントが一定数を超えた場合

		// リザルトに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// ポーズの取得処理
//======================================
CPause* CGame::GetPause(void)
{
	// ポーズの情報を返す
	return m_pPause;
}

//======================================
// ゲームの進行状態の設定処理
//======================================
void CGame::SetState(const STATE state)
{
	// ゲームの進行状態を設定する
	m_GameState = state;
}

//======================================
// ゲームの進行状態の取得処理
//======================================
CGame::STATE CGame::GetState(void)
{
	// ゲームの進行状態を返す
	return m_GameState;
}

//======================================
// プレイヤーの取得処理
//======================================
CPlayer* CGame::GetPlayer(const int nID)
{
	if (nID < MAX_PLAY)
	{ // インデックスが一定未満の場合

		// プレイヤーの情報を取得する
		return m_apPlayer[nID];
	}
	else
	{ // 上記以外

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}
}

//======================================
// ポーズのNULL化処理
//======================================
void CGame::DeletePause(void)
{
	// ポーズのポインタを NULL にする
	m_pPause = nullptr;
}

//======================================
// ネズミのNULL化処理
//======================================
void CGame::DeletePlayer(int nIdx)
{
	if (nIdx < MAX_PLAY)
	{ // 番号が最大数未満の場合

		// プレイヤーのポインタを NULL にする
		m_apPlayer[nIdx] = nullptr;
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}
}

// デバッグ版
#ifdef _DEBUG
//======================================
// エディットの取得処理
//======================================
CEdit* CGame::GetEdit(void)
{
	// エディットの情報を返す
	return m_pEdit;
}

//======================================
// エディット状況の取得処理
//======================================
bool CGame::IsEdit(void)
{
	// エディット状況を返す
	return m_bEdit;
}

#endif