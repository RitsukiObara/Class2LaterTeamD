//===========================================
//
// ���O�̃��C������[log.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "log.h"
#include "player.h"
#include "object2D.h"
#include "texture.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define LOGSIZE_BG				(D3DXVECTOR3(65.0f, 10.0f, 10.0f))		// ���O�̔w�i�̑傫��
#define LOGSIZE_PLAYERID		(D3DXVECTOR3(15.0f, 10.0f, 10.0f))		// ���O�̃v���C���[ID�̑傫��
#define LOGSIZE_MESSAGE			(D3DXVECTOR3(75.0f, 10.0f, 10.0f))		// ���O�̃��b�Z�[�W�̑傫��
#define LOGDISTANCE_PLAYERID	(-50.0f)								// ���O�̃v���C���[ID��X�ʒu
#define LOGDISTANCE_MESSAGE		(-25.0f)								// ���O�̃��b�Z�[�W��X�ʒu
#define LOGTIME					(500)									// ���O�̕\������
#define LOGSPEED_IN				(5.0f)									// ���O�̓o�ꑬ�x
#define LOGSPEED_DOWN			(1.0f)									// ���O�̗������x
#define LOGSPEED_OUT			(5.0f)									// ���O�̑ޏꑬ�x
#define LOGPOS_IN				(100.0f)								// ���O�̓o��ʒu
#define LOGPOS_DOWN				(200.0f)								// ���O�̒�~�ʒu
//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CLog::CLog() : CObject(CObject::TYPE_2DUI, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	LogPos = NONE_D3DXVECTOR3;
	m_nPlayerNumber = -1;
	m_CreateNumber = -1;
	m_State = STATE_IN;
	m_nLife = 0;
	m_Type = TYPE_DEATH;
	m_nLogIdx = -1;
	m_fLogStopPosY = 0.0f;
	m_pLogBG = NULL;
	m_pLogPlayerID = NULL;
	m_pLogMessage = NULL;
}

