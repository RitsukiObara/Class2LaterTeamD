//===========================================
//
// �v���C���[�̃��C������[player.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "player.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"
#include "MultiCamera.h"

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "collision.h"
#include "recoveringUI.h"
#include "speech_message.h"
#include "death_arrow.h"

#include "Cat.h"
#include "rat.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY				(1.0f)			// �d��
#define ADD_MOVE_Y			(30.0f)			// ����
#define NONE_PLAYERIDX		(-1)			// �v���C���[�̔ԍ��̏����l
#define STUN_HEIGHT			(80.0f)			// �C�≉�o���o�Ă��鍂��
#define ID_HEIGHT			(150.0f)		// ID���o�Ă��鍂��
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ������я�Ԃ̈ړ���
#define STUN_WAIT			(120)			// �I�u�W�F�N�g�����̑ҋ@����
#define DEATH_WAIT			(120)			// ���S���̑ҋ@����
#define SMASH_WAIT			(40)			// ������я�Ԃ̃J�E���g��
#define CAT_CAMERA_HEIGHT	(200.0f)		// �L�̃J�����̍���
#define CAT_CAMERA_DIS		(300.0f)		// �L�̃J�����̎��_�ƒ����_�̍����̍���(�p�x)
#define RAT_CAMERA_HEIGHT	(30.0f)			// �l�Y�~�̃J�����̍���
#define RAT_CAMERA_DIS		(60.0f)			// �l�Y�~�̃J�����̎��_�ƒ����_�̍����̍���(�p�x)

//==============================
// �R���X�g���N�^
//==============================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CPlayer::CPlayer(CObject::TYPE type, PRIORITY priority) : CCharacter(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �f�X�g���N�^
//==============================
CPlayer::~CPlayer()
{

}

//==============================
// �R���X�g���N�^�̔�
//==============================
void CPlayer::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;				// ���[�V�����̏��
	m_pPlayerID = nullptr;				// �v���C���[��ID�\��
	m_pStun = nullptr;					// �C��̏��
	m_pRatGhost = nullptr;				// �H��l�Y�~�̏��
	m_pRessrectionFan = nullptr;		// �~�͈̔͂̏��
	m_pRecoveringUI = nullptr;			// �񕜒���UI�̏��
	m_pSpeechMessage = nullptr;			// �`�B���b�Z�[�W�̏��
	m_pDeathArrow[MAX_PLAY] = {};		// ���S���̏��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_type = TYPE_CAT;					// ���
	m_nPlayerIdx = NONE_PLAYERIDX;		// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩
	m_CameraRot = NONE_D3DXVECTOR3;		// �J�����̌���
	m_nResurrectionTime = 0;			// ��������܂ł̎���

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		m_apLog[nCnt] = NULL;
	}
	m_nLogNumber = 0;
}

//==============================
// �v���C���[�̏���������
//==============================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pMotion = nullptr;				// ���[�V�����̏��
	m_pPlayerID = nullptr;				// �v���C���[��ID�\��
	m_pStun = nullptr;					// �C��̏��
	m_pRatGhost = nullptr;				// �H��l�Y�~�̏��
	m_pRessrectionFan = nullptr;		// �~�͈̔͂̏��
	m_pRecoveringUI = nullptr;			// �񕜒���UI�̏��
	m_pSpeechMessage = nullptr;			// �`�B���b�Z�[�W�̏��
	m_pDeathArrow[MAX_PLAY] = {};		// ���S���̏��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_type = TYPE_CAT;					// ���
	m_nPlayerIdx = NONE_PLAYERIDX;		// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩
	m_nResurrectionTime = 0;			// ��������܂ł̎���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �v���C���[�̏I������
