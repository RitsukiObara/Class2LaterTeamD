//===================================
//
// �}�b�`���O�̑I�����w�b�_�[[match_select.h]
// Author ��������
//
//===================================
#ifndef _MATCH_SELECT_H_
#define _MATCH_SELECT_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CMatchSelect)
//-----------------------------------
class CMatchSelect : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CMatchSelect();			// �R���X�g���N�^
	~CMatchSelect();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nID);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CMatchSelect* Create(const D3DXVECTOR3& pos, const int nID);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif