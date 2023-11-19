//=======================================
//
// エントリーUI処理[entry_UI.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_UI.h"
#include "texture.h"

#include "entry_frame.h"

//=======================================
// マクロ定義
//=======================================

//=========================
// コンストラクタ
//=========================
CEntryUI::CEntryUI() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pFrame = nullptr;			// 枠の情報
}

//=========================
// デストラクタ
//=========================
CEntryUI::~CEntryUI()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryUI::Init(void)
{
	// 全ての値をクリアする
	m_pFrame = nullptr;			// 枠の情報

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CEntryUI::Uninit(void)
{
	if (m_pFrame != nullptr)
	{ // 枠の情報が NULL じゃない場合

		// 枠の終了処理
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	// 本体の終了処理
	Release();
}

//=========================
// 更新処理
//=========================
void CEntryUI::Update(void)
{
	// 特になし
}

//=========================
// 描画処理
//=========================
void CEntryUI::Draw(void)
{
	// 描画するものがないため特に無し
}

//=========================
// 情報の設定処理
//=========================
void CEntryUI::SetData(const D3DXVECTOR3& pos)
{
	if (m_pFrame == nullptr)
	{ // 枠の情報が NULL の場合

		// 枠を生成する
		m_pFrame = CEntryFrame::Create(pos);
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}
}

//=========================
// 生成処理
//=========================
CEntryUI* CEntryUI::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CEntryUI* pEntry = nullptr;	// プレイヤーのインスタンスを生成

	if (pEntry == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntry = new CEntryUI;
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
		pEntry->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーUIのポインタを返す
	return pEntry;
}