//========================================
void CPlayer::Uninit(void)
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

	if (m_pRessrectionFan != nullptr)
	{ // �~�͈̔͂� NULL ����Ȃ��ꍇ

		//�~�͈̔͂̏I������
		m_pRessrectionFan = nullptr;
	}

	if (m_pRecoveringUI != nullptr)
	{ // �񕜒���UI�� NULL ����Ȃ��ꍇ

		//�񕜒���UI�̏I������
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}

	if (m_pSpeechMessage != nullptr)
	{ // �`�B���b�Z�[�W�� NULL ����Ȃ��Ƃ�

		//�`�B���b�Z�[�W�̏I������
		m_pSpeechMessage = nullptr;
	}

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (m_pDeathArrow[nCnt] != nullptr)
		{ // ���S��� NULL ����Ȃ��Ƃ�

			//���S���̏I������
			m_pDeathArrow[nCnt]->Uninit();
			m_pDeathArrow[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Uninit();
			m_apLog[nCnt] = NULL;
		}
	}

	// �v���C���[����������
	CGame::DeletePlayer(m_nPlayerIdx);

	// �I������
	CCharacter::Uninit();
}

//=====================================
// �v���C���[�̍X�V����
//=====================================
void CPlayer::Update(void)
{
	// ��Q���Ƃ̓����蔻��
	collision::ObstacleHit(this, m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	// ��Q���Ƃ̓����蔻��
	ObstacleCollision();

	// �C���Ԃ̊Ǘ�
	StunStateManager();

	// ��Ԃ̊Ǘ�
	StateManager();

	if (m_type == TYPE_CAT)
	{
		collision::ObstacleSearch(this, 30.0f * 2.0f, m_type, m_nPlayerIdx);
	}
	else if (m_type == TYPE_RAT)
	{
		collision::ObstacleSearch(this, 30.0f * 2.0f, m_type, m_nPlayerIdx);
	}

#if CAMERA != 0
	//�J�������̍X�V
	CameraUpdate();
#endif // CAMERA

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E))
	{
		collision::ObstacleAction(this, m_sizeColl.x, m_type);
	}

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1))
	{
		SetLog(CLog::TYPE::TYPE_DEATH);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2))
	{
		SetLog(CLog::TYPE::TYPE_STUN);
	}

#endif // _DEBUG

	if (m_pMotion != nullptr)
	{ // ���[�V������ NULL ����Ȃ��ꍇ

		// ���[�V�����̍X�V����
		m_pMotion->Update();
	}

	if (m_pPlayerID != nullptr)
	{ // �v���C���[��ID�\���� NULL ����Ȃ��ꍇ

		// �ʒu���̎擾
		D3DXVECTOR3 pos = GetPos();

		// �ʒu��ݒ肷��
		m_pPlayerID->SetPos(D3DXVECTOR3(pos.x, pos.y + ID_HEIGHT, pos.z));
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Update();
		}
	}

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z);
}

//=====================================
// �v���C���[�̕`�揈��
//=====================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Draw();
		}
	}
}

//=====================================
// ������я��
//=====================================
void CPlayer::Smash(const float fAngle)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 move = GetMove();	// �ړ��ʂ��擾����

	if (m_State == STATE_NONE &&
		m_StunState == STUNSTATE_NONE)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		// �ړ��ʂ��Z�o����
		move.x = sinf(fAngle) * SMASH_MOVE.x;
		move.y = SMASH_MOVE.y;
		move.z = cosf(fAngle) * SMASH_MOVE.z;

		// ������я�Ԃɂ���
		m_StunState = STUNSTATE_SMASH;

		// �C���ԃJ�E���g��ݒ肷��
		m_StunStateCount = SMASH_WAIT;
	}

	// �ړ��ʂ�K�p����
	SetMove(move);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPlayer::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦

	// �S�Ă̒l���N���A����
	m_pStun = nullptr;					// �C��̏��
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_type = type;						// ���
	m_nPlayerIdx = nID;					// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩

	if (m_pPlayerID == nullptr)
	{ // �v���C���[��ID�\���� NULL �̏ꍇ

		// �v���C���[��ID�\���̐�������
		m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + ID_HEIGHT, pos.z), nID);
	}
}

