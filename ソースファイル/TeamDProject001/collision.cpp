//===========================================
//
// �����蔻��̃��C������[collision.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
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

#include "map.h"
#include "wall.h"
#include "ground.h"
#include <cmath>
#include "objectX.h"
//===============================
// �}�N����`
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// �͂��Ȍ덷�𖄂߂邽�߂̃}�N����`(�˂�������h�~)

//===============================
// �ۉe�̓����蔻�菈��
//===============================
void collision::ShadowCollision(const D3DXVECTOR3& pos, int nIdx)
{
	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = CShadowCircle::GetShadow(nIdx);	// �e�̃|�C���^
	D3DXVECTOR3 posPlayer = pos;				// �v���C���[�̈ʒu
	D3DXVECTOR3 posCand = NONE_D3DXVECTOR3;		// �e�̈ʒu�̌��

	if (pShadow != nullptr)
	{ // �e�̃|�C���^�� NULL ����Ȃ������ꍇ

		// �e�̈ʒu���擾����
		posCand = D3DXVECTOR3(posPlayer.x, pShadow->GetPos().y, posPlayer.z);

		// �ʒu��ݒ肷��
		pShadow->SetPos(posCand);
	}
}

//===============================
// ��Q���̓����蔻��
//===============================
void collision::ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		// �����蔻�菈��
		if (pObstacle->Collision(pos, posOld, fWidth, fHeight, fDepth, type) == true)
		{
			switch (pObstacle->GetType())
			{
			case CObstacle::TYPE::TYPE_HONEY:		// �I��

				// ���ɖ���

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

			default:			// ��L�ȊO

				// ��~
				assert(false);

				break;
			}
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacle->GetNext();
	}
}

//===============================
// ��Q���̓����蔻��
//===============================
void collision::ObstacleHit(CRat* pRat, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	D3DXVECTOR3 pos = pRat->GetPos();			// �ʒu���擾����

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (pObstacle->Hit(pos, fWidth, fHeight, fDepth, type) == true)
		{ // ��Q���̓����蔻�肪�ʂ����ꍇ

			switch (pObstacle->GetType())
			{
			case CObstacle::TYPE_HONEY:

				// �ړ��ʂ�ݒ肷��
				pRat->SetSpeed(pRat->GetSpeed() * 0.3f);

				break;

			case CObstacle::TYPE_SLIME:

				// �ړ��ʂ�ݒ肷��
				pRat->SetSpeed(pRat->GetSpeed() * 0.7f);

				break;

			case CObstacle::TYPE_HAIRBALL:

				// �q�b�g����
				pRat->Hit();

				break;

			case CObstacle::TYPE_FLOWERVASE:

				// ���ɂȂ�

				break;

			case CObstacle::TYPE_PETBOTTLE:

				// �q�b�g����
				pRat->Hit();

				break;

			case CObstacle::TYPE_TOYCAR:

				break;

			default:

				// ��~
				assert(false);

				break;
			}
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacle->GetNext();
	}
}

