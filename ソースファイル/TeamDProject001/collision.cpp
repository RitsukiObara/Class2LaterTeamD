//===========================================
//
// 当たり判定のメイン処理[collision.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "game.h"
#include "collision.h"
#include "shadowCircle.h"
#include "rat.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "obstacle.h"
#include "obstacle_manager.h"
#include "useful.h"

//===============================
// マクロ定義
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// 僅かな誤差を埋めるためのマクロ定義(突っかかり防止)

//===============================
// 丸影の当たり判定処理
//===============================
void collision::ShadowCollision(const D3DXVECTOR3& pos, int nIdx)
{
	// ローカル変数宣言
	CShadowCircle* pShadow = CShadowCircle::GetShadow(nIdx);	// 影のポインタ
	D3DXVECTOR3 posPlayer = pos;				// プレイヤーの位置
	D3DXVECTOR3 posCand = NONE_D3DXVECTOR3;		// 影の位置の候補

	if (pShadow != nullptr)
	{ // 影のポインタが NULL じゃなかった場合

		// 影の位置を取得する
		posCand = D3DXVECTOR3(posPlayer.x, pShadow->GetPos().y, posPlayer.z);

		// 位置を設定する
		pShadow->SetPos(posCand);
	}
}

//===============================
// 障害物の当たり判定
//===============================
void collision::ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		switch (pObstacle->GetType())
		{
		case CObstacle::TYPE::TYPE_HAIRBALL:		// 毬

			// 毬の衝突判定
			HairBallCollision(*pObstacle, pos, fWidth, fHeight);

			break;

		default:

			// 例外が発生しても問題ないためassert無し

			break;
		}

		// 次のオブジェクトを代入する
		pObstacle = pObstacle->GetNext();
	}
}

//===============================
// 毬の衝突処理
//===============================
void collision::HairBallCollision(CObstacle& obstacle, D3DXVECTOR3& pos, const float fWidth, const float fHeight)
{
	if (pos.y <= obstacle.GetPos().y + obstacle.GetFileData().vtxMax.y || 
		pos.y + fHeight >= obstacle.GetPos().y + obstacle.GetFileData().vtxMin.y)
	{ // 毬と衝突した場合

		// 円柱の当たり判定処理
		useful::CylinderCollision(&pos, obstacle.GetPos(), obstacle.GetFileData().vtxMax.x + fWidth);
	}
}

//===============================
// 障害物の当たり判定
//===============================
void collision::ObstacleHit(CRat* pRat, const float fWidth, const float fHeight, const float fDepth)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = pRat->GetPos();			// 位置を取得する

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (pObstacle->Hit(pos, fWidth, fHeight, fDepth) == true)
		{ // 障害物の当たり判定が通った場合

			switch (pObstacle->GetType())
			{
			case CObstacle::TYPE_HONEY:

				// 移動量を設定する
				pRat->SetSpeed(pRat->GetSpeed() * 0.3f);

				break;

			case CObstacle::TYPE_SLIME:

				// 移動量を設定する
				pRat->SetSpeed(pRat->GetSpeed() * 0.7f);

				break;

			case CObstacle::TYPE::TYPE_HAIRBALL:

				// 特になし

				break;

			default:

				// 停止
				assert(false);

				break;
			}
		}

		// 次のオブジェクトを代入する
		pObstacle = pObstacle->GetNext();
	}
}

