//============================================
//
// �L�����N�^�[�̏��UI����[chara_infoUI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "chara_infoUI.h"
#include "texture.h"
#include "useful.h"

//========================
// �R���X�g���N�^
//========================
CCharaInfoUI::CCharaInfoUI() : CObject(TYPE_CHARAINFO, PRIORITY_UI)
{

}

//========================
// �f�X�g���N�^
//========================
CCharaInfoUI::~CCharaInfoUI()
{

}

//========================
// ����������
//========================
HRESULT CCharaInfoUI::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CCharaInfoUI::Uninit(void)
{
	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CCharaInfoUI::Update(void)
{

}

//========================
// �`�揈��
//========================
void CCharaInfoUI::Draw(void)
{

}

//========================
// ���̐ݒ菈��
//========================
void CCharaInfoUI::SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaImage::TYPE type)
{

}

//========================
// ��������
//========================
CCharaInfoUI* CCharaInfoUI::Create(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaImage::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCharaInfoUI* pInfoUI = nullptr;		// �L�����N�^�[���UI�̃C���X�^���X�𐶐�

	if (pInfoUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pInfoUI = new CCharaInfoUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pInfoUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pInfoUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pInfoUI->SetData(pos, nPlayerID, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �L�����N�^�[�̏��UI�̃|�C���^��Ԃ�
	return pInfoUI;
}