//=======================================
//
// �A�C�e���̃}�[�N�̃��C������[item_mark.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "item_mark.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define SIZE				(D3DXVECTOR3(30.0f,30.0f,0.0f))		// �l�Y�~�߂�̃T�C�Y
#define MOUSETRAP_TEXTURE	"data\\TEXTURE\\Mousetrap.png"		// �l�Y�~�߂�̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CItemMark::CItemMark() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CItemMark::~CItemMark()
{

}

//=========================
// ����������
//=========================
HRESULT CItemMark::Init(void)
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
void CItemMark::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CItemMark::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CItemMark::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CItemMark::SetData(const D3DXVECTOR3& pos, const CItem::TYPE type)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(SIZE);				// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	switch (type)
	{
	case CItem::TYPE_MOUSETRAP:

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(MOUSETRAP_TEXTURE));

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���_���̏�����
	SetVertex();
}

//=========================
// ��������
//=========================
CItemMark* CItemMark::Create(const D3DXVECTOR3& pos, const CItem::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CItemMark* pItemMark = nullptr;		// �v���C���[�̃C���X�^���X�𐶐�

	if (pItemMark == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pItemMark = new CItemMark;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pItemMark != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pItemMark->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pItemMark->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �A�C�e���}�[�N�̃|�C���^��Ԃ�
	return pItemMark;
}