//===============================
// 障害物の矩形当たり判定
//===============================
void collision::ObstacleRectCollision(D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	bool bHit = false;		// 当たったか

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
			pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight &&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth&&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
		{ // X軸の判定に入れる場合

			if (/*pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMax.x <= posOld.x - fWidth &&*/
				pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth)
			{ // 右にぶつかった場合

			  // 位置を設定する
				//pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMax.x + (fWidth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// 当たった状態にする
			}
			else if (/*pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMin.x >= posOld.x + fWidth &&*/
				pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth)
			{ // 左にぶつかった場合

			  // 位置を設定する
				//pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMin.x - (fWidth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// 当たった状態にする
			}
		}

		if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
			pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
			pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
			pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
		{ // Z軸の判定に入れる場合

			if (/*pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMax.z <= posOld.z - fDepth &&*/
				pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth)
			{ // 奥にぶつかった場合

			  // 位置を設定する
				//pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMax.z + (fDepth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// 当たった状態にする
			}
			else if (/*pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMin.z >= posOld.z + fDepth &&*/
				pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
			{ // 手前にぶつかった場合

			  // 位置を設定する
				//pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMin.z - (fDepth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// 当たった状態にする
			}
		}

		if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
			pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z &&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
		{ // Y軸の判定に入れる場合

			if (/*pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMax.y <= posOld.y &&*/
				pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y)
			{ // 上にぶつかった場合

			  // 位置を設定する
				//pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;
				bHit = true;		// 当たった状態にする
			}
			else if (/*pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMin.y >= posOld.y + fHeight &&*/
				pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
			{ // 下にぶつかった場合

			  // 位置を設定する
				//pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMin.y - (fHeight + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// 当たった状態にする
			}
		}

		if (bHit == true)
		{//当たってたら

			// 障害物の終了処理
			pObstacle->Uninit();
		}

		// 次のオブジェクトを代入する
		pObstacle = pObstacle->GetNext();
		bHit = false;		// 当たってない状態にする

	}
}

//===============================
// ブロックの当たり判定
//===============================
void collision::BlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	//if (pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
	//	pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight &&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth&&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // X軸の判定に入れる場合

	//	if (pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMax.x <= posOld.x - fWidth &&
	//		pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth)
	//	{ // 右にぶつかった場合

	//		// 位置を設定する
	//		pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMax.x + (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMin.x >= posOld.x + fWidth &&
	//		pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth)
	//	{ // 左にぶつかった場合

	//		// 位置を設定する
	//		pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMin.x - (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
	//	pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
	//{ // Z軸の判定に入れる場合

	//	if (pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMax.z <= posOld.z - fDepth &&
	//		pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth)
	//	{ // 奥にぶつかった場合

	//		// 位置を設定する
	//		pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMax.z + (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMin.z >= posOld.z + fDepth &&
	//		pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
	//	{ // 手前にぶつかった場合

	//		// 位置を設定する
	//		pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMin.z - (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z &&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // Y軸の判定に入れる場合

	//	if (pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMax.y <= posOld.y &&
	//		pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y)
	//	{ // 上にぶつかった場合

	//		// 位置を設定する
	//		pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;
	//	}
	//	else if (pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMin.y >= posOld.y + fHeight &&
	//		pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
	//	{ // 下にぶつかった場合

	//		// 位置を設定する
	//		pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMin.y - (fHeight + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}
}

//===============================
// 起伏地面の範囲外の当たり判定
//===============================
bool collision::ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth)
{
	// ローカル変数宣言
	CElevation* pElev = CElevationManager::Get()->GetTop();		// 先頭の起伏地面を取得する
	bool bCollision = false;									// 当たり判定状況

	while (pElev != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (pElev->GetPos().z + (pElev->GetSize().z * 0.5f) >= pPos->z &&
			pElev->GetPos().z - (pElev->GetSize().z * 0.5f) <= pPos->z &&
			pElev->GetPos().y > pPos->y)
		{ // 起伏地面より下にいる場合

			if (posOld.x + fWidth <= pElev->GetPos().x - (pElev->GetSize().x * 0.5f) &&
				pPos->x + fWidth >= pElev->GetPos().x - (pElev->GetSize().x * 0.5f))
			{ // 左の当たり判定

				// 位置を設定する
				pPos->x = pElev->GetPos().x - (pElev->GetSize().x * 0.5f) - fWidth;

				// 当たり判定状況を true にする
				bCollision = true;
			}
			else if (posOld.x - fWidth >= pElev->GetPos().x + (pElev->GetSize().x * 0.5f) &&
				pPos->x - fWidth <= pElev->GetPos().x + (pElev->GetSize().x * 0.5f))
			{ // 右の当たり判定

				// 位置を設定する
				pPos->x = pElev->GetPos().x + (pElev->GetSize().x * 0.5f) + fWidth;

				// 当たり判定状況を true にする
				bCollision = true;
			}
		}

		// 次のオブジェクトを代入する
		pElev = pElev->GetNext();
	}

	// 当たり判定状況を返す
	return bCollision;
}