//=======================================
// ��������
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// �v���C���[�̃|�C���^
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case TYPE::TYPE_CAT:		// �l�R

			// �l�R�𐶐�
			pPlayer = new CCat;

			break;

		case TYPE::TYPE_RAT:		// �l�Y�~

			// �l�Y�~�𐶐�
			pPlayer = new CRat;

			break;

		default:					// ��L�ȊO

			// ��~
			assert(false);

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPlayer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPlayer->SetData(pos, nID, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//=======================================
// �ړ����쏈��
//=======================================
void CPlayer::MoveControl(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) > 0)
	{ // �E���������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // ����������ꍇ

			// ������ݒ肷��
			rot.y = m_CameraRot.y + D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
		{ // �����������ꍇ

			// ������ݒ肷��
			rot.y = m_CameraRot.y + D3DX_PI * -0.25f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			rot.y = m_CameraRot.y + D3DX_PI * -0.5f;
		}
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) < 0)
	{ // �����������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // ����������ꍇ

			// ������ݒ肷��
			rot.y = m_CameraRot.y + D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
		{ // �����������ꍇ

			// ������ݒ肷��
			rot.y = m_CameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			rot.y = m_CameraRot.y + D3DX_PI * 0.5f;
		}
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
	{ // ����������ꍇ

		// ������ݒ肷��
		rot.y = m_CameraRot.y + D3DX_PI * 1.0f;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
	{ // �����������ꍇ

		// ������ݒ肷��
		rot.y = m_CameraRot.y + D3DX_PI * 0.0f;
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

	// �ʒu�ƌ�����K�p����
	SetRot(rot);
}

//=======================================
// �ړ�����
//=======================================
void CPlayer::Move(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ړ��ʂ����Z����
	pos += m_move;

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// ���ꂼ��̃v���C���[�̃J�����̍X�V
//=======================================
void CPlayer::CameraUpdate(void)
{
	CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
	D3DXVECTOR3 Pos = GetPos();

	if (m_type == TYPE::TYPE_CAT)
	{ //�L�̃J�����̈ʒu
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + CAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}
	else
	{ //�l�Y�~�̃J�����̈ʒu
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + RAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{
		m_CameraRot.y -= 0.05f;
	}
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true)
	{
		m_CameraRot.y += 0.05f;
	}
}

////=======================================
//// �U������
////=======================================
//void CPlayer::Attack(void)
//{
//	// ���[�J���ϐ��錾
//	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
//	D3DXVECTOR3 pos = GetPos();
//	D3DXVECTOR3 rot = GetRot();
//
//	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B,m_nRatIdx) == true/* && m_bAttack == false*/)
//	{ // B�{�^�����������ꍇ
//
//		while (pObstacle != nullptr)
//		{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ
//
//			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//				SIZE, pObstacle->GetFileData().vtxMax,
//				-SIZE, pObstacle->GetFileData().vtxMin) == true)
//			{ // XY�̋�`�ɓ������Ă���
//
//				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//					SIZE, pObstacle->GetFileData().vtxMax,
//					-SIZE, pObstacle->GetFileData().vtxMin) == true)
//				{ // XZ�̋�`�ɓ������Ă���
//
//					// ��Q���̏I������
//					pObstacle->Uninit();
//				}
//			}
//
//			// ���̃I�u�W�F�N�g��������
//			pObstacle = pObstacle->GetNext();
//		}
//
//		//m_bAttack = true;		// �U��������Ԃɂ���
//	}
//}

//=======================================
// ��Q���Ƃ̓����蔻��
//=======================================
void CPlayer::ObstacleCollision(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// ��Q���Ƃ̏Փ˔���
	collision::ObstacleCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	// �u���b�N�Ƃ̓����蔻��
	collision::BlockCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z);

	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=======================================
// �C�⏈��
//=======================================
void CPlayer::Stun(int StunTime)
{
	if (m_StunState == STUNSTATE_NONE &&
		m_State == STATE_NONE)
	{ // �ʏ��Ԃ������ꍇ

		// �C���Ԃɂ���
		m_StunState = STUNSTATE_STUN;
		m_StunStateCount = StunTime;

		// �C�≉�o�̐ݒ菈��
		SetStun(GetPos());
	}

	////�L�ƃl�Y�~�ŋC��̎d�l��ς���ꍇ�͎g����
	//if (m_type == TYPE_CAT)
	//{ // �L�̏ꍇ
	//}
	//else if (m_type == TYPE_RAT)
	//{ // �l�Y�~�̏ꍇ
	//}
}

//=======================================
// �A�C�e���̎擾����
//=======================================
void CPlayer::GetItem(const CItem::TYPE type)
{

}

//=======================================
// �C���Ԃ̊Ǘ�
//=======================================
void CPlayer::StunStateManager(void)
{
	switch (m_StunState)
	{
	case STUNSTATE_NONE:	// �����

		break;

	case STUNSTATE_SMASH:	// ������я��

		// �J�E���g�����Z����
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ

			// �C���Ԃɂ���
			m_StunState = STUNSTATE_STUN;
			m_StunStateCount = STUN_WAIT;

			// �C�≉�o�̐ݒ菈��
			SetStun(GetPos());
		}

		break;

	case STUNSTATE_STUN:	//�C����

		// �J�E���g�����Z����
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ

			// ���G��Ԃɂ���
			m_StunState = STUNSTATE_WAIT;
			m_StunStateCount = STUN_WAIT;

			if (m_pStun != nullptr)
			{ // �C�≉�o�� NULL �̏ꍇ

				// �C�≉�o���폜����
				m_pStun->Uninit();
				m_pStun = nullptr;
			}
		}
		break;

	case STUNSTATE_WAIT:	//��Q���̂ݖ��G���

		// �J�E���g�����Z����
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ

			// ����Ԃɂ���
			m_StunState = STUNSTATE_NONE;
		}
		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// ��Ԃ̊Ǘ�
//=======================================
void CPlayer::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NONE:

		break;

	case STATE_INVINCIBLE:	//���G���

		// �J�E���g�����Z����
		m_StateCount--;

		if (m_StateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ
			
			// ����Ԃɂ���
			m_State = STATE_NONE;
		}
		break;

	case STATE_DEATH:	//���S���


		break;
	}
}

