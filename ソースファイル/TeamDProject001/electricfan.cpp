//===========================================
//
// ��@�̏���[electricfan.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "electricfan.h"
#include "manager.h"
#include "renderer.h"

#include "fan_blade.h"
#include "fan_wind.h"
#include "input.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define FAN_SHIFT		(175.0f)		// ��@�̉H���̂��炷����
#define WIND_CIRCUM		(80.0f)			// ��@�̕��̉~���̑傫��
#define WIND_HEIGHT		(1600.0f)		// ��@�̕��̍���

//==============================
// �R���X�g���N�^
//==============================
CElecFan::CElecFan() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pFan = nullptr;			// ��@�̃t�@��
	m_pWind = nullptr;			// ��@�̕��̏��
	m_bPower = false;			// �d����
}

//==============================
// �f�X�g���N�^
//==============================
CElecFan::~CElecFan()
{

}

//==============================
// ��@�̏���������
//==============================
HRESULT CElecFan::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pFan = nullptr;			// ��@�̃t�@��
	m_pWind = nullptr;			// ��@�̕��̏��
	m_bPower = false;			// �d����

	// �l��Ԃ�
	return S_OK;
}

//========================================
// ��@�̏I������
//========================================
void CElecFan::Uninit(void)
{
	if (m_pFan != nullptr)
	{ // �t�@���� NULL ����Ȃ��ꍇ

		// �t�@���̏I������
		m_pFan->Uninit();
		m_pFan = nullptr;
	}

	if (m_pWind != nullptr)
	{ // ���� NULL ����Ȃ��ꍇ

		// ���̏I������
		m_pWind->Uninit();
		m_pWind = nullptr;
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// ��@�̍X�V����
//=====================================
void CElecFan::Update(void)
{
	if (m_pFan != nullptr)
	{ // �t�@���� NULL ����Ȃ��ꍇ

		// �t�@���̍X�V����
		m_pFan->Update();
	}

	if (m_pWind != nullptr)
	{ // ���� NULL ����Ȃ��ꍇ

		// ���̍X�V����
		m_pWind->Update();
	}
}

//=====================================
// ��@�̕`�揈��
//=====================================
void CElecFan::Draw(void)
{	
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �`�揈��
	CObstacle::Draw();

	if (m_pFan != nullptr)
	{ // �t�@���� NULL ����Ȃ��ꍇ

		// �t�@���̕`�揈��
		m_pFan->Draw();
	}

	if (m_pWind != nullptr)
	{ // ���� NULL ����Ȃ��ꍇ

		// �J�����O�̐ݒ��OFF�ɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// ���̕`�揈��
		m_pWind->Draw();

		// �J�����O�̐ݒ��ON�ɂ���
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CElecFan::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// �S�Ă̒l��ݒ肷��
	if (m_pFan == nullptr)
	{ // �t�@���� NULL �������ꍇ

		// �H���̈ʒu
		D3DXVECTOR3 posFan;

		// �H���̈ʒu��ݒ肷��
		posFan.x = pos.x;
		posFan.y = pos.y + FAN_SHIFT;
		posFan.z = pos.z;

		// �t�@���𐶐�����
		m_pFan = CFanBlade::Create(posFan);
	}

	if (m_pWind == nullptr)
	{ // ���̏�� NULL �̏ꍇ

		// ���𐶐�����
		m_pWind = CFanWind::Create(m_pFan->GetPos(), D3DXVECTOR3(-D3DX_PI * 0.5f, GetRot().y, GetRot().z), WIND_CIRCUM, WIND_HEIGHT);
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CElecFan::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CElecFan::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CElecFan::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return true;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CElecFan::Action(void)
{
	// �d��ON�ɂ���
	m_bPower = true;

	if (m_pWind == nullptr)
	{ // ���̏�� NULL �̏ꍇ

		// ���𐶐�����
		m_pWind = CFanWind::Create(m_pFan->GetPos(), D3DXVECTOR3(D3DX_PI * 0.5f, GetRot().y, GetRot().z), 40.0f, 80.0f);
	}
}