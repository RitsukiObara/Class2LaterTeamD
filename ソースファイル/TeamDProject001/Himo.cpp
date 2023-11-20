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

CTarai* CHimo::m_pTarai[MAX_TARAI] = {};							// ���炢�̏��
//==============================
// �R���X�g���N�^
//==============================
CHimo::CHimo() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for(int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		m_pTarai[nCnt] = NULL;
	}
	m_nTaraiCount = 0;
	m_bAction = false;
	m_fDownPosY = 0.0f;
	m_fUpPosY = 0.0f;
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
		if (m_pTarai[nCnt] != NULL)
		{
			m_pTarai[nCnt]->Update();
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
		if (m_pTarai[nCnt] != NULL)
		{
			m_pTarai[nCnt]->Draw();
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
			if (m_pTarai[nCnt] == NULL)
			{
				int nRandX = rand() % 1001;
				int nRandY = rand() % 1001;

				m_pTarai[nCnt] = CTarai::Create(D3DXVECTOR3((float)nRandX - 500.0f, 1000.0f, (float)nRandY - 500.0f));
				m_pTarai[nCnt]->SetIndex(nCnt);

				break;
			}
		}
	}
}

//=====================================
// �R����������ꂽ���̏���
//=====================================
void CHimo::ActionDown(void)
{
	m_bAction = true;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHimo::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	m_fDownPosY = pos.y - 50.0f;
	m_fUpPosY = pos.y;
}

//=====================================
// �����蔻�菈��
//=====================================
bool CHimo::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CHimo::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	//// �I������
	//Uninit();

	// false ��Ԃ�
	return false;
}