//==============================
// �f�X�g���N�^
//==============================
CLog::~CLog()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CLog::Init(void)
{
	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CLog::Uninit(void)
{
	// �I������
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Uninit();
		m_pLogBG = NULL;
	}

	if (m_pLogPlayerID != NULL)
	{
		m_pLogPlayerID->Uninit();
		m_pLogPlayerID = NULL;
	}

	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Uninit();
		m_pLogMessage = NULL;
	}

	Release();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CLog::Update(void)
{
	// �`�揈��
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Update();
	}
	if (m_pLogPlayerID != NULL)
	{
		m_pLogPlayerID->Update();
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Update();
	}

	StateManager();

	if (m_pLogBG != NULL)
	{
		m_pLogBG->SetPos(D3DXVECTOR3(LogPos.x, LogPos.y, 0.0f));
	}
	if (m_pLogPlayerID != NULL)
	{
		m_pLogPlayerID->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_PLAYERID, LogPos.y, 0.0f));
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_MESSAGE, LogPos.y, 0.0f));
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CLog::Draw(void)
{
	// �`�揈��
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Draw();
	}
	if (m_pLogPlayerID != NULL)
	{
		m_pLogPlayerID->Draw();
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CLog::StateManager(void)
{
	m_nLife--;

	switch (m_nPlayerNumber)
	{
		//��ʍ����̃v���C���[�̏ꍇ
	case 0:
	case 2:
		switch (m_State)
		{
		case CLog::STATE_IN:
			if (LogPos.x < LOGSIZE_BG.x)
			{
				LogPos.x += LOGSPEED_IN;
			}
			else
			{
				LogPos.x = LOGSIZE_BG.x;
				m_State = STATE_DOWN;
			}
			break;
		case CLog::STATE_DOWN:

			if (LogPos.y < m_fLogStopPosY - (m_CreateNumber * LOGSIZE_BG.y * 2.0f))
			{
				LogPos.y += LOGSPEED_DOWN;
			}
			else
			{
				LogPos.y = m_fLogStopPosY - (m_CreateNumber * LOGSIZE_BG.y * 2.0f);
			}

			if (m_nLife <= 0)
			{
				m_State = STATE_OUT;
			}

			break;
		case CLog::STATE_OUT:
			if (LogPos.x > -LOGSIZE_BG.x)
			{
				LogPos.x -= LOGSPEED_OUT;
			}
			else
			{
				m_pMain->DelLogNumber(m_nLogIdx);
			}
			break;
		default:
			assert(false);
			break;
		}
		break;

		//��ʉE���̃v���C���[�̏ꍇ
	case 1:
	case 3:
		switch (m_State)
		{
		case CLog::STATE_IN:
			if (LogPos.x > -LOGSIZE_BG.x + SCREEN_WIDTH)
			{
				LogPos.x -= LOGSPEED_IN;
			}
			else
			{
				LogPos.x = -LOGSIZE_BG.x + SCREEN_WIDTH;
				m_State = STATE_DOWN;
			}
			break;
		case CLog::STATE_DOWN:

			if (LogPos.y < m_fLogStopPosY - (m_CreateNumber * LOGSIZE_BG.y * 2.0f))
			{
				LogPos.y += LOGSPEED_DOWN;
			}
			else
			{
				LogPos.y = m_fLogStopPosY - (m_CreateNumber * LOGSIZE_BG.y * 2.0f);
			}

			if (m_nLife <= 0)
			{
				m_State = STATE_OUT;
			}

			break;
		case CLog::STATE_OUT:
			if (LogPos.x < LOGSIZE_BG.x + SCREEN_WIDTH)
			{
				LogPos.x += LOGSPEED_OUT;
			}
			else
			{
				m_pMain->DelLogNumber(m_nLogIdx);
			}
			break;
		default:
			assert(false);
			break;
		}
		break;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CLog::SetData(int DrawIdx, int LogIdx, int nCreateNumber, CLog::TYPE Type)
{
	m_nPlayerNumber = DrawIdx;
	m_CreateNumber = nCreateNumber;
	m_Type = Type;
	m_nLife = LOGTIME;

	if (m_pLogBG == NULL)
	{
		m_pLogBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogBG->SetPos(D3DXVECTOR3(LogPos.x, LogPos.y, 0.0f));
		m_pLogBG->SetPosOld(LogPos);
		m_pLogBG->SetRot(NONE_D3DXVECTOR3);
		m_pLogBG->SetSize(LOGSIZE_BG);
		m_pLogBG->SetLength();
		m_pLogBG->SetAngle();
		m_pLogBG->SetVertex();
		m_pLogBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\CageWall.png"));
	}
	if (m_pLogPlayerID == NULL)
	{
		m_pLogPlayerID = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogPlayerID->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_PLAYERID, LogPos.y, 0.0f));
		m_pLogPlayerID->SetPosOld(LogPos);
		m_pLogPlayerID->SetRot(NONE_D3DXVECTOR3);
		m_pLogPlayerID->SetSize(LOGSIZE_PLAYERID);
		m_pLogPlayerID->SetLength();
		m_pLogPlayerID->SetAngle();
		m_pLogPlayerID->SetVertex();

		switch (LogIdx)
		{
		case 0:
			m_pLogPlayerID->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_1P.png"));
			break;
		case 1:
			m_pLogPlayerID->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_2P.png"));
			break;
		case 2:
			m_pLogPlayerID->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_3P.png"));
			break;
		case 3:
			m_pLogPlayerID->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_4P.png"));
			break;

		default:
			assert(false);
			break;
		}
	}
	if (m_pLogMessage == NULL)
	{
		m_pLogMessage = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogMessage->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_MESSAGE, LogPos.y, 0.0f));
		m_pLogMessage->SetPosOld(LogPos);
		m_pLogMessage->SetRot(NONE_D3DXVECTOR3);
		m_pLogMessage->SetSize(LOGSIZE_MESSAGE);
		m_pLogMessage->SetLength();
		m_pLogMessage->SetAngle();
		m_pLogMessage->SetVertex();

		switch (m_Type)
		{
		case CLog::TYPE_DEATH:
			m_pLogMessage->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\log_2.png"));
			break;
		case CLog::TYPE_STUN:
			m_pLogMessage->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\log_1.png"));
			break;
		case CLog::TYPE_REVIVAL:
			m_pLogMessage->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\log_3.png"));
			break;
		default:
			break;
		}
	}

	switch (m_nPlayerNumber)
	{
	case 0:
		LogPos = D3DXVECTOR3(-200.0f, LOGPOS_IN, 0.0f);
		m_fLogStopPosY = LOGPOS_DOWN;
		break;

	case 1:
		LogPos = D3DXVECTOR3(SCREEN_WIDTH + 200.0f, LOGPOS_IN, 0.0f);
		m_fLogStopPosY = LOGPOS_DOWN;
		break;

	case 2:
		LogPos = D3DXVECTOR3(-200.0f, LOGPOS_IN + 360.0f, 0.0f);
		m_fLogStopPosY = LOGPOS_DOWN + 360.0f;
		break;

	case 3:
		LogPos = D3DXVECTOR3(SCREEN_WIDTH + 200.0f, LOGPOS_IN + 360.0f, 0.0f);
		m_fLogStopPosY = LOGPOS_DOWN + 360.0f;
		break;

	default:
		// ���炩�ɃG���[�ł��킷
		assert(false);
		break;
	}
}

//=======================================
// ��������
//=======================================
CLog* CLog::Create(int DrawIdx, int LogIdx, int nCreateNumber, CLog::TYPE Type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CLog* pSample = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pSample == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pSample = new CLog;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSample != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pSample->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSample->SetData(DrawIdx, LogIdx, nCreateNumber, Type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pSample;
}