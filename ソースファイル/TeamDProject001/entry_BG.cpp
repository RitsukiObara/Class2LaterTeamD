//=======================================
//
// エントリーの背景処理[entry_BG.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_BG.h"

#include "model.h"

//=========================
// コンストラクタ
//=========================
CEntryBG::CEntryBG() : CObject(CObject::TYPE_ENTRYBG, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;			// モデルの情報
	}
}

//=========================
// デストラクタ
//=========================
CEntryBG::~CEntryBG()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryBG::Init(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // モデルの情報が NULL の場合

			// モデルを生成する
			m_apModel[nCnt] = new CModel(TYPE_NONE, PRIORITY_BLOCK);
		}
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CEntryBG::Uninit(void)
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

//=========================
// 更新処理
//=========================
void CEntryBG::Update(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// モデルの更新処理
			m_apModel[nCnt]->Update();
		}
	}
}

//=========================
// 描画処理
//=========================
void CEntryBG::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// モデルの描画処理
			m_apModel[nCnt]->Draw();
		}
	}
}

//=========================
// 情報の設定処理
//=========================
void CEntryBG::SetData(void)
{

}

//=========================
// 生成処理
//=========================
CEntryBG* CEntryBG::Create(void)
{
	// ローカルオブジェクトを生成
	CEntryBG* pEntry = nullptr;		// エントリーの背景のインスタンスを生成

	if (pEntry == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntry = new CEntryBG;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntry != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntry->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntry->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーの背景のポインタを返す
	return pEntry;
}