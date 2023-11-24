//===========================================
//
// �X�s�[�J�[�̏���[Himo.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "speaker.h"
#include "useful.h"
#include "objectX.h"
#include "note.h"
#include "input.h"

#define SPEAKER_RADIUS (50.0f)	//�����̏o���Ԋu(�t���[��)
#define NOTE_INTERVAL (20)	//�����̏o���Ԋu(�t���[��)
#define NOTE_LIFE (120)		//�����̎���
#define NOTE_SPEED (15.0f)	//�����̑���

CNote* CSpeaker::m_apNote[MAX_NOTE] = {};							// �����̏��
//==============================
// �R���X�g���N�^
//==============================
CSpeaker::CSpeaker() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		m_apNote[nCnt] = NULL;
	}
	m_bAction = false;
	m_nNoateCount = 0;
}

//==============================
// �f�X�g���N�^
//==============================
CSpeaker::~CSpeaker()
{

}

//==============================
// �X�s�[�J�[�̏���������
//==============================
HRESULT CSpeaker::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �X�s�[�J�[�̏I������
//========================================
void CSpeaker::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != nullptr)
		{ // ������ NULL �̏ꍇ

			// �����̏I������
			m_apNote[nCnt]->Uninit();
			m_apNote[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �X�s�[�J�[�̍X�V����
//=====================================
void CSpeaker::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_bAction == true)
	{
		SetNote();
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // A�{�^�����������ꍇ
		m_bAction = m_bAction ? false : true;
	}

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != NULL)
		{
			m_apNote[nCnt]->Update();
		}
	}

	SetPos(pos);
}

//=====================================
// �X�s�[�J�[�̕`�揈��
//=====================================
void CSpeaker::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != NULL)
		{
			m_apNote[nCnt]->Draw();
		}
	}
}

//=====================================
// �����̐�������
//=====================================
void CSpeaker::SetNote(void)
{
	m_nNoateCount++;

	if (m_nNoateCount % NOTE_INTERVAL == 0)
	{
		for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
		{
			if (m_apNote[nCnt] == NULL)
			{
				D3DXVECTOR3 pos = GetPos();
				D3DXVECTOR3 rot = GetRot();

				m_apNote[nCnt] = CNote::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));
				m_apNote[nCnt]->SetIndex(nCnt);
				m_apNote[nCnt]->SetLife(NOTE_LIFE);
				m_apNote[nCnt]->SetMove(D3DXVECTOR3(
					sinf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED,
					0.0f,
					cosf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED));
				break;
			}
		}
	}
}

//=====================================
// �R����������ꂽ���̏���
//=====================================
void CSpeaker::Action(void)
{
	m_bAction = true;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSpeaker::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CSpeaker::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CSpeaker::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	for (int nCntNote = 0; nCntNote < MAX_NOTE; nCntNote++)
	{
		if (m_apNote[nCntNote] != nullptr)
		{ // ������ NULL ����Ȃ��ꍇ

			if (pos.y <= m_apNote[nCntNote]->GetPos().y + m_apNote[nCntNote]->GetFileData().vtxMax.y &&
				pos.y + fHeight >= m_apNote[nCntNote]->GetPos().y + m_apNote[nCntNote]->GetFileData().vtxMin.y &&
				useful::CylinderInner(pos,m_apNote[nCntNote]->GetPos(),m_apNote[nCntNote]->GetFileData().fRadius + fWidth) == true)
			{ // �����蔻��̒��ɓ������ꍇ

				// true ��Ԃ�
				return true;
			}
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CSpeaker::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CObstacle::COLLTYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{//�~�͈͓̔��̏ꍇture��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}