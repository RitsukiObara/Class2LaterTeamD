//===================================
//
// 当たり判定ヘッダー[collision.h]
// Author 小原立暉
//
//===================================
#ifndef _COLLISION_H_			//このマクロ定義がされていなかったら
#define _COLLISION_H_			//2重インクルード防止のマクロを定義する

//***********************************
// インクルードファイル
//***********************************
#include "main.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CRat;			// ネズミ
class CObstacle;	// 障害物

//-----------------------------------
// 名前空間(当たり判定)
//-----------------------------------
namespace collision
{
	// 丸影の当たり判定
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// 丸影の当たり判定

	// 障害物の当たり判定
	void ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth);			// 障害物の衝突判定
	void HairBallCollision(CObstacle& obstacle, D3DXVECTOR3& pos, const float fWidth, const float fHeight);			// 毬の衝突処理
	void ObstacleHit(CRat* pRat, const float fWidth, const float fHeight, const float fDepth);						// 障害物の当たり判定
	void ObstacleRectCollision(D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// 障害物の矩形の当たり判定

	// 今後実装予定のブロックの当たり判定
	void BlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth);		// ブロックの当たり判定

	// 起伏地面の当たり判定
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// 起伏地面の範囲外の当たり判定
}

#endif