//============================================
//
// �G���g���[��ʂ̃��C������[entry.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "entry.h"
#include "renderer.h"
#include "fade.h"
#include "Objectmesh.h"

#include "entry_UI.h"
#include "entry_team.h"
#include "input.h"
#include "player.h"

//=========================================
// �R���X�g���N�^
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_nCatIdx = 0;					// �l�R�����v���C���[
	for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
	{
		m_apUI[nCnt] = nullptr;		// �G���g���[UI�̏��
	}
}

//=========================================
// �f�X�g���N�^
//=========================================
CEntry::~CEntry()
{

}

//=========================================
//����������
//=========================================
HRESULT CEntry::Init(void)
{
	// �S�Ă̒l������������
	m_nCatIdx = 0;					// �l�R�����v���C���[

	//�@�V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
	{
		if (nCnt == m_nCatIdx)
		{ // �l�R�����v���C���[�̂�

			// �G���g���[UI�̐�������
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_CAT);
		}
		else
		{ // ��L�ȊO

			// �G���g���[UI�̐�������
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_RAT);
		}
	}

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CEntry::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
	{
		if (m_apUI[nCnt] != nullptr)
		{ // �G���g���[UI�̏�� NULL ����Ȃ��ꍇ

			// �G���g���[UI�̏I������
			m_apUI[nCnt]->Uninit();
			m_apUI[nCnt] = nullptr;
		}
	}

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CEntry::Update(void)
{

// �f�o�b�O��
#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // ENTER�L�[���������ꍇ

		// �Q�[�����[�h�ɑJ��
		CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
	{ // �E�L�[���������ꍇ

		// �l�R�����v���C���[��ݒ�
		m_nCatIdx = (m_nCatIdx + 1) % MAX_ENTRY;

		for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
		{
			if (nCnt == m_nCatIdx)
			{ // �l�R�����v���C���[�̂�

				// �l�R�ɐݒ肷��
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);
			}
			else
			{ // ��L�ȊO

				// �l�Y�~�ɐݒ肷��
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);
			}
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
	{ // ���L�[���������ꍇ

		// �l�R�����v���C���[��ݒ�
		m_nCatIdx = (m_nCatIdx + MAX_ENTRY - 1) % MAX_ENTRY;

		for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
		{
			if (nCnt == m_nCatIdx)
			{ // �l�R�����v���C���[�̂�

				// �l�R�ɐݒ肷��
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);
			}
			else
			{ // ��L�ȊO

				// �l�Y�~�ɐݒ肷��
				m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);
			}
		}
	}

	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//�`�揈��
//======================================
void CEntry::Draw(void)
{

}