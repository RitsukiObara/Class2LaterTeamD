//===========================================
//
// �G���g���[��ʂ̐����̃��C������[entry_message.cpp]
// Author ����������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "entry_message.h"
#include "texture.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CEntryMessage::CEntryMessage() : CObject2D(CObject::TYPE_ENTRYMESSAGEUI, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CEntryMessage::~CEntryMessage()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CEntryMessage::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CEntryMessage::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CEntryMessage::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CEntryMessage::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CEntryMessage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	//NONE_SCALE						// �g�嗦��ύX���Ȃ��Ƃ��Ƃ��Ɏg��

	// ���̐ݒ菈��
	SetPos(pos);				// �ʒu
	SetPosOld(posOld);			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);	// ����
	SetSize(size);				// �T�C�Y
	SetLength();				// ����
	SetAngle();					// ����
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\entry_message00.png"));		// �e�N�X�`���̊��蓖�ď���

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=======================================
// ��������
//=======================================
CEntryMessage* CEntryMessage::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryMessage* pEntryMessage = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pEntryMessage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pEntryMessage = new CEntryMessage;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntryMessage != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntryMessage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntryMessage->SetData(pos, posOld, size);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pEntryMessage;
}