//===============================
// �u���b�N�̓����蔻��
//===============================
void collision::BlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// �擪�̃u���b�N�̏����擾����
	CBlock* pBlock = CBlockManager::Get()->GetTop();

	while (pBlock != nullptr)
	{ // �u���b�N�� NULL �̏ꍇ	
		if (pBlock->GetCollision() == CBlock::COLLISION_SQUARE)
		{ // ��`�̓����蔻��̏ꍇ

			// ��`�̓����蔻��
			BlockRectangleCollision(*pBlock, pos, posOld);
		}
		else
		{ // ��L�ȊO

			// �~�̓����蔻��
			BlockCircleCollision(*pBlock, pos, fWidth, fHeight);
		}

		// ���̃u���b�N�̏����擾����
		pBlock = pBlock->GetNext();
	}
}
//===============================
// �u���b�N�̋�`�̓����蔻��
//===============================
void collision::BlockRectangleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	bool bPosbool = false, bPosOldbool = false, bVecbool = false, bVecboolOld = false;

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

		//�x�N�g����
		vecLine = vec[nCnt2] - vec[nCnt];

		vecMove = pos - posOld;

		vecToPos = pos - vec[nCnt];


		//�e�x�N�g���̎Z�o�ƌ�������
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

		//��������
		if (bPosbool != bPosOldbool&&bVecbool != bVecboolOld)
		{
			//�x�N�g���̐��K��
			float fmagnitude = sqrtf(vecLine.x*vecLine.x + vecLine.y*vecLine.y + vecLine.z*vecLine.z);

			D3DXVECTOR3 NorVecLine;
			if (fmagnitude != 0)
			{
				float fMove = sqrtf(powf(vecMove.x, 2) + powf(vecMove.z, 2));

				//�W����
				float sum = std::abs(vecLine.x) + std::abs(vecLine.y) + std::abs(vecLine.z);
				if (sum != 0.0f)
				{
					NorVecLine.x = /*std::abs*/(vecLine.x / sum);
					NorVecLine.y = /*std::abs*/(vecLine.y / sum);
					NorVecLine.z = /*std::abs*/(vecLine.z / sum);
				}

				//vecMove��vecLine�ւ̓��ˊp��90���ǂ���ɌX���Ă��邩�ňړ��x�N�g���ɐ�����^����
				// �x�N�g���̓��ς��v�Z����֐�
				float fdotProduct = vecLine.x * vecMove.x + vecLine.z * vecMove.z;

				//// �x�N�g���̑傫�����v�Z����֐�
				//float fmagnitudeLine = sqrt(vecLine.x * vecLine.x + vecLine.z * vecLine.z);
				//float fmagnitudeMove= sqrt(vecMove.x * vecMove.x + vecMove.z * vecMove.z);
				//
				//// �x�N�g��A�ƃx�N�g��B�̂Ȃ��p���v�Z�i���W�A���j
				//float angleRad = acos(fdotProduct / (fmagnitudeLine * fmagnitudeMove));

				// ����Əo��
				if (fdotProduct > 0.01f)
				{
					NorVecLine *= 1;
				}
				else if (fdotProduct < -0.01f)
				{
					NorVecLine *= -1;
				}
				else
				{
					NorVecLine *= 0;
				}

				D3DXVECTOR3 move = D3DXVECTOR3(fMove*NorVecLine.x, fMove*NorVecLine.y, fMove*NorVecLine.z);

				D3DXVECTOR3 SetPos = posOld + move;


				////�l���ђʖh�~�̗�O����
				//if (SetPos.x>vec[0].x && SetPos.x<vec[1].x && SetPos.z < vec[1].z && SetPos.z > vec[2].z)
				//{
				//	SetPos = posOld;
				//}

				pos = SetPos;
			}
			else
			{
				pos = posOld;
			}
		}
	}
	//if (block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y &&
	//	block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight &&
	//	block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z - fDepth&&
	//	block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // X���̔���ɓ����ꍇ

	//	if (block.GetPosOld().x + block.GetFileData().vtxMax.x <= posOld.x - fWidth &&
	//		block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth)
	//	{ // �E�ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.x = block.GetPos().x + block.GetFileData().vtxMax.x + (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (block.GetPosOld().x + block.GetFileData().vtxMin.x >= posOld.x + fWidth &&
	//		block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth)
	//	{ // ���ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.x = block.GetPos().x + block.GetFileData().vtxMin.x - (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y &&
	//	block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight)
	//{ // Z���̔���ɓ����ꍇ

	//	if (block.GetPosOld().z + block.GetFileData().vtxMax.z <= posOld.z - fDepth &&
	//		block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z - fDepth)
	//	{ // ���ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.z = block.GetPos().z + block.GetFileData().vtxMax.z + (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (block.GetPosOld().z + block.GetFileData().vtxMin.z >= posOld.z + fDepth &&
	//		block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	//	{ // ��O�ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.z = block.GetPos().z + block.GetFileData().vtxMin.z - (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (block.GetPos().x + block.GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	block.GetPos().x + block.GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	block.GetPos().z + block.GetFileData().vtxMax.z >= pos.z &&
	//	block.GetPos().z + block.GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // Y���̔���ɓ����ꍇ

	//	if (block.GetPosOld().y + block.GetFileData().vtxMax.y <= posOld.y &&
	//		block.GetPos().y + block.GetFileData().vtxMax.y >= pos.y)
	//	{ // ��ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.y = block.GetPos().y + block.GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;
	//	}
	//	else if (block.GetPosOld().y + block.GetFileData().vtxMin.y >= posOld.y + fHeight &&
	//		block.GetPos().y + block.GetFileData().vtxMin.y <= pos.y + fHeight)
	//	{ // ���ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.y = block.GetPos().y + block.GetFileData().vtxMin.y - (fHeight + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}
}

