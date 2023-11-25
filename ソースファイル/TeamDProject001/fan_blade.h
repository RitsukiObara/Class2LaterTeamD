//===================================
//
// ��@�̃t�@���w�b�_�[[fan_blade.h]
// Author ��������
//
//===================================
#ifndef _FAN_BLADE_H_
#define _FAN_BLADE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(��@�̃t�@��)
//-----------------------------------
class CFanBlade : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CFanBlade();			// �R���X�g���N�^
	~CFanBlade();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CFanBlade* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif