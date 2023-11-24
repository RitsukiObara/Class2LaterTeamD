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
#include "obstacle.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CRat;			// ネズミ
class CCat;			// ネコ
class CBlock;		// ブロック

//-----------------------------------
// 名前空間(当たり判定)
//-----------------------------------
namespace collision
{
	// 丸影の当たり判定
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// 丸影の当たり判定

	// 障害物の当たり判定
	void ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);			// 障害物の衝突判定
	void ObstacleHit(CRat* pRat, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);						// 障害物の当たり判定
	void ObstacleAction(CRat* pRat, const float Radius, const CObstacle::COLLTYPE type);					// 障害物の起動判定

	// 今後実装予定のブロックの当たり判定
	void BlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth);		// ブロックの当たり判定
	void BlockRectangleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);	// ブロックの矩形の当たり判定
	void BlockCircleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fRadius, const float fHeight);	// ブロックの円形の当たり判定

	// 起伏地面の当たり判定
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// 起伏地面の範囲外の当たり判定

	//壁との当たり判定
	D3DXVECTOR3 WallCollision(D3DXVECTOR3& objVec1, D3DXVECTOR3& objVec2);

	// アイテムとの当たり判定
	void ItemCollision(CCat& pCat);		// ネコとアイテムとの当たり判定

	// 汎用的な当たり判定
	bool HexahedronCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// 六面体の当たり判定
}

#endif