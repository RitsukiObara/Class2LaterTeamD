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
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "motion.h"
#include "player_idUI.h"
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
#define GRAVITY			(1.0f)			// �d��
#define ADD_MOVE_Y		(30.0f)			// ����
#define NONE_RATIDX		(-1)			// �l�Y�~�̔ԍ��̏����l
#define ATTACK_DISTANCE	(200.0f)		// �U���͈͂܂ł̋���
#define MAX_LIFE		(3)				// �����̍ő�l
#define TIME_DAMAGE		(60 * 1)		// �_���[�W�H�炤�܂ł̎���
#define SPEED			(20.0f)			// ���x
#define SIZE			(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// �T�C�Y

//==============================
// �R���X�g���N�^
//==============================
CRat::CRat() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;				// ���[�V�����̏��
	m_pPlayerID = nullptr;				// �v���C���[��ID�\��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_nRatIdx = NONE_RATIDX;			// �l�Y�~�̔ԍ�
	m_nLife = 0;						// ����
	m_nDamageCounter = TIME_DAMAGE;		// �_���[�W�H�炤�܂ł̃J�E���^�[
	m_fSpeed = 0.0f;					// ���x
	m_bJump = false;					// �W�����v������
	m_bAttack = false;					// �U��������
	MotionType = MOTIONTYPE_NEUTRAL;	// ���[�V�����̏��
	m_State = STATE_NONE;				// ���
}

//==============================
// �f�X�g���N�^
//==============================
CRat::~CRat()
{

}

//==============================
// �j�Ђ̏���������
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
		m_pMotion->Load(CMotion::TYPE_CAT);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	m_pMotion->Set(MotionType);

	// �S�Ă̒l������������
	m_pPlayerID = nullptr;				// �v���C���[��ID�\��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_nRatIdx = NONE_RATIDX;			// �l�Y�~�̔ԍ�
	m_fSpeed = 0.0f;					// ���x
	m_nLife = MAX_LIFE;					// ����
	m_nDamageCounter = TIME_DAMAGE;		// �_���[�W�H�炤�܂ł̃J�E���^�[
	m_bJump = false;					// �W�����v������
	m_bAttack = false;					// �U��������
	m_State = STATE_NONE;				// ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
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

	// �l�Y�~����������
	CGame::DeleteRat(m_nRatIdx);

	// �I������
	CCharacter::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CRat::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// �ړ��ʂ�ݒ肷��(�ړ��ʂ���Ɉ��ɂ��邽��)
	m_fSpeed = SPEED;

	// ��Q���Ƃ̓����蔻��
	collision::ObstacleHit(this, SIZE.x, SIZE.y, SIZE.z);

	if (m_State != STATE_DEATH)
	{ // ���S��ԈȊO�̂Ƃ�

		// �ړ�����
		Move();

		// �W�����v����
		Jump();

		// �U������
		Attack();

		//// ���[�V�����̐ݒ菈��
		MotionManager();

		if (Hit() == true)
		{ // �q�b�g�����Ŏ��񂾏ꍇ

			// ���̐�̏������s��Ȃ�
			return;
		}
	}

	// �N���n�ʂ̓����蔻��
	Elevation();

	// ��Q���Ƃ̓����蔻��
	ObstacleCollision();

	// ��ԍX�V����
	UpdateState();

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
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n�W�����v�󋵁F%d\n�����F%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump, m_nLife);
}

//=====================================
// �j�Ђ̕`�揈��
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

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦

	// ����ݒ肷��
	m_nRatIdx = nID;					// �l�Y�~�̔ԍ�
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_fSpeed = 0.0f;					// ���x
	m_nLife = MAX_LIFE;					// ����
	m_nDamageCounter = TIME_DAMAGE;		// �_���[�W�H�炤�܂ł̃J�E���^�[
	m_bJump = false;					// �W�����v������
	m_bAttack = false;					// �U��������
	m_State = STATE_NONE;				// ���

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
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
	{ // ����������ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
	{ // �����������ꍇ

		// ������ݒ肷��
		rot.y = 0.0f;
	}
	else
	{ // ��L�ȊO

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
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		m_move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, m_nRatIdx) == true &&
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
// ��ԍX�V����
//=======================================
void CRat::UpdateState(void)
{
	switch (m_State)
	{
	case CRat::STATE_NONE:		// ���ł��Ȃ����
		break;
	case CRat::STATE_WAIT:		// �ҋ@���
		break;
	case CRat::STATE_RUN:		// ���s���
		break;
	case CRat::STATE_ATTACK:	// �U�����
		break;
	case CRat::STATE_MUTEKI:	// ���G���
		break;
	case CRat::STATE_DAMAGE:	// �_���[�W���
		break;
	case CRat::STATE_DEATH:		// ���S���

		// �l�Y�~�̗H��̐���
		CRatGhost::Create(GetPos());

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// �q�b�g����
//=======================================
bool CRat::Hit(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	D3DXVECTOR3 pos = GetPos();

	if (m_nDamageCounter >= TIME_DAMAGE)
	{ // �_���[�W�H�炤���ԂɂȂ�����

		while (pObstacle != nullptr)
		{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

			/*if (useful::RectangleCollisionXY(pos, pObstacle->GetPos(),
				SIZE, pObstacle->GetFileData().vtxMax,
				-SIZE, pObstacle->GetFileData().vtxMin) == true)*/
			{ // XY�̋�`�ɓ������Ă���

				if (useful::RectangleCollisionXZ(pos, pObstacle->GetPos(),
					SIZE, pObstacle->GetFileData().vtxMax,
					-SIZE, pObstacle->GetFileData().vtxMin) == true)
				{ // XZ�̋�`�ɓ������Ă���

					m_nLife--;		// �������炷
					m_nDamageCounter = 0;		// �_���[�W�H�炤�܂ł̎��ԃ��Z�b�g

					CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //�p�[�e�B�N��

					if (m_nLife <= 0)
					{ // �����������Ƃ�

						m_State = STATE_DEATH;		// ���S��Ԃɂ���

						// �I������
						//Uninit();

						// ����Ԃ�
						return true;
					}
				}
			}

			// ���̃I�u�W�F�N�g��������
			pObstacle = pObstacle->GetNext();
		}
	}
	else
	{ // �_���[�W�H�炤���Ԃ���Ȃ�������

		m_nDamageCounter++;		// �_���[�W�H�炤�܂ł̎��ԉ��Z
	}

	// ����Ԃ�
	return false;
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
	collision::ObstacleCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z);

	// �u���b�N�Ƃ̓����蔻��
	collision::BlockCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z);

	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=======================================
// �l�Y�~�̏�Ԃ̐ݒ菈��
//=======================================
void CRat::SetState(STATE state)
{
	m_State = state;
}

//=======================================
// �l�Y�~�̏�Ԃ̎擾����
//=======================================
CRat::STATE CRat::GetState(void)
{
	return m_State;
}