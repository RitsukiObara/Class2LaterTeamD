//===================================
//
// �����蔻��w�b�_�[[collision.h]
// Author ��������
//
//===================================
#ifndef _COLLISION_H_			//���̃}�N����`������Ă��Ȃ�������
#define _COLLISION_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"
#include "obstacle.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CRat;			// �l�Y�~
class CCat;			// �l�R
class CBlock;		// �u���b�N

//-----------------------------------
// ���O���(�����蔻��)
//-----------------------------------
namespace collision
{
	// �ۉe�̓����蔻��
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// �ۉe�̓����蔻��

	// ��Q���̓����蔻��
	void ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);			// ��Q���̏Փ˔���
	void ObstacleHit(CRat* pRat, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);						// ��Q���̓����蔻��
	void ObstacleAction(CRat* pRat, const float Radius, const CObstacle::COLLTYPE type);					// ��Q���̋N������

	// ��������\��̃u���b�N�̓����蔻��
	void BlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth);		// �u���b�N�̓����蔻��
	void BlockRectangleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);	// �u���b�N�̋�`�̓����蔻��
	void BlockCircleCollision(CBlock& block, D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fRadius, const float fHeight);	// �u���b�N�̉~�`�̓����蔻��

	// �N���n�ʂ̓����蔻��
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// �N���n�ʂ͈̔͊O�̓����蔻��

	//�ǂƂ̓����蔻��
	D3DXVECTOR3 WallCollision(D3DXVECTOR3& objVec1, D3DXVECTOR3& objVec2);

	// �A�C�e���Ƃ̓����蔻��
	void ItemCollision(CCat& pCat);		// �l�R�ƃA�C�e���Ƃ̓����蔻��

	// �ėp�I�ȓ����蔻��
	bool HexahedronCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// �Z�ʑ̂̓����蔻��
}

#endif