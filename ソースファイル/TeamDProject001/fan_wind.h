//=====================================================
//
// ��@�̕��w�b�_�[ [fan_wind.h]
// Author�F��������
//
//=====================================================
#ifndef _FAN_WIND_H_			// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _FAN_WIND_H_			// ��d�C���N���[�h�h�~�̃}�N�����`����

//*****************************************************
// �C���N���[�h�t�@�C��
//*****************************************************
#include "mesh_cylinder.h"

//-----------------------------------------------------
// �N���X��`(CFanWind)
//-----------------------------------------------------
class CFanWind : public CMeshCylinder
{
public:		// �N�ł��A�N�Z�X�ł���

	CFanWind();				// �R���X�g���N�^
	~CFanWind();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CFanWind* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize);		// ��������

private:		// ���������A�N�Z�X�ł���

};


#endif