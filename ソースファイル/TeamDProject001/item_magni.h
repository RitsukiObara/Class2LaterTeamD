//============================================
//
// �A�C�e���̎����Ă��鐔�w�b�_�[[item_magni.h]
// Author�F��������
//
//============================================
#ifndef _ITEM_MAGNI_H_			// ���̃}�N����`������Ă��Ȃ�������
#define _ITEM_MAGNI_H_			// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CObject2D;			// 2D�|���S��
class CNumber;				// ����

//--------------------------------------------
// �N���X��`(�A�C�e���̔{��)
//--------------------------------------------
class CItemMagni : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CItemMagni();			// �R���X�g���N�^
	~CItemMagni();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nNum);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CItemMagni* Create(const D3DXVECTOR3& pos, const int nNum);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CObject2D* m_pMagni;		// �~�}�[�N�̏��
	CNumber* m_pNumber;			// �����̏��
};

#endif