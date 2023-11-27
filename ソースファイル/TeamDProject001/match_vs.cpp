//=======================================
//
// マッチングのVS処理[match_vs.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "match_vs.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define VS_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))		// VSマークのサイズ
#define VS_TEXTURE	"data\\TEXTURE\\MatchVS.png"			// VSマークのテクスチャ

//=========================
// コンストラクタ
//=========================
CMatchVS::CMatchVS() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CMatchVS::~CMatchVS()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CMatchVS::Init(void)
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
void CMatchVS::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CMatchVS::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CMatchVS::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CMatchVS::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(VS_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(VS_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	// 頂点カラーの設定処理
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=========================
// 生成処理
//=========================
CMatchVS* CMatchVS::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CMatchVS* pMatchVS = nullptr;	// プレイヤーのインスタンスを生成

	if (pMatchVS == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pMatchVS = new CMatchVS;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pMatchVS != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pMatchVS->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pMatchVS->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーチームのポインタを返す
	return pMatchVS;
}