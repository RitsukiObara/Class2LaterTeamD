//=======================================
//
// エントリーのマッチングUI処理[entry_match.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_match.h"
#include "manager.h"
#include "input.h"
#include "texture.h"

#include "match_frame.h"
#include "match_chara.h"

//=========================
// コンストラクタ
//=========================
CEntryMatch::CEntryMatch() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pFrame = nullptr;			// 枠の情報
	m_pChara = nullptr;			// キャラクター
}

//=========================
// デストラクタ
//=========================
CEntryMatch::~CEntryMatch()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryMatch::Init(void)
{
	// 全ての値をクリアする
	m_pFrame = nullptr;			// 枠の情報
	m_pChara = nullptr;			// キャラクター

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CEntryMatch::Uninit(void)
{
	if (m_pFrame != nullptr)
	{ // 枠の情報が NULL じゃない場合

		// 枠の終了処理
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pChara != nullptr)
	{ // キャラクターの情報が NULL じゃない場合

		// キャラクターの終了処理
		m_pChara->Uninit();
		m_pChara = nullptr;
	}

	// 本体の終了処理
	Release();
}

//=========================
// 更新処理
//=========================
void CEntryMatch::Update(void)
{
	if (m_pFrame != nullptr)
	{ // 枠の情報が NULL じゃない場合

		// 枠の更新処理
		m_pFrame->Update();
	}

	if (m_pChara != nullptr)
	{ // キャラクターの情報が NULL じゃない場合

		// キャラクターの更新処理
		m_pChara->Update();
	}
}

//=========================
// 描画処理
//=========================
void CEntryMatch::Draw(void)
{
	if (m_pFrame != nullptr)
	{ // 枠の情報が NULL じゃない場合

		// 枠の描画処理
		m_pFrame->Draw();
	}

	if (m_pChara != nullptr)
	{ // キャラクターの情報が NULL じゃない場合

		// キャラクターの描画処理
		m_pChara->Draw();
	}
}

//=========================
// 情報の設定処理
//=========================
void CEntryMatch::SetData(const D3DXVECTOR3& pos)
{
	if (m_pFrame == nullptr)
	{ // 枠の情報が NULL の場合

		// 枠を生成する
		m_pFrame = CMatchFrame::Create(pos);
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}

	if (m_pChara == nullptr)
	{ // キャラクターの情報が NULL の場合

		// 枠を生成する
		m_pChara = CMatchChara::Create(pos);
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
CEntryMatch* CEntryMatch::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CEntryMatch* pMatch = nullptr;	// プレイヤーのインスタンスを生成

	if (pMatch == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pMatch = new CEntryMatch;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pMatch != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pMatch->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pMatch->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーのマッチングのポインタを返す
	return pMatch;
}