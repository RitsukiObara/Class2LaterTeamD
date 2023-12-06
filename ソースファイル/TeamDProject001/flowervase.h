//===================================
//
// �ԕr�w�b�_�[[hairball.h]
// Author �x�씋��
//
//===================================
#ifndef _FLOWERVASE_H_
#define _FLOWERVASE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�{)
//-----------------------------------
class CFlowerVase : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CFlowerVase();			// �R���X�g���N�^
	~CFlowerVase();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Elevation(void);		// �N���n�ʂ̓����蔻��
};

#endif