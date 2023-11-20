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
#include "useful.h"

#include "objectElevation.h"
#include "elevation_manager.h"

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
	switch (m_state)
	{
	case CHairBall::STATE_STOP:



		break;

	case CHairBall::STATE_BOUND:

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
	if (pos.y <= GetPos().y + GetFileData().vtxMax.y ||
		pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y)
	{ // �{�ƏՓ˂����ꍇ

		// �~���̓����蔻�菈��
		useful::CylinderCollision(&pos, GetPos(), GetFileData().fRadius + fWidth);
	}

	// false �̏ꍇ
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CHairBall::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
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
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);		// �ʒu���擾����
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
			m_move.y *= -0.6f;

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

		// �o�E���h��Ԃɂ���
		m_state = STATE_BOUND;
	}

	// �ʒu���X�V����
	SetPos(pos);
}