//===================================
//
// �{�w�b�_�[[hairball.h]
// Author ��������
//
//===================================
#ifndef _HAIRBALL_H_
#define _HAIRBALL_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�{)
//-----------------------------------
class CHairBall : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CHairBall();			// �R���X�g���N�^
	~CHairBall();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Gravity(void);			// �d�͏���
	void Elevation(void);		// �N���n�ʂ̓����蔻��

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
};

#endif