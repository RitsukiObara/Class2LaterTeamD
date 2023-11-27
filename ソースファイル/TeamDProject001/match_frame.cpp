//=======================================
//
// �}�b�`���O�̘g�`�[������[match_frame.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "match_frame.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define TEAM_SIZE		(D3DXVECTOR3(120.0f, 60.0f, 0.0f))		// �`�[���̃T�C�Y

//=========================
// �R���X�g���N�^
//=========================
CMatchFrame::CMatchFrame() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{

}

//=========================
// �f�X�g���N�^
//=========================
CMatchFrame::~CMatchFrame()
{

}

//=========================
// ����������
//=========================
HRESULT CMatchFrame::Init(void)
{
	if (FAILED(CObject2D::Init()))
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
void CMatchFrame::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CMatchFrame::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CMatchFrame::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CMatchFrame::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(TEAM_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// ���_���̏�����
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

//=========================
// ��������
//=========================
CMatchFrame* CMatchFrame::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMatchFrame* pEntryTeam = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEntryTeam == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntryTeam = new CMatchFrame;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntryTeam != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntryTeam->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntryTeam->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�`�[���̃|�C���^��Ԃ�
	return pEntryTeam;
}