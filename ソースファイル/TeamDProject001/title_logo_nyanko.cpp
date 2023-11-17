//============================================
//
// タイトルロゴ処理[title_logo.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "title_logo_nyanko.h"
#include "texture.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define LOGO_TEXTURE		"data/TEXTURE/TitleNyanko.png"							// タイトルロゴのテクスチャ
#define LOGO_SIZE			(D3DXVECTOR3(400.0f, 100.0f, 0.0f))						// タイトルロゴのサイズ

//============================
// コンストラクタ
//============================
CTitleLogoNyanko::CTitleLogoNyanko() : CObject2D(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{

}

//============================
// デストラクタ
//============================
CTitleLogoNyanko::~CTitleLogoNyanko()
{

}

//============================
// 初期化処理
//============================
HRESULT CTitleLogoNyanko::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CTitleLogoNyanko::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//============================
// 更新処理
//============================
void CTitleLogoNyanko::Update(void)
{

}

//============================
// 描画処理
//============================
void CTitleLogoNyanko::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//============================
// 情報の設定処理
//============================
void CTitleLogoNyanko::SetData(void)
{
	// 情報を設定する
	SetPos(NONE_D3DXVECTOR3);		// 位置
	SetPosOld(NONE_D3DXVECTOR3);	// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetSize(LOGO_SIZE);				// サイズ
	SetAngle();						// 方向
	SetLength();					// 長さ

	// テクスチャの設定処理
	BindTexture(CManager::Get()->GetTexture()->Regist(LOGO_TEXTURE));

	// 頂点情報処理
	SetVertex();
}

//============================
//生成処理
//============================
CTitleLogoNyanko* CTitleLogoNyanko::Create(void)
{
	// タイトルロゴのポインタを生成
	CTitleLogoNyanko* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pTitle = new CTitleLogoNyanko;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTitle->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTitle->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// タイトルロゴのポインタを返す
	return pTitle;
}