//=======================================
// ���O�̐����ԍ��̉��Z
//=======================================
void CPlayer::SetLog(CLog::TYPE Type)
{
	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] == NULL)
		{
			m_apLog[nCnt] = CLog::Create(m_nPlayerIdx, m_nLogNumber, Type);
			m_apLog[nCnt]->SetLogIdx(nCnt);
			m_apLog[nCnt]->SetMain(this);
			break;
		}
	}

	m_nLogNumber++;
}

//=======================================
// ���O�̐����ԍ��̌��Z
//=======================================
void CPlayer::DelLogNumber(int nLogIdex)
{
	m_nLogNumber--;

	if (m_apLog[nLogIdex] != NULL)
	{
		m_apLog[nLogIdex]->Uninit();
		m_apLog[nLogIdex] = NULL;
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->DelCreateNumber();
		}
	}
}

//=======================================
// ���[�V�����̐ݒ菈��
//=======================================
void CPlayer::SetMotion(CMotion* pMotion)
{
	// ���[�V�����̏���ݒ肷��
	m_pMotion = pMotion;
}

//=======================================
// ���[�V�����̎擾����
//=======================================
CMotion* CPlayer::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//=======================================
// �v���C���[��ID�̎擾����
//=======================================
CPlayerID* CPlayer::GetPlayerID(void) const
{
	// �v���C���[��ID�̏���Ԃ�
	return m_pPlayerID;
}

//=======================================
// �C�≉�o�̐ݒ菈��
//=======================================
void CPlayer::SetStun(const D3DXVECTOR3& pos)
{
	if (m_pStun == nullptr)
	{ // �C�≉�o�� NULL �̏ꍇ

		// �C�≉�o�𐶐�����
		m_pStun = CStun::Create(D3DXVECTOR3(pos.x, pos.y + STUN_HEIGHT, pos.z));
	}
}

//=======================================
// �C�≉�o�̎擾����
//=======================================
CStun* CPlayer::GetStun(void) const
{
	// �C��̏���Ԃ�
	return m_pStun;
}

//=======================================
// �C�≉�o�̏�������
//=======================================
void CPlayer::DeleteStun(void)
{
	if (m_pStun != nullptr)
	{ // �C��̏�� NULL ����Ȃ��ꍇ

		// �C��̏I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}
}

//=======================================
// �H��l�Y�~�̐ݒ菈��
//=======================================
void CPlayer::SetRatGhost(const D3DXVECTOR3& pos)
{
	if (m_pRatGhost == nullptr)
	{ // �H��l�Y�~�� NULL �̂Ƃ�

		// �l�Y�~�̗H��̐���
		m_pRatGhost = CRatGhost::Create(pos);
	}
}

//=======================================
// �H��l�Y�~�̏��擾����
//=======================================
CRatGhost* CPlayer::GetRatGhost(void)
{
	// �H��l�Y�~�̏���Ԃ�
	return m_pRatGhost;
}

//=======================================
// �H��l�Y�~�̏���������
//=======================================
void CPlayer::DeleteRatGhost(void)
{
	if (m_pRatGhost != nullptr)
	{ // �H��l�Y�~�� NULL ����Ȃ��ꍇ

		//�H��l�Y�~�̏I������
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}
}

//=======================================
// �~�͈̔͂̐ݒ菈��
//=======================================
void CPlayer::SetRessrectionFan(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	if (m_pRessrectionFan == nullptr)
	{ // �~�͈̔͂� NULL �̂Ƃ�

		// �����Ԃ�̉~�͈̔͐���
		m_pRessrectionFan = CRessrectionFan::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), col);
	}
}

