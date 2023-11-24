//===========================================
//
// 扇風機の処理[electricfan.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "electricfan.h"
#include "manager.h"

//==============================
// コンストラクタ
//==============================
CElecFan::CElecFan() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// デストラクタ
//==============================
CElecFan::~CElecFan()
{

}

//==============================
// スピーカーの初期化処理
//==============================
HRESULT CElecFan::Init(void)
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
// スピーカーの終了処理
//========================================
void CElecFan::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// スピーカーの更新処理
//=====================================
void CElecFan::Update(void)
{

}

//=====================================
// スピーカーの描画処理
//=====================================
void CElecFan::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CElecFan::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CElecFan::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CElecFan::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CElecFan::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CElecFan::Action(void)
{

}