//=======================================
//
// �G���g���[�̖��̃��C������[entry_arrow.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_arrow.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define ARROW_SIZE		(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// ���̃T�C�Y
#define ARROW_TEXTURE	"data\\TEXTURE\\Arrow.png"				// ���̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CEntryArrow::CEntryArrow() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{

}

//=========================
// �f�X�g���N�^
//=========================
CEntryArrow::~CEntryArrow()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryArrow::Init(void)
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
void CEntryArrow::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CEntryArrow::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CEntryArrow::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryArrow::SetData(const D3DXVECTOR3& pos, const bool bRight)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(ARROW_SIZE);		// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(ARROW_TEXTURE));

	// ���_���̏�����
	SetVertex();

	if (bRight == true)
	{ // �E�����̏ꍇ

		// �e�N�X�`���̐ݒ菈��
		SetVtxTexture();
	}
	else
	{ // ��L�ȊO

		// ���]�e�N�X�`���̐ݒ菈��
		SetVtxTextureRev();
	}
}

//=========================
// ��������
//=========================
CEntryArrow* CEntryArrow::Create(const D3DXVECTOR3& pos, const bool bRight)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryArrow* pArrow = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pArrow == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pArrow = new CEntryArrow;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pArrow != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pArrow->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pArrow->SetData(pos, bRight);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�̖��̃|�C���^��Ԃ�
	return pArrow;
}