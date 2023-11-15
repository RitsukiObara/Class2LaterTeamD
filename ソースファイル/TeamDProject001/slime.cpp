//===========================================
//
// スライムのメイン処理[slime.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "slime.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CSlime::CSlime() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// デストラクタ
//==============================
CSlime::~CSlime()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CSlime::Init(void)
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
// 破片の終了処理
//========================================
void CSlime::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CSlime::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CSlime::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CSlime::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// モデルの情報を設定する
	SetFileData(CXFile::TYPE_SLIME);
}

//=====================================
// 当たり判定処理
//=====================================
bool CSlime::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CSlime::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	// ローカル変数宣言
	D3DXVECTOR3 max = D3DXVECTOR3(fWidth, fHeight, fDepth);		// サイズの最大値
	D3DXVECTOR3 min = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);		// サイズの最小値

	if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
		useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
		useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true)
	{ // 四角の当たり判定の中に入っていた場合

		// true を返す
		return true;
	}
	else
	{ // 上記以外

		// false を返す
		return false;
	}
}