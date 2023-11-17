//============================================
//
// �^�C�g�����S����[title_logo.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "title_logo_nyanko.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define LOGO_TEXTURE		"data/TEXTURE/TitleNyanko.png"							// �^�C�g�����S�̃e�N�X�`��
#define LOGO_SIZE			(D3DXVECTOR3(400.0f, 100.0f, 0.0f))						// �^�C�g�����S�̃T�C�Y

//============================
// �R���X�g���N�^
//============================
CTitleLogoNyanko::CTitleLogoNyanko() : CObject2D(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{

}

//============================
// �f�X�g���N�^
//============================
CTitleLogoNyanko::~CTitleLogoNyanko()
{

}

//============================
// ����������
//============================
HRESULT CTitleLogoNyanko::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // ���s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CTitleLogoNyanko::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//============================
// �X�V����
//============================
void CTitleLogoNyanko::Update(void)
{

}

//============================
// �`�揈��
//============================
void CTitleLogoNyanko::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//============================
// ���̐ݒ菈��
//============================
void CTitleLogoNyanko::SetData(void)
{
	// ����ݒ肷��
	SetPos(NONE_D3DXVECTOR3);		// �ʒu
	SetPosOld(NONE_D3DXVECTOR3);	// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetSize(LOGO_SIZE);				// �T�C�Y
	SetAngle();						// ����
	SetLength();					// ����

	// �e�N�X�`���̐ݒ菈��
	BindTexture(CManager::Get()->GetTexture()->Regist(LOGO_TEXTURE));

	// ���_��񏈗�
	SetVertex();
}

//============================
//��������
//============================
CTitleLogoNyanko* CTitleLogoNyanko::Create(void)
{
	// �^�C�g�����S�̃|�C���^�𐶐�
	CTitleLogoNyanko* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTitle = new CTitleLogoNyanko;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTitle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTitle->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �^�C�g�����S�̃|�C���^��Ԃ�
	return pTitle;
}