//=======================================
// �~�͈̔͂̏��擾����
//=======================================
CRessrectionFan* CPlayer::GetRessrectionFan(void)
{
	// �~�͈̔͂̏���Ԃ�
	return m_pRessrectionFan;
}

//=======================================
// �~�͈̔͂̏���������
//=======================================
void CPlayer::DeleteRessrectionFan(void)
{
	if (m_pRessrectionFan != nullptr)
	{ // �~�͈̔͂� NULL ����Ȃ��ꍇ

		//�~�͈̔͂̏I������
		m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}
}

//=======================================
// �񕜒�UI�̐ݒ菈��
//=======================================
void CPlayer::SetRecoveringUI(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	if (m_pRecoveringUI == nullptr)
	{ // �񕜒�UI�� NULL �̂Ƃ�

		// �񕜒�UI�͈̔͐���
		m_pRecoveringUI = CRecoveringUI::Create(D3DXVECTOR3(pos.x + 80.0f, pos.y + 100.0f, pos.z), posOld);
	}
}

//=======================================
// �񕜒�UI�̏��擾����
//=======================================
CRecoveringUI* CPlayer::GetRecoveringUI(void)
{
	// �񕜒�UI�̏���Ԃ�
	return m_pRecoveringUI;
}

//=======================================
// �񕜒�UI�̏���������
//=======================================
void CPlayer::DeleteRecoveringUI(void)
{
	if (m_pRecoveringUI != nullptr)
	{ // �񕜒�UI�� NULL ����Ȃ��ꍇ

		//�񕜒�UI�̏I������
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}
}

//=======================================
// �`�B���b�Z�[�W�̐ݒ菈��
//=======================================
void CPlayer::SetSpeechMessage(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const int type)
{
	if (m_pSpeechMessage == nullptr)
	{ // �`�B���b�Z�[�W�� NULL�̂Ƃ�

		m_pSpeechMessage = CSpeechMessage::Create(pos, size, nLife, (CSpeechMessage::TYPE)type);
	}
}

//=======================================
// �`�B���b�Z�[�W�̎擾����
//=======================================
CSpeechMessage* CPlayer::GetSpeechMessage(void)
{
	// �`�B���b�Z�[�W��Ԃ�
	return m_pSpeechMessage;
}

//=======================================
// �`�B���b�Z�[�W�̏�������
//=======================================
void CPlayer::DeleteSpeechMessage(void)
{
	if (m_pSpeechMessage != nullptr)
	{ // �`�B���b�Z�[�W�� NULL ����Ȃ��Ƃ�

		// �`�B���b�Z�[�W�̏I������
		m_pSpeechMessage->Uninit();
		m_pSpeechMessage = nullptr;
	}
}

//=======================================
// ���S���̐ݒ菈��
//=======================================
void CPlayer::SetDeathArrow(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx)
{
	if (m_pDeathArrow[nIdx] == nullptr)
	{ // ���S��� NULL �̎�

	  // ���S���̐���
		m_pDeathArrow[nIdx] = CDeathArrow::Create(pos, posOld, rot);
	}
	else if (m_pDeathArrow[nIdx] != nullptr)
	{ // ���S��� NULL ����Ȃ��Ƃ�

		m_pDeathArrow[nIdx]->SetPos(pos);			// �ʒu�ݒ�
		m_pDeathArrow[nIdx]->SetPosOld(posOld);		// �O��̈ʒu�ݒ�
		m_pDeathArrow[nIdx]->SetRot(rot);			// �����ݒ�
	}
}

