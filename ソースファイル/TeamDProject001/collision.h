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

//-----------------------------------
// ���O���(�����蔻��)
//-----------------------------------
namespace collision
{
	// �ۉe�̓����蔻��
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// �ۉe�̓����蔻��

	// ��Q���̓����蔻��
	void ObstacleCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth);			// ��Q���̓����蔻��

	// ��Q���̋�`�̓����蔻��
	void ObstacleRectCollision(D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);			// ��Q���̓����蔻��

	// �N���n�ʂ̓����蔻��
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// �N���n�ʂ͈̔͊O�̓����蔻��
}

#endif