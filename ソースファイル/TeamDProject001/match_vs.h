//===================================
//
// �}�b�`���O��VS�w�b�_�[[match_vs.h]
// Author ��������
//
//===================================
#ifndef _MATCH_VS_H_
#define _MATCH_VS_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CMatchVS)
//-----------------------------------
class CMatchVS : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CMatchVS();				// �R���X�g���N�^
	~CMatchVS();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CMatchVS* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif