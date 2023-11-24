//===========================================
//
// 生き返りの円の範囲の処理[resurrection_fan.h]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "resurrection_fan.h"
#include "object3Dfan.h"
#include "model.h"
#include "texture.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CRessrectionFan::CRessrectionFan()
{
	// 全ての値をクリアする
}

//==============================
// デストラクタ
//==============================
CRessrectionFan::~CRessrectionFan()
{

}

//==============================
// 生き返りの円の初期化処理
//==============================
HRESULT CRessrectionFan::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する

	// 値を返す
	return S_OK;
}

//========================================
// 生き返りの円の終了処理
//========================================
void CRessrectionFan::Uninit(void)
{
	// 終了処理
	CObject3DFan::Uninit();
}

//=====================================
// 生き返りの円の更新処理
//=====================================
void CRessrectionFan::Update(void)
{
	// 頂点座標の設定処理
	SetVertex();
}

//=====================================
// 生き返りの円の描画処理
//=====================================
void CRessrectionFan::Draw(void)
{
	// 描画処理
	CObject3DFan::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRessrectionFan::SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う
	// 情報の設定処理

	//==========================================================================
	// 3Dポリゴン
	//==========================================================================
	SetPos(pos);					// 位置
	SetPosOld(GetPos());			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetSize(NONE_SCALE);			// サイズ
	SetNumAngle(16);				// 角度の総数
	SetRadius(100.0f);				// 半径
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\cheese.jpg"));		// テクスチャの割り当て処理

	//==========================================================================
	// アニメーション系
	//==========================================================================
	//SetPos(位置を入れる);			// 位置
	//SetPosOld(位置を入れる);		// 前回の位置
	//SetRot(向きを入れる);			// 向き
	//SetSize(サイズを入れる);		// サイズ
	//SetLength(引数無し);			// 長さ
	//SetAngle(引数無し);			// 方向
	//BindTexture(CManager::Get()->GetTexture()->Regist(テクスチャの名前));		// テクスチャの割り当て処理

	// アニメーションの設定処理
	//SetAnim(カウントを入れる, パターン数を入れる);

	//// 頂点座標の設定処理
	//SetVertex();

	// テクスチャの設定(アニメーションバージョン)
	//SetVtxTextureAnim(アニメーションの総パターン数を入れる, 0);
}

//=======================================
// 生成処理
//=======================================
CRessrectionFan* CRessrectionFan::Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// ローカルオブジェクトを生成
	CRessrectionFan* pRessrectionFan = nullptr;	// サンプルのインスタンスを生成

	if (pRessrectionFan == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pRessrectionFan = new CRessrectionFan;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pRessrectionFan != nullptr)
	{ // オブジェクトが NULL じゃない場合
		
		// 情報の設定処理
		pRessrectionFan->SetData(pos, col);

		// 初期化処理
		if (FAILED(pRessrectionFan->Init()))
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

	// サンプルのポインタを返す
	return pRessrectionFan;
}