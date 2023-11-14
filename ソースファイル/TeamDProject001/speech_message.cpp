//=======================================
//
// �`�B���b�Z�[�W�̃��C������[speech_message.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "speech_message.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define HELP_TEXTURE		"data\\TEXTURE\\HelpMessage.png"		// �~���v���̃e�N�X�`��
#define MESSAGE_NONE_LIFE	(-1)		// ��������(����)�̒l

//=========================
// �R���X�g���N�^
//=========================
CSpeechMessage::CSpeechMessage() : CBillboard(CObject::TYPE_EFFECT, CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
	m_nLife = 0;			// ����
	m_type = TYPE_HELP;		// ���
}

//=========================
// �f�X�g���N�^
//=========================
CSpeechMessage::~CSpeechMessage()
{

}

//=========================
// ����������
//=========================
HRESULT CSpeechMessage::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nLife = 0;			// ����
	m_type = TYPE_HELP;		// ���

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CSpeechMessage::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CSpeechMessage::Update(void)
{
	
}

//=========================
// �`�揈��
//=========================
void CSpeechMessage::Draw(void)
{
	// �`�揈��
	CBillboard::DrawLightOff();
}

//=========================
// ���̐ݒ菈��
//=========================
void CSpeechMessage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const TYPE type)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu�ݒ�
	SetSize(size);			// �T�C�Y�ݒ�

	// �S�Ă̒l������������
	m_type = type;			// ���
	m_nLife = nLife;		// ����

	// ���_���̏�����
	SetVertex();

	switch (m_type)
	{
	case CSpeechMessage::TYPE_HELP:

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(HELP_TEXTURE));

		break;

	default:

		// ���ɂȂ�

		break;
	}
}

//=========================
// ��������
//=========================
CSpeechMessage* CSpeechMessage::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSpeechMessage* pMessage = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pMessage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMessage = new CSpeechMessage;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMessage != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pMessage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pMessage->SetData(pos, size, nLife, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �`�B���b�Z�[�W�̃|�C���^��Ԃ�
	return pMessage;
}