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
#include "objectElevation.h"
#include "elevation_manager.h"
#include "obstacle_manager.h"
#include "block.h"
#include "block_manager.h"
#include "useful.h"
#include "Particle.h"
#include "map.h"
#include "wall.h"
#include "ground.h"
#include <cmath>
#include "objectX.h"
#include "item.h"
#include "item_manager.h"
#include "player.h"

//===============================
// マクロ定義
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// 僅かな誤差を埋めるためのマクロ定義(突っかかり防止)
#define COLLISION_CAT_SIZE				(D3DXVECTOR3(70.0f,250.0f,70.0f))		// ネコの当たり判定のサイズ
#define WIND_MOVE						(17.0f)			// 風で吹き飛ぶ移動量

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
void collision::ObstacleCollision(CPlayer* player, const float fWidth, const float fHeight, const float fDepth)
{
	// ローカル変数宣言
	D3DXVECTOR3 collSize = D3DXVECTOR3(fWidth, fHeight, fDepth);	// 当たり判定のサイズ
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		// 当たり判定処理
		if (pObstacle->Collision(player, collSize) == true)
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

			case CObstacle::TYPE::TYPE_PETBOTTLE:

				break;

			case CObstacle::TYPE::TYPE_TOYCAR:

				break;

			default:			// 上記以外

				// 停止
				//assert(false);

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
void collision::ObstacleHit(CPlayer* pPlayer, const float fWidth, const float fHeight, const float fDepth)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物
	CObstacle* pObstacleNext = nullptr;				// 次の障害物
	D3DXVECTOR3 pos = pPlayer->GetPos();			// 位置
	D3DXVECTOR3 collSize = D3DXVECTOR3(fWidth, fHeight, fDepth);	// 当たり判定のサイズ
	float fAngle;				// 吹き飛ぶ方向
	bool bHitMove = false;		// ヒット状況

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		// 障害物の次のポインタを取得する
		pObstacleNext = pObstacle->GetNext();

		if (pObstacle->Hit(pPlayer, collSize) == true)
		{ // 障害物の当たり判定が通った場合

			switch (pObstacle->GetType())
			{
			case CObstacle::TYPE_HONEY:

				// 移動量を設定する
				pPlayer->SetSpeed(pPlayer->GetSpeedCopy() * 0.3f);

				// ジャンプ状況を設定する
				pPlayer->SetEnableJump(true);

				// ヒットした
				bHitMove = true;

				break;

			case CObstacle::TYPE_SLIME:

				// 移動量を設定する
				pPlayer->SetSpeed(pPlayer->GetSpeedCopy() * 0.7f);

				if (pPlayer->IsMove() == true)
				{
					CParticle::Create(pos, CParticle::TYPE_SLIME);
				}

				// ヒットした
				bHitMove = true;

				break;

			case CObstacle::TYPE_HAIRBALL:

				// 向きを算出する
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// ヒット処理
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_PETBOTTLE:

				// 向きを算出する
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// ヒット処理
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_TOYCAR:

			{ // プレイヤーを飛ばす処理

				// 向きを算出する
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// 吹き飛び処理
				pPlayer->Smash(fAngle);
			}

				break;

			case CObstacle::TYPE_ROOMBA:

				// 向きを算出する
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// 吹き飛び処理
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_HIMO:

				// ヒット処理
				pPlayer->Stun(60);

				break;


			case CObstacle::TYPE_SPEAKER:

				// 向きを算出する
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// ヒット処理
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_MOUSETRAP:

				// 気絶状態
				pPlayer->Stun(60);

				break;

			case CObstacle::TYPE_LEASH:

				// 気絶処理
				pPlayer->Stun(60);

				break;

			case CObstacle::TYPE_PIN:

				// 気絶処理
				pPlayer->Stun(60);

				break;

			case CObstacle::TYPE_FAN:

				// 向きを算出する
				fAngle = pObstacle->GetRot().y + D3DX_PI;

				// 向きを正規化する
				useful::RotNormalize(&fAngle);

				// 位置を押し出す
				pos.x += sinf(fAngle) * WIND_MOVE;
				pos.z += cosf(fAngle) * WIND_MOVE;

				// 位置を設定する
				pPlayer->SetPos(pos);

				break;

			case CObstacle::TYPE_CUP:

				// 気絶状態
				pPlayer->Stun(60);

				break;

			case CObstacle::TYPE_GARBAGECAN:

				// 気絶状態
				pPlayer->Stun(90);
				pObstacle->SlideOn(pPlayer->GetPos(), pPlayer->GetMove(), pPlayer);
				break;

			case CObstacle::TYPE_BOOK:

				// 気絶状態
				pPlayer->Stun(60);

				break;

			default:

				//特になし

				break;
			}
		}

		// 次のオブジェクトを代入する
		pObstacle = pObstacleNext;
	}

	if (bHitMove == false)
	{ // ヒットしていない場合

		// 速度を通常に設定
		pPlayer->SetSpeed(pPlayer->GetSpeedCopy());
	}
}

