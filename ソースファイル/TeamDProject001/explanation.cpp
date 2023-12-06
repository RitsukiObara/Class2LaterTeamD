//===========================================
//
// 説明のメイン処理[explanation.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "explanation.h"
#include "answer.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SET_SIDE		(200.0f)
#define CAT_KING_POS	(D3DXVECTOR3(-SET_SIDE,360.0f,0.0f))
#define CAT_KING_SIZE	(D3DXVECTOR3(100.0f,600.0f,0.0f))
#define CAT_BG_POS		(D3DXVECTOR3(-SET_SIDE,150.0f,0.0f))
#define CAT_BG_SIZE		(D3DXVECTOR3(300.0f,150.0f,0.0f))
#define CAT_TEXT_POS	(D3DXVECTOR3(-SET_SIDE,150.0f,0.0f))
#define CAT_TEXT_SIZE	(D3DXVECTOR3(250.0f,100.0f,0.0f))

#define RAT_KING_POS	(D3DXVECTOR3(1280.0f + SET_SIDE,400,0.0f))
#define RAT_KING_SIZE	(D3DXVECTOR3(100.0f,400.0f,0.0f))
#define RAT_BG_POS		(D3DXVECTOR3(1280.0f + SET_SIDE,500.0f,0.0f))
#define RAT_BG_SIZE		(D3DXVECTOR3(300.0f,150.0f,0.0f))
#define RAT_TEXT_POS	(D3DXVECTOR3(1280.0f + SET_SIDE,500.0f,0.0f))
#define RAT_TEXT_SIZE	(D3DXVECTOR3(250.0f,100.0f,0.0f))

#define CAT_KING_STOP	(150.0f)
#define CAT_BG_STOP		(500.0f)
#define CAT_TEXT_STOP	(500.0f)
#define RAT_KING_STOP	(1280.0f - 150.0f)
#define RAT_BG_STOP		(1280.0f - 500.0f)
#define RAT_TEXT_STOP	(1280.0f - 500.0f)

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CExplanation::CExplanation() : CObject/*親クラス*/(/*ここにタイプを入れる*/CObject::TYPE_2DUI, /*ここに優先順位を入れる*/CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_pBG = NULL;
	m_pCatKing = NULL;
	m_pCatBG = NULL;
	m_pCatText = NULL;
	m_pRatKing = NULL;
	m_pRatBG = NULL;
	m_pRatText = NULL;
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_apImage[nCnt] = NULL;
	}
}

//==============================
// デストラクタ
//==============================
CExplanation::~CExplanation()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CExplanation::Init(void)
{
	//if (FAILED(親クラス::Init()))
	//{ // 初期化処理に失敗した場合

	//	// 失敗を返す
	//	return E_FAIL;
	//}

	// 全ての値を初期化する

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CExplanation::Uninit(void)
{
	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}
	if (m_pCatKing != NULL)
	{
		m_pCatKing->Uninit();
		m_pCatKing = NULL;
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Uninit();
		m_pCatBG = NULL;
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Uninit();
		m_pCatText = NULL;
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Uninit();
		m_pRatKing = NULL;
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Uninit();
		m_pRatBG = NULL;
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Uninit();
		m_pRatText = NULL;
	}
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Uninit();
			m_apImage[nCnt] = NULL;
		}
	}

	Release();
}

