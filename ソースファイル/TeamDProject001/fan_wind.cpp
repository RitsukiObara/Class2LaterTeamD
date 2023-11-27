//====================================================================
//
//	��@�̕����� [fan_wind.cpp]
//	Author�F��������
//
//====================================================================
//********************************************************************
//	�C���N���[�h�t�@�C��
//********************************************************************
#include "fan_wind.h"

//--------------------------------------------------------------------
// �}�N����`
//--------------------------------------------------------------------
#define FAN_CIRCUM		(8)			// ���̉~���̕�����
#define FAN_HEIGHT		(1)			// ���̏c�̕�����

//================================
// �R���X�g���N�^
//================================
CFanWind::CFanWind() : CMeshCylinder(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{
	
}

//================================
// �f�X�g���N�^
//================================
CFanWind::~CFanWind()
{

}

//================================
// ����������
//================================
HRESULT CFanWind::Init(void)
{
	if (FAILED(CMeshCylinder::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//================================
// �I������
//================================
void CFanWind::Uninit(void)
{
	// �I������
	CMeshCylinder::Uninit();
}

//================================
// �X�V����
//================================
void CFanWind::Update(void)
{

}

//================================
// �`�揈��
//================================
void CFanWind::Draw(void)
{
	// �`�揈��
	CMeshCylinder::Draw();
}

//================================
// ���̐ݒ菈��
//================================
void CFanWind::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize)
{
	// ���b�V���V�����_�[�̐ݒ菈��
	CMeshCylinder::SetDataCylinder(pos, rot, fCircumSize, fHeightSize, FAN_CIRCUM, FAN_HEIGHT);
}

//================================
// ��������
//================================
CFanWind* CFanWind::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CFanWind* pFanWind = nullptr;	// �C���X�^���X�𐶐�

	// ��������̎Ԃ𐶐�����
	pFanWind = new CFanWind;

	if (pFanWind != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		pFanWind->SetData(pos, rot, fCircumSize, fHeightSize);

		// ����������
		if (FAILED(pFanWind->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��@�̕��̃|�C���^��Ԃ�
	return pFanWind;
}