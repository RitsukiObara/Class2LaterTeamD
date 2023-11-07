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

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CObstacle* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif