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
#include "obstacle.h"
#include "obstacle_manager.h"
#include "useful.h"

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
void collision::ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		switch (pObstacle->GetType())
		{
		case CObstacle::TYPE::TYPE_HAIRBALL:		// �{

			// �{�̏Փ˔���
			HairBallCollision(*pObstacle, pos, fWidth, fHeight);

			break;

		default:

			// ��O���������Ă����Ȃ�����assert����

			break;
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacle->GetNext();
	}
}

//===============================
// �{�̏Փˏ���
//===============================
void collision::HairBallCollision(CObstacle& obstacle, D3DXVECTOR3& pos, const float fWidth, const float fHeight)
{
	if (pos.y <= obstacle.GetPos().y + obstacle.GetFileData().vtxMax.y || 
		pos.y + fHeight >= obstacle.GetPos().y + obstacle.GetFileData().vtxMin.y)
	{ // �{�ƏՓ˂����ꍇ

		// �~���̓����蔻�菈��
		useful::CylinderCollision(&pos, obstacle.GetPos(), obstacle.GetFileData().vtxMax.x + fWidth);
	}
}

//===============================
// ��Q���̓����蔻��
//===============================
void collision::ObstacleHit(CRat* pRat, const float fWidth, const float fHeight, const float fDepth)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	D3DXVECTOR3 pos = pRat->GetPos();			// �ʒu���擾����

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (pObstacle->Hit(pos, fWidth, fHeight, fDepth) == true)
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

			case CObstacle::TYPE::TYPE_HAIRBALL:

				// ���ɂȂ�

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
// ��Q���̋�`�����蔻��
//===============================
void collision::ObstacleRectCollision(D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	bool bHit = false;		// ����������

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
			pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight &&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth&&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
		{ // X���̔���ɓ����ꍇ

			if (/*pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMax.x <= posOld.x - fWidth &&*/
				pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth)
			{ // �E�ɂԂ������ꍇ

			  // �ʒu��ݒ肷��
				//pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMax.x + (fWidth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// ����������Ԃɂ���
			}
			else if (/*pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMin.x >= posOld.x + fWidth &&*/
				pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth)
			{ // ���ɂԂ������ꍇ

			  // �ʒu��ݒ肷��
				//pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMin.x - (fWidth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// ����������Ԃɂ���
			}
		}

		if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
			pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
			pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
			pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
		{ // Z���̔���ɓ����ꍇ

			if (/*pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMax.z <= posOld.z - fDepth &&*/
				pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth)
			{ // ���ɂԂ������ꍇ

			  // �ʒu��ݒ肷��
				//pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMax.z + (fDepth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// ����������Ԃɂ���
			}
			else if (/*pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMin.z >= posOld.z + fDepth &&*/
				pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
			{ // ��O�ɂԂ������ꍇ

			  // �ʒu��ݒ肷��
				//pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMin.z - (fDepth + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// ����������Ԃɂ���
			}
		}

		if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
			pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z &&
			pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
		{ // Y���̔���ɓ����ꍇ

			if (/*pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMax.y <= posOld.y &&*/
				pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y)
			{ // ��ɂԂ������ꍇ

			  // �ʒu��ݒ肷��
				//pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;
				bHit = true;		// ����������Ԃɂ���
			}
			else if (/*pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMin.y >= posOld.y + fHeight &&*/
				pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
			{ // ���ɂԂ������ꍇ

			  // �ʒu��ݒ肷��
				//pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMin.y - (fHeight + COLLISION_ADD_DIFF_LENGTH);
				bHit = true;		// ����������Ԃɂ���
			}
		}

		if (bHit == true)
		{//�������Ă���

			// ��Q���̏I������
			pObstacle->Uninit();
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacle->GetNext();
		bHit = false;		// �������ĂȂ���Ԃɂ���

	}
}

//===============================
// �u���b�N�̓����蔻��
//===============================
void collision::BlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	//if (pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
	//	pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight &&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth&&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // X���̔���ɓ����ꍇ

	//	if (pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMax.x <= posOld.x - fWidth &&
	//		pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth)
	//	{ // �E�ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMax.x + (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (pObstacle->GetPosOld().x + pObstacle->GetFileData().vtxMin.x >= posOld.x + fWidth &&
	//		pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth)
	//	{ // ���ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.x = pObstacle->GetPos().x + +pObstacle->GetFileData().vtxMin.x - (fWidth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y &&
	//	pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
	//{ // Z���̔���ɓ����ꍇ

	//	if (pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMax.z <= posOld.z - fDepth &&
	//		pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z - fDepth)
	//	{ // ���ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMax.z + (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//	else if (pObstacle->GetPosOld().z + pObstacle->GetFileData().vtxMin.z >= posOld.z + fDepth &&
	//		pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
	//	{ // ��O�ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.z = pObstacle->GetPos().z + +pObstacle->GetFileData().vtxMin.z - (fDepth + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}

	//if (pObstacle->GetPos().x + pObstacle->GetFileData().vtxMax.x >= pos.x - fWidth &&
	//	pObstacle->GetPos().x + pObstacle->GetFileData().vtxMin.x <= pos.x + fWidth &&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMax.z >= pos.z &&
	//	pObstacle->GetPos().z + pObstacle->GetFileData().vtxMin.z <= pos.z + fDepth)
	//{ // Y���̔���ɓ����ꍇ

	//	if (pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMax.y <= posOld.y &&
	//		pObstacle->GetPos().y + pObstacle->GetFileData().vtxMax.y >= pos.y)
	//	{ // ��ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;
	//	}
	//	else if (pObstacle->GetPosOld().y + pObstacle->GetFileData().vtxMin.y >= posOld.y + fHeight &&
	//		pObstacle->GetPos().y + pObstacle->GetFileData().vtxMin.y <= pos.y + fHeight)
	//	{ // ���ɂԂ������ꍇ

	//		// �ʒu��ݒ肷��
	//		pos.y = pObstacle->GetPos().y + +pObstacle->GetFileData().vtxMin.y - (fHeight + COLLISION_ADD_DIFF_LENGTH);
	//	}
	//}
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