//===========================================
//
// �y�b�g�{�g���̃��C������[petbottle.cpp]
// Author ���˕�
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "hairball.h"
#include "useful.h"
#include "petbottle.h"

#include "objectElevation.h"
#include "elevation_manager.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define STAND_ROT	(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f))		// ������Ԃ̌���
#define GRAVITY		(0.5f)											// �d��

//==============================
// �R���X�g���N�^
//==============================
CPetbottle::CPetbottle() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;
	m_state = STATE_STAND;
}

//==============================
// �f�X�g���N�^
//==============================
CPetbottle::~CPetbottle()
{

}

//==============================
// �y�b�g�{�g���̏���������
//==============================
HRESULT CPetbottle::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;
	m_state = STATE_STAND;

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �y�b�g�{�g���̏I������
//========================================
void CPetbottle::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �y�b�g�{�g���̍X�V����
//=====================================
void CPetbottle::Update(void)
{
	switch (m_state)
	{
	case CPetbottle::STATE_STAND:

		// ������ݒ肷��
		SetRot(STAND_ROT);

		break;

	case CPetbottle::STATE_COLLAPSE:

		// ��]����
		Cycle();

		// �d�͏���
		Gravity();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �N���n�ʂƂ̓����蔻��
	Elevation();
}

//=====================================
// �y�b�g�{�g���̕`�揈��
//=====================================
void CPetbottle::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPetbottle::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// ������ݒ肷��
	SetRot(STAND_ROT);

	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STAND;			// ���
}

//=====================================
// �����蔻�菈��
//=====================================
bool CPetbottle::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	if (m_state == STATE_STAND)
	{ // ������Ԃ̏ꍇ

		if (pos.y <= GetPos().y + GetFileData().vtxMax.y &&
			pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y)
		{ // �y�b�g�{�g���ƏՓ˂����ꍇ

			// �~���̓����蔻�菈��
			if (useful::CylinderCollision(&pos, GetPos(), GetFileData().vtxMax.x + fWidth) == true)
			{ // �����蔻�肪 false �̏ꍇ

				if (posOld.y >= GetPos().y + GetFileData().vtxMax.y &&
					pos.y <= GetPos().y + GetFileData().vtxMax.y)
				{ // �ォ��̓����蔻��

					// �c�̈ʒu��ݒ肷��
					pos.y = GetPos().y + GetFileData().vtxMax.y + 0.01f;
				}
				else if (posOld.y + fHeight <= GetPos().y + GetFileData().vtxMin.y &&
					pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y)
				{ // ������̓����蔻��

					// �c�̈ʒu��ݒ肷��
					pos.y = GetPos().y + GetFileData().vtxMin.y - fHeight - 0.01f;
				}
			}
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CPetbottle::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);

	if (m_state == STATE_COLLAPSE &&
		type == COLLTYPE_RAT)
	{ // �|���Ԃ̏ꍇ

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
		{ // �����蔻�肪 true �̏ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// ��]����
//=====================================
void CPetbottle::Cycle(void)
{
	// �ړ��ʂ�ݒ肷��
	m_move.x = -10.0f;

	// �����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����

	// ���������Z����
	rot.z += 0.01f;

	// �ʒu���ړ�����
	pos.x += m_move.x;

	// ����K�p����
	SetPos(pos);		// �ʒu
	SetRot(rot);		// ����
}

//=====================================
// �d�͏���
//=====================================
void CPetbottle::Gravity(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �d�͏���
	useful::Gravity(&m_move.y, pos, GRAVITY);
	
	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=====================================
// �N���n�ʂ̓����蔻��
//=====================================
void CPetbottle::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);		// �ʒu���擾����
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight - GetFileData().vtxMin.y;
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}