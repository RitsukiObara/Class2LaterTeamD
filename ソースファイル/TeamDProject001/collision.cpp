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
#include "obstacle_manager.h"
#include "block.h"
#include "block_manager.h"
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
void collision::ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		// 当たり判定処理
		if (pObstacle->Collision(pos, posOld, fWidth, fHeight, fDepth, type) == true)
		{
			switch (pObstacle->GetType())
			{
			case CObstacle::TYPE::TYPE_HONEY:		// 蜂蜜

				// 特に無し

				break;

			case CObstacle::TYPE::TYPE_SLIME:

				break;

			case CObstacle::TYPE::TYPE_HAIRBALL:

				break;

			case CObstacle::TYPE::TYPE_FLOWERVASE:

				break;

			case CObstacle::TYPE::TYPE_PLASTICCASE:

				break;

			case CObstacle::TYPE::TYPE_PETBOTTLE:

				break;

			case CObstacle::TYPE::TYPE_TOYCAR:

				break;

			default:			// 上記以外

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
// 障害物の当たり判定
//===============================
void collision::ObstacleHit(CRat* pRat, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = pRat->GetPos();			// 位置を取得する

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (pObstacle->Hit(pos, fWidth, fHeight, fDepth, type) == true)
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

			case CObstacle::TYPE_HAIRBALL:

				// ヒット処理
				pRat->Hit();

				break;

			case CObstacle::TYPE_FLOWERVASE:

				// 特になし

				break;

			case CObstacle::TYPE_PLASTICCASE:

				// 特になし

				break;

			case CObstacle::TYPE_PETBOTTLE:

				break;

			case CObstacle::TYPE_TOYCAR:

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
// ブロックの当たり判定
//===============================
void collision::BlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// 先頭のブロックの情報を取得する
	CBlock* pBlock = CBlockManager::Get()->GetTop();

	while (pBlock != nullptr)
	{ // ブロックが NULL の場合

		if (pBlock->GetCollision() == CBlock::COLLISION_SQUARE)
		{ // 矩形の当たり判定の場合

			// 矩形の当たり判定
			BlockRectangleCollision(*pBlock, pos, posOld, fWidth, fHeight, fDepth);
		}
		else
		{ // 上記以外

			// 円の当たり判定
			BlockCircleCollision(*pBlock, pos, fWidth, fHeight);
		}

		// 次のブロックの情報を取得する
		pBlock = pBlock->GetNext();
	}
}

//===============================
// ブロックの矩形の当たり判定
//===============================
void collision::BlockRectangleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	if (block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y &&
		block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight &&
		block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z - fDepth&&
		block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	{ // X軸の判定に入れる場合

		if (block.GetPosOld().x + block.GetFileData().vtxMax.x <= posOld.x - fWidth &&
			block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth)
		{ // 右にぶつかった場合

			// 位置を設定する
			pos.x = block.GetPos().x + block.GetFileData().vtxMax.x + (fWidth + COLLISION_ADD_DIFF_LENGTH);
		}
		else if (block.GetPosOld().x + block.GetFileData().vtxMin.x >= posOld.x + fWidth &&
			block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth)
		{ // 左にぶつかった場合

			// 位置を設定する
			pos.x = block.GetPos().x + block.GetFileData().vtxMin.x - (fWidth + COLLISION_ADD_DIFF_LENGTH);
		}
	}

	if (block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth &&
		block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth &&
		block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y &&
		block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight)
	{ // Z軸の判定に入れる場合

		if (block.GetPosOld().z + block.GetFileData().vtxMax.z <= posOld.z - fDepth &&
			block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z - fDepth)
		{ // 奥にぶつかった場合

			// 位置を設定する
			pos.z = block.GetPos().z + block.GetFileData().vtxMax.z + (fDepth + COLLISION_ADD_DIFF_LENGTH);
		}
		else if (block.GetPosOld().z + block.GetFileData().vtxMin.z >= posOld.z + fDepth &&
			block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
		{ // 手前にぶつかった場合

			// 位置を設定する
			pos.z = block.GetPos().z + block.GetFileData().vtxMin.z - (fDepth + COLLISION_ADD_DIFF_LENGTH);
		}
	}

	if (block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth &&
		block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth &&
		block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z &&
		block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	{ // Y軸の判定に入れる場合

		if (block.GetPosOld().y + block.GetFileData().vtxMax.y <= posOld.y &&
			block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y)
		{ // 上にぶつかった場合

			// 位置を設定する
			pos.y = block.GetPos().y + block.GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;
		}
		else if (block.GetPosOld().y + block.GetFileData().vtxMin.y >= posOld.y + fHeight &&
			block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight)
		{ // 下にぶつかった場合

			// 位置を設定する
			pos.y = block.GetPos().y + block.GetFileData().vtxMin.y - (fHeight + COLLISION_ADD_DIFF_LENGTH);
		}
	}
}

//===============================
// ブロックの円形の当たり判定
//===============================
void collision::BlockCircleCollision(CBlock& block, D3DXVECTOR3& pos, const float fRadius, const float fHeight)
{
	if (pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y ||
		pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
	{ // 毬と衝突した場合

		// 円柱の当たり判定処理
		useful::CylinderCollision(&pos, block.GetPos(), block.GetFileData().fRadius + fRadius);
	}
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

//======================
// 六面体の当たり判定
//======================
bool collision::HexahedronCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	if (posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // X軸の判定に入れる場合

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos.x + min.x)
		{ // 右にぶつかった場合

			// 位置を設定する
			pos.x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos.x + max.x)
		{ // 左にぶつかった場合

			// 位置を設定する
			pos.x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y)
	{ // Z軸の判定に入れる場合

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos.z + min.z)
		{ // 奥にぶつかった場合

			// 位置を設定する
			pos.z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos.z + max.z)
		{ // 手前にぶつかった場合

			// 位置を設定する
			pos.z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // Y軸の判定に入れる場合

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos.y + min.y)
		{ // 上にぶつかった場合

			// 位置を設定する
			pos.y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos.y + max.y)
		{ // 下にぶつかった場合

			// 位置を設定する
			pos.y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}