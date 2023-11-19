//=======================================
//
// エントリーの矢印のメイン処理[entry_arrow.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_arrow.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define ARROW_SIZE		(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// 矢印のサイズ
#define ARROW_TEXTURE	"data\\TEXTURE\\Arrow.png"				// 矢印のテクスチャ

//=========================
// コンストラクタ
//=========================
CEntryArrow::CEntryArrow() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{

}

//=========================
// デストラクタ
//=========================
CEntryArrow::~CEntryArrow()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryArrow::Init(void)
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
void CEntryArrow::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CEntryArrow::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CEntryArrow::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CEntryArrow::SetData(const D3DXVECTOR3& pos, const bool bRight)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(ARROW_SIZE);		// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(ARROW_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	if (bRight == true)
	{ // 右向きの場合

		// テクスチャの設定処理
		SetVtxTexture();
	}
	else
	{ // 上記以外

		// 反転テクスチャの設定処理
		SetVtxTextureRev();
	}
}

//=========================
// 生成処理
//=========================
CEntryArrow* CEntryArrow::Create(const D3DXVECTOR3& pos, const bool bRight)
{
	// ローカルオブジェクトを生成
	CEntryArrow* pArrow = nullptr;	// プレイヤーのインスタンスを生成

	if (pArrow == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pArrow = new CEntryArrow;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pArrow != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pArrow->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pArrow->SetData(pos, bRight);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーの矢印のポインタを返す
	return pArrow;
}