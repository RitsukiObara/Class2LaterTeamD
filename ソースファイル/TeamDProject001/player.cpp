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

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "collision.h"

#include "Cat.h"
#include "rat.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY				(1.0f)			// �d��
#define ADD_MOVE_Y			(30.0f)			// ����
#define NONE_PLAYERIDX		(-1)			// �v���C���[�̔ԍ��̏����l
#define MAX_LIFE			(1)				// �����̍ő�l
#define STUN_HEIGHT			(80.0f)			// �C�≉�o���o�Ă��鍂��
#define ID_HEIGHT			(90.0f)			// ID���o�Ă��鍂��
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// ������я�Ԃ̈ړ���

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
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_type = TYPE_CAT;					// ���
	m_nLife = 0;						// ����
	m_nPlayerIdx = NONE_PLAYERIDX;		// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩
}

//==============================
// �l�Y�~�̏���������
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
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_type = TYPE_CAT;					// ���
	m_nLife = 0;						// ����
	m_nPlayerIdx = NONE_PLAYERIDX;		// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~�̏I������
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

	// �I������
	CCharacter::Uninit();
}

//=====================================
// �l�Y�~�̍X�V����
//=====================================
void CPlayer::Update(void)
{
	// ��Q���Ƃ̓����蔻��
	collision::ObstacleHit(this, m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	//�ǂƂ̓����蔻��
	SetPos(collision::WallCollision(GetPosOld(), GetPos()));

	// ��Q���Ƃ̓����蔻��
	ObstacleCollision();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E))
	{
		collision::ObstacleAction(this, m_sizeColl.x, m_type);
	}

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

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n�����F%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_nLife);
}

//=====================================
// �l�Y�~�̕`�揈��
//=====================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//=====================================
// ������я��
//=====================================
void CPlayer::Smash(const float fAngle)
{
	// �ړ��ʂ�ݒ肷��
	m_move.x = sinf(fAngle) * SMASH_MOVE.x;
	m_move.y = SMASH_MOVE.y;
	m_move.z = cosf(fAngle) * SMASH_MOVE.z;
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
	m_nLife = MAX_LIFE;					// ����
	m_nPlayerIdx = nID;					// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩

	if (m_pPlayerID == nullptr)
	{ // �v���C���[��ID�\���� NULL �̏ꍇ

		// �v���C���[��ID�\���̐�������
		m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z), nID);
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
// �����̐ݒ菈��
//=======================================
void CPlayer::SetLife(const int nLife)
{
	// ������ݒ肷��
	m_nLife = nLife;
}

//=======================================
// �����̎擾����
//=======================================
int CPlayer::GetLife(void) const
{
	// ������Ԃ�
	return m_nLife;
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
// ��������
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// �l�Y�~�̃|�C���^
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
// �ړ�����
//=======================================
void CPlayer::Move(void)
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
			rot.y = D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
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
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) < 0)
	{ // �����������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // ����������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
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
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
	{ // ����������ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
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
	//collision::ObstacleCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	// �u���b�N�Ƃ̓����蔻��
	collision::BlockCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z);

	// �ʒu��ݒ肷��
	SetPos(pos);
}