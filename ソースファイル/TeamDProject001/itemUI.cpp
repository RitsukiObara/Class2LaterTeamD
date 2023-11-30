//============================================
//
// �A�C�e��UI����[itemUI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "itemUI.h"
#include "texture.h"
#include "useful.h"

#include "item_mark.h"

//========================
// �R���X�g���N�^
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pMark = nullptr;		// �}�[�N�̏��
}

//========================
// �f�X�g���N�^
//========================
CItemUI::~CItemUI()
{

}

//========================
// ����������
//========================
HRESULT CItemUI::Init(void)
{
	// �S�Ă̒l������������
	m_pMark = nullptr;		// �}�[�N�̏��

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CItemUI::Uninit(void)
{
	if (m_pMark != nullptr)
	{ // �}�[�N�� NULL ����Ȃ��ꍇ

		// �}�[�N�̏I������
		m_pMark->Uninit();
		m_pMark = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//========================
// �X�V����
//========================
void CItemUI::Update(void)
{
	if (m_pMark != nullptr)
	{ // �}�[�N�� NULL ����Ȃ��ꍇ

		// �}�[�N�̍X�V����
		m_pMark->Update();
	}
}

//========================
// �`�揈��
//========================
void CItemUI::Draw(void)
{
	if (m_pMark != nullptr)
	{ // �}�[�N�� NULL ����Ȃ��ꍇ

		// �}�[�N�̕`�揈��
		m_pMark->Draw();
	}
}

//========================
// ���̐ݒ菈��
//========================
void CItemUI::SetData(const D3DXVECTOR3& pos)
{

}

//========================
// ��������
//========================
CItemUI* CItemUI::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CItemUI* pItemUI = nullptr;		// �L�����N�^�[���UI�̃C���X�^���X�𐶐�

	if (pItemUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pItemUI = new CItemUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pItemUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pItemUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pItemUI->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �A�C�e��UI�̃|�C���^��Ԃ�
	return pItemUI;
}