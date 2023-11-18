//============================================
//
// タイトルロゴ処理[title_logo.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "title_logo.h"
#include "object2D.h"
#include "title.h"
#include "texture.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define RAT_TEXTURE			"data/TEXTURE/TitleRat.png"				// タイトルロゴ(ネズミ)のテクスチャ
#define CAT_TEXTURE			"data/TEXTURE/TitleCat.png"				// タイトルロゴ(ネコ)のテクスチャ
#define AND_TEXTURE			"data/TEXTURE/TitleAnd.png"				// タイトルロゴ(＆)のテクスチャ
#define RAT_POS				(D3DXVECTOR3(-250.0f, SCREEN_HEIGHT * 0.5f + 30.0f, 0.0f))		// ネズミの位置
#define CAT_POS				(D3DXVECTOR3(-400.0f, SCREEN_HEIGHT * 0.5f - 30.0f, 0.0f))		// ネコの位置
#define AND_POS				(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))	// ＆の位置
#define RAT_SIZE			(D3DXVECTOR3(150.0f, 60.0f, 0.0f))								// ネズミの位置
#define CAT_SIZE			(D3DXVECTOR3(240.0f, 60.0f, 0.0f))								// ネコの位置
#define AND_SIZE			(D3DXVECTOR3(50.0f, 50.0f, 0.0f))								// ＆の位置
#define MOVE_SPEED			(21.0f)			// 移動量の速度
#define CAT_APPEAR_RAT_POS	(500.0f)		// ネコが移動しだすネズミの位置
#define RAT_STOP_POS		(900.0f)		// ネズミの止まる位置
#define CAT_STOP_POS		()

//============================
// コンストラクタ
//============================
CTitleLogo::CTitleLogo() : CObject(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;	// 移動量
		m_aTitle[nCnt].pLogo = nullptr;			// タイトルのポリゴン
		m_aTitle[nCnt].bDisp = false;			// 表示状況
		m_aTitle[nCnt].bMove = false;			// 移動状況
	}

	m_state = STATE_ESCAPE;						// 状態
}

//============================
// デストラクタ
//============================
CTitleLogo::~CTitleLogo()
{

}

//============================
// 初期化処理
//============================
HRESULT CTitleLogo::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo == nullptr)
		{ // タイトルが NULL の場合

			// タイトルのロゴを生成する
			m_aTitle[nCnt].pLogo = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}

		// 全ての値を初期化する
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// 移動量
		m_aTitle[nCnt].bDisp = false;				// 表示状況
		m_aTitle[nCnt].bMove = false;				// 移動状況
	}

	m_state = STATE_ESCAPE;						// 状態

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CTitleLogo::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // タイトルのポリゴンが NULL じゃない場合

			// 終了処理
			m_aTitle[nCnt].pLogo->Uninit();
			m_aTitle[nCnt].pLogo = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//============================
// 更新処理
//============================
void CTitleLogo::Update(void)
{
	switch (CTitle::GetState())
	{
	case CTitle::STATE_TITLE_APPEAR:		// 出現状態

		// 逃走状態の処理
		EscapeProcess();

		break;

	case CTitle::STATE_WAIT:				// 待機状態

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	switch (m_state)
	{
	case STATE_ESCAPE:

		// 逃走状態の処理
		EscapeProcess();

		break;

	case STATE_WAIT:

		break;

	default:
		
		// 停止
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// 頂点座標の設定処理
		m_aTitle[nCnt].pLogo->SetVertexRot();
	}
}

//============================
// 描画処理
//============================
void CTitleLogo::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr &&
			m_aTitle[nCnt].bDisp == true)
		{ // タイトルが NULL じゃない場合

			// 描画処理
			m_aTitle[nCnt].pLogo->Draw();
		}
	}
}

