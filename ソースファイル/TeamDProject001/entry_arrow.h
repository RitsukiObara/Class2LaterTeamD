//===================================
//
// �G���g���[�̖��w�b�_�[[entry_arrow.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_ARROW_H_
#define _ENTRY_ARROW_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CEntryArrow)
//-----------------------------------
class CEntryArrow : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CEntryArrow();			// �R���X�g���N�^
	~CEntryArrow();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const bool bRight);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryArrow* Create(const D3DXVECTOR3& pos, const bool bRight);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif