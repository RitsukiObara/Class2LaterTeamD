//=======================================
//
// アイテムのマークのメイン処理[item_mark.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "item_mark.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================

//=========================
// コンストラクタ
//=========================
CItemMark::CItemMark() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CItemMark::~CItemMark()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CItemMark::Init(void)
{
	if (FAILED(CObject2D::Init()))
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
void CItemMark::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CItemMark::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CItemMark::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CItemMark::SetData(const D3DXVECTOR3& pos, const CItem::TYPE type)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(NONE_D3DXVECTOR3);	// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 頂点情報の初期化
	SetVertex();
}

//=========================
// 生成処理
//=========================
CItemMark* CItemMark::Create(const D3DXVECTOR3& pos, const CItem::TYPE type)
{
	// ローカルオブジェクトを生成
	CItemMark* pCharaImage = nullptr;	// プレイヤーのインスタンスを生成

	if (pCharaImage == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCharaImage = new CItemMark;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCharaImage != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCharaImage->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCharaImage->SetData(pos, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// キャラクター画像のポインタを返す
	return pCharaImage;
}