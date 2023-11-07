//============================================
//
// ���ԏ���[time.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "game_timer.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"

#include "pause.h"

//--------------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------------
CGameTime* CGameTime::m_pGameTimer = nullptr;		// �Q�[���^�C�}�[�̏��

//--------------------------------------------------
// �}�N����`
//--------------------------------------------------
#define TIME_POS			(D3DXVECTOR3(500.0f, 50.0f, 0.0f))		// �Q�[���^�C�}�[�̓_�̃T�C�Y
#define TIME_SIZE			(D3DXVECTOR3(25.0f, 40.0f, 0.0f))		// �Q�[���^�C�}�[�̓_�̃T�C�Y
#define TIME_DOT_SIZE		(D3DXVECTOR3(8.0f, 8.0f, 0.0f))			// �Q�[���^�C�}�[�̓_�̃T�C�Y
#define TIME_WIDTH_SHIFT	(50.0f)									// �Q�[���^�C�}�[�̂��炷����

//========================
// �R���X�g���N�^
//========================
CGameTime::CGameTime() : CTime(CObject::TYPE_TIME, CObject::PRIORITY_UI)
{
	// �S�Ă̒l������������
	m_StartTime = 0;		// �J�n����
	m_PauseTime = 0;		// �|�[�Y���̎���
	m_bGoal = false;		// �S�[����
}

//========================
// �f�X�g���N�^
//========================
CGameTime::~CGameTime()
{

}

//========================
// ����������
//========================
HRESULT CGameTime::Init(void)
{
	// �S�Ă̒l������������
	m_StartTime = 0;		// �J�n����
	m_bGoal = false;		// �S�[����
	m_PauseTime = 0;		// �|�[�Y���̎���

	if (FAILED(CTime::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CGameTime::Uninit(void)
{
	// �^�C���̏I������
	CTime::Uninit();

	// �Q�[���^�C�}�[�� NULL �ɂ���
	m_pGameTimer = nullptr;
}

//========================
// �X�V����
//========================
void CGameTime::Update(void)
{
	if (CGame::GetPause() != nullptr)
	{ // �|�[�Y�̏�񂪂���ꍇ

		if (CGame::GetPause()->GetPause() == true &&
			CGame::GetState() == CGame::STATE_PLAY)
		{ // �|�[�Y�����A�v���C���̏ꍇ

			// �|�[�Y���̏���
			PauseProcess();
		}
		else
		{ // ��L�ȊO

			if (CGame::GetState() != CGame::STATE_START)
			{ // �X�^�[�g��Ԃ܂��́A�J�E���g�_�E����ԈȊO�̏ꍇ

				// �ʏ�̍X�V����
				Basic();
			}
		}
	}
	else
	{ // ��L�ȊO

		if (CGame::GetState() != CGame::STATE_START)
		{ // �X�^�[�g��Ԃ܂��́A�J�E���g�_�E����ԈȊO�̏ꍇ

			// �ʏ�̍X�V����
			Basic();
		}
	}
}

//========================
// �`�揈��
//========================
void CGameTime::Draw(void)
{
	// �`�揈��
	CTime::Draw();
}

//========================
// �^�C���̊J�n����
//========================
void CGameTime::TimeStart(void)
{
	// ���݂̎������擾����
	m_StartTime = timeGetTime();
}

//========================
// �ʏ�̍X�V����
//========================
void CGameTime::Basic(void)
{
	if (CGame::GetState() == CGame::STATE_GOAL)
	{ // �S�[����Ԃ̏ꍇ

		// �S�[���󋵂� true �ɂ���
		m_bGoal = true;
	}

	if (m_bGoal == false)
	{ // �S�[���󋵂� false �̏ꍇ

		// �v�Z����
		Calculate();

		// 1�����Ƃ̃e�N�X�`���̐ݒ菈��
		SetTexture();
	}
}

//========================
// �|�[�Y���̏���
//========================
void CGameTime::PauseProcess(void)
{
	// ���[�J���ϐ��錾
	DWORD NowTime = timeGetTime();		// ���݂̎���
	DWORD TotalTime = GetTotalTime();	// ���v����

	// �|�[�Y���̎��Ԃ�ݒ肷��
	m_PauseTime = (NowTime - m_StartTime) - TotalTime;
}

//========================
// �v�Z����
//========================
void CGameTime::Calculate(void)
{
	// ���[�J���ϐ��錾
	DWORD NowTime;				// ���݂̎���

	// ���ݎ������擾����
	NowTime = timeGetTime();

	// �o�߂����b���𑪂�
	SetTotalTime((NowTime - m_StartTime) - m_PauseTime);

	if (GetTotalTime() >= MAX_TIME)
	{ // �o�ߎ��Ԃ� �ő吔 �𒴂����ꍇ

		// �o�ߎ��Ԃ�␳����
		SetTotalTime(MAX_TIME);
	}

	// ���l�̐ݒ菈��
	SetNumber();
}

//========================
// �擾����
//========================
CGameTime* CGameTime::Get(void)
{
	if (m_pGameTimer != nullptr)
	{ // �Q�[���^�C�}�[�� NULL ����Ȃ������ꍇ

		// �Q�[���^�C����Ԃ�
		return m_pGameTimer;
	}
	else
	{ // ��L�ȊO

		// �������ĕԂ�
		return m_pGameTimer = CGameTime::Create();
	}
}

//========================
// ��������
//========================
CGameTime* CGameTime::Create(void)
{
	if (m_pGameTimer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		m_pGameTimer = new CGameTime;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (m_pGameTimer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pGameTimer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pGameTimer->SetData(TIME_POS, NONE_D3DXVECTOR3, TIME_SIZE, TIME_DOT_SIZE, TIME_WIDTH_SHIFT);

		// ���ݎ�����ݒ肷��
		m_pGameTimer->m_StartTime = timeGetTime();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���Ԃ̃|�C���^��Ԃ�
	return m_pGameTimer;
}