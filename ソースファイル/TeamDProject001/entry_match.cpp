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
#include "match_vs.h"
#include "match_select.h"

//---------------------------------------
// �}�N����`
//---------------------------------------
#define MATCH_SHIFT_HEIGHT		(-50.0f)		// �G���g���[�̂��炷����

//=========================
// �R���X�g���N�^
//=========================
CEntryMatch::CEntryMatch() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��
	m_pChara = nullptr;			// �L�����N�^�[
	m_pVS = nullptr;			// VS�}�[�N
	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		m_apSelect[nCnt] = nullptr;	// �I����
	}
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
	m_pVS = nullptr;			// VS�}�[�N
	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		m_apSelect[nCnt] = nullptr;	// �I����
	}

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

	if (m_pVS != nullptr)
	{ // VS�}�[�N�̏�� NULL ����Ȃ��ꍇ

		// VS�}�[�N�̏I������
		m_pVS->Uninit();
		m_pVS = nullptr;
	}

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] != nullptr)
		{ // �I�����̏�� NULL ����Ȃ��ꍇ

			// �I�����̏I������
			m_apSelect[nCnt]->Uninit();
			m_apSelect[nCnt] = nullptr;
		}
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

	if (m_pVS != nullptr)
	{ // VS�}�[�N�̏�� NULL ����Ȃ��ꍇ

		// VS�}�[�N�̍X�V����
		m_pVS->Update();
	}

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] != nullptr)
		{ // �I�����̏�� NULL ����Ȃ��ꍇ

			// �I�����̍X�V����
			m_apSelect[nCnt]->Update();
		}
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

	if (m_pVS != nullptr)
	{ // VS�}�[�N�̏�� NULL ����Ȃ��ꍇ

		// VS�}�[�N�̕`�揈��
		m_pVS->Draw();
	}

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] != nullptr)
		{ // �I�����̏�� NULL ����Ȃ��ꍇ

			// �I�����̕`�揈��
			m_apSelect[nCnt]->Draw();
		}
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

	if (m_pChara == nullptr)
	{ // �L�����N�^�[�̏�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pChara = CMatchChara::Create(D3DXVECTOR3(pos.x, pos.y + MATCH_SHIFT_HEIGHT, pos.z));
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pVS == nullptr)
	{ // �L�����N�^�[�̏�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pVS = CMatchVS::Create(D3DXVECTOR3(pos.x, pos.y, pos.z));
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	// �ݒ�p�̃J�E���g�ϐ�
	int nCntSet = 0;

	for (int nCnt = 0; nCnt < MATCH_ID_MAX; nCnt++)
	{
		if (m_apSelect[nCnt] == nullptr)
		{ // �I�����̏�� NULL �̏ꍇ

			if (nID == nCnt)
			{ // �C���f�b�N�X����Ȃ������ꍇ

				// ID�𐶐�����
				m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x - 80.0f, pos.y + 30.0f, pos.z), nCnt);
			}
			else
			{ // ��L�ȊO

				switch (nCntSet)
				{
				case 0:

					// ID�𐶐�����
					m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x + 30.0f, pos.y + 50.0f, pos.z), nCnt);

					break;

				case 1:

					// ID�𐶐�����
					m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x + 70.0f, pos.y + 10.0f, pos.z), nCnt);

					break;

				case 2:

					// ID�𐶐�����
					m_apSelect[nCnt] = CMatchSelect::Create(D3DXVECTOR3(pos.x + 110.0f, pos.y + 50.0f, pos.z), nCnt);

					break;
				}

				nCntSet++;
			}
		}
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