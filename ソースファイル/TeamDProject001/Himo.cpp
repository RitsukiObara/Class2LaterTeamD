//===========================================
//
// ひもの処理[tarai.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Himo.h"
#include "useful.h"
#include "objectX.h"

//==============================
// コンストラクタ
//==============================
CHimo::CHimo() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
}

//==============================
// デストラクタ
//==============================
CHimo::~CHimo()
{

}

//==============================
// たらいの初期化処理
//==============================
HRESULT CHimo::Init(void)
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
// たらいの終了処理
//========================================
void CHimo::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// たらいの更新処理
//=====================================
void CHimo::Update(void)
{

}

//=====================================
// たらいの描画処理
//=====================================
void CHimo::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CHimo::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CHimo::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CHimo::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	//// 終了処理
	//Uninit();

	// false を返す
	return false;
}