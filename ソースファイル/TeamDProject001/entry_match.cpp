//=======================================
//
// �G���g���[�̃}�b�`���OUI����[entry_match.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_match.h"
#include "manager.h"
#include "input.h"
#include "texture.h"

#include "match_frame.h"

//=========================
// �R���X�g���N�^
//=========================
CEntryMatch::CEntryMatch() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��
}

//=========================
// �f�X�g���N�^
//=========================
CEntryMatch::~CEntryMatch()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryMatch::Init(void)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEntryMatch::Uninit(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̏I������
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//=========================
// �X�V����
//=========================
void CEntryMatch::Update(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̍X�V����
		m_pFrame->Update();
	}
}

//=========================
// �`�揈��
//=========================
void CEntryMatch::Draw(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̕`�揈��
		m_pFrame->Draw();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryMatch::SetData(const D3DXVECTOR3& pos, const int nID)
{
	if (m_pFrame == nullptr)
	{ // �g�̏�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pFrame = CMatchFrame::Create(pos);
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
CEntryMatch* CEntryMatch::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryMatch* pMatch = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pMatch == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMatch = new CEntryMatch;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMatch != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pMatch->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pMatch->SetData(pos, nID);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�̃}�b�`���O�̃|�C���^��Ԃ�
	return pMatch;
}