//============================================
//
// �}�l�[�W���[�̃��C������[manager.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "renderer.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "Objectmesh.h"

#include "file.h"
#include "camera.h"
#include "skybox.h"
#include "game.h"
#include "result_letter.h"
#include "objectElevation.h"
#include "rat.h"
#include "Cat.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CRat* CResult::m_apRat[MAX_RAT] = {};							// �l�Y�~�̏��
int CResult::m_nGameState = 0;			// �Q�[���̏��

//=========================================
// �R���X�g���N�^
//=========================================
CResult::CResult() : CScene(TYPE_SCENE, PRIORITY_BG)
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CResult::~CResult()
{

}

//=========================================
//����������
//=========================================
HRESULT CResult::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �e�L�X�g�ǂݍ��ݏ���
	CMesh::TxtSet();

	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// �Q�[���̏�Ԃ��擾����
	m_nGameState = CGame::GetState();

	// 3D�e�L�X�g����
	if (m_nGameState == CGame::STATE_CAT_WIN)
	{ // �l�R����������

		CResultLetter::Create(D3DXVECTOR3(0.0f, 300.0f, 0.0f), CXFile::TYPE_WINCAT_TEXT);		// �˂��̂���

	}
	else if (m_nGameState == CGame::STATE_RAT_WIN)
	{ // �l�Y�~����������

		CResultLetter::Create(D3DXVECTOR3(0.0f, 300.0f, 0.0f), CXFile::TYPE_WINRAT_TEXT);		// �˂��݂̂���

	}

	// �l�Y�~�̐���
	for (int nCntRat = 0; nCntRat < MAX_RAT; nCntRat++)
	{
		m_apRat[nCntRat] = CRat::Create(D3DXVECTOR3(200.0f * nCntRat, 0.0f, 0.0f), nCntRat);
	}

	//�L�̐���
	CCat::Create(D3DXVECTOR3(-300.0f, 0.0f, 0.0f));

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CResult::Uninit(void)
{
	// �j������
	Release();
}

//======================================
//�X�V����
//======================================
void CResult::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A,0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTER�L�[���������ꍇ

		// �����L���O�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �X�V����
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//�`�揈��
//======================================
void CResult::Draw(void)
{

}

//======================================
//�Q�[���̏��擾����
//======================================
int CResult::GetState(void)
{
	return m_nGameState;
}