//=====================================
// 破片の更新処理
//=====================================
void CExplanation::Update(void)
{
	if (m_pCatKing != NULL)
	{
		m_pCatKing->Update();

		D3DXVECTOR3 pos = m_pCatKing->GetPos();
		pos.x += 2.0f;

		if (pos.x > CAT_KING_STOP)
		{
			pos.x = CAT_KING_STOP;
		}

		m_pCatKing->SetPos(pos);
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Update();

		D3DXVECTOR3 pos = m_pCatBG->GetPos();
		pos.x += 2.0f;

		if (pos.x > CAT_BG_STOP)
		{
			pos.x = CAT_BG_STOP;
		}

		m_pCatBG->SetPos(pos);
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Update();

		D3DXVECTOR3 pos = m_pCatText->GetPos();
		pos.x += 2.0f;

		if (pos.x > CAT_TEXT_STOP)
		{
			pos.x = CAT_TEXT_STOP;
		}

		m_pCatText->SetPos(pos);
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Update();

		D3DXVECTOR3 pos = m_pRatKing->GetPos();
		pos.x -= 2.0f;

		if (pos.x < RAT_KING_STOP)
		{
			pos.x = RAT_KING_STOP;
		}

		m_pRatKing->SetPos(pos);
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Update();

		D3DXVECTOR3 pos = m_pRatBG->GetPos();
		pos.x -= 2.0f;

		if (pos.x < RAT_BG_STOP)
		{
			pos.x = RAT_BG_STOP;
		}

		m_pRatBG->SetPos(pos);
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Update();

		D3DXVECTOR3 pos = m_pRatText->GetPos();
		pos.x -= 2.0f;

		if (pos.x < RAT_TEXT_STOP)
		{
			pos.x = RAT_TEXT_STOP;
		}

		m_pRatText->SetPos(pos);
	}
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Update();
		}
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CExplanation::Draw(void)
{
	if (m_pBG != NULL)
	{
		m_pBG->Draw();
	}
	if (m_pCatKing != NULL)
	{
		m_pCatKing->Draw();
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Draw();
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Draw();
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Draw();
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Draw();
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Draw();
	}
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CExplanation::SetData(CTutorial::TUTORIAL Tutorial)
{
	if (m_pBG == NULL)
	{
		m_pBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pBG->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// 位置
		m_pBG->SetPosOld(D3DXVECTOR3(640.0f, 360.0f, 0.0f));// 前回の位置
		m_pBG->SetRot(NONE_D3DXVECTOR3);					// 向き
		m_pBG->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// サイズ
		m_pBG->SetLength();									// 長さ
		m_pBG->SetAngle();									// 方向
		m_pBG->SetVtxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));	// 色

		// 頂点座標の設定処理
		m_pBG->SetVertex();

	}
	if (m_pCatKing == NULL)
	{
		m_pCatKing = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pCatKing->SetPos(CAT_KING_POS);			// 位置
		m_pCatKing->SetPosOld(CAT_KING_POS);		// 前回の位置
		m_pCatKing->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pCatKing->SetSize(CAT_KING_SIZE);			// サイズ
		m_pCatKing->SetLength();					// 長さ
		m_pCatKing->SetAngle();						// 方向
		m_pCatKing->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\image.png"));		// テクスチャの割り当て処理
		
		// 頂点座標の設定処理
		m_pCatKing->SetVertex();

	}
	if (m_pCatBG == NULL)
	{
		m_pCatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pCatBG->SetPos(CAT_BG_POS);				// 位置
		m_pCatBG->SetPosOld(CAT_BG_POS);			// 前回の位置
		m_pCatBG->SetRot(NONE_D3DXVECTOR3);			// 向き
		m_pCatBG->SetSize(CAT_BG_SIZE);				// サイズ
		m_pCatBG->SetLength();						// 長さ
		m_pCatBG->SetAngle();						// 方向
		m_pCatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\image.png"));		// テクスチャの割り当て処理

		// 頂点座標の設定処理
		m_pCatBG->SetVertex();
	}
	if (m_pCatText == NULL)
	{
		m_pCatText = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pCatText->SetPos(CAT_TEXT_POS);			// 位置
		m_pCatText->SetPosOld(CAT_TEXT_POS);		// 前回の位置
		m_pCatText->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pCatText->SetSize(CAT_TEXT_SIZE);			// サイズ
		m_pCatText->SetLength();					// 長さ
		m_pCatText->SetAngle();						// 方向
		m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\image.png"));		// テクスチャの割り当て処理

		// 頂点座標の設定処理
		m_pCatText->SetVertex();
	}
	if (m_pRatKing == NULL)
	{
		m_pRatKing = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pRatKing->SetPos(RAT_KING_POS);			// 位置
		m_pRatKing->SetPosOld(RAT_KING_POS);		// 前回の位置
		m_pRatKing->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pRatKing->SetSize(RAT_KING_SIZE);			// サイズ
		m_pRatKing->SetLength();					// 長さ
		m_pRatKing->SetAngle();						// 方向
		m_pRatKing->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\image.png"));		// テクスチャの割り当て処理

		// 頂点座標の設定処理
		m_pRatKing->SetVertex();
	}
	if (m_pRatBG == NULL)
	{
		m_pRatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pRatBG->SetPos(RAT_BG_POS);				// 位置
		m_pRatBG->SetPosOld(RAT_BG_POS);			// 前回の位置
		m_pRatBG->SetRot(NONE_D3DXVECTOR3);			// 向き
		m_pRatBG->SetSize(RAT_BG_SIZE);				// サイズ
		m_pRatBG->SetLength();						// 長さ
		m_pRatBG->SetAngle();						// 方向
		m_pRatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\image.png"));		// テクスチャの割り当て処理

		// 頂点座標の設定処理
		m_pRatBG->SetVertex();
	}
	if (m_pRatText == NULL)
	{
		m_pRatText = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pRatText->SetPos(RAT_TEXT_POS);			// 位置
		m_pRatText->SetPosOld(RAT_TEXT_POS);		// 前回の位置
		m_pRatText->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pRatText->SetSize(RAT_TEXT_SIZE);			// サイズ
		m_pRatText->SetLength();					// 長さ
		m_pRatText->SetAngle();						// 方向
		m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\image.png"));		// テクスチャの割り当て処理

		// 頂点座標の設定処理
		m_pRatText->SetVertex();
	}

	switch (Tutorial)
	{
	case CTutorial::TUTORIAL_MOVE:
		break;
	case CTutorial::TUTORIAL_ATTACK_JAMP:
		break;
	case CTutorial::TUTORIAL_CAT_KILL:
		break;
	case CTutorial::TUTORIAL_RAT_RESCUE:
		break;
	case CTutorial::TUTORIAL_ACTION:
		break;
	case CTutorial::TUTORIAL_ITEM_MULTI:
		break;
	case CTutorial::TUTORIAL_GIMMICK:
		break;
	case CTutorial::TUTORIAL_LETS_GO:
		break;
	default:
		break;
	}

	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う
	// 情報の設定処理

	//==========================================================================
	// 2Dポリゴン
	//==========================================================================
	//SetPos(位置を入れる);			// 位置
	//SetPosOld(位置を入れる);		// 前回の位置
	//SetRot(向きを入れる);			// 向き
	//SetSize(サイズを入れる);		// サイズ
	//SetLength(引数無し);			// 長さ
	//SetAngle(引数無し);			// 方向
	//BindTexture(CManager::Get()->GetTexture()->Regist(テクスチャの名前));		// テクスチャの割り当て処理

	//// 頂点座標の設定処理
	//SetVertex();

	//==========================================================================
	// 3Dポリゴン
	//==========================================================================
	//SetPos(位置を入れる);			// 位置
	//SetPosOld(位置を入れる);		// 前回の位置
	//SetRot(向きを入れる);			// 向き
	//SetSize(サイズを入れる);		// サイズ
	//BindTexture(CManager::Get()->GetTexture()->Regist(テクスチャの名前));		// テクスチャの割り当て処理

	//// 頂点座標の設定処理
	//SetVertex();

	//==========================================================================
	// ビルボード
	//==========================================================================
	//SetPos(位置を入れる);			// 位置
	//SetPosOld(位置を入れる);		// 前回の位置
	//SetSize(サイズを入れる);		// サイズ
	//BindTexture(CManager::Get()->GetTexture()->Regist(テクスチャの名前));		// テクスチャの割り当て処理

	//// 頂点座標の設定処理
	//SetVertex();

	//==========================================================================
	// アニメーション系
	//==========================================================================
	//SetPos(位置を入れる);			// 位置
	//SetPosOld(位置を入れる);		// 前回の位置
	//SetRot(向きを入れる);			// 向き
	//SetSize(サイズを入れる);		// サイズ
	//SetLength(引数無し);			// 長さ
	//SetAngle(引数無し);			// 方向
	//BindTexture(CManager::Get()->GetTexture()->Regist(テクスチャの名前));		// テクスチャの割り当て処理

	// アニメーションの設定処理
	//SetAnim(カウントを入れる, パターン数を入れる);

	//// 頂点座標の設定処理
	//SetVertex();

	// テクスチャの設定(アニメーションバージョン)
	//SetVtxTextureAnim(アニメーションの総パターン数を入れる, 0);

	//==========================================================================
	// モデル
	//==========================================================================
	//SetPos(位置を入れる);					// 位置
	//SetPosOld(位置を入れる);				// 前回の位置
	//SetRot(向きを入れる);					// 向き
	//SetScale(拡大率を入れる);				// 拡大率
	//SetFileData(モデルの種類を入れる);	// モデルの情報
}

//=======================================
// 生成処理
//=======================================
CExplanation* CExplanation::Create(CTutorial::TUTORIAL Tutorial)
{
	// ローカルオブジェクトを生成
	CExplanation* pSample = nullptr;	// 返事入力のリアクションのインスタンスを生成

	if (pSample == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pSample = new CExplanation;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pSample != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pSample->Init()))
		{ // 初期化に失敗した場合

		  // 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSample->SetData(Tutorial);
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 返事入力のリアクションのポインタを返す
	return pSample;
}