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
#include "tutorial.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "motion.h"
#include "player_idUI.h"
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
#include "recoveringUI.h"
#include "speech_message.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY				(0.55f)			// �d��
#define ADD_MOVE_Y			(10.0f)			// �W�����v��
#define NONE_RATIDX			(-1)			// �l�Y�~�̔ԍ��̏����l
#define ATTACK_DISTANCE		(230.0f)		// �U���͈͂܂ł̋���
#define SPEED				(15.0f)			// ���x
#define SIZE				(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// �����蔻��ł̃T�C�Y
#define STUN_HEIGHT			(80.0f)			// �C�≉�o���o�Ă��鍂��
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ������я�Ԃ̈ړ���
#define INVINCIBLE_COUNT	(60)			// ���G�J�E���g
#define ARROW_DISTANCE		(100.0f)		// ���̃l�Y�~�̖��̋���

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
bool CRat::m_bResurrection = false;		// ���������Ă�̂�

//==============================
// �R���X�g���N�^
//==============================
CRat::CRat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_nRezCounter = 0;					// �񕜂���܂ł̃J�E���^�[
	m_bJump = false;					// �W�����v��
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

	// �S�Ă̒l������������
	m_bJump = false;				// �W�����v��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~�̏I������
//========================================
void CRat::Uninit(void)
{
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

	// �d�͏���
	Gravity();

	if (CPlayer::GetStunState() != CPlayer::STUNSTATE_STUN &&
		CPlayer::GetState() != CPlayer::STATE_DEATH)
	{ // �C����or���S��Ԃ���Ȃ��ꍇ

		if (GetTutorial() != true)
		{
			// �W�����v����
			Jump();

			if (GetStunState() != STUNSTATE_SMASH)
			{ // ������я�Ԃ̏ꍇ

				// �ړ����쏈��
				MoveControl();
			}

			// �U������
			Attack();

			// ���[�V�����̐ݒ菈��
			MotionManager();

			// �����Ԃ�̓����蔻��
			ResurrectionCollision();

			//�ړ�����
			Move();
		}
	}

	// ���S���̏���
	DeathArrow();

	// �N���n�ʂ̓����蔻��
	Elevation();

	// �p�x�̐��K��
	RotNormalize();

	// �v���C���[�̍X�V����
	CPlayer::Update();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�h���J�E���g�F%d\n", CPlayer::GetResurrectionTime());
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

	// �����蔻��̃T�C�Y�̐ݒ�
	SetSizeColl(SIZE);

	// ����ݒ肷��
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
// �W�����v����
//=======================================
void CRat::Jump(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move = GetMove();

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		GetStunState() != STUNSTATE_SMASH &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, GetPlayerIdx()) == true &&
		GetStunState() != STUNSTATE_SMASH &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

	// ����K�p����
	SetMove(move);
}

//=======================================
// �d�͏���
//=======================================
void CRat::Gravity(void)
{
	// �ړ��ʂ��擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// �d�͂����Z����
	move.y -= GRAVITY;

	// �ʒu�����Z����
	pos.y += move.y;

	// �ړ��ʂ�K�p����
	SetPos(pos);
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

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, GetPlayerIdx()) == true)
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
	}
}

