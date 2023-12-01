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
// �������O���
//--------------------------------------------
namespace
{
	static const D3DXVECTOR3 FRAME_POS_SHIFT_BACK = D3DXVECTOR3(-40.0f, 20.0f, 0.0f);		// ���̘g�̈ʒu�̂��炷��
	static const D3DXVECTOR3 FRAME_SIZE[CItemUI::ORDER_MAX] =								// �g�̃T�C�Y
	{
		D3DXVECTOR3(30.0f, 30.0f, 0.0f),			// ���
		D3DXVECTOR3(50.0f, 50.0f, 0.0f),			// �O
	};
	static const D3DXVECTOR3 MARK_SIZE[CItemUI::ORDER_MAX] =								// �g�̃T�C�Y
	{
		D3DXVECTOR3(15.0f, 15.0f, 0.0f),			// ���
		D3DXVECTOR3(30.0f, 30.0f, 0.0f),			// �O
	};
}

//========================
// �R���X�g���N�^
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		m_aItemUI[nCnt].pMark = nullptr;				// �}�[�N�̏��
		m_aItemUI[nCnt].pFrame = nullptr;				// �g�̏��
		m_aItemUI[nCnt].type = CItem::TYPE_MOUSETRAP;	// ���
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
		m_aItemUI[nCnt].pMark = nullptr;				// �}�[�N�̏��
		m_aItemUI[nCnt].pFrame = nullptr;				// �g�̏��
		m_aItemUI[nCnt].type = CItem::TYPE_MOUSETRAP;	// ���
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
		if (m_aItemUI[nCnt].pMark != nullptr)
		{ // �}�[�N�� NULL ����Ȃ��ꍇ

			// �}�[�N�̏I������
			m_aItemUI[nCnt].pMark->Uninit();
			m_aItemUI[nCnt].pMark = nullptr;
		}

		if (m_aItemUI[nCnt].pFrame != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̏I������
			m_aItemUI[nCnt].pFrame->Uninit();
			m_aItemUI[nCnt].pFrame = nullptr;
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
		if (m_aItemUI[nCnt].pFrame != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̍X�V����
			m_aItemUI[nCnt].pFrame->Update();
		}

		if (m_aItemUI[nCnt].pMark != nullptr)
		{ // �}�[�N�� NULL ����Ȃ��ꍇ

			// �}�[�N�̍X�V����
			m_aItemUI[nCnt].pMark->Update();
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
		if (m_aItemUI[nCnt].pFrame != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̕`�揈��
			m_aItemUI[nCnt].pFrame->Draw();
		}

		if (m_aItemUI[nCnt].pMark != nullptr)
		{ // �}�[�N�� NULL ����Ȃ��ꍇ

			// �}�[�N�̕`�揈��
			m_aItemUI[nCnt].pMark->Draw();
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
			m_aItemUI[nCnt].pFrame = CItemFrame::Create(pos + FRAME_POS_SHIFT_BACK, FRAME_SIZE[nCnt], CPlayer::TYPE::TYPE_CAT);

			break;

		case ORDER_FRONT:		// �O

			// �g�𐶐�����
			m_aItemUI[nCnt].pFrame = CItemFrame::Create(pos, FRAME_SIZE[nCnt], CPlayer::TYPE::TYPE_CAT);

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
void CItemUI::SetMark(const CItem::TYPE type, const ORDER order)
{
	if (m_aItemUI[order].pMark == nullptr)
	{ // �}�[�N�̏�� NULL �̏ꍇ

		// �A�C�e��UI�̃}�[�N��ݒ肷��
		m_aItemUI[order].pMark = CItemMark::Create(m_aItemUI[order].pFrame->GetPos(), MARK_SIZE[order], type);
	}
}

//========================
// �A�C�e��UI�̎擾����
//========================
CItemUI::SItemUI CItemUI::GetItemUI(const ORDER order) const
{
	// �A�C�e��UI�̏���Ԃ�
	return m_aItemUI[order];
}