//=======================================
//
// 天井処理[ceil.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "ceil.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define CEIL_ROT		(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI))		// 天井のサイズ
#define CEIL_SIZE		(D3DXVECTOR3(1600.0f, 0.0f, 1000.0f))		// 天井のサイズ

//=========================
// コンストラクタ
//=========================
CCeil::CCeil() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// デストラクタ
//=========================
CCeil::~CCeil()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CCeil::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CCeil::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//=========================
// 更新処理
//=========================
void CCeil::Update(void)
{
	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 描画処理
//=========================
void CCeil::Draw(void)
{
	// 描画処理
	CObject3D::DrawLightOff();
}

//=========================
// 情報の設定処理
//=========================
void CCeil::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);			// 位置設定
	SetPosOld(pos);			// 前回の位置設定
	SetRot(CEIL_ROT);		// 向き設定
	SetSize(CEIL_SIZE);		// サイズ設定

	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 生成処理
//=========================
CCeil* CCeil::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CCeil* pCeil = nullptr;	// プレイヤーのインスタンスを生成

	if (pCeil == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCeil = new CCeil;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCeil != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCeil->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCeil->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 紙吹雪のポインタを返す
	return pCeil;
}