//=======================================
// �q�b�g����
//=======================================
void CRat::Hit(void)
{
	// ���[�J���ϐ��錾
	CPlayer *pPlayer;						// �l�Y�~�̏��
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	STATE state = GetState();				// ��Ԃ��擾����
	STUNSTATE stunState = GetStunState();	// �C���Ԃ��擾����
	int nCntDeath = 0;						// ���S������

	if (state == STATE_NONE &&
		stunState != STUNSTATE_WAIT)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //�p�[�e�B�N��

		SetState(STATE_DEATH);				// ���S��Ԃɂ���

		// �����Ԃ�̉~�͈̔͐���
		CPlayer::SetRessrectionFan(pos, D3DXCOLOR(1.0f, 0.0f, 0.1f, 0.5f));

		// �l�Y�~�̗H��̐���
		CPlayer::SetRatGhost(pos);

		// �񕜒�UI�̐���
		CPlayer::SetRecoveringUI(pos, GetPosOld());

		// �`�B���b�Z�[�W�̕\��
		CPlayer::SetSpeechMessage(D3DXVECTOR3(pos.x, pos.y + 120.0f, pos.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f), -1, CSpeechMessage::TYPE_HELP);

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
			{
				// �v���C���[�̏����擾����
				pPlayer = CTutorial::GetPlayer(nCnt);
			}
			else
			{
				// �v���C���[�̏����擾����
				pPlayer = CGame::GetPlayer(nCnt);
			}

			if (pPlayer != nullptr &&
				pPlayer->GetType() == TYPE_RAT && 
				pPlayer->GetState() == STATE_DEATH)
			{ // ���S���Ă�l�Y�~�̎�

				nCntDeath++;
			}
		}

		if (nCntDeath >= (MAX_PLAY - 1))
		{ // �l�Y�~�S�C���񂾂�

			// �l�R������������Ԃɂ���
			CGame::SetState(CGame::STATE_CAT_WIN);
		}
	}
}

