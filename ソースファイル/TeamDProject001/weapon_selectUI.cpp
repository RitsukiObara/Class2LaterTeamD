//=======================================
//
// 武器選択UIのメイン処理[weapon_selectUI.cpp]
// Author 小原立暉
//
//=======================================
#include "main.h"
#include "manager.h"
#include "weapon_selectUI.h"
#include "object2D.h"
#include "texture.h"

#include "weapon_cage.h"

//---------------------------------------
// マクロ定義
//---------------------------------------

//==========================================
// コンストラクタ
//==========================================
CWeaponSelectUI::CWeaponSelectUI() : CObject(TYPE_WEAPONSELECTUI, PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pWeaponCage = nullptr;		// 武器小屋の情報
}

//==========================================
// デストラクタ
//==========================================
CWeaponSelectUI::~CWeaponSelectUI()
{

}

//==========================================
// ポーズの初期化処理
//==========================================
HRESULT CWeaponSelectUI::Init(void)
{
	if (m_pWeaponCage == nullptr)
	{ // 武器小屋の情報が NULL の場合

		// 武器小屋を生成する
		m_pWeaponCage = CWeaponCage::Create();
	}

	// 成功を返す
	return S_OK;
}

//========================================
// ポーズの終了処理
//========================================
void CWeaponSelectUI::Uninit(void)
{
	if (m_pWeaponCage != nullptr)
	{ // 武器小屋が NULL じゃない場合

		// 武器小屋の終了処理
		m_pWeaponCage->Uninit();
		m_pWeaponCage = nullptr;
	}

	// 本体の終了処理
	Release();
}

//========================================
// ポーズの更新処理
//========================================
void CWeaponSelectUI::Update(void)
{
	
}

//=====================================
// ポーズの描画処理
//=====================================
void CWeaponSelectUI::Draw(void)
{
	if (m_pWeaponCage != nullptr)
	{ // 武器小屋が NULL じゃない場合

		// 描画処理
		m_pWeaponCage->Draw();
	}
}

//=====================================
// 生成処理
//=====================================
CWeaponSelectUI* CWeaponSelectUI::Create(void)
{
	// ローカルオブジェクトを生成
	CWeaponSelectUI* pWeapon = nullptr;	// プレイヤーのインスタンスを生成

	if (pWeapon == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pWeapon = new CWeaponSelectUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pWeapon != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pWeapon->Init()))
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

	// 武器選択UIのポインタを返す
	return pWeapon;
}