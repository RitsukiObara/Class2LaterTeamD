//===========================================
//
// ���b�g�̏�Ԃ̃��C������[rat_state.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "rat_state.h"
#include "rat.h"

// �}�N����`
#define INVINCIBLE_COUNT	(60)			// ���G��Ԃ̃J�E���g��
#define SMASH_COUNT			(40)			// ������я�Ԃ̃J�E���g��
#define DAMAGE_COUNT		(10)			// �_���[�W��Ԃ̃J�E���g��

//==============================
// �R���X�g���N�^
//==============================
CRatState::CRatState()
{
	// �S�Ă̒l���N���A����
	m_State = STATE_WAIT;	// ���
	m_nStateCount = 0;		// ��ԃJ�E���g
}

//==============================
// �f�X�g���N�^
//==============================
CRatState::~CRatState()
{

}

//==============================
// ����������
//==============================
HRESULT CRatState::Init(void)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_WAIT;	// ���
	m_nStateCount = 0;		// ��ԃJ�E���g

	// OK��Ԃ�
	return S_OK;
}

//==============================
// �I������
//==============================
void CRatState::Uninit(void)
{

}

//==============================
// �X�V����
//==============================
void CRatState::Update(CRat& pRat)
{
	// ��ԃJ�E���g�����Z����
	m_nStateCount++;

	switch (m_State)
	{
	case STATE_WAIT:		// �ҋ@���
		break;
	case STATE_RUN:			// ���s���
		break;
	case STATE_ATTACK:		// �U�����
		break;
	case STATE_INVINCIBLE:	// ���G���

		if (m_nStateCount >= INVINCIBLE_COUNT)
		{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

			// �ʏ��Ԃɂ���
			m_State = STATE_WAIT;

			// ��ԃJ�E���g������������
			m_nStateCount = 0;
		}

		break;

	case STATE_DAMAGE:		// �_���[�W���

		if (m_nStateCount >= DAMAGE_COUNT)
		{ // ��ԃJ�E���g����萔�ɒB�����ꍇ

			// ���G��Ԃɂ���
			m_State = STATE_INVINCIBLE;

			// ��ԃJ�E���g������������
			m_nStateCount = 0;
		}

		break;

	case STATE_SMASH:		// ������я��

		if (m_nStateCount >= SMASH_COUNT)
		{ // ��ԃJ�E���g�����ȏ�ɂȂ����ꍇ

			// �ʏ��Ԃɂ���
			m_State = STATE_WAIT;

			// ��ԃJ�E���g������������
			m_nStateCount = 0;
		}

		break;

	case STATE_STUN:		// �C����

		break;

	case STATE_DEATH:		// ���S���

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//==============================
// ��Ԃ̐ݒ菈��
//==============================
void CRatState::SetState(const STATE state)
{
	// ��Ԃ�ݒ肷��
	m_State = state;

	// ��ԃJ�E���g������������
	m_nStateCount = 0;
}

//==============================
// ��Ԃ̎擾����
//==============================
CRatState::STATE CRatState::GetState(void)
{
	// ��Ԃ�Ԃ�
	return m_State;
}