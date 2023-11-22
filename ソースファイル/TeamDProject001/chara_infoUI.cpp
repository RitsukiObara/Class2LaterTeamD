//============================================
//
// キャラクターの情報UI処理[chara_infoUI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "chara_infoUI.h"
#include "texture.h"
#include "useful.h"

//========================
// コンストラクタ
//========================
CCharaInfoUI::CCharaInfoUI() : CObject(TYPE_CHARAINFO, PRIORITY_UI)
{

}

//========================
// デストラクタ
//========================
CCharaInfoUI::~CCharaInfoUI()
{

}

//========================
// 初期化処理
//========================
HRESULT CCharaInfoUI::Init(void)
{
	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CCharaInfoUI::Uninit(void)
{
	// 数字の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CCharaInfoUI::Update(void)
{

}

//========================
// 描画処理
//========================
void CCharaInfoUI::Draw(void)
{

}

//========================
// 情報の設定処理
//========================
void CCharaInfoUI::SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaImage::TYPE type)
{

}

//========================
// 生成処理
//========================
CCharaInfoUI* CCharaInfoUI::Create(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaImage::TYPE type)
{
	// ローカルオブジェクトを生成
	CCharaInfoUI* pInfoUI = nullptr;		// キャラクター情報UIのインスタンスを生成

	if (pInfoUI == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pInfoUI = new CCharaInfoUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pInfoUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pInfoUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pInfoUI->SetData(pos, nPlayerID, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// キャラクターの情報UIのポインタを返す
	return pInfoUI;
}