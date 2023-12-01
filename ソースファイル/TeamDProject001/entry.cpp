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
#include "debugproc.h"
#include "entry_UI.h"
#include "entry_team.h"
#include "input.h"
#include "player.h"

//--------------------------------------------
// �ÓI�����o�ϐ�
//--------------------------------------------
int CEntry::m_nCatIdx = 0;		// �l�R�����v���C���[
int CEntry::m_nCatOldIdx = 0;	// �����pID
int CEntry::m_EntryId[MAX_PLAY] = {};	// �����pID
CPlayer* CEntry::m_apPlayer[MAX_PLAY] = {};	// �v���C���[�̃��f�����

//=========================================
// �R���X�g���N�^
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_nCatIdx = 0;					// �l�R�����v���C���[
	m_nCatOldIdx = 0;				// �����pID
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_apUI[nCnt] = nullptr;		// �G���g���[UI�̏��
		m_apPlayer[nCnt] = nullptr;	// �v���C���[�̃��f�����
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
	m_nCatOldIdx = 0;				// �����pID

	//�@�V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (nCnt == m_nCatIdx)
		{ // �l�R�����v���C���[�̂�

			// �G���g���[UI�̐�������
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_CAT);

			// �l�R�̐�������
			m_apPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-500.0f + (350.0f*nCnt), -100.0f, -150.0f), nCnt, CPlayer::TYPE_CAT);

		}
		else
		{ // ��L�ȊO

			// �G���g���[UI�̐�������
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_RAT);

			// ���b�g�̐�������
			m_apPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-500.0f + (350.0f*nCnt), -100.0f, -150.0f), nCnt, CPlayer::TYPE_RAT);

		}
		m_EntryId[nCnt] = nCnt;
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
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (m_apUI[nCnt] != nullptr)
		{ // �G���g���[UI�̏�� NULL ����Ȃ��ꍇ

			// �G���g���[UI�̏I������
			m_apUI[nCnt]->Uninit();
			m_apUI[nCnt] = nullptr;
		}
		m_apPlayer[nCnt] = nullptr;		// �l�Y�~�̏��
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
		m_nCatIdx = (m_nCatIdx + 1) % MAX_PLAY;

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
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
		m_nCatIdx = (m_nCatIdx + MAX_PLAY - 1) % MAX_PLAY;

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
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

	if (m_nCatOldIdx != m_nCatIdx)
	{
		int nKeepID = 0;
 		nKeepID = m_EntryId[m_nCatIdx];
		m_EntryId[m_nCatIdx] = m_EntryId[m_nCatOldIdx];
		m_EntryId[m_nCatOldIdx] = nKeepID;
		m_nCatOldIdx = m_nCatIdx;
	}
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_apPlayer[nCnt]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		
	}
	m_apPlayer[m_EntryId[0]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f*0), -100.0f, -150.0f));
	m_apPlayer[m_EntryId[1]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f*1), -100.0f, -150.0f));
	m_apPlayer[m_EntryId[2]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f*2), -100.0f, -150.0f));
	m_apPlayer[m_EntryId[3]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f*3), -100.0f, -150.0f));

	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//�`�揈��
//======================================
void CEntry::Draw(void)
{

}

//======================================
// �l�R�S���̎擾����
//======================================
int CEntry::GetCatIdx(void)
{
	// �l�R�̃C���f�b�N�X��Ԃ�
	return m_nCatIdx;
}