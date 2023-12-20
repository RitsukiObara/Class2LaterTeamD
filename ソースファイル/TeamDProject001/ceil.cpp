//=======================================
//
// �V�䏈��[ceil.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "ceil.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define CEIL_ROT		(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI))		// �V��̃T�C�Y
#define CEIL_SIZE		(D3DXVECTOR3(1600.0f, 0.0f, 1000.0f))		// �V��̃T�C�Y

//=========================
// �R���X�g���N�^
//=========================
CCeil::CCeil() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// �f�X�g���N�^
//=========================
CCeil::~CCeil()
{

}

//=========================
// ����������
//=========================
HRESULT CCeil::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CCeil::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//=========================
// �X�V����
//=========================
void CCeil::Update(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CCeil::Draw(void)
{
	// �`�揈��
	CObject3D::DrawLightOff();
}

//=========================
// ���̐ݒ菈��
//=========================
void CCeil::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu�ݒ�
	SetPosOld(pos);			// �O��̈ʒu�ݒ�
	SetRot(CEIL_ROT);		// �����ݒ�
	SetSize(CEIL_SIZE);		// �T�C�Y�ݒ�

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// ��������
//=========================
CCeil* CCeil::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCeil* pCeil = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCeil == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCeil = new CCeil;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCeil != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCeil->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCeil->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ������̃|�C���^��Ԃ�
	return pCeil;
}