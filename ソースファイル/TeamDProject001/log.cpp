//===========================================
//
// ログのメイン処理[log.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "log.h"
#include "object2D.h"
#include "texture.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CLog::CLog() : CObject(CObject::TYPE_2DUI, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	LogPos = NONE_D3DXVECTOR3;
	m_nPlayerNumber = -1;
	m_CreateNumber = -1;
	m_pLogBG = NULL;
	m_pLogPlayerID = NULL;
	m_pLogMessage = NULL;
}

//==============================
// デストラクタ
//==============================
CLog::~CLog()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CLog::Init(void)
{
	// 全ての値を初期化する

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CLog::Uninit(void)
{
	// 終了処理
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Uninit();
		m_pLogBG = NULL;
	}
	if (m_pLogPlayerID != NULL)
	{
		m_pLogPlayerID->Uninit();
		m_pLogPlayerID = NULL;
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Uninit();
		m_pLogMessage = NULL;
	}
}

//=====================================
// 破片の更新処理
//=====================================
void CLog::Update(void)
{
	// 描画処理
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Update();
	}
	if (m_pLogPlayerID != NULL)
	{
		m_pLogPlayerID->Update();
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Update();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CLog::Draw(void)
{
	// 描画処理
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Draw();
	}
	if (m_pLogPlayerID != NULL)
	{
		m_pLogPlayerID->Draw();
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CLog::SetData(int nIdex, int nCreateNumber)
{
	m_nPlayerNumber = nIdex;
	m_CreateNumber = nCreateNumber;

	switch (m_nPlayerNumber)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:

		// 明らかにエラーでごわす
		assert(false);

		break;
	}

	LogPos = D3DXVECTOR3(100.0f, 200.0f, 0.0f);

	if (m_pLogBG == NULL)
	{
		m_pLogBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogBG->SetPos(D3DXVECTOR3(LogPos.x, LogPos.y, 0.0f));
		m_pLogBG->SetPosOld(LogPos);
		m_pLogBG->SetRot(NONE_D3DXVECTOR3);
		m_pLogBG->SetSize(D3DXVECTOR3(100.0f, 50.0f, 0.0f));
		m_pLogBG->SetLength();
		m_pLogBG->SetAngle();
		m_pLogBG->SetVertex();
		m_pLogBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\CageWall.png"));
	}
	if (m_pLogPlayerID == NULL)
	{
		m_pLogPlayerID = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogPlayerID->SetPos(D3DXVECTOR3(LogPos.x - 40.0f, LogPos.y, 0.0f));
		m_pLogPlayerID->SetPosOld(LogPos);
		m_pLogPlayerID->SetRot(NONE_D3DXVECTOR3);
		m_pLogPlayerID->SetSize(D3DXVECTOR3(40.0f, 30.0f, 0.0f));
		m_pLogPlayerID->SetVtxTextureAnim(0.25f, nIdex);
		m_pLogPlayerID->SetLength();
		m_pLogPlayerID->SetAngle();
		m_pLogPlayerID->SetVertex();
		m_pLogPlayerID->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID.png"));
	}
	if (m_pLogMessage == NULL)
	{
		m_pLogMessage = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogMessage->SetPos(D3DXVECTOR3(LogPos.x + 40.0f, LogPos.y, 0.0f));
		m_pLogMessage->SetPosOld(LogPos);
		m_pLogMessage->SetRot(NONE_D3DXVECTOR3);
		m_pLogMessage->SetSize(D3DXVECTOR3(40.0f, 30.0f, 0.0f));
		m_pLogMessage->SetLength();
		m_pLogMessage->SetAngle();
		m_pLogMessage->SetVertex();
		m_pLogMessage->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\CageWall.png"));
	}
}

//=======================================
// 生成処理
//=======================================
CLog* CLog::Create(int nIdex, int nCreateNumber)
{
	// ローカルオブジェクトを生成
	CLog* pSample = nullptr;	// サンプルのインスタンスを生成

	if (pSample == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pSample = new CLog;
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
		pSample->SetData(nIdex, nCreateNumber);
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pSample;
}