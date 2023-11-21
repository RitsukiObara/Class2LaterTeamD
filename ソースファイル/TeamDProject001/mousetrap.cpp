//===========================================
//
// ネズミ捕りのメイン処理[mousetrap.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "mousetrap.h"
#include "obstacle.h"
#include "mousetrap_iron.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CMouseTrap::CMouseTrap() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pIron = nullptr;		// 鉄部分
}

//==============================
// デストラクタ
//==============================
CMouseTrap::~CMouseTrap()
{

}

//==============================
// ネズミ捕りの初期化処理
//==============================
HRESULT CMouseTrap::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	m_pIron = nullptr;		// 鉄部分

	// 値を返す
	return S_OK;
}

//========================================
// ネズミ捕りの終了処理
//========================================
void CMouseTrap::Uninit(void)
{
	if (m_pIron != nullptr)
	{ // 鉄部分が NULL じゃない場合

		// 鉄部分の終了処理
		m_pIron->Uninit();
		m_pIron = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ネズミ捕りの更新処理
//=====================================
void CMouseTrap::Update(void)
{
	if (m_pIron != nullptr)
	{ // 鉄部分が NULL じゃない場合

		// 鉄部分の更新処理
		m_pIron->Update();
	}
}

//=====================================
// ネズミ捕りの描画処理
//=====================================
void CMouseTrap::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	if (m_pIron != nullptr)
	{ // 鉄部分が NULL じゃない場合

		// 鉄部分の描画処理
		m_pIron->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CMouseTrap::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// 全ての値をクリアする
	if (m_pIron == nullptr)
	{ // 鉄部分が NULL の場合

		// 鉄部分を生成
		m_pIron = CTrapIron::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z));
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CMouseTrap::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CMouseTrap::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}