//===============================
// �u���b�N�̉~�`�̓����蔻��
//===============================
void collision::BlockCircleCollision(CBlock& block, D3DXVECTOR3& pos, const float fRadius, const float fHeight)
{
	if (pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y ||
		pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
	{ // �{�ƏՓ˂����ꍇ

		// �~���̓����蔻�菈��
		useful::CylinderCollision(&pos, block.GetPos(), block.GetFileData().fRadius + fRadius);
	}
}

//===============================
// �N���n�ʂ͈̔͊O�̓����蔻��
//===============================
bool collision::ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth)
{
	// ���[�J���ϐ��錾
	CElevation* pElev = CElevationManager::Get()->GetTop();		// �擪�̋N���n�ʂ��擾����
	bool bCollision = false;									// �����蔻���

	while (pElev != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (pElev->GetPos().z + (pElev->GetSize().z * 0.5f) >= pPos->z &&
			pElev->GetPos().z - (pElev->GetSize().z * 0.5f) <= pPos->z &&
			pElev->GetPos().y > pPos->y)
		{ // �N���n�ʂ�艺�ɂ���ꍇ

			if (posOld.x + fWidth <= pElev->GetPos().x - (pElev->GetSize().x * 0.5f) &&
				pPos->x + fWidth >= pElev->GetPos().x - (pElev->GetSize().x * 0.5f))
			{ // ���̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x - (pElev->GetSize().x * 0.5f) - fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
			else if (posOld.x - fWidth >= pElev->GetPos().x + (pElev->GetSize().x * 0.5f) &&
				pPos->x - fWidth <= pElev->GetPos().x + (pElev->GetSize().x * 0.5f))
			{ // �E�̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x + (pElev->GetSize().x * 0.5f) + fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
		}

		// ���̃I�u�W�F�N�g��������
		pElev = pElev->GetNext();
	}

	// �����蔻��󋵂�Ԃ�
	return bCollision;
}
//===============================
//�ǂƂ̓����蔻��i�ǂ���L�j
//===============================
D3DXVECTOR3 collision::WallCollision(D3DXVECTOR3& objVec1, D3DXVECTOR3& objVec2)
{
	bool bPosbool = false, bPosOldbool = false, bVecbool = false, bVecboolOld = false;

	D3DXVECTOR3 vecLine, vecMove, vecToPos, vecToPosOld, posOldToVec, posOldToVecOld;

	//CWall* pWall = CMap::GetWall();

	D3DXVECTOR3 vec[4];

	//�ǂ̒��_�i�x�^�ł��j
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

		//�x�N�g����
		vecLine = vec[nCnt2] - vec[nCnt];

		vecMove = objVec2 - objVec1;

		vecToPos = objVec2 - vec[nCnt];


		//�e�x�N�g���̎Z�o�ƌ�������
		if (0 <= (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
		{
			bPosbool = true;
		}
		else if (0 > (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
		{
			bPosbool = false;
		}

		vecToPosOld = objVec1 - vec[nCnt];

		if (0 <= (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
		{
			bPosOldbool = true;
		}
		else if (0 > (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
		{
			bPosOldbool = false;
		}

		posOldToVec = vec[nCnt2] - objVec1;

		if (0 <= (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
		{
			bVecbool = true;
		}
		else if (0 > (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
		{
			bVecbool = false;
		}

		posOldToVecOld = vec[nCnt] - objVec1;

		if (0 <= (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
		{
			bVecboolOld = true;
		}
		else if (0 > (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
		{
			bVecboolOld = false;
		}

		//��������
		if (bPosbool != bPosOldbool&&bVecbool != bVecboolOld)
		{
			//�x�N�g���̐��K��
			float fmagnitude = sqrtf(vecLine.x*vecLine.x + vecLine.y*vecLine.y + vecLine.z*vecLine.z);

			D3DXVECTOR3 NorVecLine;
			if (fmagnitude != 0)
			{
				NorVecLine = D3DXVECTOR3(std::abs(vecLine.x / fmagnitude), std::abs(vecLine.y / fmagnitude), std::abs(vecLine.z / fmagnitude));

				D3DXVECTOR3 move = D3DXVECTOR3((objVec2.x - objVec1.x)*NorVecLine.x, (objVec2.y - objVec1.y)*NorVecLine.y, (objVec2.z - objVec1.z)*NorVecLine.z);

				D3DXVECTOR3 SetPos = objVec1 + move;


				//�l���ђʖh�~�̗�O����
				if (SetPos.x<vec[0].x || SetPos.x>vec[1].x || SetPos.z > vec[1].z || SetPos.z < vec[2].z)
				{
					SetPos = objVec1;
				}

				return	SetPos;
			}
			else
			{
				return objVec1;
			}
		}
	}

	return objVec2;
}
//======================
// �Z�ʑ̂̓����蔻��
//======================
bool collision::HexahedronCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	if (posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos.x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos.x + max.x)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos.z + min.z)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos.z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos.y + min.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos.y + max.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}