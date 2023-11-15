//===========================================
//
// ��������̎Ԃ̃��C������[toycar.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "toycar.h"
#include "renderer.h"
#include "input.h"
#include "useful.h"

#include "car_gear.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define CAR_GEAR_SHIFT		(D3DXVECTOR3(0.0f, 200.0f, 0.0f))		// �Ԃ̎��Ԃ̂��炷��

//==============================
// �R���X�g���N�^
//==============================
CToyCar::CToyCar() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pGear = nullptr;			// ���Ԃ̏��
}

//==============================
// �f�X�g���N�^
//==============================
CToyCar::~CToyCar()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CToyCar::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pGear = nullptr;		// ���Ԃ̒l

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CToyCar::Uninit(void)
{
	if (m_pGear != nullptr)
	{ // ���Ԃ̏�� NULL ����Ȃ��ꍇ

		// �I������
		m_pGear->Uninit();
		m_pGear = nullptr;
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CToyCar::Update(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	pos.x -= sinf(rot.y) * 10.0f;
	pos.z -= cosf(rot.y) * 10.0f;

	rot.y -= 0.02f;

	// �ʒu��K�p����
	SetPos(pos);
	SetRot(rot);

	if (m_pGear != nullptr)
	{ // ���Ԃ� NULL ����Ȃ��ꍇ

		// �ʒu�����肷��
		m_pGear->SetPos(GetPos() + CAR_GEAR_SHIFT);

		// �X�V����
		m_pGear->Update();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CToyCar::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	if (m_pGear != nullptr)
	{ // ���Ԃ� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pGear->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CToyCar::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// ���f���̏���ݒ肷��
	SetFileData(CXFile::TYPE_TOYCARBODY);

	if (m_pGear == nullptr)
	{ // ���Ԃ̏�� NULL �̏ꍇ

		// ���Ԃ̐���
		m_pGear = CCarGear::Create(GetPos() + CAR_GEAR_SHIFT);
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CToyCar::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CToyCar::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	// false ��Ԃ�
	return false;
}