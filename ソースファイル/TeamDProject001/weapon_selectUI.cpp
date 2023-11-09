//=======================================
//
// ����I��UI�̃��C������[weapon_selectUI.cpp]
// Author ��������
//
//=======================================
#include "main.h"
#include "manager.h"
#include "weapon_selectUI.h"
#include "object2D.h"
#include "texture.h"

#include "weapon_cage.h"

//---------------------------------------
// �}�N����`
//---------------------------------------

//==========================================
// �R���X�g���N�^
//==========================================
CWeaponSelectUI::CWeaponSelectUI() : CObject(TYPE_WEAPONSELECTUI, PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pWeaponCage = nullptr;		// ���포���̏��
}

//==========================================
// �f�X�g���N�^
//==========================================
CWeaponSelectUI::~CWeaponSelectUI()
{

}

//==========================================
// �|�[�Y�̏���������
//==========================================
HRESULT CWeaponSelectUI::Init(void)
{
	if (m_pWeaponCage == nullptr)
	{ // ���포���̏�� NULL �̏ꍇ

		// ���포���𐶐�����
		m_pWeaponCage = CWeaponCage::Create();
	}

	// ������Ԃ�
	return S_OK;
}

//========================================
// �|�[�Y�̏I������
//========================================
void CWeaponSelectUI::Uninit(void)
{
	if (m_pWeaponCage != nullptr)
	{ // ���포���� NULL ����Ȃ��ꍇ

		// ���포���̏I������
		m_pWeaponCage->Uninit();
		m_pWeaponCage = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//========================================
// �|�[�Y�̍X�V����
//========================================
void CWeaponSelectUI::Update(void)
{
	
}

//=====================================
// �|�[�Y�̕`�揈��
//=====================================
void CWeaponSelectUI::Draw(void)
{
	if (m_pWeaponCage != nullptr)
	{ // ���포���� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pWeaponCage->Draw();
	}
}

//=====================================
// ��������
//=====================================
CWeaponSelectUI* CWeaponSelectUI::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CWeaponSelectUI* pWeapon = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pWeapon == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pWeapon = new CWeaponSelectUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pWeapon != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pWeapon->Init()))
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

	// ����I��UI�̃|�C���^��Ԃ�
	return pWeapon;
}