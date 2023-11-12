//============================================
//
// 斬撃演出のメイン処理[slash.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "slash.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define TURN_TEXTURE		"data/TEXTURE/SlashStaging001.png"	// 斬撃演出のテクスチャ
#define TURN_COUNT			(2)									// 斬撃演出のカウント
#define TURN_PATTERN		(8)									// 斬撃演出のパターン数

//===========================================
// コンストラクタ
//===========================================
CSlash::CSlash() : CBillboardAnim(CObject::TYPE_SLASH,CObject::PRIORITY_EFFECT)
{
	// 全ての値をクリアする
	m_nLife = 0;				// 寿命
}

//===========================================
// デストラクタ
//===========================================
CSlash::~CSlash()
{

}

//===========================================
// 初期化処理
//===========================================
HRESULT CSlash::Init(void)
{
	if (FAILED(CBillboardAnim::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_nLife = 0;				// 寿命

	// 成功を返す
	return S_OK;
}

//===========================================
// 終了処理
//===========================================
void CSlash::Uninit(void)
{
	// 終了
	CBillboardAnim::Uninit();
}

//===========================================
// 更新処理
//===========================================
void CSlash::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	// 更新処理
	CBillboardAnim::Update();

	// テクスチャ座標の設定処理
	SetVtxAnim(GetTexPattern(), GetPattern());

	if (m_nLife <= 0)
	{ // パターン数が最大数を超えた場合

		// 終了処理
		Uninit();
	}
}

//===========================================
// 描画処理
//===========================================
void CSlash::Draw(void)
{
	// 描画処理
	CBillboardAnim::DrawLightOff();
}

//===========================================
// 設定処理
//===========================================
void CSlash::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetSize(D3DXVECTOR3(1000.0f, 1000.0f, 0.0f));			// サイズ設定

	// アニメーションの設定処理
	SetAnim(TURN_COUNT, TURN_PATTERN);

	// 全ての値を初期化する
	m_nLife = TURN_COUNT * TURN_PATTERN;	// 寿命

	// 頂点情報の初期化
	SetVertex();

	// テクスチャ座標の設定処理
	SetVtxAnim(GetTexPattern(), GetPattern());

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TURN_TEXTURE));
}

//===========================================
// 生成処理
//===========================================
CSlash* CSlash::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CSlash* pSlash = nullptr;	// プレイヤーのインスタンスを生成

	if (pSlash == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pSlash = new CSlash;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pSlash != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pSlash->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSlash->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 斬撃演出のポインタを返す
	return pSlash;
}