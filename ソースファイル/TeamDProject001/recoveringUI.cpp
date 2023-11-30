//===========================================
//
// 回復中UIメイン処理[recoveringUI.cpp]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "recoveringUI.h"
#include "model.h"
#include "texture.h"
#include "player.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CRecoveringUI::CRecoveringUI() : CBillboard(CObject::TYPE_RECOVERINGUI, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_bDisp = false;			// UIを表示するか
}

//==============================
// デストラクタ
//==============================
CRecoveringUI::~CRecoveringUI()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CRecoveringUI::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_bDisp = false;			// UIを表示するか

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CRecoveringUI::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CRecoveringUI::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CRecoveringUI::Draw(void)
{
	if (m_bDisp == true)
	{ // UIを表示する状態のとき

		// 描画処理
		CBillboard::Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CRecoveringUI::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	// 情報の設定処理

	//==========================================================================
	// ビルボード
	//==========================================================================
	SetPos(pos);			// 位置
	SetPosOld(posOld);		// 前回の位置
	SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));	// サイズ
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\CageMark.png"));		// テクスチャの割り当て処理

	// 頂点座標の設定処理
	SetVertex();
}

//=======================================
// 生成処理
//=======================================
CRecoveringUI* CRecoveringUI::Create(const D3DXVECTOR3& pos, const  D3DXVECTOR3& posOld)
{
	// ローカルオブジェクトを生成
	CRecoveringUI* pRecoveringUI = nullptr;	// サンプルのインスタンスを生成

	if (pRecoveringUI == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pRecoveringUI = new CRecoveringUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pRecoveringUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pRecoveringUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pRecoveringUI->SetData(pos, posOld);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pRecoveringUI;
}

//=======================================
// UIの表示状態の設定
//=======================================
void CRecoveringUI::SetDisplayUI(bool bRez)
{
	// UIの表示状態を設定
	m_bDisp = bRez;
}

//=======================================
// UIの表示状態の取得
//=======================================
bool CRecoveringUI::GetDisplayUI(void)
{
	// UIの表示状態を返す
	return m_bDisp;
}