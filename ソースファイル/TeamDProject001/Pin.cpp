//===========================================
//
// 画鋲の処理[Pin.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Pin.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"

#define ACTION_TIME (120)
#define WAIT_TIME (20)

//==============================
// コンストラクタ
//==============================
CPin::CPin() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする

}

//==============================
// デストラクタ
//==============================
CPin::~CPin()
{

}

//==============================
// リードの初期化処理
//==============================
HRESULT CPin::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// リードの終了処理
//========================================
void CPin::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// リードの更新処理
//=====================================
void CPin::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//ギミック起動時の処理
	if (m_bAction == true)
	{//起動していない時にネズミが両端を持ったら

	}

	//重力
	m_move.y -= 1.0f;

	//位置更新
	pos.y += m_move.y;

	//地面判定
	if (pos.y < 0.0f)
	{

	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // Aボタンを押した場合

	}

	SetPos(pos);
}

//=====================================
// リードの描画処理
//=====================================
void CPin::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 両端起動時の処理
//=====================================
void CPin::Action(void)
{
	m_bAction = true;
}

//=====================================
// 情報の設定処理
//=====================================
void CPin::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CPin::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CPin::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	//// 終了処理
	//Uninit();

	// false を返す
	return false;
}