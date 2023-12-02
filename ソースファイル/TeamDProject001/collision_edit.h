//===================================
//
// �����蔻��G�f�B�b�g�w�b�_�[[collision_edit.h]
// Author ��������
//
//===================================
#ifndef _COLLISION_EDIT_H_
#define _COLLISION_EDIT_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MIN_NUMCOLL			(1)			// �����蔻��̍ŏ���
#define MAX_NUMCOLL			(10)		// �����蔻��̍ő吔

//-----------------------------------
// �O���錾
//-----------------------------------
class CModel;			// ���f��

//-----------------------------------
// �N���X��`(�����蔻��G�f�B�b�g)
//-----------------------------------
class CCollisionEdit : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CCollisionEdit();		// �R���X�g���N�^
	~CCollisionEdit();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCollisionEdit* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);			// �ړ�����
	void Adjust(void);			// ����������
	void PosReset(void);		// �ʒu�̃��Z�b�g����

	// �����o�ϐ�
	CModel* m_apModel[MAX_NUMCOLL];		// �����蔻��̏��
	D3DXVECTOR3 m_posInit;				// �����ʒu
	int m_nNumColl;						// �����蔻��̑���
	int m_nIdx;							// �C���f�b�N�X
};

#endif