//============================
// 情報の設定処理
//============================
void CTitleLogo::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // タイトルが NULL じゃない場合

			// 情報を設定する
			switch (nCnt)
			{
			case TYPE_RAT:		// ネズミ

				m_aTitle[nCnt].pLogo->SetPos(RAT_POS);		// 位置
				m_aTitle[nCnt].pLogo->SetPosOld(RAT_POS);	// 前回の位置
				m_aTitle[nCnt].pLogo->SetSize(RAT_SIZE);	// サイズ

				// テクスチャの設定処理
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

				// 情報を設定する
				m_aTitle[nCnt].move.x = MOVE_SPEED;			// 移動量
				m_aTitle[nCnt].bDisp = true;				// 表示状況
				m_aTitle[nCnt].bMove = true;				// 移動状況

				break;

			case TYPE_AND:		// アンド

				m_aTitle[nCnt].pLogo->SetPos(AND_POS);		// 位置
				m_aTitle[nCnt].pLogo->SetPosOld(AND_POS);	// 前回の位置
				m_aTitle[nCnt].pLogo->SetSize(AND_SIZE);	// サイズ

				// テクスチャの設定処理
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(AND_TEXTURE));

				// 情報を設定する
				m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// 移動量
				m_aTitle[nCnt].bDisp = false;				// 表示状況
				m_aTitle[nCnt].bMove = false;			// 移動状況

				break;

			case TYPE_CAT:		// ネコ

				m_aTitle[nCnt].pLogo->SetPos(CAT_POS);		// 位置
				m_aTitle[nCnt].pLogo->SetPosOld(CAT_POS);	// 前回の位置
				m_aTitle[nCnt].pLogo->SetSize(CAT_SIZE);	// サイズ

				// テクスチャの設定処理
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(CAT_TEXTURE));

				// 情報を設定する
				m_aTitle[nCnt].move.x = MOVE_SPEED;			// 移動量
				m_aTitle[nCnt].bDisp = true;				// 表示状況
				m_aTitle[nCnt].bMove = false;			// 移動状況

				break;
			}

			m_aTitle[nCnt].pLogo->SetRot(NONE_D3DXVECTOR3);	// 向き
			m_aTitle[nCnt].pLogo->SetAngle();				// 方向
			m_aTitle[nCnt].pLogo->SetLength();				// 長さ

			// 頂点座標の設定処理
			m_aTitle[nCnt].pLogo->SetVertexRot();
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}
	}

	m_state = STATE_ESCAPE;						// 状態
}

//============================
//生成処理
//============================
CTitleLogo* CTitleLogo::Create(void)
{
	// タイトルロゴのポインタを生成
	CTitleLogo* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pTitle = new CTitleLogo;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTitle->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTitle->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// タイトルロゴのポインタを返す
	return pTitle;
}

//============================
// 逃走状態の処理
//============================
void CTitleLogo::EscapeProcess(void)
{
	// 移動処理
	Move(TYPE::TYPE_RAT);		// ネズミ
	Move(TYPE::TYPE_CAT);		// ネコ

	// ネズミの位置の設定処理
	EscapeRatPosSet();

	// ネコの位置の設定処理
	EscapeCatPosSet();
}

//============================
// 移動処理
//============================
void CTitleLogo::Move(const TYPE type)
{
	if (m_aTitle[type].bMove == true)
	{ // 移動状況が true の場合

		// 位置を取得する
		D3DXVECTOR3 pos = m_aTitle[type].pLogo->GetPos();

		// 位置を加算する
		pos.x += m_aTitle[type].move.x;

		// 位置を適用する
		m_aTitle[type].pLogo->SetPos(pos);
	}
}

//============================
// 逃走状態のネズミの位置関係処理
//============================
void CTitleLogo::EscapeRatPosSet(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x >= CAT_APPEAR_RAT_POS)
	{ // ネズミの位置が一定位置を超えた場合

		// 移動状況を true にする
		m_aTitle[TYPE_CAT].bMove = true;
	}

	if (pos.x >= RAT_STOP_POS)
	{ // ネズミの位置が一定の位置に達した場合

		// ネズミの位置を補正する
		pos.x = RAT_STOP_POS;

		// 移動状況を false にする
		m_aTitle[TYPE_RAT].bMove = false;
	}

	// 位置を適用する
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// 逃走状態のネコの位置関係処理
//============================
void CTitleLogo::EscapeCatPosSet(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_CAT].pLogo->GetPos();

	if (pos.x >= RAT_STOP_POS)
	{ // ネコの位置が一定の位置に達した場合

		// ネコの位置を補正する
		pos.x = RAT_STOP_POS;

		// 移動状況を false にする
		m_aTitle[TYPE_CAT].bMove = false;

		// 待機状態にする
		m_state = STATE_WAIT;

		// タイトルを待機状態にする
		CTitle::SetState(CTitle::STATE_WAIT);
	}

	// 位置を適用する
	m_aTitle[TYPE_CAT].pLogo->SetPos(pos);
}