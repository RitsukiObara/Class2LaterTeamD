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
#include "file.h"
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
	m_pPosInit = NONE_D3DXVECTOR3;	// �����ʒu
	m_pGear = nullptr;				// ���Ԃ̏��
	m_pPosDest = nullptr;			// �ړI�̈ʒu
	m_nPosDestNum = 0;				// �ړI�̈ʒu�̑���
	m_nPosDestIdx = 0;				// �ړI�̈ʒu�̔ԍ�
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
	m_pPosInit = NONE_D3DXVECTOR3;	// �����ʒu
	m_pGear = nullptr;				// ���Ԃ̒l
	m_pPosDest = nullptr;			// �ړI�̈ʒu
	m_nPosDestNum = 0;				// �ړI�̈ʒu�̑���
	m_nPosDestIdx = 0;				// �ړI�̈ʒu�̔ԍ�

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
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// ���s����
	CarDrive();

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
	// �Ԃ̌o�H��ݒ肷��
	int nType = rand() % CManager::Get()->GetFile()->GetCarRouteNum();

	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// ���f���̏���ݒ肷��
	SetFileData(CXFile::TYPE_TOYCARBODY);

	if (m_pGear == nullptr)
	{ // ���Ԃ̏�� NULL �̏ꍇ

		// ���Ԃ̐���
		m_pGear = CCarGear::Create(GetPos() + CAR_GEAR_SHIFT);
	}

	// �S�Ă̒l��ݒ肷��
	m_pPosInit = pos;		// �����ʒu
	m_nPosDestIdx = 0;		// �ړI�̈ʒu�̔ԍ�
	m_nPosDestNum = CManager::Get()->GetFile()->GetCarRouteNumPos(nType);		// �ړI�̈ʒu�̑���
	m_pPosDest = CManager::Get()->GetFile()->GetCarRoute(nType);				// �ړI�̈ʒu�̃|�C���^

	// �ړI�n�ւ̌����̌v�Z����
	RotCalc();
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

//=====================================
// ���s����
//=====================================
void CToyCar::CarDrive(void)
{
	// �����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����

	// �ړ�������
	pos.x += sinf(rot.y) * -6.0f;
	pos.z += cosf(rot.y) * -6.0f;

	// �ʒu��K�p����
	SetPos(pos);

	if (m_pPosDest != nullptr)
	{ // �ʒu�� NULL ����Ȃ��ꍇ

		// �ʒu�̊m�F����
		Check();
	}
}

//=====================================
// �ʒu�̊m�F����
//=====================================
void CToyCar::Check(void)
{
	// �����擾����
	D3DXVECTOR3 pos = GetPos();			// �ʒu���擾����
	D3DXVECTOR3 posOld = GetPosOld();	// �O��̈ʒu���擾����

	if (((m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x >= posOld.x && m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x <= pos.x) ||
		(m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x <= posOld.x && m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x >= pos.x)) ||
		((m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z >= posOld.z && m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z <= pos.z) ||
		(m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z <= posOld.z && m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z >= pos.z)))
	{ // �ʒu���ړI�n�𒴂����ꍇ

		// �ʒu��␳����
		pos = m_pPosInit + m_pPosDest[m_nPosDestIdx];

		// ������ς���
		m_nPosDestIdx = (m_nPosDestIdx + 1) % m_nPosDestNum;

		// �����̐ݒ菈��
		RotCalc();
	}
}

//=====================================
// �����̐ݒ菈��
//=====================================
void CToyCar::RotCalc(void)
{
	// �����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����

	// ������ݒ肷��
	rot.y = atan2f(pos.x - (m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x), pos.z - (m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z));

	// ������ݒ肷��
	SetRot(rot);
}