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
#include "object2D.h"
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
CLog::CLog() : CObject(CObject::TYPE_2DUI, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	LogPos = NONE_D3DXVECTOR3;
	m_nPlayerNumber = -1;
	m_CreateNumber = -1;
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
void CLog::SetData(int nIdex, int nCreateNumber)
{
	m_nPlayerNumber = nIdex;
	m_CreateNumber = nCreateNumber;

	switch (m_nPlayerNumber)
	{
	case 0:
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

	LogPos = D3DXVECTOR3(100.0f, 200.0f, 0.0f);

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
		m_pLogMessage->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\CageWall.png"));
	}
}

//=======================================
// ��������
//=======================================
CLog* CLog::Create(int nIdex, int nCreateNumber)
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
		pSample->SetData(nIdex, nCreateNumber);
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