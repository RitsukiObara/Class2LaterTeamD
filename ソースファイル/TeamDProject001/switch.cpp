//===========================================
//
// ネズミ捕りの鉄部分のメイン処理[mousetrap_iron.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "switch.h"
#include "model.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CSwitch::CSwitch() : CObject(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// モデルの情報
	}
	m_bMove = false;					// 移動状況
	m_bBoot = false;					// 起動状況
}

//==============================
// デストラクタ
//==============================
CSwitch::~CSwitch()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CSwitch::Init(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // モデルの情報が NULL の場合

			// モデルの生成処理
			m_apModel[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);
		}
	}
	m_bMove = false;					// 移動状況
	m_bBoot = false;					// 起動状況

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CSwitch::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// モデルの終了処理
			m_apModel[nCnt]->Uninit();
			m_apModel[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//=====================================
// 破片の更新処理
//=====================================
void CSwitch::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CSwitch::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルが NULL じゃない場合

			// モデルの描画処理
			m_apModel[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CSwitch::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// 全ての値を設定する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルが NULL じゃない場合

			// 情報の設定処理
			m_apModel[nCnt]->SetPos(pos);							// 位置
			m_apModel[nCnt]->SetPosOld(pos);						// 前回の位置
			m_apModel[nCnt]->SetRot(rot);							// 向き
			m_apModel[nCnt]->SetScale(NONE_SCALE);					// 拡大率
			m_apModel[nCnt]->SetFileData(CXFile::TYPE_TRAPIRON);	// モデル情報
		}
	}
	m_bMove = false;					// 移動状況
	m_bBoot = false;					// 起動状況
}

//=======================================
// 生成処理
//=======================================
CSwitch* CSwitch::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{ // オブジェクトが NULL の場合

		// スイッチを生成
		pSwitch = new CSwitch;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pSwitch != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pSwitch->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSwitch->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// スイッチのポインタを返す
	return pSwitch;
}

//=======================================
// モデルの取得処理
//=======================================
CModel* CSwitch::GetModel(const TYPE type)
{
	// モデルの情報を返す
	return m_apModel[type];
}

//=======================================
// 起動状況の設定処理
//=======================================
void CSwitch::SetBoot(const bool bBoot)
{
	// 起動状況を設定する
	m_bBoot = bBoot;
}

//=======================================
// 起動状況の取得処理
//=======================================
bool CSwitch::GetBoot(void) const
{
	// 起動状況を返す
	return m_bBoot;
}