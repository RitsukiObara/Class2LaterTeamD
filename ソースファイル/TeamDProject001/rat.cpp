//===========================================
//
// ���b�g�̃��C������[rat.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "rat.h"
#include "player.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "motion.h"
#include "player_idUI.h"
#include "rat_state.h"
#include "stun.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "obstacle_manager.h"
#include "obstacle.h"
#include "Particle.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "object3Dfan.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY				(1.0f)			// �d��
#define ADD_MOVE_Y			(30.0f)			// ����
#define NONE_RATIDX			(-1)			// �l�Y�~�̔ԍ��̏����l
#define ATTACK_DISTANCE		(230.0f)		// �U���͈͂܂ł̋���
#define MAX_LIFE			(1)				// �����̍ő�l
#define SPEED				(20.0f)			// ���x
#define SIZE				(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// �����蔻��ł̃T�C�Y
#define STUN_HEIGHT			(80.0f)			// �C�≉�o���o�Ă��鍂��
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ������я�Ԃ̈ړ���
#define TIME_RESURRECTION	(60 * 4)		// ��������

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
int CRat::m_nNumAll = 0;				// �l�Y�~�̑���
int CRat::m_nResurrectionCounter = 0;	// �����Ԃ�܂ł̃J�E���^�[

//==============================
// �R���X�g���N�^
//==============================
CRat::CRat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pRatState = nullptr;				// �l�Y�~�̏�Ԃ̏��
	m_pRatGhost = nullptr;				// �H��l�Y�~�̏��
	m_pRessrectionFan = nullptr;		// �~�͈̔͂̏��
	m_nRatIdx = NONE_RATIDX;			// �l�Y�~�̔ԍ�
	m_bJump = false;					// �W�����v��
	m_nNumAll++;						// �l�Y�~�̑������Z
}

//==============================
// �f�X�g���N�^
//==============================
CRat::~CRat()
{

}

//==============================
// �l�Y�~�̏���������
//==============================
HRESULT CRat::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �x�^�ł�
	SetNumModel(6);

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
		pMotion->Load(CMotion::TYPE_RAT);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	// ���[�V�����̏���ݒ肷��
	SetMotion(pMotion);

	if (m_pRatState == nullptr)
	{ // �l�Y�~�̏�Ԃ� NULL �̏ꍇ
		
		// �l�Y�~�̏�Ԃ̏��𐶐�����
		m_pRatState = new CRatState;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	// �S�Ă̒l������������
	m_nRatIdx = NONE_RATIDX;		// �l�Y�~�̔ԍ�
	m_bJump = false;				// �W�����v��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~�̏I������
//========================================
void CRat::Uninit(void)
{
	if (m_pRatState != nullptr)
	{ // �l�Y�~�̏�Ԃ� NULL ����Ȃ��ꍇ

		// �l�Y�~�̏�Ԃ̏I������
		delete m_pRatState;
		m_pRatState = nullptr;
	}

	if (m_pRatGhost != nullptr)
	{ // �H��l�Y�~�� NULL ����Ȃ��ꍇ

		//�H��l�Y�~�̏I������
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}

	if (m_pRessrectionFan != nullptr)
	{ // �~�͈̔͂� NULL ����Ȃ��ꍇ

		//�~�͈̔͂̏I������
		//m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}

	// �l�Y�~����������
	CGame::DeleteRat(m_nRatIdx);

	// �I������
	CPlayer::Uninit();
}

//=====================================
// �l�Y�~�̍X�V����
//=====================================
void CRat::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// �ړ��ʂ�ݒ肷��(�ړ��ʂ���Ɉ��ɂ��邽��)
	SetSpeed(SPEED);

	if (m_pRatState->GetState() != CRatState::STATE_DEATH &&
		m_pRatState->GetState() != CRatState::STATE_STUN)
	{ // �H���ԂƋC���ԈȊO�̂Ƃ�

		if (m_pRatState->GetState() != CRatState::STATE_SMASH)
		{ // ������я�Ԃ̏ꍇ

			// �ړ�����
			Move();
		}

		// �W�����v����
		Jump();

		// �U������
		Attack();

		// ���[�V�����̐ݒ菈��
		MotionManager();

		// �����Ԃ�̓����蔻��
		ResurrectionCollision();
	}

	// �N���n�ʂ̓����蔻��
	Elevation();

	//�ǂƂ̓����蔻��
	SetPos(collision::WallCollision(GetPosOld(), GetPos()));

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E))
	{
		collision::ObstacleAction(this, SIZE.x, CObstacle::COLLTYPE_RAT);
	}

	if (m_pRatState != nullptr)
	{ // �l�Y�~�̏�Ԃ� NULL ����Ȃ��ꍇ

		// �l�Y�~�̏�Ԃ̍X�V����
		m_pRatState->Update(*this);
	}

	// �v���C���[�̍X�V����
	CPlayer::Update();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("\n�l�Y�~�̑���:%d\n", m_nNumAll);
	CManager::Get()->GetDebugProc()->Print("�h���J�E���g�F%d\n", m_nResurrectionCounter);
}

