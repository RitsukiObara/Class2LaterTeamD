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
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 375.0f, SCREEN_HEIGHT * 0.5f, 0.0f), 0);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 125.0f, SCREEN_HEIGHT * 0.5f, 0.0f), 1);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 125.0f, SCREEN_HEIGHT * 0.5f, 0.0f), 2);
	CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 375.0f, SCREEN_HEIGHT * 0.5f, 0.0f), 3);

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
	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//�`�揈��
//======================================
void CEntry::Draw(void)
{

}