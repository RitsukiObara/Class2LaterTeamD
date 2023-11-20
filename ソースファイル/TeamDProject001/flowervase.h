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

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Elevation(void);		// �N���n�ʂ̓����蔻��
};

#endif