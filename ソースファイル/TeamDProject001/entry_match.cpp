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
#include "match_chara.h"

//=========================
// �R���X�g���N�^
//=========================
CEntryMatch::CEntryMatch() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��
	m_pChara = nullptr;			// �L�����N�^�[
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
	m_pChara = nullptr;			// �L�����N�^�[

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

	if (m_pChara != nullptr)
	{ // �L�����N�^�[�̏�� NULL ����Ȃ��ꍇ

		// �L�����N�^�[�̏I������
		m_pChara->Uninit();
		m_pChara = nullptr;
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

	if (m_pChara != nullptr)
	{ // �L�����N�^�[�̏�� NULL ����Ȃ��ꍇ

		// �L�����N�^�[�̍X�V����
		m_pChara->Update();
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

	if (m_pChara != nullptr)
	{ // �L�����N�^�[�̏�� NULL ����Ȃ��ꍇ

		// �L�����N�^�[�̕`�揈��
		m_pChara->Draw();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryMatch::SetData(const D3DXVECTOR3& pos)
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

	if (m_pChara == nullptr)
	{ // �L�����N�^�[�̏�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pChara = CMatchChara::Create(pos);
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
CEntryMatch* CEntryMatch::Create(const D3DXVECTOR3& pos)
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
		pMatch->SetData(pos);
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