//=======================================
//
// マッチングの選択肢処理[match_select.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "match_select.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define SELECT_SIZE			(D3DXVECTOR3(40.0f, 20.0f, 0.0f))		// 選択肢のサイズ
#define SELECT_TEXTURE		"data\\TEXTURE\\PlayerID.png"			// 選択肢のテクスチャ
#define SELECT_PATTERN		(0.25f)									// 選択肢のパターン数

//=========================
// コンストラクタ
//=========================
CMatchSelect::CMatchSelect() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CMatchSelect::~CMatchSelect()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CMatchSelect::Init(void)
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
void CMatchSelect::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CMatchSelect::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CMatchSelect::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CMatchSelect::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(SELECT_SIZE);		// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(SELECT_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	// テクスチャ座標の設定処理
	SetVtxTextureAnim(SELECT_PATTERN, nID);
}

//=========================
// 生成処理
//=========================
CMatchSelect* CMatchSelect::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ローカルオブジェクトを生成
	CMatchSelect* pMatchVS = nullptr;	// プレイヤーのインスタンスを生成

	if (pMatchVS == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pMatchVS = new CMatchSelect;
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
		pMatchVS->SetData(pos, nID);
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