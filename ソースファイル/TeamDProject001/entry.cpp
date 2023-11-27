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
#include "entry_match.h"
#include "input.h"

//=========================================
// コンストラクタ
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{

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
	//　シーンの初期化
	CScene::Init();

	// テキスト読み込み処理
	CMesh::TxtSet();

	// エントリーUIの生成処理
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 375.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 0);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 125.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 1);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 125.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 2);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 375.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 3);

	// マッチングUIの生成処理
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 450.0f, SCREEN_HEIGHT * 0.1f, 0.0f));
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 150.0f, SCREEN_HEIGHT * 0.1f, 0.0f));
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 150.0f, SCREEN_HEIGHT * 0.1f, 0.0f));
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 450.0f, SCREEN_HEIGHT * 0.1f, 0.0f));

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CEntry::Uninit(void)
{
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


	// レンダラーの更新
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//描画処理
//======================================
void CEntry::Draw(void)
{

}