//=======================================
// ���S���̏���
//=======================================
void CRat::DeathArrow(void)
{
	CPlayer *pPlayer;						// �l�Y�~�̏��
	STATE state = GetState();				// ��Ԃ��擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu�擾
	D3DXVECTOR3 posOld = GetPosOld();		// �O��̈ʒu�擾
	int nIdx = -1;							// �v���C���[�̔ԍ�
	bool abRez[MAX_PLAY];					// �������Ă邩

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			// �v���C���[�̏����擾����
			pPlayer = CTutorial::GetPlayer(nCnt);
		}
		else
		{
			// �v���C���[�̏����擾����
			pPlayer = CGame::GetPlayer(nCnt);
		}

		abRez[nCnt] = false;

		if (pPlayer != nullptr &&
			pPlayer->GetType() == TYPE_RAT &&
			GetPlayerIdx() != pPlayer->GetPlayerIdx())
		{ // ���삵�Ă�l�Y�~����Ȃ��Ƃ�

			if (pPlayer->GetState() == STATE_DEATH && state != STATE_DEATH)
			{ // ���̃l�Y�~�����S��Ԃ̎�

				D3DXVECTOR3 DestPos = pos - pPlayer->GetPos();		// �ړI�̈ʒu
				D3DXVECTOR3 DestRot = NONE_D3DXVECTOR3;				// �ړI�̌���

				// �ړI�̌��������߂�
				DestRot.y = atan2f(-DestPos.z, DestPos.x);

				// ���S��󐶐�
				SetDeathArrow(D3DXVECTOR3(pos.x + sinf(DestRot.y + -D3DX_PI * 0.5f) * ARROW_DISTANCE,
					pos.y - 1.0f,
					pos.z + cosf(DestRot.y + -D3DX_PI * 0.5f) * ARROW_DISTANCE),
					posOld, DestRot, nCnt);

				// �񕜂����Ă��Ԃɂ���
				abRez[nCnt] = true;
			}

			if (abRez[nCnt] == false)
			{ // �����Ԃ�����

				// ���S������
				DeleteDeathArrow(nCnt);
			}
		}
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
	CPlayer *pPlayer = nullptr;				// �l�Y�~�̏��
	bool bCollXY = false;					// XY�͈̔͂ɓ�������
	bool bCollXZ = false;					// XZ�͈̔͂ɓ�������
	bool abRez[MAX_PLAY];					// �񕜂��Ă邩
	STATE state = GetState();				// ��Ԃ��擾����
	STUNSTATE stunState = GetStunState();	// �C���Ԃ��擾����

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			// �v���C���[�̏����擾����
			pPlayer = CTutorial::GetPlayer(nCnt);
		}
		else
		{
			// �v���C���[�̏����擾����
			pPlayer = CGame::GetPlayer(nCnt);
		}
		abRez[nCnt] = false;

		if (pPlayer != nullptr &&
			pPlayer->GetType() == TYPE_RAT &&
			GetPlayerIdx() != pPlayer->GetPlayerIdx())
		{ // ���삵�Ă�l�Y�~����Ȃ��Ƃ�

			if (pPlayer->GetState() == STATE_DEATH &&
				state != STATE_DEATH && 
				stunState != STUNSTATE::STUNSTATE_SMASH &&
				stunState != STUNSTATE::STUNSTATE_STUN)
			{ // ���̃l�Y�~�����S��� && ���삵�Ă�l�Y�~��������������Ԃ̎�

				// �~�̓����蔻��(XY����)�擾
				bCollXY = useful::CircleCollisionXY(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// �~�̓����蔻��(XZ����)�擾
				bCollXZ = useful::CircleCollisionXZ(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// ���̃l�Y�~�Ƃ̓����蔻��
				if (bCollXY == true && bCollXZ == true)
				{ // �~�̓����蔻��(XY����)��(XZ����)�͈̔͂ɂ���ꍇ

					if (m_bResurrection == false)
					{ // ���������ĂȂ���Ԃ�������

						// ���������Ă��Ԃɂ���
						m_bResurrection = true;
					}

					// �񕜂����Ă��Ԃɂ���
					abRez[nCnt] = true;

					// ���݂̐����Ԃ�̎��Ԏ擾
					m_nRezCounter = pPlayer->GetResurrectionTime();
							
					// �����Ԃ�̃J�E���^�[���Z
					m_nRezCounter++;

					// �񕜒�UI�\���ݒ�
					pPlayer->SetDispRecoveringUI(abRez[nCnt]);

					pPlayer->SetResurrectionTime(m_nRezCounter);

					if (pPlayer->GetResurrectionTime() >= NUM_REZ_ANGLE)
					{ // ��莞�Ԍo������

						// ���G��Ԃɂ���
						pPlayer->SetState(STATE_INVINCIBLE);
						pPlayer->SetStateCount(INVINCIBLE_COUNT);

						// �~�͈̔͂̔j��
						pPlayer->DeleteRessrectionFan();

						// �H��l�Y�~�̔j��
						pPlayer->DeleteRatGhost();

						// �񕜒�UI�̔j��
						pPlayer->DeleteRecoveringUI();

						// �`�B���b�Z�[�W�̔j��
						pPlayer->DeleteSpeechMessage();

						// �����Ԃ�̃J�E���^�[������
						pPlayer->SetResurrectionTime(0);
						m_nRezCounter = 0;

						// ���������ĂȂ���Ԃɂ���
						m_bResurrection = false;
					}
				}
				else if (m_bResurrection == false && (bCollXY == false || bCollXZ == true))
				{ // ���������ĂȂ���� && �~�̓����蔻��(XY����)��(XZ����)�͈̔͂ɂ��Ȃ��ꍇ

					// �񕜒�UI�\���ݒ�
					pPlayer->SetDispRecoveringUI(false);

					if (pPlayer->GetResurrectionTime() > 0)
					{ // �����Ԃ�̃J�E���^�[�����Z����Ă���

						pPlayer->AddResurrectionTime(-1);		// �J�E���^�[���Z
					}
					else
					{ // �����Ԃ�̃J�E���^�[��0�ȉ���������

						// �����Ԃ�̃J�E���^�[������
						pPlayer->SetResurrectionTime(0);
					}
				}

				// �񕜂���͈͂̏��擾
				CRessrectionFan *pResurrectionFan = pPlayer->GetRessrectionFan();

				if (pResurrectionFan != nullptr)
				{ // �񕜂���͈͂� NULL�̂Ƃ�

					// �񕜂͈̔͂̎��Ԑݒ�
					pResurrectionFan->SetResurrectionFan(pPlayer->GetResurrectionTime());
				}
			}
		}
	}

	if (abRez[0] == false && abRez[1] == false && abRez[2] == false && abRez[3] == false)
	{ // �S�����N�������ĂȂ��Ƃ�

		// ���������ĂȂ���Ԃɂ���
		m_bResurrection = false;
	}
}