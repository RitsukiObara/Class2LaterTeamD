//===========================================
//
// �Ђ��̏���[Himo.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Himo.h"
#include "useful.h"
#include "objectX.h"
#include "tarai.h"
#include "input.h"

#define TARAI_FALL_AREA_X (3001)	//���炢�̗����͈�(X)
#define TARAI_FALL_AREA_Z (2001)	//���炢�̗����͈�(Z)

CTarai* CHimo::m_apTarai[MAX_TARAI] = {};							// ���炢�̏��
//==============================
// �R���X�g���N�^
//==============================
CHimo::CHimo() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for(int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		m_apTarai[nCnt] = NULL;
	}
	m_nTaraiCount = 0;
	m_bAction = false;
	m_fDownPosY = 0.0f;
	m_fUpPosY = 0.0f;
	SetCatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CHimo::~CHimo()
{

}

//==============================
// �Ђ��̏���������
//==============================
HRESULT CHimo::Init(void)
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
// �Ђ��̏I������
//========================================
void CHimo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != nullptr)
		{ // �^���C�� NULL ����Ȃ��ꍇ

			// �^���C�̏I������
			m_apTarai[nCnt]->Uninit();
			m_apTarai[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �Ђ��̍X�V����
//=====================================
void CHimo::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_bAction == true)
	{
		if (pos.y > m_fDownPosY)
		{
			pos.y -= 2.0f;
		}

		SetTarai();
	}
	else
	{
		if (pos.y < m_fUpPosY)
		{
			pos.y += 2.0f;
		}
	}

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{
			m_apTarai[nCnt]->Update();
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // A�{�^�����������ꍇ
		m_bAction = m_bAction ? false : true;
	}

	SetPos(pos);
}

//=====================================
// �Ђ��̕`�揈��
//=====================================
void CHimo::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{
			m_apTarai[nCnt]->Draw();
		}
	}
}

//=====================================
// ���炢�̐�������
//=====================================
void CHimo::SetTarai(void)
{
	m_nTaraiCount++;

	if (m_nTaraiCount % 5 == 0)
	{
		for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
		{
			if (m_apTarai[nCnt] == NULL)
			{
				int nRandX = rand() % TARAI_FALL_AREA_X;
				int nRandY = rand() % TARAI_FALL_AREA_Z;

				m_apTarai[nCnt] = CTarai::Create(D3DXVECTOR3((float)nRandX - ((float)TARAI_FALL_AREA_X * 0.5f), 1000.0f, (float)nRandY - ((float)TARAI_FALL_AREA_Z * 0.5f)));
				m_apTarai[nCnt]->SetIndex(nCnt);

				break;
			}
		}
	}
}

//=====================================
// �R����������ꂽ���̏���
//=====================================
void CHimo::Action(void)
{
	m_bAction = true;
	SetAction(true);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHimo::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	m_fDownPosY = pos.y - 50.0f;
	m_fUpPosY = pos.y;
}

//=====================================
// �q�b�g����
//=====================================
bool CHimo::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	for (int nCntTarai = 0; nCntTarai < MAX_TARAI; nCntTarai++)
	{
		if (m_apTarai[nCntTarai] != nullptr)
		{ // �^���C�� NULL ����Ȃ��ꍇ

			if (pos.y + collSize.y <= m_apTarai[nCntTarai]->GetPosOld().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				pos.y + collSize.y >= m_apTarai[nCntTarai]->GetPos().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				useful::CylinderInner(pos, m_apTarai[nCntTarai]->GetPos(), m_apTarai[nCntTarai]->GetFileData().fRadius + collSize.x) == true)
			{ // �^���C������ɗ����Ă����ꍇ

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
bool CHimo::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{//�~�͈͓̔��̏ꍇture��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}