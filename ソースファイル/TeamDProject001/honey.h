//===================================
//
// �I���w�b�_�[[honey.h]
// Author ��������
//
//===================================
#ifndef _HONEY_H_
#define _HONEY_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�I��)
//-----------------------------------
class CHoney : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CHoney();				// �R���X�g���N�^
	~CHoney();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���
};

#endif