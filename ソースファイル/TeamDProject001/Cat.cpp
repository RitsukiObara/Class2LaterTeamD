//============================================
//
// �L�̃��C������[Cat.cpp]
// Author�F��{�ėB
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "Cat.h"
#include "manager.h"
#include "game.h"
#include "result.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "sound.h"
#include "useful.h"
#include "texture.h"

#include "camera.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "effect.h"
#include "Particle.h"
#include "motion.h"
#include "shadowCircle.h"
#include "destruction.h"
#include "ripple.h"
#include "obstacle_manager.h"
#include "rat.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MOVE_SPEED				(20.0f)			// �̗͂̍ő吔
#define ATTACK_DISTANCE	(160.0f)		// �U���͈͂܂ł̋���

//=========================================
// �R���X�g���N�^
//=========================================
CCat::CCat() : CPlayer(CObject::TYPE_CAT, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_AttackPos = NONE_D3DXVECTOR3;	//�U���̈ʒu
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
}

//=========================================
// �f�X�g���N�^
//=========================================
CCat::~CCat()
{

}

//===========================================
// �v���C���[�̏���������
//===========================================
HRESULT CCat::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �x�^�ł�
	SetNumModel(10);

	// �f�[�^�̐ݒ菈��
	CCharacter::SetData();

	// ���[�V�����̃|�C���^��錾
	CMotion* pMotion = nullptr;

	if (pMotion == nullptr)
	{ // ���[�V������ NULL �������ꍇ

		// ���[�V�����̐�������
		pMotion = CMotion::Create();
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);
	}

	if (pMotion != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ���[�V�����̏����擾����
		pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ���[�h����
		pMotion->Load(CMotion::TYPE_CAT);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	// ���[�V��������ݒ肷��
	SetMotion(pMotion);

	// �S�Ă̒l������������
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CCat::Uninit(void)
{
	// �I������
	CPlayer::Uninit();

	// �v���C���[����������
	CGame::DeletePlayer(3);
}

//===========================================
// �X�V����
//===========================================
void CCat::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	if (m_AttackState == ATTACKSTATE_MOVE)
	{// �ړ���Ԃ̎�

		// ���x��ݒ肷��
		SetSpeed(MOVE_SPEED);

		// �U���ʒu�̈ړ����͏���
		Move();

		{
			// �ʒu�ƈړ��ʂ��擾����
			D3DXVECTOR3 pos = GetPos();
			D3DXVECTOR3 move = GetMove();

			// �ړ��ʂ����Z����
			pos += move;

			// �ʒu��K�p����
			SetPos(pos);
		}

		// �U�����͂̏���
		Attack();

		// ���[�V������Ԃ̊Ǘ�
		MotionManager();
	}
	else
	{
		// �ړ��ʂ�����������
		SetMove(NONE_D3DXVECTOR3);
	}

	// �U����Ԃ̊Ǘ�
	AttackStateManager();

	 // �e�̈ʒu�����̐ݒ菈��
	CShadowCircle::SetPosRot(m_nShadowIdx, GetPos(), GetRot());

	// �A�C�e���Ƃ̓����蔻�菈��
	collision::ItemCollision(*this);

	// �X�V����
	CPlayer::Update();

	// �f�o�b�O�\��
	DebugMessage();
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CCat::Draw(void)
{
	// �`�揈��
	CPlayer::Draw();
}

//===========================================
// �U������
//===========================================
void CCat::Attack(void)
{
	// ���[�J���ϐ��錾
	CPlayer *pRat[3];
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // W�L�[�������Ă����ꍇ

		// ��Ԃ��U�������ɂ���
		m_AttackState = ATTACKSTATE_STANDBY;
		m_nAtkStateCount = 20;
		for (int nCnt = 0; nCnt < 3; nCnt++)

		{
			pRat[nCnt] = CGame::GetPlayer(nCnt);
			while (pRat[nCnt] != nullptr)
			{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

				if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE),
					pRat[nCnt]->GetPos(),
					D3DXVECTOR3(30.0f, 50.0f, 30.0f), 
					D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f), 
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
				{ // XY�̋�`�ɓ������Ă���

					if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE), pRat[nCnt]->GetPos(),
						D3DXVECTOR3(30.0f, 50.0f, 30.0f), D3DXVECTOR3(30.0f, 50.0f, 30.0f),
						D3DXVECTOR3(-30.0f, -50.0f, -30.0f), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
					{ // XZ�̋�`�ɓ������Ă���
						pRat[nCnt]->Hit();
					}
				}
				break;
			}
		}
	}



	

	//m_bAttack = true;		// �U��������Ԃɂ���
}

