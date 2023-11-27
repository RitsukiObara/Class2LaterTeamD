//=======================================
//
// �}�b�`���O��VS����[match_vs.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "match_vs.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define VS_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))		// VS�}�[�N�̃T�C�Y
#define VS_TEXTURE	"data\\TEXTURE\\MatchVS.png"			// VS�}�[�N�̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CMatchVS::CMatchVS() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CMatchVS::~CMatchVS()
{

}

//=========================
// ����������
//=========================
HRESULT CMatchVS::Init(void)
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
void CMatchVS::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CMatchVS::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CMatchVS::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CMatchVS::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(VS_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(VS_TEXTURE));

	// ���_���̏�����
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=========================
// ��������
//=========================
CMatchVS* CMatchVS::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMatchVS* pMatchVS = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pMatchVS == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMatchVS = new CMatchVS;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMatchVS != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pMatchVS->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pMatchVS->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�`�[���̃|�C���^��Ԃ�
	return pMatchVS;
}