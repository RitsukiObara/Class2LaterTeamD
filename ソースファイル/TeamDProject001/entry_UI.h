//===================================
//
// �G���g���[UI�w�b�_�[[entry_UI.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_UI_H_
#define _ENTRY_UI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CEntryFrame;			// �G���g���[�̘g

//-----------------------------------
// �N���X��`(CEntryUI)
//-----------------------------------
class CEntryUI : public CObject
{
public:

	CEntryUI();				// �R���X�g���N�^
	~CEntryUI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryUI* Create(const D3DXVECTOR3& pos);	// ��������

private:

	// �����o�ϐ�
	CEntryFrame* m_pFrame;			// �g�̏��
};

#endif