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
void collision::ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
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
void collision::ObstacleHit(CPlayer* pPlayer, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	CObstacle* pObstacleNext = nullptr;				// 次の障害物を取得する
	D3DXVECTOR3 pos = pPlayer->GetPos();			// 位置を取得する
	float fAngle;								// 吹き飛ぶ方向

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		// 障害物の次のポインタを取得する
		pObstacleNext = pObstacle->GetNext();

		if (pObstacle->Hit(pos, fWidth, fHeight, fDepth, type) == true)
		{ // 障害物の当たり判定が通った場合

			switch (pObstacle->GetType())
			{
			case CObstacle::TYPE_HONEY:

				// 移動量を設定する
				pPlayer->SetSpeed(pPlayer->GetSpeed() * 0.3f);

				break;

			case CObstacle::TYPE_SLIME:

				// 移動量を設定する
				pPlayer->SetSpeed(pPlayer->GetSpeed() * 0.7f);

				if (pPlayer->IsMove() == true)
				{
					CParticle::Create(pos, CParticle::TYPE_SLIME);
				}

				break;

			case CObstacle::TYPE_HAIRBALL:

				// 向きを算出する
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// ヒット処理
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_FLOWERVASE:

				// 特になし

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

			default:

				//特になし

				break;
			}
		}

		// 次のオブジェクトを代入する
		pObstacle = pObstacleNext;
	}
}

