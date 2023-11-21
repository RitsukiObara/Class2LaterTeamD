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
#include "collision.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define CAR_GEAR_SHIFT		(D3DXVECTOR3(0.0f, 40.0f, 0.0f))		// �Ԃ̎��Ԃ̂��炷��
#define CAR_SPEED			(-4.0f)									// �Ԃ̑��x
#define CAR_CURVE_SPEED		(0.03f)									// �Ԃ̋Ȃ��鑬�x
#define CAR_DEST_ROT_SHIFT	(0.05f)									// �Ԃ���ԑJ�ڂ�������̍����̋��e�l

//==============================
// �R���X�g���N�^
//==============================
CToyCar::CToyCar() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pPosInit = NONE_D3DXVECTOR3;	// �����ʒu
	m_pGear = nullptr;				// ���Ԃ̏��
	m_pPosDest = nullptr;			// �ړI�̈ʒu
	m_state = STATE_DRIVE;			// ���
	m_nPosDestNum = 0;				// �ړI�̈ʒu�̑���
	m_nPosDestIdx = 0;				// �ړI�̈ʒu�̔ԍ�
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_bRight = false;				// �E������
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
	m_state = STATE_DRIVE;			// ���
	m_nPosDestNum = 0;				// �ړI�̈ʒu�̑���
	m_nPosDestIdx = 0;				// �ړI�̈ʒu�̔ԍ�
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_bRight = false;				// �E������

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

	switch (m_state)
	{
	case CToyCar::STATE_DRIVE:

		// ���s����
		Drive();

		break;

	case CToyCar::STATE_CURVE:

		// �J�[�r���O����
		Curve();
		
		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (m_pPosDest != nullptr)
	{ // �ʒu�� NULL ����Ȃ��ꍇ

		// �ʒu�̊m�F����
		Check();
	}

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

	if (m_pGear == nullptr)
	{ // ���Ԃ̏�� NULL �̏ꍇ

		// ���Ԃ̐���
		m_pGear = CCarGear::Create(GetPos() + CAR_GEAR_SHIFT);
	}

	// �S�Ă̒l��ݒ肷��
	m_pPosInit = pos;				// �����ʒu
	m_nPosDestIdx = 0;				// �ړI�̈ʒu�̔ԍ�
	m_nPosDestNum = CManager::Get()->GetFile()->GetCarRouteNumPos(nType);		// �ړI�̈ʒu�̑���
	m_pPosDest = CManager::Get()->GetFile()->GetCarRoute(nType);				// �ړI�̈ʒu�̃|�C���^
	m_state = STATE_CURVE;			// ���
	m_bRight = false;				// �E������

	// �ړI�n�ւ̌����̌v�Z����
	RotCalc();
}

//=====================================
// �����蔻�菈��
//=====================================
bool CToyCar::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// �ŏ��l�ƍő�l��錾
	D3DXVECTOR3 vtxMin, vtxMax;

	// �ŏ��l�ƍő�l��ݒ肷��
	vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);
	vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);

	// �Z�ʑ̂̓����蔻��
	collision::HexahedronCollision(pos, GetPos(), posOld, GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax);

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CToyCar::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// �ŏ��l�ƍő�l��錾
	D3DXVECTOR3 vtxMin, vtxMax;

	// �ŏ��l�ƍő�l��ݒ肷��
	vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);
	vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);

	if (type == COLLTYPE_RAT &&
		m_state == STATE_DRIVE)
	{ // �l�Y�~���A�h���C�u��Ԃ̏ꍇ

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
		{ // ���ɂ���ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// ���s����
//=====================================
void CToyCar::Drive(void)
{
	// �����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����

	// �ړ�������
	pos.x += sinf(rot.y) * CAR_SPEED;
	pos.z += cosf(rot.y) * CAR_SPEED;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �J�[�r���O����
//=====================================
void CToyCar::Curve(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();		

	if (m_bRight == true)
	{ // �E�����̏ꍇ

		// ���������Z����
		rot.y += CAR_CURVE_SPEED;
	}
	else
	{ // ��L�ȊO

		// ���������Z����
		rot.y -= CAR_CURVE_SPEED;
	}

	// �����̐��K��
	useful::RotNormalize(&rot.y);

	if (fabsf(m_fRotDest - rot.y) <= CAR_DEST_ROT_SHIFT)
	{ // ���������܂ōs�����ꍇ

		// ������␳����
		rot.y = m_fRotDest;

		// �h���C�u��Ԃɂ���
		m_state = STATE_DRIVE;
	}

	// ������K�p����
	SetRot(rot);
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

		// �J�[�u��Ԃ�ݒ肷��
		m_state = STATE_CURVE;
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
	float fRotDiff;					// �����̍���

	// �ړI�̌�����ݒ肷��
	m_fRotDest = atan2f(pos.x - (m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x), pos.z - (m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z));

	// �����̍��������߂�
	fRotDiff = m_fRotDest - rot.y;

	// �����𐳋K������
	useful::RotNormalize(&fRotDiff);

	if (fRotDiff >= 0.0f)
	{ // �����̍������v���X�̒l�̏ꍇ

		// �E�����ɂ���
		m_bRight = true;
	}
	else
	{ // ��L�ȊO

		// �������ɂ���
		m_bRight = false;
	}
}