//============================================
//
// �^�C�g����ʂ̃��C������[title.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "title.h"
#include "fade.h"
#include "Objectmesh.h"

#include "2DUI_edit.h"
#include "title_logo.h"
#include "skybox.h"

// �}�N����`
#define SET_RANKING_TIMER		(600)		// �����L���O��ʂɑJ�ڂ���J�E���g��

//=========================================
// �R���X�g���N�^
//=========================================
CTitle::CTitle() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pUIEdit = NULL;
	m_nTransCount = 0;
	m_bEdit = false;
}

//=========================================
// �f�X�g���N�^
//=========================================
CTitle::~CTitle()
{

}

//=========================================
//����������
//=========================================
HRESULT CTitle::Init(void)
{
	//�@�V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �^�C�g�����S�̐���
	CTitleLogo::Create();

	//UI�G�f�B�^�[�̐���
	m_pUIEdit = C2DUIEdit::Create();
	m_pUIEdit->LoadData(LOADUI_NAME,NONE_D3DXVECTOR3);

	// �S�Ă̒l������������
	m_nTransCount = 0;

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTitle::Uninit(void)
{
	// �I������
	CScene::Uninit();

	if (m_pUIEdit != NULL)
	{
		//�G�f�B�b�g���[�h�̏I������
		m_pUIEdit->Uninit();

		delete m_pUIEdit;
		m_pUIEdit = NULL;
	}
}

//======================================
//�X�V����
//======================================
void CTitle::Update(void)
{
	//�G�f�B�b�g���[�h�̃I���I�t
	if (m_bEdit)
	{
		//�G�f�B�b�g���[�h�̍X�V����
		m_pUIEdit->Update();
	}
	else
	{

		// �J�ڃJ�E���g�����Z����
		m_nTransCount++;

		if (m_nTransCount % SET_RANKING_TIMER == 0)
		{ // �J�ڃJ�E���g����萔�ɒB�����ꍇ

			// �����L���O�ɑJ�ڂ���
			CManager::Get()->GetFade()->SetFade(CScene::MODE_ENTRY);

			// ���̐�̏������s��Ȃ�
			return;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
		{ // ENTER�L�[���������ꍇ

			// �`���[�g���A���ɑJ�ڂ���
			CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);

			// ���̐�̏������s��Ȃ�
			return;
		}
	}

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F2) == true)
	{
		m_bEdit = m_bEdit ? false : true;
	}

#endif // _DEBUG

	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//�`�揈��
//======================================
void CTitle::Draw(void)
{

}