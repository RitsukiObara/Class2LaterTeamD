//=======================================
//
// �G���g���[�`�[������[entry_team.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_team.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define TEAM_SIZE		(D3DXVECTOR3(80.0f, 40.0f, 0.0f))		// �`�[���̃T�C�Y
#define TEAM_TEXTURE	"data\\TEXTURE\\Entry_Team.png"			// �`�[���̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CEntryTeam::CEntryTeam() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{

}

//=========================
// �f�X�g���N�^
//=========================
CEntryTeam::~CEntryTeam()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryTeam::Init(void)
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
void CEntryTeam::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CEntryTeam::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CEntryTeam::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryTeam::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(TEAM_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEAM_TEXTURE));

	// ���_���̏�����
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//=========================
// ��������
//=========================
CEntryTeam* CEntryTeam::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryTeam* pEntryTeam = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEntryTeam == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntryTeam = new CEntryTeam;
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