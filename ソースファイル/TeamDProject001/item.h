//===================================
//
// �A�C�e���w�b�_�[[item.h]
// Author ��������
//
//===================================
#ifndef _ITEM_H_
#define _ITEM_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�A�C�e��)
//-----------------------------------
class CItem : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CItem();			// �R���X�g���N�^
	~CItem();			// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CItem* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CItem* pNext);		// ��̃|�C���^�̐ݒ菈��
	CItem* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CItem* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CItem* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// ���X�g�\���֌W
	CItem* m_pPrev;	// �O�ւ̃|�C���^
	CItem* m_pNext;	// ���ւ̃|�C���^
};

#endif