//===============================
// 障害物の起動判定
//===============================
void collision::ObstacleAction(CPlayer* pPlayer, const float Radius)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();	// 先頭の障害物
	CPlayer::TYPE type = pPlayer->GetType();					// 種類

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (type == CPlayer::TYPE::TYPE_CAT)
		{
			if (pObstacle->GetCatUse() == true)
			{
				if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH ||
					pObstacle->GetType() == CObstacle::TYPE::TYPE_REDKATEN)
				{//リードのとき
					pObstacle->HitMultiCircle(pPlayer, Radius, true);
				}
				else
				{//リード以外のとき
					if (pObstacle->HitCircle(pPlayer, Radius) == true)
					{ // 障害物の当たり判定が通った場合

						//起動状態にする
						pObstacle->Action();

						//ネズミがアクションを行った判定(チュートリアル用)
						pPlayer->SetUseAction(true);
					}
				}
			}
		}
		else if(type == CPlayer::TYPE::TYPE_RAT)
		{
			if (pObstacle->GetRatUse() == true)
			{
				if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH ||
					pObstacle->GetType() == CObstacle::TYPE::TYPE_REDKATEN)
				{//リードのとき
					pObstacle->HitMultiCircle(pPlayer, Radius, true);
				}
				else
				{//リード以外のとき
					if (pObstacle->HitCircle(pPlayer, Radius) == true)
					{ // 障害物の当たり判定が通った場合

					  //起動状態にする
						pObstacle->Action();

						//ネズミがアクションを行った判定(チュートリアル用)
						pPlayer->SetUseAction(true);
					}
				}
			}
		}

		// 次のオブジェクトを代入する
		pObstacle = pObstacle->GetNext();
	}
}

//===========================================
// 起動可能障害物や警告を出す障害物のサーチ
//===========================================
void collision::ObstacleSearch(CPlayer* pPlayer, const float Radius)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物
	CPlayer::TYPE type = pPlayer->GetType();						// 種類
	int nIdx = pPlayer->GetPlayerIdx();								// インデックス
	float fAngle;													// 吹き飛ぶ方向

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (type == CPlayer::TYPE::TYPE_CAT)
		{
			if (pObstacle->GetCatUse() == true)
			{
				if (pObstacle->HitCircle(pPlayer, Radius) == true)
				{ // 障害物の当たり判定が通った場合
					pObstacle->GimmickUI(true, nIdx);
				}
				else
				{
					pObstacle->GimmickUI(false, nIdx);
				}
			}
			else
			{
				pObstacle->GimmickUI(false, nIdx);
			}
		}
		else if (type == CPlayer::TYPE::TYPE_RAT)
		{
			if (pObstacle->GetRatUse() == true)
			{
				if (pObstacle->HitCircle(pPlayer, Radius) == true)
				{ // 障害物の当たり判定が通った場合
					if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH)
					{//リードのとき
						pObstacle->MultiGimmickUI(true, nIdx);
					}
					else
					{//リード以外のとき
						pObstacle->GimmickUI(true, nIdx);
					}
				}
				else
				{
					if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH)
					{//リードのとき
						pObstacle->MultiGimmickUI(false, nIdx);
						pObstacle->HitMultiCircle(pPlayer, Radius, false);
					}
					else
					{//リード以外のとき
						pObstacle->GimmickUI(false, nIdx);
					}
				}
			}
			else
			{
				pObstacle->GimmickUI(false, nIdx);
			}
		}

		// 次のオブジェクトを代入する
		pObstacle = pObstacle->GetNext();
	}
}

//===============================
// ブロックの当たり判定
//===============================
bool collision::BlockCollision(CPlayer* player, const D3DXVECTOR3& collSize)
{
	// 先頭のブロックの情報を取得する
	CBlock* pBlock = CBlockManager::Get()->GetTop();
	bool bJump = false;			// ジャンプ状況

	while (pBlock != nullptr)
	{ // ブロックが NULL の場合

		switch (pBlock->GetCollision())
		{
		case CBlock::COLLISION_SQUARE:

			// 矩形の当たり判定
			BlockRectangleCollision(*pBlock, player, collSize, &bJump);

			break;

		case CBlock::COLLISION_CIRCLE:

			// 円の当たり判定
			BlockCircleCollision(*pBlock, player, collSize.x, collSize.y, &bJump);

			break;
		}

		// 次のブロックの情報を取得する
		pBlock = pBlock->GetNext();
	}

	// ジャンプ状況を返す
	return bJump;
}

//===============================
// ブロックの矩形の当たり判定
//===============================
void collision::BlockRectangleCollision(const CBlock& block, CPlayer* player, const D3DXVECTOR3& collSize, bool* pJump)
{
	// 当たり判定の変数を宣言
	SCollision collision = {};

	// ブロックの当たり判定に必要な変数を宣言
	D3DXVECTOR3 pos = player->GetPos();										// 位置
	D3DXVECTOR3 posOld = player->GetPosOld();								// 前回の位置
	D3DXVECTOR3 move = player->GetMove();									// 移動量
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// 最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// 最小値

	// 六面体の当たり判定
	collision = HexahedronClush
	(
		&pos,
		block.GetPos(),
		posOld,
		block.GetPosOld(),
		vtxMin,
		block.GetVtxMin(),
		vtxMax,
		block.GetVtxMax()
	);

	if (collision.bTop == true)
	{ // 上に乗った場合

		// 重力を0.0fにする
		move.y = 0.0f;

		// trueにする
		*pJump = true;
	}

	// 位置と移動量を適用する
	player->SetPos(pos);		// 位置
	player->SetMove(move);		// 移動量
}

//===============================
// ブロックの円形の当たり判定
//===============================
void collision::BlockCircleCollision(CBlock& block, CPlayer* player, const float fRadius, const float fHeight, bool* pJump)
{
	// 位置と前回の位置と移動量を取得する
	D3DXVECTOR3 pos = player->GetPos();
	D3DXVECTOR3 posOld = player->GetPosOld();
	D3DXVECTOR3 move = player->GetMove();

	if (pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y &&
		pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
	{ // ブロックと衝突した場合

		if (useful::CylinderInner(pos, block.GetPos(), block.GetFileData().fRadius + fRadius) == true)
		{ // 円柱の内側にいた場合

			if (posOld.y >= block.GetPos().y + block.GetFileData().vtxMax.y &&
				pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y)
			{ // 上からの当たり判定

				// 位置を設定する
				pos.y = block.GetPos().y + block.GetFileData().vtxMax.y;

				// 移動量を0にする
				move.y = 0.0f;

				// trueにする
				*pJump = true;
			}
			else if (posOld.y + fHeight <= block.GetPos().y + block.GetFileData().vtxMin.y &&
				pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
			{ // 下からの当たり判定

				// 位置を設定する
				pos.y = block.GetPos().y + block.GetFileData().vtxMin.y - fHeight;
			}
		}

		// 円柱の当たり判定処理
		useful::CylinderCollision(&pos, block.GetPos(), block.GetFileData().fRadius + fRadius);
	}

	// 位置と移動量を適用する
	player->SetPos(pos);
	player->SetMove(move);
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
//===============================
//壁との当たり判定
//===============================
void collision::WallCollision(CPlayer* player, const D3DXVECTOR3& collSize)
{
	// 位置と前回の位置と移動量を取得する
	D3DXVECTOR3 pos = player->GetPos();
	D3DXVECTOR3 posOld = player->GetPosOld();
	D3DXVECTOR3 move = player->GetMove();

	if (pos.x + collSize.x >= MAP_SIZE.x)
	{ // 右から出そうになった場合

		// 位置を設定する
		pos.x = MAP_SIZE.x - collSize.x;

		// 移動量を設定する
		move.x = 0.0f;
	}

	if (pos.x - collSize.x <= -MAP_SIZE.x)
	{ // 左から出そうになった場合

		// 位置を設定する
		pos.x = -MAP_SIZE.x + collSize.x;

		// 移動量を設定する
		move.x = 0.0f;
	}

	if (pos.z + collSize.z >= MAP_SIZE.z)
	{ // 奥から出そうになった場合

		// 位置を設定する
		pos.z = MAP_SIZE.z - collSize.z;

		// 移動量を設定する
		move.z = 0.0f;
	}

	if (pos.z - collSize.z <= -MAP_SIZE.z)
	{ // 手前から出そうになった場合

		// 位置を設定する
		pos.z = -MAP_SIZE.z + collSize.z;

		// 移動量を設定する
		move.z = 0.0f;
	}

	// 位置と移動量を適用する
	player->SetPos(pos);
	player->SetMove(move);
}

//======================
// ネコとアイテムとの当たり判定
//======================
void collision::ItemCollision(CPlayer& pPlayer, const int nHave)
{
	// 処理に使う変数を宣言
	CItem* pItem = CItemManager::Get()->GetTop();	// 最初のアイテムの情報を取得する
	CItem* pItemNext;								// 次のアイテム
	D3DXVECTOR3 pos = pPlayer.GetPos();				// 位置
	D3DXVECTOR3 Max = COLLISION_CAT_SIZE;													// 最大値
	D3DXVECTOR3 Min = D3DXVECTOR3(-COLLISION_CAT_SIZE.x, 0.0f, -COLLISION_CAT_SIZE.z);		// 最小値

	while (pItem != nullptr)
	{ // アイテムが NULL じゃない場合

		// 次のアイテムを取得する
		pItemNext = pItem->GetNext();

		if (nHave < 2 &&
			useful::RectangleCollisionXY(pos, pItem->GetPos(), Max, pItem->GetFileData().vtxMax, Min, pItem->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(pos, pItem->GetPos(), Max, pItem->GetFileData().vtxMax, Min, pItem->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(pos, pItem->GetPos(), Max, pItem->GetFileData().vtxMax, Min, pItem->GetFileData().vtxMin) == true)
		{ // 判定内に入った場合

			// アイテムの取得処理
			pPlayer.GetItem(pItem->GetType());

			// 終了処理
			pItem->Uninit();

			// アイテム出現してない状態にする
			CGame::SetItemSpawn(false);
		}

		// 次のアイテムを設定する
		pItem = pItemNext;
	}
}

//======================
// 六面体の当たり判定
//======================
bool collision::HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X軸の判定に入れる場合

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // 右にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // 左にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z軸の判定に入れる場合

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // 奥にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // 手前にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y軸の判定に入れる場合

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // 上にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // 下にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//======================
// 六面体の当たり判定(どの面に乗ったかの判定付き)
//======================
collision::SCollision collision::HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	// 当たり判定の変数を宣言
	SCollision collision = { false,false,false,false,false,false };

	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X軸の判定に入れる場合

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // 右にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// 右の当たり判定を true にする
			collision.bRight = true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // 左にぶつかった場合

			// 位置を設定する
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// 左の当たり判定を true にする
			collision.bLeft = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z軸の判定に入れる場合

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // 奥にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// 奥の当たり判定を true にする
			collision.bFar = true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // 手前にぶつかった場合

			// 位置を設定する
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// 手前の当たり判定を true にする
			collision.bNear = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y軸の判定に入れる場合

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // 上にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// 上の当たり判定を true にする
			collision.bTop = true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // 下にぶつかった場合

			// 位置を設定する
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// 下の当たり判定を true にする
			collision.bBottom = true;
		}
	}

	// 当たり判定の変数を返す
	return collision;
}