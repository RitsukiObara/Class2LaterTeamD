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
#define FRAME_POS_SHIFT_BACK	(D3DXVECTOR3(-40.0f, 20.0f,0.0f))		// ���̘g�̈ʒu�̂��炷��
#define FRAME_SIZE_FRONT		(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// �O�̘g�̃T�C�Y
#define FRAME_SIZE_BACK			(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// ���̘g�̃T�C�Y
#define ITEM_MARK_SHIFT			(D3DXVECTOR3(0.0f, -5.0f, 0.0f))		// �}�[�N�̂��炷��

//========================
// �R���X�g���N�^
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		m_aItemUI[nCnt].m_pMark = nullptr;		// �}�[�N�̏��
		m_aItemUI[nCnt].m_pFrame = nullptr;		// �g�̏��
	}
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
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		m_aItemUI[nCnt].m_pMark = nullptr;		// �}�[�N�̏��
		m_aItemUI[nCnt].m_pFrame = nullptr;		// �g�̏��
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CItemUI::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].m_pMark != nullptr)
		{ // �}�[�N�� NULL ����Ȃ��ꍇ

			// �}�[�N�̏I������
			m_aItemUI[nCnt].m_pMark->Uninit();
			m_aItemUI[nCnt].m_pMark = nullptr;
		}

		if (m_aItemUI[nCnt].m_pFrame != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̏I������
			m_aItemUI[nCnt].m_pFrame->Uninit();
			m_aItemUI[nCnt].m_pFrame = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//========================
// �X�V����
//========================
void CItemUI::Update(void)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].m_pFrame != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̍X�V����
			m_aItemUI[nCnt].m_pFrame->Update();
		}

		if (m_aItemUI[nCnt].m_pMark != nullptr)
		{ // �}�[�N�� NULL ����Ȃ��ꍇ

			// �}�[�N�̍X�V����
			m_aItemUI[nCnt].m_pMark->Update();
		}
	}
}

//========================
// �`�揈��
//========================
void CItemUI::Draw(void)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].m_pFrame != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̕`�揈��
			m_aItemUI[nCnt].m_pFrame->Draw();
		}

		if (m_aItemUI[nCnt].m_pMark != nullptr)
		{ // �}�[�N�� NULL ����Ȃ��ꍇ

			// �}�[�N�̕`�揈��
			m_aItemUI[nCnt].m_pMark->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CItemUI::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		switch (nCnt)
		{
		case ORDER_BACK:		// ���

			// �g�𐶐�����
			m_aItemUI[nCnt].m_pFrame = CItemFrame::Create(pos + FRAME_POS_SHIFT_BACK, FRAME_SIZE_BACK, CPlayer::TYPE::TYPE_CAT);

			break;

		case ORDER_FRONT:		// �O

			// �g�𐶐�����
			m_aItemUI[nCnt].m_pFrame = CItemFrame::Create(pos, FRAME_SIZE_FRONT, CPlayer::TYPE::TYPE_CAT);

			break;

		default:

			// ��~
			assert(false);

			break;
		}
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

}