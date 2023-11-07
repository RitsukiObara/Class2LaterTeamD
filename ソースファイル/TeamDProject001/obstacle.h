//===================================
//
// ��Q���w�b�_�[[obstacle.h]
// Author ��������
//
//===================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(��Q��)
//-----------------------------------
class CObstacle : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CObstacle();			// �R���X�g���N�^
	~CObstacle();			// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CObstacle* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CObstacle* pNext);		// ��̃|�C���^�̐ݒ菈��
	CObstacle* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CObstacle* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CObstacle* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// ���X�g�\���֌W
	CObstacle* m_pPrev;	// �O�ւ̃|�C���^
	CObstacle* m_pNext;	// ���ւ̃|�C���^
};

#endif