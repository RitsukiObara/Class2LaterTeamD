//===========================================
//
// �R�b�v�̏���[cup.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "cup.h"
#include "useful.h"
#include "objectX.h"
#include "consent.h"
#include "object3D.h"
#include "input.h"
#include "texture.h"

//==============================
// �R���X�g���N�^
//==============================
CCup::CCup() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;
	m_State = STATE_FALSE;
	m_pWater = NULL;
	m_pConsent = NULL;
	m_WaterSize = NONE_D3DXVECTOR3;
}

//==============================
// �f�X�g���N�^
//==============================
CCup::~CCup()
{

}

//==============================
// �R�b�v�̏���������
//==============================
HRESULT CCup::Init(void)
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
// �R�b�v�̏I������
//========================================
void CCup::Uninit(void)
{
	if (m_pConsent != NULL)
	{ // �R���Z���g�� NULL �̏ꍇ

	  // �R���Z���g�̏I������
		m_pConsent->Uninit();
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �R�b�v�̍X�V����
//=====================================
void CCup::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	StateManager(&pos, &rot);

	//�ʒu�X�V
	pos += m_move;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�{�^�����������ꍇ
		Action();
	}

	SetPos(pos);
	SetRot(rot);
}

//=====================================
// �R�b�v�̕`�揈��
//=====================================
void CCup::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	if (m_pConsent != NULL)
	{
		m_pConsent->Draw();
	}
}

//=====================================
// ��ԊǗ�
//=====================================
void CCup::StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	switch (m_State)
	{
	case CCup::STATE_FALSE:

		break;

	case CCup::STATE_FALLWAIT:	//�M�~�b�N�N��������ʔ����܂ł̏�������
		rot->z += 0.07;
		m_move.y -= 0.75f;
		m_move.x = sinf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;

		if (pos->y < 15.0f)
		{
			pos->y = 15.0f;
			m_State = STATE_TRUE;

			m_pWater = CObject3D::Create(CObject3D::TYPE_3DPOLYGON);
			m_pWater->SetPos(GetPos());
			m_pWater->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
			m_pWater->SetSize(m_WaterSize);
			m_pWater->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\water.png"));
		}
		break;

	case CCup::STATE_TRUE:	//�M�~�b�N�̌��ʔ��������~�܂ł̏���
		m_move = NONE_D3DXVECTOR3;
		pos->y = 15.0f;

		D3DXVECTOR3 WaterPos = m_pWater->GetPos();

		if (m_WaterSize.x < 150.0f)
		{
			WaterPos.x += sinf(0.0f + (D3DX_PI * -0.5f)) * 0.5f;
			WaterPos.z += cosf(0.0f + (D3DX_PI * -0.5f)) * 0.5f;
			m_WaterSize.x += 0.5f;
			m_WaterSize.y += 0.5f;
		}

		m_pWater->SetPos(WaterPos);
		m_pWater->SetSize(m_WaterSize);
		break;
	}
}

//=====================================
// �R����������ꂽ���̏���
//=====================================
void CCup::Action(void)
{
	if (m_State == STATE_FALSE)
	{
		m_State = STATE_FALLWAIT;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCup::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	if (m_pConsent == NULL)
	{
		m_pConsent = CConsent::Create(D3DXVECTOR3(
			pos.x + sinf(0.0f + (D3DX_PI * -0.5f)) * 200.0f,
			0.0f,
			pos.z + cosf(0.0f + (D3DX_PI * -0.5f)) * 200.0f));
		m_pConsent->SetMain(this);
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CCup::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CCup::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	if (m_pConsent != nullptr)
	{ // �R���Z���g�� NULL ����Ȃ��ꍇ

		if (pos.y <= m_pConsent->GetPos().y + m_pConsent->GetFileData().vtxMax.y &&
			pos.y + fHeight >= m_pConsent->GetPos().y + m_pConsent->GetFileData().vtxMin.y &&
			useful::CylinderInner(pos, m_pConsent->GetPos(), m_pConsent->GetFileData().fRadius + fWidth) == true)
		{ // �����蔻��̒��ɓ������ꍇ

		  // true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CCup::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{//�~�͈͓̔��̏ꍇture��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}