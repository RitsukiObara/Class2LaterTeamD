//============================================
//
// ��ʂ̘g�w�b�_�[[screen_frame.h]
// Author�F��������
//
//============================================
#ifndef _SCREEN_FRAME_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SCREEN_FRAME_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"

//--------------------------------------------
// �N���X��`(��ʂ̘g)
//--------------------------------------------
class CScreenFrame : public CObject2D
{
public:				// �N�ł��A�N�Z�X�ł���

	CScreenFrame();			// �R���X�g���N�^
	~CScreenFrame();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	static CScreenFrame* Create(void);		// ��������

private:			// ���������A�N�Z�X�ł���

};

#endif