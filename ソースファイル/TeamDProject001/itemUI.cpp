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
#include "item_frame.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define ITEM_MARK_SHIFT		(D3DXVECTOR3(0.0f, -5.0f, 0.0f))		// �}�[�N�̂��炷��
#define ITEM_MAGNI_SHIFT	(D3DXVECTOR3(10.0f, 30.0f, 0.0f))		// �{���̂��炷��

//========================
// �R���X�g���N�^
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pMark = nullptr;		// �}�[�N�̏��
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
}

//========================
// ���̐ݒ菈��
//========================
void CItemUI::SetData(const D3DXVECTOR3& pos)
{
	if (m_pFrame == nullptr)
	{ // �g�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pFrame = CItemFrame::Create(pos,NONE_D3DXVECTOR3, CPlayer::TYPE_CAT);
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

//========================
// �}�[�N�̐�������
//========================
void CItemUI::SetMark(const CItem::TYPE type)
{
	if (m_pMark == nullptr &&
		m_pFrame != nullptr)
	{ // �}�[�N�� NULL �̏ꍇ

		// �}�[�N�𐶐�����
		m_pMark = CItemMark::Create(m_pFrame->GetPos() + ITEM_MARK_SHIFT, type);
	}
}