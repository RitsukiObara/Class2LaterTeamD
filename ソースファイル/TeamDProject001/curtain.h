//===================================
//
// �J�[�e���w�b�_�[[curtain.h]
// Author ��������
//
//===================================
#ifndef _CURTAIN_H_
#define _CURTAIN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�J�[�e��)
//-----------------------------------
class CCurtain : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CCurtain();				// �R���X�g���N�^
	~CCurtain();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

};

#endif