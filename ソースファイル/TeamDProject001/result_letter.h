//===================================
//
// ���ʂ̕����̏���[result_letter.h]
// Author ����������
//
//===================================
#ifndef _RESULT_LETTER_H_
#define _RESULT_LETTER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�T���v��)
//-----------------------------------
class CResultLetter : public CObject/*�e�N���X*/
{
public:			// �N�ł��A�N�Z�X�ł���

	CResultLetter();			// �R���X�g���N�^
	~CResultLetter();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void/*����*/);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CResultLetter* Create(void/*����*/);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif