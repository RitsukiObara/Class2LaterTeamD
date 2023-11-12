//============================================
//
// �a�����o�w�b�_�[[slash.h]
// Author�F��������
//
//============================================
#ifndef _SLASH_H_			//���̃}�N����`������Ă��Ȃ�������
#define _SLASH_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// �N���X(�a�����o�N���X)
//--------------------------------------------
class CSlash : public CBillboardAnim
{
public:			// �N�ł��A�N�Z�X�ł���

	CSlash();				// �R���X�g���N�^
	~CSlash();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// �ݒ菈��

	// �ÓI�����o�֐�
	static CSlash* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nLife;			// ����
};

#endif