//===========================================
// �U����Ԃ̊Ǘ�
//===========================================
void CCat::AttackStateManager(void)
{
	switch (m_AttackState)
	{
	case ATTACKSTATE_MOVE:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.8f), true);

		break;

	case ATTACKSTATE_STANDBY:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), true);

		if (m_nAtkStateCount <= 0)
		{//��ԃJ�E���g���O�ɂȂ�����
			m_AttackState = ATTACKSTATE_ATTACK;
			m_nAtkStateCount = 10;
		}
		break;

	case ATTACKSTATE_ATTACK:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), true);

		if (useful::CircleCollisionXZ(m_AttackPos, m_AttackPos,10.0f,10.0f) == true)
		{

		}

		if (m_nAtkStateCount <= 0)
		{//��ԃJ�E���g���O�ɂȂ�����
			m_AttackState = ATTACKSTATE_MOVE;
		}
		break;
	}

	if (m_nAtkStateCount > 0)
	{
		m_nAtkStateCount--;
	}
}

//===========================================
// �f�o�b�O�\��
//===========================================
void CCat::DebugMessage(void)
{
	CManager::Get()->GetDebugProc()->Print("\n �L���--------------------------------------------\n");

	// �L�̍U���ʒu����\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n", m_AttackPos.x, m_AttackPos.y, m_AttackPos.z);

	// �L�̑�����@��\��
	CManager::Get()->GetDebugProc()->Print("�ړ����́F��:[I] / ��:[J] / ��:[K] / �E:[L] \n");
	CManager::Get()->GetDebugProc()->Print("�U�� : [ENTER] \n");
}

//=======================================
// �q�b�g����
//=======================================
void CCat::Hit(void)
{

}

//=======================================
// ������я��
//=======================================
void CCat::Smash(const float fAngle)
{

}

//=======================================
// �C����
//=======================================
void CCat::Stun(void)
{

}

//=======================================
// ���̐ݒ菈��
//=======================================
void CCat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// ���̐ݒ菈��
	CPlayer::SetData(pos, nID, type);

	// �S�Ă̒l������������
	m_posDest = pos;		// �ړI�̈ʒu
	m_rotDest = GetRot();	// �ړI�̌�����ݒ肷��

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// ����������
		GetHierarchy(nCntData)->SetPos(pos);										// �ʒu
		GetHierarchy(nCntData)->SetPosOld(pos);										// �O��̈ʒu
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_CAT + nCntData));				// �f�[�^�̐ݒ菈��
	}

	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = nullptr;		// �e�ւ̃|�C���^

	// �e�̐ݒ菈��
	pShadow = CShadowCircle::Create(pos, GetRot(), 40.0f);

	if (pShadow != nullptr)
	{ // �e�̃|�C���^�� NULL�ȊO�̏ꍇ

		// �e�̃C���f�b�N�X�ݒ�
		m_nShadowIdx = pShadow->GetNumID();
	}

	// ���[�V�����̐ݒ菈��
	GetMotion()->Set(MOTIONTYPE_NEUTRAL);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCat::MotionManager(void)
{
	// ���[�V�����̎�ނ��擾����
	int nMotionType = GetMotion()->GetType();

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // ���U���g && �˂��̂���

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // �˂��݂̂���

			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // �˂��̂���

			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
	}
	else
	{ // ���U���g�ȊO�̂Ƃ�

		if (m_AttackState == ATTACKSTATE_STANDBY)
		{
			if (nMotionType != MOTIONTYPE_JUMP)
			{
				nMotionType = MOTIONTYPE_JUMP;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else if (GetMove().x > 0.05f || GetMove().x < -0.05f ||
			GetMove().z > 0.05f || GetMove().z < -0.05f)
		{
			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else
		{
			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
	}
}