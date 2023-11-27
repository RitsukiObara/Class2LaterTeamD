//=======================================
//
// �}�b�`���O�̃L�����N�^�[����[match_chara.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "match_chara.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define CHARA_SIZE		(D3DXVECTOR3(120.0f, 30.0f, 0.0f))		// �L�����N�^�[�̃T�C�Y
#define CHARA_TEXTURE	"data\\TEXTURE\\MatchChara.png"			// �L�����N�^�[�̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CMatchChara::CMatchChara() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CMatchChara::~CMatchChara()
{

}

//=========================
// ����������
//=========================
HRESULT CMatchChara::Init(void)
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
void CMatchChara::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CMatchChara::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CMatchChara::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CMatchChara::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(CHARA_SIZE);		// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̊��蓖��.����
	BindTexture(CManager::Get()->GetTexture()->Regist(CHARA_TEXTURE));

	// ���_���̏�����
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=========================
// ��������
//=========================
CMatchChara* CMatchChara::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMatchChara* pChara = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pChara == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pChara = new CMatchChara;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pChara != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pChara->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pChara->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�`�[���̃|�C���^��Ԃ�
	return pChara;
}