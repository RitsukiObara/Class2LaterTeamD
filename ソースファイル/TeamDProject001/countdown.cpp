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
#define COUNT_FRAME			(50)	// 1�J�E���g���Ƃ̃t���[����

//=========================
// �R���X�g���N�^
//=========================
CCountdown::CCountdown() : CNumber(CObject::TYPE_COUNTDOWN, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_nFrame = 0;			// �o�߃t���[����
	m_nSecond = 0;			// �b��
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
	m_nFrame = 0;			// �o�߃t���[����
	m_nSecond = 0;			// �b��

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
	// �v�Z����
	Calculate();

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

	// �S�Ă̒l������������
	m_nFrame = 0;				// �o�߃t���[����
	m_nSecond = COUNTDOWN_TIME;	// �b��

	// ���_���̏�����
	SetVertexRot();

	// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
	SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_nSecond);

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

//=========================
// �v�Z����
//=========================
void CCountdown::Calculate(void)
{
	// ���Ԃ̌o�߂����Z����
	m_nFrame++;

	if ((m_nFrame % COUNT_FRAME) == 0)
	{ // 1�b�o������

		// 1�b���炷
		m_nSecond--;

		if (m_nSecond <= 0)
		{ // ���Ԃ�0�𒴂����ꍇ

			// ���Ԃ�␳����
			m_nSecond = 0;
		}

		// �����̐ݒ菈��
		SetNumber(m_nSecond);

		// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
		SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_nSecond);
	}
}