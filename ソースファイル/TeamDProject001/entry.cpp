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
#include "input.h"
#include "player.h"

//--------------------------------------------
// �ÓI�����o�ϐ�
//--------------------------------------------
CEntryUI* CEntry::m_apUI[MAX_ENTRY] = {};		// �G���g���[UI�̏��

//=========================================
// �R���X�g���N�^
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
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
	//�@�V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	for (int nCnt = 0; nCnt < MAX_ENTRY; nCnt++)
	{
		if (nCnt == 0)
		{ // �ŏ��̂�

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


	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//�`�揈��
//======================================
void CEntry::Draw(void)
{

}