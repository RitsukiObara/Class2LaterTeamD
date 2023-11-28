//============================================
//
// エントリー画面のメイン処理[entry.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "entry.h"
#include "renderer.h"
#include "fade.h"
#include "Objectmesh.h"

#include "entry_UI.h"
#include "entry_team.h"
#include "input.h"
#include "player.h"

//=========================================
// コンストラクタ
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_nCatIdx = 0;					// ネコをやるプレイヤー
	for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
	{
		m_apUI[nCnt] = nullptr;		// エントリーUIの情報
	}
}

//=========================================
// デストラクタ
//=========================================
CEntry::~CEntry()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CEntry::Init(void)
{
	// 全ての値を初期化する
	m_nCatIdx = 0;					// ネコをやるプレイヤー

	//　シーンの初期化
	CScene::Init();

	// テキスト読み込み処理
	CMesh::TxtSet();

	for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
	{
		if (nCnt == m_nCatIdx)
		{ // ネコをやるプレイヤーのみ

			// エントリーUIの生成処理
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_CAT);
		}
		else
		{ // 上記以外

			// エントリーUIの生成処理
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_RAT);
		}
	}

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CEntry::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
	{
		if (m_apUI[nCnt] != nullptr)
		{ // エントリーUIの情報が NULL じゃない場合

			// エントリーUIの終了処理
			m_apUI[nCnt]->Uninit();
			m_apUI[nCnt] = nullptr;
		}
	}

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CEntry::Update(void)
{

// デバッグ版
#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // ENTERキーを押した場合

		// ゲームモードに遷移
		CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
	{ // 右キーを押した場合

		// ネコをやるプレイヤーを設定
		m_nCatIdx = (m_nCatIdx + 1) % MAX_ENTRY;

		for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
		{
			if (nCnt == m_nCatIdx)
			{ // ネコをやるプレイヤーのみ

				// ネコに設定する
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);
			}
			else
			{ // 上記以外

				// ネズミに設定する
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);
			}
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
	{ // 左キーを押した場合

		// ネコをやるプレイヤーを設定
		m_nCatIdx = (m_nCatIdx + MAX_ENTRY - 1) % MAX_ENTRY;

		for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
		{
			if (nCnt == m_nCatIdx)
			{ // ネコをやるプレイヤーのみ

				// ネコに設定する
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);
			}
			else
			{ // 上記以外

				// ネズミに設定する
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);
			}
		}
	}

	// レンダラーの更新
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//描画処理
//======================================
void CEntry::Draw(void)
{

}