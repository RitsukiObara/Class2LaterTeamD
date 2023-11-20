//===========================================
//
// �{�̃��C������[hairball.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "hairball.h"
#include "collision.h"
#include "useful.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "block.h"
#include "block_manager.h"
#include "input.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY		(0.5f)		// �d��

//==============================
// �R���X�g���N�^
//==============================
CHairBall::CHairBall() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
}

//==============================
// �f�X�g���N�^
//==============================
CHairBall::~CHairBall()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CHairBall::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CHairBall::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CHairBall::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_STOP:

		// ���ɂȂ�

		break;

	case STATE_SMASH:

		// �ړ�����
		Move();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �d�͏���
	Gravity();

	// �N���n�ʂƂ̓����蔻��
	Elevation();

	// �u���b�N�Ƃ̓����蔻��
	Block();
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CHairBall::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHairBall::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
}

//=====================================
// �����蔻�菈��
//=====================================
bool CHairBall::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	if (pos.y <= GetPos().y + GetFileData().vtxMax.y &&
		pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y)
	{ // �{�ƏՓ˂����ꍇ

		// �~���̓����蔻�菈��
		if (useful::CylinderCollision(&pos, GetPos(), GetFileData().fRadius + fWidth) == true)
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

	// false �̏ꍇ
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CHairBall::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// �^�[�Q�b�g�̈ʒu��ݒ肷��
	D3DXVECTOR3 Targetpos = pos;

	if (m_state == STATE_SMASH &&
		type == COLLTYPE_RAT &&
		pos.y <= GetPos().y + GetFileData().vtxMax.y &&
		pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y &&
		useful::CylinderCollision(&Targetpos, GetPos(), GetFileData().fRadius + fWidth) == true)
	{ // �{�ƏՓ˂����ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}

//=====================================
// �ړ�����
//=====================================
void CHairBall::Move(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ʒu���ړ�����
	pos.x += m_move.x;
	pos.z += m_move.z;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �d�͏���
//=====================================
void CHairBall::Gravity(void)
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
void CHairBall::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	float fHeight = 0.0f;					// ����
	bool bLand = false;						// ���n��

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight - GetFileData().vtxMin.y;

			// �ړ��ʂ����Z����
			m_move.x *= 0.6f;
			m_move.y *= -0.6f;
			m_move.z *= 0.6f;

			if (m_move.y <= 5.0f)
			{ // �ړ��ʂ����ȉ��̏ꍇ

				// �d�͂�␳����
				m_move.y = 0.0f;

				// ���n����
				bLand = true;
			}
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	if (bLand == true)
	{ // ���n�󋵂� true �ɂ���

		// ��~��Ԃɂ���
		m_state = STATE_STOP;
	}
	else
	{ // ��L�ȊO

		// ������΂���Ԃɂ���
		m_state = STATE_SMASH;
	}

	// �ʒu���X�V����
	SetPos(pos);
}

//=====================================
// �u���b�N�̓����蔻��
//=====================================
void CHairBall::Block(void)
{
	// ���[�J���ϐ��錾
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// �u���b�N�̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	bool bLand = false;						// ���n��

	while (pBlock != nullptr)
	{ // �n�ʂ̏�񂪂�������

		if (collision::HexahedronCollision(pos, pBlock->GetPos(), GetPosOld(), pBlock->GetPosOld(), GetFileData().vtxMin, pBlock->GetFileData().vtxMin, GetFileData().vtxMax, pBlock->GetFileData().vtxMax) == true)
		{ // �����蔻�肪 true �̏ꍇ

		}

		// ���̃|�C���^���擾����
		pBlock = pBlock->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}