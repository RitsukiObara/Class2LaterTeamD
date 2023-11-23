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

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY				(1.0f)			// �d��
#define ADD_MOVE_Y			(30.0f)			// ����
#define NONE_RATIDX			(-1)			// �l�Y�~�̔ԍ��̏����l
#define ATTACK_DISTANCE		(200.0f)		// �U���͈͂܂ł̋���
#define MAX_LIFE			(1)				// �����̍ő�l
#define SPEED				(20.0f)			// ���x
#define SIZE				(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// �����蔻��ł̃T�C�Y
#define STUN_HEIGHT			(80.0f)			// �C�≉�o���o�Ă��鍂��
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ������я�Ԃ̈ړ���

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
int CRat::m_nNumAll = 0;				// �l�Y�~�̑���

//==============================
// �R���X�g���N�^
//==============================
CRat::CRat() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;				// ���[�V�����̏��
	m_pPlayerID = nullptr;				// �v���C���[��ID�\��
	m_pRatState = nullptr;				// �l�Y�~�̏�Ԃ̏��
	m_pStun = nullptr;					// �C��̏��
	m_pRatGhost = nullptr;				// �H��l�Y�~�̏��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_nRatIdx = NONE_RATIDX;			// �l�Y�~�̔ԍ�
	m_nLife = 0;						// ����
	m_fSpeed = 0.0f;					// ���x
	m_bJump = false;					// �W�����v������
	m_bAttack = false;					// �U��������
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
	if (FAILED(CCharacter::Init()))
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

	if (m_pMotion == nullptr)
	{ // ���[�V������ NULL �������ꍇ

		// ���[�V�����̐�������
		m_pMotion = CMotion::Create();
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ���[�V�����̏����擾����
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ���[�h����
		m_pMotion->Load(CMotion::TYPE_RAT);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	m_pMotion->Set(MotionType);

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
	m_pPlayerID = nullptr;			// �v���C���[��ID�\��
	m_pStun = nullptr;				// �C��̏��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_nRatIdx = NONE_RATIDX;		// �l�Y�~�̔ԍ�
	m_fSpeed = 0.0f;				// ���x
	m_nLife = MAX_LIFE;				// ����
	m_bJump = false;				// �W�����v������
	m_bAttack = false;				// �U��������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~�̏I������
//========================================
void CRat::Uninit(void)
{
	if (m_pMotion != nullptr)
	{ // ���[�V������ NULL ����Ȃ��ꍇ

		// ���[�V�����̃��������J������
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_pPlayerID != nullptr)
	{ // �v���C���[��ID�\���� NULL ����Ȃ��ꍇ

		// �v���C���[��ID�\���̏I������
		m_pPlayerID->Uninit();
		m_pPlayerID = nullptr;
	}

	if (m_pRatState != nullptr)
	{ // �l�Y�~�̏�Ԃ� NULL ����Ȃ��ꍇ

		// �l�Y�~�̏�Ԃ̏I������
		delete m_pRatState;
		m_pRatState = nullptr;
	}

	if (m_pStun != nullptr)
	{ // �C�≉�o�� NULL ����Ȃ��ꍇ

		// �C�≉�o�̏I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}

	if (m_pRatGhost != nullptr)
	{ // �H��l�Y�~�� NULL ����Ȃ��ꍇ

		//�H��l�Y�~�̏I������
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}

	// �l�Y�~����������
	CGame::DeleteRat(m_nRatIdx);

	// �I������
	CCharacter::Uninit();
}

//=====================================
// �l�Y�~�̍X�V����
//=====================================
void CRat::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// �ړ��ʂ�ݒ肷��(�ړ��ʂ���Ɉ��ɂ��邽��)
	m_fSpeed = SPEED;

	// ��Q���Ƃ̓����蔻��
	collision::ObstacleHit(this, SIZE.x, SIZE.y, SIZE.z, CObstacle::COLLTYPE_RAT);

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

	// ��Q���Ƃ̓����蔻��
	ObstacleCollision();

	if (m_pRatState != nullptr)
	{ // �l�Y�~�̏�Ԃ� NULL ����Ȃ��ꍇ

		// �l�Y�~�̏�Ԃ̍X�V����
		m_pRatState->Update(*this);
	}

	if (m_pMotion != nullptr)
	{ // ���[�V������ NULL ����Ȃ��ꍇ

		// ���[�V�����̍X�V����
		m_pMotion->Update();
	}

	if (m_pPlayerID != nullptr)
	{ // �v���C���[��ID�\���� NULL ����Ȃ��ꍇ

		// �ʒu���擾����
		D3DXVECTOR3 pos = GetPos();

		// �ʒu��ݒ肷��
		m_pPlayerID->SetPos(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z));
	}

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n�W�����v�󋵁F%d\n�����F%d\n�l�Y�~�̏�ԁF%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump, m_nLife, m_pRatState->GetState());
	CManager::Get()->GetDebugProc()->Print("\n�l�Y�~�̑���:%d\n", m_nNumAll);
}

//=====================================
// �l�Y�~�̕`�揈��
//=====================================
void CRat::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::MotionManager(void)
{
	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // ���U���g

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // �˂��݂̂���

			if (MotionType != MOTIONTYPE_MOVE)
			{
				MotionType = MOTIONTYPE_MOVE;

				// ���[�V�����̐ݒ菈��
				m_pMotion->Set(MotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // �˂��̂���

			if (MotionType != MOTIONTYPE_NEUTRAL)
			{
				MotionType = MOTIONTYPE_NEUTRAL;

				// ���[�V�����̐ݒ菈��
				m_pMotion->Set(MotionType);
			}
		}
	}
	else
	{ // ���U���g�ȊO�̂Ƃ�

		if (m_bJump == true)
		{
			if (MotionType != MOTIONTYPE_JUMP)
			{
				MotionType = MOTIONTYPE_JUMP;

				// ���[�V�����̐ݒ菈��
				m_pMotion->Set(MotionType);
			}
		}
		else if (m_move.x > 0.05f || m_move.x < -0.05f ||
			m_move.z > 0.05f || m_move.z < -0.05f)
		{
			if (MotionType != MOTIONTYPE_MOVE)
			{
				MotionType = MOTIONTYPE_MOVE;

				// ���[�V�����̐ݒ菈��
				m_pMotion->Set(MotionType);
			}
		}
		else
		{
			if (MotionType != MOTIONTYPE_NEUTRAL)
			{
				MotionType = MOTIONTYPE_NEUTRAL;

				// ���[�V�����̐ݒ菈��
				m_pMotion->Set(MotionType);
			}
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦

	// ����ݒ肷��
	m_pStun = nullptr;				// �C��̏��
	m_nRatIdx = nID;				// �l�Y�~�̔ԍ�
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_fSpeed = 0.0f;				// ���x
	m_nLife = MAX_LIFE;				// ����
	m_bJump = false;				// �W�����v������
	m_bAttack = false;				// �U��������

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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	//if (m_pPlayerID == nullptr)
	//{ // �v���C���[��ID�\���� NULL �̏ꍇ

	//	// �v���C���[��ID�\���̐�������
	//	m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z), m_nRatIdx);
	//}
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CRat::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
D3DXVECTOR3 CRat::GetMove(void) const
{
	// �ړ��ʂ�Ԃ�
	return m_move;
}

//=======================================
// ���x�̐ݒ菈��
//=======================================
void CRat::SetSpeed(const float fSpeed)
{
	// ���x��ݒ肷��
	m_fSpeed = fSpeed;
}

//=======================================
// ���x�̎擾����
//=======================================
float CRat::GetSpeed(void) const
{
	// ���x��Ԃ�
	return m_fSpeed;
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
// // �ړ��󋵂̎擾����
//=======================================
bool CRat::IsMove(void)
{
	// �ړ��󋵂�Ԃ�
	return m_bMove;
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
// �C�≉�o�̐ݒ菈��
//=======================================
void CRat::SetStun(void)
{
	if (m_pStun == nullptr)
	{ // �C��̏�� NULL �������ꍇ

		// �C�≉�o�𐶐�����
		m_pStun = CStun::Create(D3DXVECTOR3(GetPos().x, GetPos().y + STUN_HEIGHT, GetPos().z));
	}
}

//=======================================
// �C�≉�o�̎擾����
//=======================================
CStun* CRat::GetStun(void)
{
	// �C�≉�o��Ԃ�
	return m_pStun;
}

//=======================================
// �C�≉�o�̏�������
//=======================================
void CRat::DeleteStun(void)
{
	if (m_pStun != nullptr)
	{ // �C�≉�o�� NULL ����Ȃ��ꍇ

		// �C�≉�o�̏I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}
}

//=======================================
// �H��l�Y�~�̎擾����
//=======================================
CRatGhost* CRat::GetRatGhost(void)
{
	return m_pRatGhost;
}

//=======================================
// �H��l�Y�~�̏�������
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
// ��������
//=======================================
CRat* CRat::Create(const D3DXVECTOR3& pos, const int nID)
{
	// �l�Y�~�̃|�C���^
	CRat* pRat = nullptr;

	if (pRat == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pRat = new CRat;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRat != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pRat->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pRat->SetData(pos, nID);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pRat;
}

//=======================================
// �ړ�����
//=======================================
void CRat::Move(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nRatIdx) > 0)
	{ // �E���������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
		{ // ����������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
		{ // �����������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * -0.25f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			rot.y = D3DX_PI * -0.5f;
		}
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nRatIdx) < 0)
	{ // �����������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
		{ // ����������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
		{ // �����������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.25f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.5f;
		}
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
	{ // ����������ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
	{ // �����������ꍇ

		// ������ݒ肷��
		rot.y = 0.0f;
		m_bMove = true;
	}
	else
	{ // ��L�ȊO
		m_bMove = false;
		// ���x��ݒ肷��
		m_fSpeed = 0.0f;
	}

	// �ړ��ʂ�ݒ肷��
	m_move.x = -sinf(rot.y) * m_fSpeed;
	m_move.z = -cosf(rot.y) * m_fSpeed;

	// ������K�p����
	SetRot(rot);
}

//=======================================
// �W�����v����
//=======================================
void CRat::Jump(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		m_move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, m_nRatIdx) == true &&
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		m_move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

	m_move.y -= GRAVITY;		// �d�͉��Z

	// �ʒu�����Z����
	pos += m_move;

	// ����K�p����
	SetPos(pos);
	SetRot(rot);
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
bool CRat::Hit(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	CRatState::STATE state = m_pRatState->GetState();	// ��Ԃ��擾����

	if (state != CRatState::STATE_DAMAGE && 
		state != CRatState::STATE_INVINCIBLE)
	{ // �_���[�W�󂯂��Ԃ������ꍇ
		m_nLife--;			// �������炷

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //�p�[�e�B�N��

		if (m_nLife <= 0)
		{ // �����������Ƃ�

			m_pRatState->SetState(CRatState::STATE_DEATH);		// ���S��Ԃɂ���

			// �l�Y�~�̗H��̐���
			if (m_pRatGhost == nullptr)
			{ // �H��l�Y�~�� NULL �̂Ƃ�

				m_pRatGhost = CRatGhost::Create(GetPos());

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

			// ����Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			m_pRatState->SetState(CRatState::STATE_DAMAGE);		// �_���[�W��Ԃɂ���
		}

		// ����Ԃ�
		return true;
	}

	// ����Ԃ�
	return false;
}

//=======================================
// ������я��
//=======================================
void CRat::Smash(const float fAngle)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	CRatState::STATE state = m_pRatState->GetState();	// ��Ԃ��擾����

	if (state != CRatState::STATE_DAMAGE &&
		state != CRatState::STATE_INVINCIBLE &&
		state != CRatState::STATE_SMASH &&
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		// �ړ��ʂ��Z�o����
		m_move.x = sinf(fAngle) * SMASH_MOVE.x;
		m_move.y = SMASH_MOVE.y;
		m_move.z = cosf(fAngle) * SMASH_MOVE.z;

		// ������я�Ԃɂ���
		m_pRatState->SetState(CRatState::STATE_SMASH);
	}
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
		state != CRatState::STATE_SMASH &&
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		// �C���Ԃɂ���
		m_pRatState->SetState(CRatState::STATE_STUN);
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
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

		  // ������ݒ肷��
			pos.y = fHeight;

			m_move.y = 0.0f;

			m_bJump = false;		// �W�����v���ĂȂ���Ԃɂ���
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}

//=======================================
// ��Q���Ƃ̓����蔻��
//=======================================
void CRat::ObstacleCollision(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// ��Q���Ƃ̏Փ˔���
	collision::ObstacleCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z, CObstacle::COLLTYPE_RAT);

	// �u���b�N�Ƃ̓����蔻��
	collision::BlockCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z);

	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=======================================
// �����Ԃ�̓����蔻��
//=======================================
void CRat::ResurrectionCollision(void)
{
	CRat *pRat;		// �l�Y�~�̏��

	// ��Ԃ��擾����
	CRatState::STATE state = m_pRatState->GetState();

	for (int nCntRat = 0; nCntRat < MAX_RAT; nCntRat++)
	{
		if (m_nRatIdx != nCntRat)
		{ // ���삵�Ă�l�Y�~����Ȃ��Ƃ�

			// ���̃l�Y�~�̏��擾
			pRat = CGame::GetRat(nCntRat);

			if (pRat->GetState()->GetState() == CRatState::STATE_DEATH && 
				state != CRatState::STATE_STUN && state != CRatState::STATE_DEATH)
			{ // ���̃l�Y�~�����S��� && ���삵�Ă�l�Y�~��������������Ԃ̎�

				// ���̃l�Y�~�Ƃ̓����蔻��
				if (useful::RectangleCollisionXY(GetPos(), pRat->GetPos(),
					D3DXVECTOR3(30.0f, 50.0f, 30.0f), D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
				{ // XY���W�̋�`�̓����蔻��

					if (useful::RectangleCollisionXZ(GetPos(), pRat->GetPos(),
						D3DXVECTOR3(30.0f, 50.0f, 30.0f), D3DXVECTOR3(30.0f, 50.0f, 30.0f),
						D3DXVECTOR3(-30.0f, -50.0f, -30.0f), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
					{ // XZ�̋�`�ɓ������Ă���

						// ���G��Ԃɂ���
						pRat->GetState()->SetState(CRatState::STATE_INVINCIBLE);

						// �H��l�Y�~�̔j��
						pRat->DeleteRatGhost();

						m_nNumAll++;		// �������₷
					}
				}
			}
		}
	}
}