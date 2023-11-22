//============================================
//
// マネージャーのメイン処理[manager.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "renderer.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "Objectmesh.h"

#include "file.h"
#include "camera.h"
#include "skybox.h"
#include "game.h"
#include "result_letter.h"
#include "objectElevation.h"
#include "rat.h"
#include "Cat.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CRat* CResult::m_apRat[MAX_RAT] = {};							// ネズミの情報
int CResult::m_nGameState = 0;			// ゲームの情報

//=========================================
// コンストラクタ
//=========================================
CResult::CResult() : CScene(TYPE_SCENE, PRIORITY_BG)
{

}

//=========================================
// デストラクタ
//=========================================
CResult::~CResult()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CResult::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// スカイボックスの生成処理
	CSkyBox::Create();

	// テキスト読み込み処理
	CMesh::TxtSet();

	// テキスト読み込み処理
	CElevation::TxtSet();

	// ゲームの状態を取得する
	m_nGameState = CGame::GetState();

	// 3Dテキスト生成
	if (m_nGameState == CGame::STATE_CAT_WIN)
	{ // ネコが勝ったら

		CResultLetter::Create(D3DXVECTOR3(0.0f, 300.0f, 0.0f), CXFile::TYPE_WINCAT_TEXT);		// ねこのかち

	}
	else if (m_nGameState == CGame::STATE_RAT_WIN)
	{ // ネズミが勝ったら

		CResultLetter::Create(D3DXVECTOR3(0.0f, 300.0f, 0.0f), CXFile::TYPE_WINRAT_TEXT);		// ねずみのかち

	}

	// ネズミの生成
	for (int nCntRat = 0; nCntRat < MAX_RAT; nCntRat++)
	{
		m_apRat[nCntRat] = CRat::Create(D3DXVECTOR3(200.0f * nCntRat, 0.0f, 0.0f), nCntRat);
	}

	//猫の生成
	CCat::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f));

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CResult::Uninit(void)
{
	// 破棄処理
	Release();
}

//======================================
//更新処理
//======================================
void CResult::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A,0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTERキーを押した場合

		// ランキングに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

		// この先の処理を行わない
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// 更新処理
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//描画処理
//======================================
void CResult::Draw(void)
{

}

//======================================
//ゲームの情報取得処理
//======================================
int CResult::GetState(void)
{
	return m_nGameState;
}