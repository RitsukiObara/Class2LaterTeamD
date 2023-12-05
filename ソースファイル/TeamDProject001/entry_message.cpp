//===========================================
//
// エントリー画面の説明のメイン処理[entry_message.cpp]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "entry_message.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CEntryMessage::CEntryMessage() : CObject2D(CObject::TYPE_ENTRYMESSAGEUI, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
}

//==============================
// デストラクタ
//==============================
CEntryMessage::~CEntryMessage()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CEntryMessage::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CEntryMessage::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CEntryMessage::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CEntryMessage::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CEntryMessage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う
	// 情報の設定処理

	//==========================================================================
	// 2Dポリゴン
	//==========================================================================
	SetPos(pos);			// 位置
	SetPosOld(posOld);		// 前回の位置
	SetRot(NONE_D3DXVECTOR3);			// 向き
	SetSize(size);		// サイズ
	SetLength();		// 長さ
	SetAngle();			// 方向
	//BindTexture(CManager::Get()->GetTexture()->Regist(テクスチャの名前));		// テクスチャの割り当て処理

	// 頂点座標の設定処理
	SetVertex();

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
CEntryMessage* CEntryMessage::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// ローカルオブジェクトを生成
	CEntryMessage* pEntryMessage = nullptr;	// サンプルのインスタンスを生成

	if (pEntryMessage == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pEntryMessage = new CEntryMessage;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntryMessage != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntryMessage->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntryMessage->SetData(pos, posOld, size);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pEntryMessage;
}