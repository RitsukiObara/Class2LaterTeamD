//===================================
//
// ���[�h�w�b�_�[[Himo.h]
// Author ��{�ėB
//
//===================================
#ifndef _LEASH_H_
#define _LEASH_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(���[�h)
//-----------------------------------
class CLeash : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CLeash();				// �R���X�g���N�^
	~CLeash();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����
	void CollisionHead(bool Set) { m_bSetHead = Set; }
	void CollisionToes(bool Set) { m_bSetToes = Set; }

private:		// ���������A�N�Z�X�ł���
	void Action(void);
	void SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	D3DXVECTOR3 ActionPosHead;	//��[�̈ʒu
	D3DXVECTOR3 ActionPosToes;	//���[�̈ʒu

	bool m_bSetHead;	//��[�̏�������
	bool m_bSetToes;	//���[�̏�������
	bool m_bAction;		//�M�~�b�N���N�����Ă��邩�ǂ���
};

#endif