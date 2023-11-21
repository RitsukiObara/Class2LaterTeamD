//===================================
//
// �l�Y�~�߂�w�b�_�[[mousetrap.h]
// Author ��������
//
//===================================
#ifndef _MOUSETRAP_H_
#define _MOUSETRAP_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CTrapIron;		// �l�Y�~�߂�̓S����
class CDangerMark;		// �댯�}�[�N

//-----------------------------------
// �N���X��`(�l�Y�~�߂�)
//-----------------------------------
class CMouseTrap : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CMouseTrap();			// �R���X�g���N�^
	~CMouseTrap();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void IronPosSet(void);		// �S�����̈ʒu�̐ݒ菈��

	// �����o�ϐ�
	CTrapIron* m_pIron;			// �S����
	CDangerMark* m_pMark;		// �댯�}�[�N�̏��
};

#endif