//============================================
//
// ゲームのメイン処理[game.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "skybox.h"
#include "confetti.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define SUCCESS_TRANS_COUNT		(80)		// 成功時の遷移カウント
#define FAILED_TRANS_COUNT		(200)		// 失敗時の遷移カウント

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// ポーズの情報
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// ゲームの進行状態
int CGame::m_nFinishCount = 0;								// 終了カウント

//=========================================
// コンストラクタ
//=========================================
CGame::CGame() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pPause = nullptr;			// ポーズ
	m_nFinishCount = 0;			// 終了カウント
	m_GameState = STATE_START;	// 状態
}

//=========================================
// デストラクタ
//=========================================
CGame::~CGame()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CGame::Init(void)
{
	// テキスト読み込み処理
	CElevation::TxtSet();

	// メッシュの読み込み処理
	CMesh::TxtSet();

	// メッシュのテキスト読み込み
	//CMesh::TxtSet();

	//if (m_pField == NULL)
	//{ // フィールドへのポインタが NULL の場合

	//	// フィールドの設定処理
	//	m_pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
	//}

	// スカイボックスの生成処理
	CSkyBox::Create();

	// シーンの初期化
	CScene::Init();

	// 紙吹雪
	CConfetti::Create(D3DXVECTOR3(0.0f, 470.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(0.02f, 0.0f, 0.03f),1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 9999);
	CConfetti::Create(D3DXVECTOR3(30.0f, 470.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(0.03f, 0.03f, 0.0f), 1.3f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 9999);
	CConfetti::Create(D3DXVECTOR3(-30.0f, 470.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(-0.02f, 0.02f, 0.03f), 1.4f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 9999);
	CConfetti::Create(D3DXVECTOR3(0.0f, 440.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(-0.02f, 0.03f, -0.03f), 0.9f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 9999);
	CConfetti::Create(D3DXVECTOR3(30.0f, 440.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(-0.03f, -0.03f, 0.0f), 0.7f, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 9999);
	CConfetti::Create(D3DXVECTOR3(-30.0f, 440.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(0.02f, 0.02f, 0.0f), 1.1f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 9999);

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
	m_GameState = STATE_START;		// 状態

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CGame::Uninit(void)
{
	// ポインタを NULL にする
	m_pPause = nullptr;			// ポーズ

	// 情報を初期化する
	m_GameState = STATE_START;	// ゲームの進行状態

	// 終了カウントを初期化する
	m_nFinishCount = 0;

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CGame::Update(void)
{

// デバッグ版
#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F7) == true)
	{ // F7キーを押した場合

		//// エディット状況を入れ替える
		//m_bEdit = m_bEdit ? false : true;

		//if (m_bEdit == true)
		//{ // エディット状況が true の場合

		//}
		//else
		//{ // 上記以外

		//	if (m_pEdit != nullptr)
		//	{ // エディット状況が NULL じゃない場合

		//		// 終了処理
		//		m_pEdit->Uninit();
		//		m_pEdit = nullptr;
		//	}
		//	else
		//	{ // 上記以外

		//		// 停止
		//		assert(false);
		//	}
		//}
	}

#endif

	switch (m_GameState)
	{
	case CGame::STATE_START:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_PLAY:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_GOAL:

		// 遷移処理
		Transition();

		break;

	case CGame::STATE_FINISH:

		// 遷移処理
		Transition();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

#ifdef _DEBUG

	//if (m_bEdit == true)
	//{ // エディット状況が true の場合

	//	if (m_pEdit != nullptr)
	//	{ // エディットが NULL じゃない場合

	//		// エディットの更新処理
	//		m_pEdit->Update();
	//	}
	//}
	//else
	{ // 上記以外

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // レンダラーが NULL じゃない場合

			// レンダラーの更新
			CManager::Get()->GetRenderer()->Update();
		}
	}

#else

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// レンダラーの更新
		CManager::Get()->GetRenderer()->Update();
	}

#endif

	CManager::Get()->GetDebugProc()->Print("状態：%d", m_GameState);
}

//======================================
//描画処理
//======================================
void CGame::Draw(void)
{

}

//======================================
// 情報の設定処理
//======================================
void CGame::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);

	if (m_pPause == nullptr)
	{ // ポーズへのポインタが NULL の場合

		// ポーズの生成処理
		m_pPause = CPause::Create();
	}

	// スタート状態にする
	m_GameState = STATE_START;

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
}

//======================================
// ポーズ処理
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true)
	{ // Pキーを押した場合

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // フェード無し状態かつ、終了以外の場合

			if (m_pPause->GetPause() == false)
			{ // ポーズが false だった場合

				// ポーズ状況を true にする
				m_pPause->SetPause(true);
			}
			else
			{ // ポーズが true だった場合

				// ポーズ状況を false にする
				m_pPause->SetPause(false);
			}

			// 決定音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// 遷移処理
//======================================
void CGame::Transition(void)
{
	// 終了カウントを加算する
	m_nFinishCount++;

	if (m_nFinishCount % SUCCESS_TRANS_COUNT == 0)
	{ // 終了カウントが一定数を超えた場合

		// リザルトに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// ポーズの取得処理
//======================================
CPause* CGame::GetPause(void)
{
	// ポーズの情報を返す
	return m_pPause;
}

//======================================
// ゲームの進行状態の設定処理
//======================================
void CGame::SetState(const STATE state)
{
	// ゲームの進行状態を設定する
	m_GameState = state;
}

//======================================
// ゲームの進行状態の取得処理
//======================================
CGame::STATE CGame::GetState(void)
{
	// ゲームの進行状態を返す
	return m_GameState;
}

//======================================
// ポーズのNULL化処理
//======================================
void CGame::DeletePause(void)
{
	// ポーズのポインタを NULL にする
	m_pPause = nullptr;
}

//// デバッグ版
//#ifdef _DEBUG
////======================================
//// エディットの取得処理
////======================================
//CEdit* CGame::GetEdit(void)
//{
//	// エディットの情報を返す
//	return m_pEdit;
//}
//
////======================================
//// エディット状況の取得処理
////======================================
//bool CGame::IsEdit(void)
//{
//	// エディット状況を返す
//	return m_bEdit;
//}
//
//#endif