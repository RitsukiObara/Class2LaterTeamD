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
#include "title_logo.h"
#include "object2D.h"
#include "texture.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define RAT_TEXTURE			"data/TEXTURE/TitleRat.png"				// タイトルロゴ(ネズミ)のテクスチャ
#define CAT_TEXTURE			"data/TEXTURE/TitleCat.png"				// タイトルロゴ(ネコ)のテクスチャ
#define AND_TEXTURE			"data/TEXTURE/TitleAnd.png"				// タイトルロゴ(＆)のテクスチャ
#define TITLE_LOGO_SIZE		(D3DXVECTOR3(200.0f, 100.0f, 0.0f))		// タイトルのサイズ

//============================
// コンストラクタ
//============================
CTitleLogo::CTitleLogo() : CObject(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apTitle[nCnt] = nullptr;		// タイトルのポリゴン
	}
}

//============================
// デストラクタ
//============================
CTitleLogo::~CTitleLogo()
{

}

//============================
// 初期化処理
//============================
HRESULT CTitleLogo::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] == nullptr)
		{ // タイトルが NULL の場合

			// タイトルのロゴを生成する
			m_apTitle[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}
	}

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CTitleLogo::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] != nullptr)
		{ // タイトルのポリゴンが NULL じゃない場合

			// 終了処理
			m_apTitle[nCnt]->Uninit();
			m_apTitle[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//============================
// 更新処理
//============================
void CTitleLogo::Update(void)
{

}

//============================
// 描画処理
//============================
void CTitleLogo::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] != nullptr)
		{ // タイトルが NULL じゃない場合

			// 描画処理
			m_apTitle[nCnt]->Draw();
		}
	}
}

//============================
// 情報の設定処理
//============================
void CTitleLogo::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] != nullptr)
		{ // タイトルが NULL じゃない場合

			// 情報を設定する
			m_apTitle[nCnt]->SetPos(NONE_D3DXVECTOR3);					// 位置
			m_apTitle[nCnt]->SetPosOld(m_apTitle[nCnt]->GetPos());		// 前回の位置
			m_apTitle[nCnt]->SetRot(NONE_D3DXVECTOR3);					// 向き
			m_apTitle[nCnt]->SetSize(TITLE_LOGO_SIZE);					// サイズ
			m_apTitle[nCnt]->SetAngle();								// 方向
			m_apTitle[nCnt]->SetLength();								// 長さ

			// テクスチャの設定処理
			m_apTitle[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

			// 頂点情報処理
			m_apTitle[nCnt]->SetVertexRot();
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}
	}
}

//============================
//生成処理
//============================
CTitleLogo* CTitleLogo::Create(void)
{
	// タイトルロゴのポインタを生成
	CTitleLogo* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pTitle = new CTitleLogo;
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