//=====================================
// �l�Y�~�̕`�揈��
//=====================================
void CRat::Draw(void)
{
	// �`�揈��
	CPlayer::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::MotionManager(void)
{
	// ���[�V�����̎�ނ��擾����
	int nMotionType = GetMotion()->GetType();

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // ���U���g

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // �˂��݂̂���

			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // �˂��̂���

			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
	}
	else
	{ // ���U���g�ȊO�̂Ƃ�

		if (m_bJump == true)
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

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// ���̐ݒ菈��
	CPlayer::SetData(pos, nID, type);

	// ����ݒ肷��
	m_nRatIdx = nID;				// �l�Y�~�̔ԍ�
	m_bJump = false;				// �W�����v������

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// ����������
		GetHierarchy(nCntData)->SetPos(pos);										// �ʒu
		GetHierarchy(nCntData)->SetPosOld(pos);										// �O��̈ʒu
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_RAT + nCntData));		// �f�[�^�̐ݒ菈��
	}

	// ���[�V�����̐ݒ菈��
	GetMotion()->Set(MOTIONTYPE_NEUTRAL);

	//if (m_pPlayerID == nullptr)
	//{ // �v���C���[��ID�\���� NULL �̏ꍇ

	//	// �v���C���[��ID�\���̐�������
	//	m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z), m_nRatIdx);
	//}
}

//=======================================
// �l�Y�~�̔ԍ��̎擾����
//=======================================
int CRat::GetRatIdx(void) const
{
	// �l�Y�~�̔ԍ���Ԃ�
	return m_nRatIdx;
}

//=======================================
// �l�Y�~�̏�Ԃ̎擾����
//=======================================
CRatState* CRat::GetState(void)
{
	// �l�Y�~�̏�Ԃ�Ԃ�
	return m_pRatState;
}

//=======================================
// �H��l�Y�~�̏��擾����
//=======================================
CRatGhost* CRat::GetRatGhost(void)
{
	// �H��l�Y�~�̏���Ԃ�
	return m_pRatGhost;
}

//=======================================
// �H��l�Y�~�̏���������
//=======================================
void CRat::DeleteRatGhost(void)
{
	if (m_pRatGhost != nullptr)
	{ // �H��l�Y�~�� NULL ����Ȃ��ꍇ

		//�H��l�Y�~�̏I������
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}
}
//=======================================
// �~�͈̔͂̏��擾����
//=======================================
CRessrectionFan* CRat::GetRessrectionFan(void)
{
	// �~�͈̔͂̏���Ԃ�
	return m_pRessrectionFan;
}

//=======================================
// �~�͈̔͂̏���������
//=======================================
void CRat::DeleteRessrectionFan(void)
{
	if (m_pRessrectionFan != nullptr)
	{ // �~�͈̔͂� NULL ����Ȃ��ꍇ

		//�~�͈̔͂̏I������
		m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}
}

//=======================================
// �W�����v����
//=======================================
void CRat::Jump(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = GetMove();

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, m_nRatIdx) == true &&
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

	move.y -= GRAVITY;		// �d�͉��Z

	// �ʒu�����Z����
	pos += move;

	// ����K�p����
	SetPos(pos);
	SetRot(rot);
	SetMove(move);
}

//=======================================
// �U������
//=======================================
void CRat::Attack(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B,m_nRatIdx) == true/* && m_bAttack == false*/)
	{ // B�{�^�����������ꍇ

		while (pObstacle != nullptr)
		{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
				SIZE, pObstacle->GetFileData().vtxMax,
				-SIZE, pObstacle->GetFileData().vtxMin) == true)
			{ // XY�̋�`�ɓ������Ă���

				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
					SIZE, pObstacle->GetFileData().vtxMax,
					-SIZE, pObstacle->GetFileData().vtxMin) == true)
				{ // XZ�̋�`�ɓ������Ă���

					// ��Q���̏I������
					pObstacle->Uninit();
				}
			}

			// ���̃I�u�W�F�N�g��������
			pObstacle = pObstacle->GetNext();
		}

		//m_bAttack = true;		// �U��������Ԃɂ���
	}
}

