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
#include "match_vs.h"
#include "match_select.h"

//---------------------------------------
// マクロ定義
//---------------------------------------
#define MATCH_SHIFT_HEIGHT		(-50.0f)		// エントリーのずらす高さ

//=========================
// コンストラクタ
//=========================
CEntryMatch::CEntryMatch() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pFrame = nullptr;			// 枠の情報
	m_pChara = nullptr;			// キャラクター
	m_pVS = nullptr;			// VSマーク
	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		m_apSelect[nCnt] = nullptr;	// 選択肢
	}
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
	m_pVS = nullptr;			// VSマーク
	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		m_apSelect[nCnt] = nullptr;	// 選択肢
	}

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

	if (m_pVS != nullptr)
	{ // VSマークの情報が NULL じゃない場合

		// VSマークの終了処理
		m_pVS->Uninit();
		m_pVS = nullptr;
	}

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] != nullptr)
		{ // 選択肢の情報が NULL じゃない場合

			// 選択肢の終了処理
			m_apSelect[nCnt]->Uninit();
			m_apSelect[nCnt] = nullptr;
		}
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

	if (m_pVS != nullptr)
	{ // VSマークの情報が NULL じゃない場合

		// VSマークの更新処理
		m_pVS->Update();
	}

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] != nullptr)
		{ // 選択肢の情報が NULL じゃない場合

			// 選択肢の更新処理
			m_apSelect[nCnt]->Update();
		}
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

	if (m_pVS != nullptr)
	{ // VSマークの情報が NULL じゃない場合

		// VSマークの描画処理
		m_pVS->Draw();
	}

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] != nullptr)
		{ // 選択肢の情報が NULL じゃない場合

			// 選択肢の描画処理
			m_apSelect[nCnt]->Draw();
		}
	}
}

//=========================
// 情報の設定処理
//=========================
void CEntryMatch::SetData(const D3DXVECTOR3& pos, const int nID)
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
		m_pChara = CMatchChara::Create(D3DXVECTOR3(pos.x, pos.y + MATCH_SHIFT_HEIGHT, pos.z));
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}

	if (m_pVS == nullptr)
	{ // キャラクターの情報が NULL の場合

		// 枠を生成する
		m_pVS = CMatchVS::Create(D3DXVECTOR3(pos.x, pos.y, pos.z));
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}

	// 設定用のカウント変数
	int nCntSet = 0;

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] == nullptr)
		{ // 選択肢の情報が NULL の場合

			if (nID == nCnt)
			{ // インデックスじゃなかった場合

				// IDを生成する
				m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x - 80.0f, pos.y + 30.0f, pos.z), nCnt);
			}
			else
			{ // 上記以外

				switch (nCntSet)
				{
				case 0:

					// IDを生成する
					m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x + 30.0f, pos.y + 50.0f, pos.z), nCnt);

					break;

				case 1:

					// IDを生成する
					m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x + 70.0f, pos.y + 10.0f, pos.z), nCnt);

					break;

				case 2:

					// IDを生成する
					m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x + 110.0f, pos.y + 50.0f, pos.z), nCnt);

					break;
				}

				nCntSet++;
			}
		}
	}
}

//=========================
// 生成処理
//=========================
CEntryMatch* CEntryMatch::Create(const D3DXVECTOR3& pos, const int nID)
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
		pMatch->SetData(pos, nID);
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