//===============================
// 障害物の起動判定
//===============================
void collision::ObstacleAction(CPlayer* pPlayer, const float Radius, const CPlayer::TYPE type)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = pPlayer->GetPos();			// 位置を取得する
	float fAngle;								// 吹き飛ぶ方向

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (type == CPlayer::TYPE::TYPE_CAT)
		{
			if (pObstacle->GetCatUse() == true)
			{
				if (pObstacle->HitCircle(pos, Radius, type) == true)
				{ // 障害物の当たり判定が通った場合
					pObstacle->Action();
				}
			}
		}
		else if(type == CPlayer::TYPE::TYPE_RAT)
		{
			if (pObstacle->GetRatUse() == true)
			{
				if (pObstacle->HitCircle(pos, Radius, type) == true)
				{ // 障害物の当たり判定が通った場合
					pObstacle->Action();
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
void collision::ObstacleSearch(CPlayer* pPlayer, const float Radius, const CPlayer::TYPE type, int Player_Idx)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = pPlayer->GetPos();			// 位置を取得する
	float fAngle;								// 吹き飛ぶ方向

	while (pObstacle != nullptr)
	{ // ブロックの情報が NULL じゃない場合

		if (type == CPlayer::TYPE::TYPE_CAT)
		{
			if (pObstacle->GetCatUse() == true)
			{
				if (pObstacle->HitCircle(pos, Radius, type) == true)
				{ // 障害物の当たり判定が通った場合
					pObstacle->GimmickUI(true, Player_Idx);
				}
				else
				{
					pObstacle->GimmickUI(false, Player_Idx);
				}
			}
		}
		else if (type == CPlayer::TYPE::TYPE_RAT)
		{
			if (pObstacle->GetRatUse() == true)
			{
				if (pObstacle->HitCircle(pos, Radius, type) == true)
				{ // 障害物の当たり判定が通った場合
					pObstacle->GimmickUI(true, Player_Idx);
				}
				else
				{
					pObstacle->GimmickUI(false, Player_Idx);
				}
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
	int nCollision = 0;

	while (pBlock != nullptr)
	{ // ブロックが NULL の場合	
		if (pBlock->GetCollision() == CBlock::COLLISION_SQUARE)
		{ // 矩形の当たり判定の場合

			// 矩形の当たり判定
			BlockRectangleCollision(*pBlock, pos, posOld, nCollision);

		}
		else
		{ // 上記以外

			// 円の当たり判定
			BlockCircleCollision(*pBlock, pos, posOld, fWidth, fHeight);
		}

		// 次のブロックの情報を取得する
		pBlock = pBlock->GetNext();
	}
	while (pBlock != nullptr)
	{ // ブロックが NULL の場合	
		if (pBlock->GetCollision() == CBlock::COLLISION_SQUARE)
		{ // 矩形の当たり判定の場合

		  // 矩形の当たり判定
			BlockRectangleCollision(*pBlock, pos, posOld, nCollision);

		}

		// 次のブロックの情報を取得する
		pBlock = pBlock->GetNext();
	}
WallCollision(pos, posOld);
}
//===============================
// ブロックの矩形の当たり判定
//===============================
void collision::BlockRectangleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld,int& nCollision)
{
	bool bPosbool = false, bPosOldbool = false, bVecbool = false, bVecboolOld = false;
	bool bZeroVec = false;
	bool bInside[4] = {};

	D3DXVECTOR3 vecLine, vecMove, vecToPos, vecToPosOld, posOldToVec, posOldToVecOld;
	D3DXVECTOR3 vec[4];

	D3DXVECTOR3 objpos = block.GetPos();
	D3DXVECTOR3 rot = block.GetRot();
	D3DXVECTOR3 vtxMax = block.GetFileData().vtxMax;
	D3DXVECTOR3 vtxMin = block.GetFileData().vtxMin;

	float fAngle[4];
	fAngle[0] = atan2f(vtxMin.x, vtxMax.z);
	fAngle[1] = atan2f(vtxMax.x, vtxMax.z);
	fAngle[2] = atan2f(vtxMax.x, vtxMin.z);
	fAngle[3] = atan2f(vtxMin.x, vtxMin.z);

	float fDistance[4];
	fDistance[0] = sqrtf(powf(vtxMin.x, 2) + powf(vtxMax.z, 2));
	fDistance[1] = sqrtf(powf(vtxMax.x, 2) + powf(vtxMax.z, 2));
	fDistance[2] = sqrtf(powf(vtxMax.x, 2) + powf(vtxMin.z, 2));
	fDistance[3] = sqrtf(powf(vtxMin.x, 2) + powf(vtxMin.z, 2));

	vec[0] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[0] + rot.y)*fDistance[0], 0, objpos.z - cosf(-D3DX_PI + fAngle[0] + rot.y)* fDistance[0]);
	vec[1] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[1] + rot.y)*fDistance[1], 0, objpos.z - cosf(-D3DX_PI + fAngle[1] + rot.y)* fDistance[1]);
	vec[2] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[2] + rot.y)*fDistance[2], 0, objpos.z - cosf(-D3DX_PI + fAngle[2] + rot.y)* fDistance[2]);
	vec[3] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[3] + rot.y)*fDistance[3], 0, objpos.z - cosf(-D3DX_PI + fAngle[3] + rot.y)* fDistance[3]);



	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		int nCnt2 = nCnt + 1;

		if (nCnt2 >= 4)
		{
			nCnt2 = 0;
		}

		//ベクトル化
		vecLine = vec[nCnt2] - vec[nCnt];

		vecMove = pos - posOld;

		vecToPos = pos - vec[nCnt];


		//各ベクトルの算出と交差判定
		if (0 < (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
		{
			bPosbool = true;
		}
		else if (0 > (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
		{
			bPosbool = false;
		}
		

		vecToPosOld = posOld - vec[nCnt];

		if (0 < (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
		{
			bPosOldbool = true;
		}
		else if (0 > (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
		{
			bPosOldbool = false;
		}

		posOldToVec = vec[nCnt2] - posOld;

		if (0 < (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
		{
			bVecbool = true;
		}
		else if (0 > (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
		{
			bVecbool = false;
		}
		

		posOldToVecOld = vec[nCnt] - posOld;

		if (0 < (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
		{
			bVecboolOld = true;
		}
		else if (0 > (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
		{
			bVecboolOld = false;
		}

		bInside[nCnt] = bPosbool;

		if (bPosbool != bPosOldbool&&bVecbool != bVecboolOld&&objpos.y + vtxMax.y > posOld.y)
		{
			//ベクトルの正規化
			float fmagnitude = sqrtf(vecLine.x*vecLine.x + vecLine.y*vecLine.y + vecLine.z*vecLine.z);


			D3DXVECTOR3 NorVecLine;
			if (fmagnitude != 0)
			{
				float fMove = sqrtf(powf(vecMove.x, 2) + powf(vecMove.z, 2));

				//標準化
				float sum = std::abs(vecLine.x) + std::abs(vecLine.y) + std::abs(vecLine.z);
				if (sum != 0.0f)
				{
					NorVecLine.x = /*std::abs*/(vecLine.x / sum);
					NorVecLine.y = /*std::abs*/(vecLine.y / sum);
					NorVecLine.z = /*std::abs*/(vecLine.z / sum);
				}

				//vecMoveのvecLineへの入射角が90よりどちらに傾いているかで移動ベクトルに正負を与える
				// ベクトルの内積を計算する関数
				float fdotProduct = vecLine.x * vecMove.x + vecLine.z * vecMove.z;

				//// ベクトルの大きさを計算する関数
				//float fmagnitudeLine = sqrt(vecLine.x * vecLine.x + vecLine.z * vecLine.z);
				//float fmagnitudeMove= sqrt(vecMove.x * vecMove.x + vecMove.z * vecMove.z);
				//
				//// ベクトルAとベクトルBのなす角を計算（ラジアン）
				//float angleRad = acos(fdotProduct / (fmagnitudeLine * fmagnitudeMove));
				float fLength = D3DXVec3Length(&vecToPosOld);
				float fLength2 = D3DXVec3Length(&(posOld - vec[nCnt2]));
				// 判定と出力
				if (nCollision>=2)
				{
					pos = posOld;
				}
				else if (fLength > 20.0f&&fLength2>20.0f)
				{
					if (fdotProduct > 0.005)
					{
						NorVecLine *= 1;
						
					}
					else if (fdotProduct < -0.005)
					{
						NorVecLine *= -1;
						

					}
					else
					{
						NorVecLine *= 0;
					}
					D3DXVECTOR3 move = D3DXVECTOR3(fMove*NorVecLine.x, pos.y, fMove*NorVecLine.z);

					D3DXVECTOR3 SetPos = D3DXVECTOR3(posOld.x + move.x, pos.y, posOld.z + move.z);

					pos = SetPos;
				}
				else
				{
					if (fdotProduct > 0.0f)
					{
						NorVecLine *= 1;
						

					}
					else
					{
						NorVecLine *= -0.5;
						

					}
					D3DXVECTOR3 move = D3DXVECTOR3(fMove*NorVecLine.x, pos.y, fMove*NorVecLine.z);

					D3DXVECTOR3 SetPos = D3DXVECTOR3(posOld.x + move.x, pos.y, posOld.z + move.z);

					pos = SetPos;
				}

				
			}
		
		}
	}
	//上からの判定
	if (bInside[0] == bInside[1] && bInside[1] == bInside[2] && bInside[2] == bInside[3] && objpos.y + vtxMax.y > pos.y&&objpos.y + vtxMax.y <= posOld.y)
	{
		pos .y= objpos.y + vtxMax.y;
	}
	if (bInside[0] == bInside[1] && bInside[1] == bInside[2] && bInside[2] == bInside[3]&& objpos.y + vtxMax.y > posOld.y)
	{
		nCollision++;
	}


	//if (block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y &&
	//	block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight &&
	//	block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z - fDepth&&
	//	block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // X軸の判定に入れる場合

	//	if (block.GetPosOld().x + block.GetFileData().vtxMax.x <= posOld.x - fWidth &&
	//		block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth)
	//	{ // 右にぶつかった場合

	//		// 位置を設定する
	//		pos.x = block.GetPos().x + block.GetFileData().vtxMax.x + (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (block.GetPosOld().x + block.GetFileData().vtxMin.x >= posOld.x + fWidth &&
	//		block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth)
	//	{ // 左にぶつかった場合

	//		// 位置を設定する
	//		pos.x = block.GetPos().x + block.GetFileData().vtxMin.x - (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y &&
	//	block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight)
	//{ // Z軸の判定に入れる場合

	//	if (block.GetPosOld().z + block.GetFileData().vtxMax.z <= posOld.z - fDepth &&
	//		block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z - fDepth)
	//	{ // 奥にぶつかった場合

	//		// 位置を設定する
	//		pos.z = block.GetPos().z + block.GetFileData().vtxMax.z + (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (block.GetPosOld().z + block.GetFileData().vtxMin.z >= posOld.z + fDepth &&
	//		block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	//	{ // 手前にぶつかった場合

	//		// 位置を設定する
	//		pos.z = block.GetPos().z + block.GetFileData().vtxMin.z - (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z &&
	//	block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // Y軸の判定に入れる場合

	//	if (block.GetPosOld().y + block.GetFileData().vtxMax.y <= posOld.y &&
	//		block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y)
	//	{ // 上にぶつかった場合

	//		// 位置を設定する
	//		pos.y = block.GetPos().y + block.GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;
	//	}
	//	else if (block.GetPosOld().y + block.GetFileData().vtxMin.y >= posOld.y + fHeight &&
	//		block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight)
	//	{ // 下にぶつかった場合

	//		// 位置を設定する
	//		pos.y = block.GetPos().y + block.GetFileData().vtxMin.y - (fHeight + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}
}

//===============================
// ブロックの円形の当たり判定
//===============================
void collision::BlockCircleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fRadius, const float fHeight)
{
	if (pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y &&
		pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
	{ // 毬と衝突した場合

		if (useful::CylinderInner(pos, block.GetPos(), block.GetFileData().fRadius + fRadius) == true)
		{ // 円柱の内側にいた場合

			if (posOld.y >= block.GetPos().y + block.GetFileData().vtxMax.y &&
				pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y)
			{ // 上からの当たり判定

				// 位置を設定する
				pos.y = block.GetPos().y + block.GetFileData().vtxMax.y;
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
//壁との当たり判定（壁ずり有）
//===============================
void collision::WallCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	bool bPosbool = false, bPosOldbool = false, bVecbool = false, bVecboolOld = false;

	D3DXVECTOR3 vecLine, vecMove, vecToPos, vecToPosOld, posOldToVec, posOldToVecOld;

	//CWall* pWall = CMap::GetWall();

	D3DXVECTOR3 vec[4];

	//壁の頂点（ベタ打ち）
	vec[0] = D3DXVECTOR3(-MAP_SIZE.x, 0, MAP_SIZE.z);
	vec[1] = D3DXVECTOR3(MAP_SIZE.x, 0, MAP_SIZE.z);
	vec[2] = D3DXVECTOR3(MAP_SIZE.x, 0, -MAP_SIZE.z);
	vec[3] = D3DXVECTOR3(-MAP_SIZE.x, 0, -MAP_SIZE.z);

	for (int nCnt = 0; nCnt < WALL_NUM; nCnt++)
	{
		int nCnt2 = nCnt + 1;

		if (nCnt2 >= WALL_NUM)
		{
			nCnt2 = 0;
		}

		//ベクトル化
		vecLine = vec[nCnt2] - vec[nCnt];

		vecMove = pos - posOld;

		vecToPos = pos - vec[nCnt];


		//各ベクトルの算出と交差判定
		if (0 <= (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
		{
			bPosbool = true;
		}
		else if (0 > (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
		{
			bPosbool = false;
		}

		vecToPosOld = posOld - vec[nCnt];

		if (0 <= (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
		{
			bPosOldbool = true;
		}
		else if (0 > (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
		{
			bPosOldbool = false;
		}

		posOldToVec = vec[nCnt2] - posOld;

		if (0 <= (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
		{
			bVecbool = true;
		}
		else if (0 > (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
		{
			bVecbool = false;
		}

		posOldToVecOld = vec[nCnt] - posOld;

		if (0 <= (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
		{
			bVecboolOld = true;
		}
		else if (0 > (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
		{
			bVecboolOld = false;
		}

		//交差判定
		if (bPosbool != bPosOldbool&&bVecbool != bVecboolOld)
		{
			//ベクトルの正規化
			float fmagnitude = sqrtf(vecLine.x*vecLine.x + vecLine.y*vecLine.y + vecLine.z*vecLine.z);

			D3DXVECTOR3 NorVecLine;
			if (fmagnitude != 0)
			{
				NorVecLine = D3DXVECTOR3(std::abs(vecLine.x / fmagnitude), std::abs(vecLine.y / fmagnitude), std::abs(vecLine.z / fmagnitude));

				D3DXVECTOR3 move = D3DXVECTOR3((pos.x - posOld.x)*NorVecLine.x, (pos.y - posOld.y)*NorVecLine.y, (pos.z - posOld.z)*NorVecLine.z);

				D3DXVECTOR3 SetPos = posOld + move;


				//四隅貫通防止の例外処理
				if (SetPos.x<vec[0].x || SetPos.x>vec[1].x || SetPos.z > vec[1].z || SetPos.z < vec[2].z)
				{
					SetPos = posOld;
				}

				SetPos.y = pos.y;

				pos=SetPos;
			}
			else
			{
				pos= posOld;
			}
		}
	}
	//四隅貫通防止の例外処理
	if (pos.x<vec[0].x || pos.x>vec[1].x || pos.z > vec[1].z || pos.z < vec[2].z)
	{
		pos = posOld;
	}
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
		}

		// 次のアイテムを設定する
		pItem = pItemNext;
	}
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