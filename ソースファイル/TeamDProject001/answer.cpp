//===========================================
//
// 返事入力のリアクションのメイン処理[sample.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "answer.h"
#include "object2D.h"
#include "texture.h"
#include "input.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CAnswer::CAnswer() : CObject/*親クラス*/(/*ここにタイプを入れる*/CObject::TYPE_2DUI, /*ここに優先順位を入れる*/CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_apAnswer[nCnt] = NULL;
		m_abPressAnswer[nCnt] = false;
		m_apPlayerID[nCnt] = NULL;
	}
}

//==============================
// デストラクタ
//==============================
CAnswer::~CAnswer()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CAnswer::Init(void)
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
void CAnswer::Uninit(void)
{
	//// 終了処理
	//親クラス::Uninit();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apAnswer[nCnt] != NULL)
		{
			m_apAnswer[nCnt]->Uninit();
			m_apAnswer[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayerID[nCnt] != NULL)
		{
			m_apPlayerID[nCnt]->Uninit();
			m_apPlayerID[nCnt] = NULL;
		}
	}

	Release();
}

//=====================================
// 破片の更新処理
//=====================================
void CAnswer::Update(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
		{
			m_abPressAnswer[nCnt] = true;
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apAnswer[nCnt] != NULL)
		{
			if (m_abPressAnswer[nCnt] == true)
			{
				m_apAnswer[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\use_check.png"));		// テクスチャの割り当て処理
			}

			m_apAnswer[nCnt]->Update();
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayerID[nCnt] != NULL)
		{
			m_apPlayerID[nCnt]->Update();
		}
	}

	if (m_abPressAnswer[0] == true &&
		m_abPressAnswer[1] == true &&
		m_abPressAnswer[2] == true &&
		m_abPressAnswer[3] == true)
	{
		CTutorial::PlayTrue();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CAnswer::Draw(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apAnswer[nCnt] != NULL)
		{
			m_apAnswer[nCnt]->Draw();
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayerID[nCnt] != NULL)
		{
			m_apPlayerID[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CAnswer::SetData(void)
{
	if (CTutorial::GetPlay() == true)
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apAnswer[nCnt] == NULL)
			{
				m_apAnswer[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
				m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(100.0f, 100.0f, 0.0f));		// 位置
				m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(100.0f, 100.0f, 0.0f));		// 前回の位置
				m_apAnswer[nCnt]->SetRot(NONE_D3DXVECTOR3);							// 向き
				m_apAnswer[nCnt]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));		// サイズ
				m_apAnswer[nCnt]->SetLength();										// 長さ
				m_apAnswer[nCnt]->SetAngle();										// 方向
				m_apAnswer[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\no_check.png"));		// テクスチャの割り当て処理

				// 頂点座標の設定処理
				m_apAnswer[nCnt]->SetVertex();
			}
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apAnswer[nCnt] == NULL)
			{
				m_apAnswer[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
				m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(200.0f + 200.0f * nCnt, 550.0f, 0.0f));		// 位置
				m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(200.0f + 200.0f * nCnt, 550.0f, 0.0f));		// 前回の位置
				m_apAnswer[nCnt]->SetRot(NONE_D3DXVECTOR3);							// 向き
				m_apAnswer[nCnt]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));		// サイズ
				m_apAnswer[nCnt]->SetLength();										// 長さ
				m_apAnswer[nCnt]->SetAngle();										// 方向
				m_apAnswer[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\no_check.png"));		// テクスチャの割り当て処理

																																	// 頂点座標の設定処理
				m_apAnswer[nCnt]->SetVertex();
			}
		}

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayerID[nCnt] == NULL)
			{
				m_apPlayerID[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
				m_apPlayerID[nCnt]->SetPos(D3DXVECTOR3(200.0f + 200.0f * nCnt, 500.0f, 0.0f));		// 位置
				m_apPlayerID[nCnt]->SetPosOld(D3DXVECTOR3(200.0f + 200.0f * nCnt, 500.0f, 0.0f));	// 前回の位置
				m_apPlayerID[nCnt]->SetRot(NONE_D3DXVECTOR3);						// 向き
				m_apPlayerID[nCnt]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));		// サイズ
				m_apPlayerID[nCnt]->SetLength();									// 長さ
				m_apPlayerID[nCnt]->SetAngle();										// 方向

				switch (nCnt)
				{
				case 0:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_1P.png"));		// テクスチャの割り当て処理
					break;
				case 1:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_2P.png"));		// テクスチャの割り当て処理
					break;
				case 2:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_3P.png"));		// テクスチャの割り当て処理
					break;
				case 3:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_4P.png"));		// テクスチャの割り当て処理
					break;
				default:
					break;
				}

				// 頂点座標の設定処理
				m_apPlayerID[nCnt]->SetVertex();
			}
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_abPressAnswer[nCnt] = false;
	}
}

//=======================================
// 生成処理
//=======================================
CAnswer* CAnswer::Create(void)
{
	// ローカルオブジェクトを生成
	CAnswer* pSample = nullptr;	// 返事入力のリアクションのインスタンスを生成

	if (pSample == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pSample = new CAnswer;
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
		pSample->SetData();
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