//===========================================
//
// ���포���̃��C������[weapon_cage.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "weapon_cage.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define WEAPON_CAGE_POS		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))		// ���포���̈ʒu

//==============================
// �R���X�g���N�^
//==============================
CWeaponCage::CWeaponCage() : CModel(CObject::TYPE_FRACTION, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CWeaponCage::~CWeaponCage()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CWeaponCage::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CWeaponCage::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CWeaponCage::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CWeaponCage::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CWeaponCage::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(WEAPON_CAGE_POS);				// �ʒu
	SetPosOld(WEAPON_CAGE_POS);				// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_WEAPONCAGE);	// ���f�����
}

//=======================================
// ��������
//=======================================
CWeaponCage* CWeaponCage::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CWeaponCage* pCage = nullptr;	// �C���X�^���X�𐶐�

	if (pCage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pCage = new CWeaponCage;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCage != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCage->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �P�[�W�̃|�C���^��Ԃ�
	return pCage;
}