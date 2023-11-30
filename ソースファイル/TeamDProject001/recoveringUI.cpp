//===========================================
//
// �񕜒�UI���C������[recoveringUI.cpp]
// Author ����������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "recoveringUI.h"
#include "model.h"
#include "texture.h"
#include "player.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CRecoveringUI::CRecoveringUI() : CBillboard(CObject::TYPE_RECOVERINGUI, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_bDisp = false;			// UI��\�����邩
}

//==============================
// �f�X�g���N�^
//==============================
CRecoveringUI::~CRecoveringUI()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CRecoveringUI::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_bDisp = false;			// UI��\�����邩

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CRecoveringUI::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CRecoveringUI::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CRecoveringUI::Draw(void)
{
	if (m_bDisp == true)
	{ // UI��\�������Ԃ̂Ƃ�

		// �`�揈��
		CBillboard::Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRecoveringUI::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	// ���̐ݒ菈��

	//==========================================================================
	// �r���{�[�h
	//==========================================================================
	SetPos(pos);			// �ʒu
	SetPosOld(posOld);		// �O��̈ʒu
	SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));	// �T�C�Y
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\CageMark.png"));		// �e�N�X�`���̊��蓖�ď���

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=======================================
// ��������
//=======================================
CRecoveringUI* CRecoveringUI::Create(const D3DXVECTOR3& pos, const  D3DXVECTOR3& posOld)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRecoveringUI* pRecoveringUI = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pRecoveringUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pRecoveringUI = new CRecoveringUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRecoveringUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pRecoveringUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pRecoveringUI->SetData(pos, posOld);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pRecoveringUI;
}

//=======================================
// UI�̕\����Ԃ̐ݒ�
//=======================================
void CRecoveringUI::SetDisplayUI(bool bRez)
{
	// UI�̕\����Ԃ�ݒ�
	m_bDisp = bRez;
}

//=======================================
// UI�̕\����Ԃ̎擾
//=======================================
bool CRecoveringUI::GetDisplayUI(void)
{
	// UI�̕\����Ԃ�Ԃ�
	return m_bDisp;
}