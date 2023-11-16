//===================================
//
// �J�E���g�_�E���w�b�_�[[countdown.h]
// Author ��������
//
//===================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "number.h"

//-----------------------------------
// �N���X��`(�J�E���g�_�E��)
//-----------------------------------
class CCountdown : public CNumber
{
public:			// �N�ł��A�N�Z�X�ł���

	CCountdown();			// �R���X�g���N�^
	~CCountdown();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCountdown* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
};

#endif