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
#define MOUSETRAP_TEXTURE	"data\\TEXTURE\\Mousetrap.png"		// ネズミ捕りのテクスチャ

//=========================
// コンストラクタ
//=========================
CItemMark::CItemMark() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_type = CItem::TYPE_MOUSETRAP;		// 種類
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

	// 全ての値を初期化する
	m_type = CItem::TYPE_MOUSETRAP;		// 種類

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
void CItemMark::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(size);				// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 全ての値を設定する
	m_type = type;				// 種類

	switch (type)
	{
	case CItem::TYPE_MOUSETRAP:

		// テクスチャの割り当て処理
		BindTexture(CManager::Get()->GetTexture()->Regist(MOUSETRAP_TEXTURE));

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 頂点情報の初期化
	SetVertex();
}

//=========================
// 生成処理
//=========================
CItemMark* CItemMark::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type)
{
	// ローカルオブジェクトを生成
	CItemMark* pItemMark = nullptr;		// プレイヤーのインスタンスを生成

	if (pItemMark == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pItemMark = new CItemMark;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pItemMark != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pItemMark->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pItemMark->SetData(pos, size, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// アイテムマークのポインタを返す
	return pItemMark;
}

//=========================
// 種類の取得処理
//=========================
CItem::TYPE CItemMark::GetType(void) const
{
	// 種類を返す
	return m_type;
}