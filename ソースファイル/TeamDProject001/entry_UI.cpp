//=======================================
//
// �G���g���[UI����[entry_UI.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_UI.h"
#include "texture.h"

#include "entry_frame.h"
#include "entry_team.h"

//=======================================
// �}�N����`
//=======================================
#define TEAM_SHIFT			(200.0f)		// �`�[���̂��炷����

//=========================
// �R���X�g���N�^
//=========================
CEntryUI::CEntryUI() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��
	m_pTeam = nullptr;			// �`�[���̏��
}

//=========================
// �f�X�g���N�^
//=========================
CEntryUI::~CEntryUI()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryUI::Init(void)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��
	m_pTeam = nullptr;			// �`�[���̏��

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEntryUI::Uninit(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̏I������
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pTeam != nullptr)
	{ // �`�[���̏�� NULL ����Ȃ��ꍇ

		// �`�[���̏I������
		m_pTeam->Uninit();
		m_pTeam = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//=========================
// �X�V����
//=========================
void CEntryUI::Update(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̍X�V����
		m_pFrame->Update();
	}

	if (m_pTeam != nullptr)
	{ // �`�[���̏�� NULL ����Ȃ��ꍇ

		// �`�[���̍X�V����
		m_pTeam->Update();
	}
}

//=========================
// �`�揈��
//=========================
void CEntryUI::Draw(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̕`�揈��
		m_pFrame->Draw();
	}

	if (m_pTeam != nullptr)
	{ // �`�[���̏�� NULL ����Ȃ��ꍇ

		// �`�[���̕`�揈��
		m_pTeam->Draw();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryUI::SetData(const D3DXVECTOR3& pos)
{
	if (m_pFrame == nullptr)
	{ // �g�̏�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pFrame = CEntryFrame::Create(pos);
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pTeam == nullptr)
	{ // �`�[���̏�� NULL �̏ꍇ

		// �`�[���𐶐�����
		m_pTeam = CEntryTeam::Create(D3DXVECTOR3(pos.x, pos.y - TEAM_SHIFT, 0.0f));
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}
}

//=========================
// ��������
//=========================
CEntryUI* CEntryUI::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryUI* pEntry = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEntry == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntry = new CEntryUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntry != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntry->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntry->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[UI�̃|�C���^��Ԃ�
	return pEntry;
}