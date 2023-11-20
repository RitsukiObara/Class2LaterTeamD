//===================================
//
// �v���X�`�b�N�P�[�X�w�b�_�[[plastic_case.h]
// Author �x�씋��
//
//===================================
#ifndef _PLASTICCASE_H_
#define _PLASTICCASE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�v���X�`�b�N�P�[�X)
//-----------------------------------
class CPlasticCase : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CPlasticCase();			// �R���X�g���N�^
	~CPlasticCase();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

};

#endif