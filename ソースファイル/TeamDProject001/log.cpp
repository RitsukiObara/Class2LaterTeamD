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
#define LOGSIZE_BG			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ���O�̔w�i�̑傫��
#define LOGSIZE_PLAYERID	(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ���O�̃v���C���[ID�̑傫��
#define LOGSIZE_MESSAGE		(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ���O�̃��b�Z�[�W�̑傫��
#define STUN_WAIT			(300)			// ���O�̕\������
#define CAT_CAMERA_HEIGHT	(200.0f)		// ���O�̏o���X�s�[�h
#define CAT_CAMERA_HEIGHT	(200.0f)		// ���O�̗������x
#define CAT_CAMERA_HEIGHT	(200.0f)		// ���O��
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
		m_pLogPlayerID->SetPos(D3DXVECTOR3(LogPos.x - 40.0f, LogPos.y, 0.0f));
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->SetPos(D3DXVECTOR3(LogPos.x + 40.0f, LogPos.y, 0.0f));
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

	switch (m_State)
	{
	case CLog::STATE_IN:
		if (LogPos.x <= 200.0f)
		{
			LogPos.x += 10.0f;
		}
		else
		{
			LogPos.x = 200.0f;
			m_State = STATE_DOWN;
		}
		break;
	case CLog::STATE_DOWN:

		if (LogPos.y < 200.0f)
		{
			LogPos.y += 10.0f;
		}
		else
		{
			LogPos.y = 200.0f;
		}

		if (m_nLife <= 0)
		{
			m_State = STATE_OUT;
		}

		break;
	case CLog::STATE_OUT:
		if (LogPos.x >= -200.0f)
		{
			LogPos.x -= 2.0f;
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
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CLog::SetData(int nIdex, int nCreateNumber, CLog::TYPE Type)
{
	m_nPlayerNumber = nIdex;
	m_CreateNumber = nCreateNumber;
	m_Type = Type;
	m_nLife = 120;

	LogPos = D3DXVECTOR3(-200.0f, 100.0f, 0.0f);

	if (m_pLogBG == NULL)
	{
		m_pLogBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogBG->SetPos(D3DXVECTOR3(LogPos.x, LogPos.y, 0.0f));
		m_pLogBG->SetPosOld(LogPos);
		m_pLogBG->SetRot(NONE_D3DXVECTOR3);
		m_pLogBG->SetSize(D3DXVECTOR3(100.0f, 50.0f, 0.0f));
		m_pLogBG->SetLength();
		m_pLogBG->SetAngle();
		m_pLogBG->SetVertex();
		m_pLogBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\CageWall.png"));
	}
	if (m_pLogPlayerID == NULL)
	{
		m_pLogPlayerID = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogPlayerID->SetPos(D3DXVECTOR3(LogPos.x - 40.0f, LogPos.y, 0.0f));
		m_pLogPlayerID->SetPosOld(LogPos);
		m_pLogPlayerID->SetRot(NONE_D3DXVECTOR3);
		m_pLogPlayerID->SetSize(D3DXVECTOR3(40.0f, 30.0f, 0.0f));
		m_pLogPlayerID->SetVtxTextureAnim(0.25f, nIdex);
		m_pLogPlayerID->SetLength();
		m_pLogPlayerID->SetAngle();
		m_pLogPlayerID->SetVertex();
		m_pLogPlayerID->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID.png"));
	}
	if (m_pLogMessage == NULL)
	{
		m_pLogMessage = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY::PRIORITY_UI);
		m_pLogMessage->SetPos(D3DXVECTOR3(LogPos.x + 40.0f, LogPos.y, 0.0f));
		m_pLogMessage->SetPosOld(LogPos);
		m_pLogMessage->SetRot(NONE_D3DXVECTOR3);
		m_pLogMessage->SetSize(D3DXVECTOR3(40.0f, 30.0f, 0.0f));
		m_pLogMessage->SetLength();
		m_pLogMessage->SetAngle();
		m_pLogMessage->SetVertex();

		switch (m_Type)
		{
		case CLog::TYPE_DEATH:
			m_pLogMessage->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\log.2.png"));
			break;
		case CLog::TYPE_STUN:
			m_pLogMessage->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\log.1.png"));
			break;
		default:
			break;
		}
	}

	switch (m_nPlayerNumber)
	{
	case 0:
		LogPos = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
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
CLog* CLog::Create(int nIdex, int nCreateNumber, CLog::TYPE Type)
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
		pSample->SetData(nIdex, nCreateNumber, Type);
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