//=======================================
//
// �L�����N�^�[�̉摜�̃��C������[chara_image.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "chara_image.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define ICON_SIZE			(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// �A�C�R���̃T�C�Y
#define CAT_ICON_TEXTURE	"data\\TEXTURE\\Cat_Icon.png"			// �l�R�̃A�C�R���̃e�N�X�`��
#define RAT_ICON_TEXTURE	"data\\TEXTURE\\Rat_Icon.png"			// �l�Y�~�̃A�C�R���̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CCharaImage::CCharaImage() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CCharaImage::~CCharaImage()
{

}

//=========================
// ����������
//=========================
HRESULT CCharaImage::Init(void)
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
void CCharaImage::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CCharaImage::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CCharaImage::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CCharaImage::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(ICON_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// ���_���̏�����
	SetVertex();

	switch (type)
	{
	case TYPE::TYPE_CAT:

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(CAT_ICON_TEXTURE));

		break;

	case TYPE::TYPE_RAT:

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(RAT_ICON_TEXTURE));

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=========================
// ��������
//=========================
CCharaImage* CCharaImage::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCharaImage* pCharaImage = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCharaImage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCharaImage = new CCharaImage;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCharaImage != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCharaImage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCharaImage->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �L�����N�^�[�摜�̃|�C���^��Ԃ�
	return pCharaImage;
}