//=======================================
// �q�b�g����
//=======================================
void CRat::Hit(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	int nLife = GetLife();			// �������擾����
	CRatState::STATE state = m_pRatState->GetState();	// ��Ԃ��擾����

	if (state != CRatState::STATE_DAMAGE && 
		state != CRatState::STATE_INVINCIBLE)
	{ // �_���[�W�󂯂��Ԃ������ꍇ
		nLife--;			// �������炷

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //�p�[�e�B�N��

		if (nLife <= 0)
		{ // �����������Ƃ�

			m_pRatState->SetState(CRatState::STATE_DEATH);		// ���S��Ԃɂ���

			// �����Ԃ�̉~�͈̔͐���
			if (m_pRessrectionFan == nullptr)
			{ // �~�͈̔͂� NULL �̂Ƃ�

				m_pRessrectionFan = CRessrectionFan::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			// �l�Y�~�̗H��̐���
			if (m_pRatGhost == nullptr)
			{ // �H��l�Y�~�� NULL �̂Ƃ�

				m_pRatGhost = CRatGhost::Create(pos);

				m_nNumAll--;						// �l�Y�~�̑������Z
			}

#if 0	// �f�o�b�O�ׂ̈̏�����

			// �I����Ԃɂ���
			Uninit();
#endif

			if (m_nNumAll <= 0)
			{ // �l�Y�~���S�ł�����

				// �l�R������������Ԃɂ���
				CGame::SetState(CGame::STATE_CAT_WIN);
			}
		}
		else
		{ // ��L�ȊO

			m_pRatState->SetState(CRatState::STATE_DAMAGE);		// �_���[�W��Ԃɂ���
		}
	}

	// ������ݒ肷��
	SetLife(nLife);
}

//=======================================
// ������я��
//=======================================
void CRat::Smash(const float fAngle)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 move = GetMove();	// �ړ��ʂ��擾����
	CRatState::STATE state = m_pRatState->GetState();	// ��Ԃ��擾����

	if (state != CRatState::STATE_DAMAGE &&
		state != CRatState::STATE_INVINCIBLE &&
		state != CRatState::STATE_SMASH &&
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		// �ړ��ʂ��Z�o����
		move.x = sinf(fAngle) * SMASH_MOVE.x;
		move.y = SMASH_MOVE.y;
		move.z = cosf(fAngle) * SMASH_MOVE.z;

		// ������я�Ԃɂ���
		m_pRatState->SetState(CRatState::STATE_SMASH);
	}

	// �ړ��ʂ�K�p����
	SetMove(move);
}

//=======================================
// �C����
//=======================================
void CRat::Stun(void)
{
	// ��Ԃ��擾����
	CRatState::STATE state = m_pRatState->GetState();

	if (state != CRatState::STATE_DAMAGE &&
		state != CRatState::STATE_INVINCIBLE &&
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		// �C���Ԃɂ���
		m_pRatState->SetState(CRatState::STATE_STUN);

		// �C�≉�o�̐ݒ菈��
		SetStun(GetPos());
	}
}

//=======================================
// �N���n�ʂ̓����蔻��
//=======================================
void CRat::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	D3DXVECTOR3 move = GetMove();			// �ړ��ʂ��擾����
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight;

			move.y = 0.0f;

			m_bJump = false;		// �W�����v���ĂȂ���Ԃɂ���
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu�ƈړ��ʂ��X�V����
	SetPos(pos);
	SetMove(move);
}

//=======================================
// �����Ԃ�̓����蔻��
//=======================================
void CRat::ResurrectionCollision(void)
{
	//CPlayer *pRat;		// �l�Y�~�̏��
	//bool bCollYZ = false;		// ����������

	//// ��Ԃ��擾����
	//CRatState::STATE state = m_pRatState->GetState();

	//for (int nCntRat = 0; nCntRat < MAX_RAT; nCntRat++)
	//{
	//	if (m_nRatIdx != nCntRat)
	//	{ // ���삵�Ă�l�Y�~����Ȃ��Ƃ�

	//		// ���̃l�Y�~�̏��擾
	//		pRat = CGame::GetRat(nCntRat);

	//		if (pRat->GetState()->GetState() == CRatState::STATE_DEATH && 
	//			state != CRatState::STATE_STUN && state != CRatState::STATE_DEATH)
	//		{ // ���̃l�Y�~�����S��� && ���삵�Ă�l�Y�~��������������Ԃ̎�

	//			// ���̃l�Y�~�Ƃ̓����蔻��
	//			if (useful::CircleCollisionXY(GetPos(), pRat->GetPos(), 30.0f, ATTACK_DISTANCE) == true)
	//			{ // �~�̓����蔻��(XY����)

	//				// �~�̓����蔻��(XZ����)
	//				bCollYZ = useful::CircleCollisionXZ(GetPos(), pRat->GetPos(), 30.0f, ATTACK_DISTANCE);

	//				if (bCollYZ == true)
	//				{ // �~�̓����蔻��(XZ����)

	//					// �����Ԃ�̃J�E���^�[���Z
	//					m_nResurrectionCounter++;

	//					if (m_nResurrectionCounter >= TIME_RESURRECTION)
	//					{ // ��莞�Ԍo������

	//						// ���G��Ԃɂ���
	//						pRat->GetState()->SetState(CRatState::STATE_INVINCIBLE);

	//						// �~�͈̔͂̔j��
	//						pRat->DeleteRessrectionFan();

	//						// �H��l�Y�~�̔j��
	//						pRat->DeleteRatGhost();

	//						// �����Ԃ�̃J�E���^�[������
	//						m_nResurrectionCounter = 0;

	//						m_nNumAll++;		// �������₷
	//					}
	//				}
	//				else if(bCollYZ == false)
	//				{
	//					// �����Ԃ�̃J�E���^�[������
	//					m_nResurrectionCounter = 0;
	//				}

	//			}
	//		}
	//	}
	//}
}