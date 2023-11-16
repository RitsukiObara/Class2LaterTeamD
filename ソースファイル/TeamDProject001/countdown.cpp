//=======================================
//
// �J�E���g�_�E���̃��C������[countdown.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "countdown.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define COUNTDOWN_TIME		(5)		// �J�E���g�_�E���̎���

//=========================
// �R���X�g���N�^
//=========================
CCountdown::CCountdown() : CNumber(CObject::TYPE_COUNTDOWN, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
}

//=========================
// �f�X�g���N�^
//=========================
CCountdown::~CCountdown()
{

}

//=========================
// ����������
//=========================
HRESULT CCountdown::Init(void)
{
	if (FAILED(CNumber::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CCountdown::Uninit(void)
{
	// �I��
	CNumber::Uninit();
}

//=========================
// �X�V����
//=========================
void CCountdown::Update(void)
{
	// ���_���̏�����
	SetVertexRot();
}

//=========================
// �`�揈��
//=========================
void CCountdown::Draw(void)
{
	// �`�揈��
	CNumber::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CCountdown::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// �����̐ݒ菈��
	SetPos(pos);				// �ʒu
	SetPosOld(pos);				// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);	// ����
	SetSize(size);				// �T�C�Y
	SetLength();				// ����
	SetAngle();					// ����
	SetNumber(COUNTDOWN_TIME);	// ����
	SetType(TYPE_DECIMAL);		// ���

	// ���_���̏�����
	SetVertexRot();

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\Number.png"));
}

//=========================
// ��������
//=========================
CCountdown* CCountdown::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCountdown* pCountdown = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCountdown == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCountdown = new CCountdown;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCountdown != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCountdown->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCountdown->SetData(pos, size);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �J�E���g�_�E���̃|�C���^��Ԃ�
	return pCountdown;
}