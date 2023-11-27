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
#include "entry_match.h"
#include "input.h"

//=========================================
// �R���X�g���N�^
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{

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

	// �G���g���[UI�̐�������
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 375.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 0);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 125.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 1);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 125.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 2);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 375.0f, SCREEN_HEIGHT * 0.6f, 0.0f), 3);

	// �}�b�`���OUI�̐�������
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 450.0f, SCREEN_HEIGHT * 0.1f, 0.0f));
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 150.0f, SCREEN_HEIGHT * 0.1f, 0.0f));
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 150.0f, SCREEN_HEIGHT * 0.1f, 0.0f));
	CEntryMatch::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 450.0f, SCREEN_HEIGHT * 0.1f, 0.0f));

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CEntry::Uninit(void)
{
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