//============================================
//
// 画面の枠処理[screen_frame.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "screen_frame.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	static const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// 位置
	static const D3DXVECTOR3 FRAME_SIZE = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// サイズ
}

//============================
// コンストラクタ
//============================
CScreenFrame::CScreenFrame() : CObject2D(CObject::TYPE_SCREENFRAME, CObject::PRIORITY_BG)
{

}

//============================
// デストラクタ
//============================
CScreenFrame::~CScreenFrame()
{

}

//============================
// 初期化処理
//============================
HRESULT CScreenFrame::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CScreenFrame::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//============================
// 更新処理
//============================
void CScreenFrame::Update(void)
{
	// 頂点情報の設定処理
	SetVertex();
}

//============================
// 描画処理
//============================
void CScreenFrame::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//============================
// 情報の設定処理
//============================
void CScreenFrame::SetData(void)
{
	// スクロールの設定処理
	SetPos(FRAME_POS);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);		// 向き設定
	SetSize(FRAME_SIZE);			// サイズ設定
	SetLength();					// 長さ設定
	SetAngle();						// 方向設定

	// 頂点情報の初期化
	SetVertex();
}

//============================
//生成処理
//============================
CScreenFrame* CScreenFrame::Create(void)
{
	// ローカルオブジェクトを生成
	CScreenFrame* pScreen = nullptr;	// 画面の枠のインスタンスを生成

	if (pScreen == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pScreen = new CScreenFrame;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pScreen != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pScreen->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 画面の枠のポインタを返す
	return pScreen;
}