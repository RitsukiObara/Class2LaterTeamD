//============================================
//
// アイテムUI処理[itemUI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "itemUI.h"
#include "texture.h"
#include "useful.h"

#include "item_mark.h"
#include "item_magni.h"
#include "item_frame.h"

//========================
// コンストラクタ
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// 全ての値をクリアする
	m_pMark = nullptr;		// マークの情報
	m_pMagni = nullptr;		// 所持数の情報
	m_pFrame = nullptr;		// 枠の情報
}

//========================
// デストラクタ
//========================
CItemUI::~CItemUI()
{

}

//========================
// 初期化処理
//========================
HRESULT CItemUI::Init(void)
{
	// 全ての値を初期化する
	m_pMark = nullptr;		// マークの情報
	m_pMagni = nullptr;		// 所持数の情報
	m_pFrame = nullptr;		// 枠の情報

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CItemUI::Uninit(void)
{
	if (m_pMark != nullptr)
	{ // マークが NULL じゃない場合

		// マークの終了処理
		m_pMark->Uninit();
		m_pMark = nullptr;
	}

	if (m_pMagni != nullptr)
	{ // 倍率が NULL じゃない場合

		// 倍率の終了処理
		m_pMagni->Uninit();
		m_pMagni = nullptr;
	}

	if (m_pFrame != nullptr)
	{ // 枠が NULL じゃない場合

		// 枠の終了処理
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	// 本体の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CItemUI::Update(void)
{
	if (m_pFrame != nullptr)
	{ // 枠が NULL じゃない場合

		// 枠の更新処理
		m_pFrame->Update();
	}

	if (m_pMark != nullptr)
	{ // マークが NULL じゃない場合

		// マークの更新処理
		m_pMark->Update();
	}

	if (m_pMagni != nullptr)
	{ // 倍率が NULL じゃない場合

		// 倍率の更新処理
		m_pMagni->Update();
	}
}

//========================
// 描画処理
//========================
void CItemUI::Draw(void)
{
	if (m_pFrame != nullptr)
	{ // 枠が NULL じゃない場合

		// 枠の描画処理
		m_pFrame->Draw();
	}

	if (m_pMark != nullptr)
	{ // マークが NULL じゃない場合

		// マークの描画処理
		m_pMark->Draw();
	}

	if (m_pMagni != nullptr)
	{ // 倍率が NULL じゃない場合

		// 倍率の描画処理
		m_pMagni->Draw();
	}
}

//========================
// 情報の設定処理
//========================
void CItemUI::SetData(const D3DXVECTOR3& pos)
{
	if (m_pFrame == nullptr)
	{ // 枠が NULL の場合

		// 枠を生成する
		m_pFrame = CItemFrame::Create(pos, CPlayer::TYPE_CAT);
	}
}

//========================
// 生成処理
//========================
CItemUI* CItemUI::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CItemUI* pItemUI = nullptr;		// キャラクター情報UIのインスタンスを生成

	if (pItemUI == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pItemUI = new CItemUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pItemUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pItemUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pItemUI->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// アイテムUIのポインタを返す
	return pItemUI;
}