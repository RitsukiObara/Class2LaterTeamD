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
#include "item_frame.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define FRAME_POS_SHIFT_BACK	(D3DXVECTOR3(-40.0f, 20.0f,0.0f))		// 後ろの枠の位置のずらす幅
#define FRAME_SIZE_FRONT		(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// 前の枠のサイズ
#define FRAME_SIZE_BACK			(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// 後ろの枠のサイズ
#define ITEM_MARK_SHIFT			(D3DXVECTOR3(0.0f, -5.0f, 0.0f))		// マークのずらす幅

//========================
// コンストラクタ
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		m_aItemUI[nCnt].m_pMark = nullptr;		// マークの情報
		m_aItemUI[nCnt].m_pFrame = nullptr;		// 枠の情報
	}
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
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		m_aItemUI[nCnt].m_pMark = nullptr;		// マークの情報
		m_aItemUI[nCnt].m_pFrame = nullptr;		// 枠の情報
	}

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CItemUI::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].m_pMark != nullptr)
		{ // マークが NULL じゃない場合

			// マークの終了処理
			m_aItemUI[nCnt].m_pMark->Uninit();
			m_aItemUI[nCnt].m_pMark = nullptr;
		}

		if (m_aItemUI[nCnt].m_pFrame != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の終了処理
			m_aItemUI[nCnt].m_pFrame->Uninit();
			m_aItemUI[nCnt].m_pFrame = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CItemUI::Update(void)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].m_pFrame != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の更新処理
			m_aItemUI[nCnt].m_pFrame->Update();
		}

		if (m_aItemUI[nCnt].m_pMark != nullptr)
		{ // マークが NULL じゃない場合

			// マークの更新処理
			m_aItemUI[nCnt].m_pMark->Update();
		}
	}
}

//========================
// 描画処理
//========================
void CItemUI::Draw(void)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].m_pFrame != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の描画処理
			m_aItemUI[nCnt].m_pFrame->Draw();
		}

		if (m_aItemUI[nCnt].m_pMark != nullptr)
		{ // マークが NULL じゃない場合

			// マークの描画処理
			m_aItemUI[nCnt].m_pMark->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CItemUI::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		switch (nCnt)
		{
		case ORDER_BACK:		// 後ろ

			// 枠を生成する
			m_aItemUI[nCnt].m_pFrame = CItemFrame::Create(pos + FRAME_POS_SHIFT_BACK, FRAME_SIZE_BACK, CPlayer::TYPE::TYPE_CAT);

			break;

		case ORDER_FRONT:		// 前

			// 枠を生成する
			m_aItemUI[nCnt].m_pFrame = CItemFrame::Create(pos, FRAME_SIZE_FRONT, CPlayer::TYPE::TYPE_CAT);

			break;

		default:

			// 停止
			assert(false);

			break;
		}
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

//========================
// マークの生成処理
//========================
void CItemUI::SetMark(const CItem::TYPE type)
{

}