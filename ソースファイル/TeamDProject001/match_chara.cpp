//=======================================
//
// マッチングのキャラクター処理[match_chara.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "match_chara.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define CHARA_SIZE		(D3DXVECTOR3(120.0f, 30.0f, 0.0f))		// キャラクターのサイズ
#define CHARA_TEXTURE	"data\\TEXTURE\\MatchChara.png"			// キャラクターのテクスチャ

//=========================
// コンストラクタ
//=========================
CMatchChara::CMatchChara() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CMatchChara::~CMatchChara()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CMatchChara::Init(void)
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
void CMatchChara::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CMatchChara::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CMatchChara::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CMatchChara::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(CHARA_SIZE);		// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの割り当て.処理
	BindTexture(CManager::Get()->GetTexture()->Regist(CHARA_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	// 頂点カラーの設定処理
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=========================
// 生成処理
//=========================
CMatchChara* CMatchChara::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CMatchChara* pChara = nullptr;	// プレイヤーのインスタンスを生成

	if (pChara == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pChara = new CMatchChara;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pChara != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pChara->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pChara->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーチームのポインタを返す
	return pChara;
}