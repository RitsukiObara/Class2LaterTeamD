//===========================================
//
// �J�[�e���̏���[curtain.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "curtain.h"
#include "useful.h"
#include "input.h"

#include "switch.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	static const D3DXVECTOR3 SWITCH_POS[MAX_SWITCH] =		// �X�C�b�`�̈ʒu
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
	};
	static const D3DXVECTOR3  SWITCH_ROT[MAX_SWITCH] =		// �X�C�b�`�̌���
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
	};
}
#define CLOSE_SCALE		(0.03f)		// ������Ԃ̊g�嗦
#define SCALE_CORRECT	(0.01f)		// �g�嗦�̕␳��
#define OPEN_SCALE		(1.0f)		// �J������Ԃ̊g�嗦

//==============================
// �R���X�g���N�^
//==============================
CCurtain::CCurtain() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// �X�C�b�`�̏��
	}
	m_state = STATE_CLOSE;				// ���
	SetCatUse(false);					// �l�R�̎g�p����
	SetRatUse(true);					// �l�Y�~�̎g�p����
}

//==============================
// �f�X�g���N�^
//==============================
CCurtain::~CCurtain()
{

}

//==============================
// �J�[�e���̏���������
//==============================
HRESULT CCurtain::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_state = STATE_CLOSE;				// ���
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// ���f���̏��
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �J�[�e���̏I������
//========================================
void CCurtain::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̏I������
			m_apSwitch[nCnt]->Uninit();
			m_apSwitch[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �J�[�e���̍X�V����
//=====================================
void CCurtain::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// ��ԃ}�l�[�W���[
	StateManager();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̍X�V����
			m_apSwitch[nCnt]->Update();
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�L�[���������ꍇ

		// ��Ԃ�ݒ肷��
		m_state = (STATE)((m_state + 1) % STATE_MAX);
	}
}

//=====================================
// �J�[�e���̕`�揈��
//=====================================
void CCurtain::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̕`�揈��
			m_apSwitch[nCnt]->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCurtain::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �g�嗦������������
	SetScale(D3DXVECTOR3(1.0f, 1.0f, CLOSE_SCALE));

	// �S�Ă̒l��ݒ肷��
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̐�������
			m_apSwitch[nCnt] = CSwitch::Create(SWITCH_POS[nCnt], SWITCH_ROT[nCnt]);
		}
	}
	m_state = STATE_CLOSE;		// ���
}

//=====================================
// ��ԃ}�l�[�W���[
//=====================================
void CCurtain::StateManager(void)
{
	// �g�嗦���擾����
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CCurtain::STATE_CLOSE:		// ������

		// �ϓ��ȕ␳����
		useful::FrameCorrect(CLOSE_SCALE, &scale.z, SCALE_CORRECT);

		break;

	case CCurtain::STATE_OPEN:		// �J�������

		// �ϓ��ȕ␳����
		useful::FrameCorrect(OPEN_SCALE, &scale.z, SCALE_CORRECT);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �g�嗦��K�p����
	SetScale(scale);
}