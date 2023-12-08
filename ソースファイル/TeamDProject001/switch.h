//===================================
//
// �X�C�b�`�w�b�_�[[switch.h]
// Author ��������
//
//===================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�X�C�b�`)
//-----------------------------------
class CSwitch : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CSwitch();				// �R���X�g���N�^
	~CSwitch();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CSwitch* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif