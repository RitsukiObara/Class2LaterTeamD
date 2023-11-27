//=======================================
//
// �}�b�`���O�̑I��������[match_select.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "match_select.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define SELECT_SIZE			(D3DXVECTOR3(40.0f, 20.0f, 0.0f))		// �I�����̃T�C�Y
#define SELECT_TEXTURE		"data\\TEXTURE\\PlayerID.png"			// �I�����̃e�N�X�`��
#define SELECT_PATTERN		(0.25f)									// �I�����̃p�^�[����

//=========================
// �R���X�g���N�^
//=========================
CMatchSelect::CMatchSelect() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CMatchSelect::~CMatchSelect()
{

}

//=========================
// ����������
//=========================
HRESULT CMatchSelect::Init(void)
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
void CMatchSelect::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CMatchSelect::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CMatchSelect::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CMatchSelect::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(SELECT_SIZE);		// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(SELECT_TEXTURE));

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxTextureAnim(SELECT_PATTERN, nID);
}

//=========================
// ��������
//=========================
CMatchSelect* CMatchSelect::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMatchSelect* pMatchVS = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pMatchVS == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMatchVS = new CMatchSelect;
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
		pMatchVS->SetData(pos, nID);
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