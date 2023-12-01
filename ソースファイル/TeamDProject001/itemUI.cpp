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
#include "item_magni.h"
#include "item_frame.h"

//========================
// �R���X�g���N�^
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pMark = nullptr;		// �}�[�N�̏��
	m_pMagni = nullptr;		// �������̏��
	m_pFrame = nullptr;		// �g�̏��
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
	m_pMagni = nullptr;		// �������̏��
	m_pFrame = nullptr;		// �g�̏��

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

	if (m_pMagni != nullptr)
	{ // �{���� NULL ����Ȃ��ꍇ

		// �{���̏I������
		m_pMagni->Uninit();
		m_pMagni = nullptr;
	}

	if (m_pFrame != nullptr)
	{ // �g�� NULL ����Ȃ��ꍇ

		// �g�̏I������
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//========================
// �X�V����
//========================
void CItemUI::Update(void)
{
	if (m_pFrame != nullptr)
	{ // �g�� NULL ����Ȃ��ꍇ

		// �g�̍X�V����
		m_pFrame->Update();
	}

	if (m_pMark != nullptr)
	{ // �}�[�N�� NULL ����Ȃ��ꍇ

		// �}�[�N�̍X�V����
		m_pMark->Update();
	}

	if (m_pMagni != nullptr)
	{ // �{���� NULL ����Ȃ��ꍇ

		// �{���̍X�V����
		m_pMagni->Update();
	}
}

//========================
// �`�揈��
//========================
void CItemUI::Draw(void)
{
	if (m_pFrame != nullptr)
	{ // �g�� NULL ����Ȃ��ꍇ

		// �g�̕`�揈��
		m_pFrame->Draw();
	}

	if (m_pMark != nullptr)
	{ // �}�[�N�� NULL ����Ȃ��ꍇ

		// �}�[�N�̕`�揈��
		m_pMark->Draw();
	}

	if (m_pMagni != nullptr)
	{ // �{���� NULL ����Ȃ��ꍇ

		// �{���̕`�揈��
		m_pMagni->Draw();
	}
}

//========================
// ���̐ݒ菈��
//========================
void CItemUI::SetData(const D3DXVECTOR3& pos)
{
	if (m_pFrame == nullptr)
	{ // �g�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pFrame = CItemFrame::Create(pos, CPlayer::TYPE_CAT);
	}
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