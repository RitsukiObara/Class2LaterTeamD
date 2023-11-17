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
#include "title_logo.h"
#include "object2D.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define RAT_TEXTURE			"data/TEXTURE/TitleRat.png"				// �^�C�g�����S(�l�Y�~)�̃e�N�X�`��
#define CAT_TEXTURE			"data/TEXTURE/TitleCat.png"				// �^�C�g�����S(�l�R)�̃e�N�X�`��
#define AND_TEXTURE			"data/TEXTURE/TitleAnd.png"				// �^�C�g�����S(��)�̃e�N�X�`��
#define TITLE_LOGO_SIZE		(D3DXVECTOR3(200.0f, 100.0f, 0.0f))		// �^�C�g���̃T�C�Y

//============================
// �R���X�g���N�^
//============================
CTitleLogo::CTitleLogo() : CObject(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apTitle[nCnt] = nullptr;		// �^�C�g���̃|���S��
	}
}

//============================
// �f�X�g���N�^
//============================
CTitleLogo::~CTitleLogo()
{

}

//============================
// ����������
//============================
HRESULT CTitleLogo::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] == nullptr)
		{ // �^�C�g���� NULL �̏ꍇ

			// �^�C�g���̃��S�𐶐�����
			m_apTitle[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CTitleLogo::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] != nullptr)
		{ // �^�C�g���̃|���S���� NULL ����Ȃ��ꍇ

			// �I������
			m_apTitle[nCnt]->Uninit();
			m_apTitle[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//============================
// �X�V����
//============================
void CTitleLogo::Update(void)
{

}

//============================
// �`�揈��
//============================
void CTitleLogo::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] != nullptr)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apTitle[nCnt]->Draw();
		}
	}
}

//============================
// ���̐ݒ菈��
//============================
void CTitleLogo::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apTitle[nCnt] != nullptr)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			m_apTitle[nCnt]->SetPos(NONE_D3DXVECTOR3);					// �ʒu
			m_apTitle[nCnt]->SetPosOld(m_apTitle[nCnt]->GetPos());		// �O��̈ʒu
			m_apTitle[nCnt]->SetRot(NONE_D3DXVECTOR3);					// ����
			m_apTitle[nCnt]->SetSize(TITLE_LOGO_SIZE);					// �T�C�Y
			m_apTitle[nCnt]->SetAngle();								// ����
			m_apTitle[nCnt]->SetLength();								// ����

			// �e�N�X�`���̐ݒ菈��
			m_apTitle[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

			// ���_��񏈗�
			m_apTitle[nCnt]->SetVertexRot();
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}
	}
}

//============================
//��������
//============================
CTitleLogo* CTitleLogo::Create(void)
{
	// �^�C�g�����S�̃|�C���^�𐶐�
	CTitleLogo* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTitle = new CTitleLogo;
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