//=======================================
// ���S���̎擾����
//=======================================
CDeathArrow* CPlayer::GetDeathArrow(const int nIdx)
{
	// ���S���̏���Ԃ�
	return m_pDeathArrow[nIdx];
}

//=======================================
// ���S���̏�������
//=======================================
void CPlayer::DeleteDeathArrow(const int nIdx)
{
	if (m_pDeathArrow[nIdx] != nullptr)
	{ // ���S��� NULL ����Ȃ���

	  // ���S���̏I������
		m_pDeathArrow[nIdx]->Uninit();
		m_pDeathArrow[nIdx] = nullptr;
	}
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
D3DXVECTOR3 CPlayer::GetMove(void) const
{
	// �ړ��ʂ�Ԃ�
	return m_move;
}

//=======================================
// �����蔻��T�C�Y�̐ݒ菈��
//=======================================
void CPlayer::SetSizeColl(const D3DXVECTOR3& size)
{
	// �����蔻��̃T�C�Y��ݒ肷��
	m_sizeColl = size;
}

//=======================================
// ��ނ̐ݒ菈��
//=======================================
void CPlayer::SetType(const TYPE type)
{
	// ��ނ�ݒ肷��
	m_type = type;
}

//=======================================
// ��ނ̎擾����
//=======================================
CPlayer::TYPE CPlayer::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=======================================
// �v���C���[��ID�̎擾����
//=======================================
int CPlayer::GetPlayerIdx(void) const
{
	// �v���C���[�̃C���f�b�N�X��Ԃ�
	return m_nPlayerIdx;
}

//=======================================
// ���x�̐ݒ菈��
//=======================================
void CPlayer::SetSpeed(const float fSpeed)
{
	// ���x��ݒ肷��
	m_fSpeed = fSpeed;
}

//=======================================
// ���x�̎擾����
//=======================================
float CPlayer::GetSpeed(void) const
{
	// ���x��Ԃ�
	return m_fSpeed;
}

//=======================================
// �U������̐ݒ菈��
//=======================================
void CPlayer::SetEnableAttack(const bool bAttack)
{
	// �U�������ݒ肷��
	m_bAttack = bAttack;
}

//=======================================
// �U������̎擾����
//=======================================
bool CPlayer::IsAttack(void) const
{
	// �U�������Ԃ�
	return m_bAttack;
}

//=======================================
// �ړ��󋵂̐ݒ菈��
//=======================================
void CPlayer::SetEnableMove(const bool bMove)
{
	// �ړ��󋵂�ݒ肷��
	m_bMove = bMove;
}

//=======================================
// �ړ��󋵂̎擾����
//=======================================
bool CPlayer::IsMove(void) const
{
	// �ړ��󋵂�Ԃ�
	return m_bMove;
}

//=======================================
// ���񂾃l�Y�~�̕������Ԃ̍��v�ݒ�
//=======================================
void CPlayer::SetResurrectionTime(const int nRezTime)
{
	// �������Ԃ̍��v�ݒ�
	m_nResurrectionTime = nRezTime;
}

//=======================================
// ���񂾃l�Y�~�̕������Ԃ̍��v�ǉ�
//=======================================
void CPlayer::AddResurrectionTime(const int nRezTime)
{
	// �������Ԃ̍��v���Z
	m_nResurrectionTime += nRezTime;
}

//=======================================
// ���񂾃l�Y�~�̕������Ԃ̍��v�擾
//=======================================
int CPlayer::GetResurrectionTime(void)
{
	// �������Ԃ̍��v��Ԃ�
	return m_nResurrectionTime;
}

//=======================================
// �񕜒��\���̔���
//=======================================
void CPlayer::SetDispRecoveringUI(const bool bRez)
{
	if (m_pRecoveringUI != nullptr)
	{ // �񕜒�UI�� NULL����Ȃ�������

		// �񕜏�Ԃ�ݒ肷��
		m_pRecoveringUI->SetDisplayUI(bRez);
	}
}

//=======================================
// �񕜒��\���̎擾
//=======================================
bool CPlayer::IsDispRecoveringUI(void)
{
	// �񕜏�Ԃ�Ԃ�
	return m_pRecoveringUI->GetDisplayUI();
}