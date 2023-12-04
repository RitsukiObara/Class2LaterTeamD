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
#include "itemUI.h"
#include "fraction.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	static const D3DXVECTOR3 ITEMUI_POS[MAX_PLAY] =			// �A�C�e��UI�̈ʒu
	{
		D3DXVECTOR3(70.0f,50.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 70.0f,50.0f,0.0f),
		D3DXVECTOR3(70.0f,SCREEN_HEIGHT * 0.5f + 50.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 70.0f,SCREEN_HEIGHT * 0.5f + 50.0f,0.0f)
	};
	static const float MOVE_SPEED = 20.0f;			// �ړ����x
	static const float ATTACK_DISTANCE = 100.0f;	// �U���͈͂܂ł̋���
	static const D3DXVECTOR3 CAT_SIZE = D3DXVECTOR3(70.0f, 200.0f, 70.0f);		// �����蔻��̃T�C�Y
	static const float GRAVITY = 1.0f;				// �d��
}

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define ATTACK_SIZE		(D3DXVECTOR3(95.0f, 50.0f, 95.0f))		// �U���̔���̑傫��

//=========================================
// �R���X�g���N�^
//=========================================
CCat::CCat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pItemUI = nullptr;			// �A�C�e��UI�̏��
	m_AttackPos = NONE_D3DXVECTOR3;	//�U���̈ʒu
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_nItemCount = 0;				// �A�C�e���̏�����
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
	m_pItemUI = nullptr;			// �A�C�e��UI�̏��
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_nItemCount = 0;				// �A�C�e���̏�����

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �v���C���[�̏I������
//===========================================
void CCat::Uninit(void)
{
	if (m_pItemUI != nullptr)
	{ // �A�C�e��UI�̏�� NULL ����Ȃ��ꍇ
		
		// �A�C�e��UI�̏I������
		m_pItemUI->Uninit();
		m_pItemUI = nullptr;
	}

	// �I������
	CPlayer::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CCat::Update(void)
{
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	// �d�͏���
	Gravity();

	if (CPlayer::GetStunState() != CPlayer::STUNSTATE_STUN &&
		CPlayer::GetState() != CPlayer::STATE_DEATH &&
		m_AttackState == ATTACKSTATE_MOVE)
	{// �ړ���Ԃ̎�

		// ���x��ݒ肷��
		SetSpeed(MOVE_SPEED);

		if (GetStunState() != STUNSTATE_SMASH)
		{ // ������я�ԈȊO�̏ꍇ

			// �ړ����쏈��
			MoveControl();

			// �A�C�e���̐ݒu����
			ItemSet();
		}

		// �U�����͂̏���
		Attack();

		// ���[�V������Ԃ̊Ǘ�
		MotionManager();

		// �ړ�����
		Move();
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
	collision::ItemCollision(*this, m_nItemCount);

	// �N���n�ʂ̓����蔻��
	Elevation();

	// �p�x�̐��K��
	RotNormalize();

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
// �d�͏���
//===========================================
void CCat::Gravity(void)
{
	// �ړ��ʂ��擾����
	D3DXVECTOR3 move = GetMove();

	// �d�͉��Z
	move.y -= GRAVITY;

	// ����K�p����
	SetMove(move);
}

//===========================================
// �U������
//===========================================
void CCat::Attack(void)
{
	// ���[�J���ϐ��錾
	CPlayer* pPlayer = nullptr;
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, GetPlayerIdx()) == true)
	{ // ENTER�L�[(A�{�^��)�������Ă����ꍇ

		// ��Ԃ��U�������ɂ���
		m_AttackState = ATTACKSTATE_STANDBY;
		m_nAtkStateCount = 20;
		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			// �v���C���[�̏����擾����
			pPlayer = CGame::GetPlayer(nCnt);

			if (pPlayer != nullptr &&
				pPlayer->GetType() == CPlayer::TYPE_RAT)
			{ // �v���C���[���l�Y�~�̏ꍇ

				if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE),
					pPlayer->GetPos(),
					ATTACK_SIZE,
					D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(-ATTACK_SIZE.x, -ATTACK_SIZE.y, -ATTACK_SIZE.z),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
				{ // XY�̋�`�ɓ������Ă���

					if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE),
						pPlayer->GetPos(),
						ATTACK_SIZE, D3DXVECTOR3(30.0f, 50.0f, 30.0f),
						D3DXVECTOR3(-ATTACK_SIZE.x, -ATTACK_SIZE.y, -ATTACK_SIZE.z), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
					{ // XZ�̋�`�ɓ������Ă���

						// �v���C���[�̃q�b�g����
						pPlayer->Hit();
					}
				}
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
		{//��ԃJ�E���g��0�ɂȂ�����

			D3DXVECTOR3 pos = GetPos();
			D3DXVECTOR3 rot = GetRot();

			m_AttackState = ATTACKSTATE_ATTACK;
			m_nAtkStateCount = 10;

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				// �j�Ђ̐���
				CFraction::Create(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE), CFraction::TYPE_CAT_ATTACK);
			}
		}
		break;

	case ATTACKSTATE_ATTACK:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), true);

		if (useful::CircleCollisionXZ(m_AttackPos, m_AttackPos,10.0f,10.0f) == true)
		{

		}

		if (m_nAtkStateCount <= 0)
		{//��ԃJ�E���g��0�ɂȂ�����
			m_AttackState = ATTACKSTATE_MOVE;
		}
		break;
	}

	if (m_nAtkStateCount > 0)
	{
		m_nAtkStateCount--;
	}
}

//=======================================
// �N���n�ʂ̓����蔻��
//=======================================
void CCat::Elevation(void)
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
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu�ƈړ��ʂ��X�V����
	SetPos(pos);
	SetMove(move);
}

//===========================================
// �l�R�̃A�C�e���ݒu����
//===========================================
void CCat::ItemSet(void)
{
	if (m_nItemCount > 0 &&
		m_pItemUI->GetItemUI(CItemUI::ORDER_FRONT).pMark != nullptr &&
		(CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_TAB) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, GetPlayerIdx()) == true))
	{ // �A�C�e���������Ă����Ԃ�Y�{�^���������ꂽ�ꍇ

		switch (m_pItemUI->GetItemUI(CItemUI::ORDER_FRONT).type)
		{
		case CItem::TYPE_MOUSETRAP:		// �l�Y�~�߂�

			// �A�C�e����ݒu����
			CObstacle::Create(GetPos(), GetRot(), CObstacle::TYPE::TYPE_MOUSETRAP);

			break;

		default:

			// ��~
			assert(false);

			break;
		}

		// ���̃\�[�g����
		m_pItemUI->SortInfo();

		// �A�C�e���̃J�E���g�������Z����
		m_nItemCount--;
	}
}

//===========================================
// �f�o�b�O�\��
//===========================================
void CCat::DebugMessage(void)
{
	CManager::Get()->GetDebugProc()->Print("\n �L���--------------------------------------------\n");

	// �L�̍U���ʒu����\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n", GetPos().x, GetPos().y, GetPos().z);

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
// ���̐ݒ菈��
//=======================================
void CCat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// ���̐ݒ菈��
	CPlayer::SetData(pos, nID, type);

	// �����蔻��̃T�C�Y�̐ݒ�
	SetSizeColl(CAT_SIZE);

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

	// �A�C�e��UI�̐�������
	SetItemUI();
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

//=====================================
// �A�C�e���̎擾����
//=====================================
void CCat::GetItem(const CItem::TYPE type)
{
	// �A�C�e���̏����J�E���g�����Z����
	m_nItemCount++;

	if (m_nItemCount == 1)
	{ // 1�ڂ̏ꍇ

		// �A�C�e���̃}�[�N�𐶐�����
		m_pItemUI->SetMark(type, CItemUI::ORDER_FRONT);
	}
	else if (m_nItemCount == 2)
	{ // 2�ڂ̏ꍇ

		// �A�C�e���̃}�[�N�𐶐�����
		m_pItemUI->SetMark(type, CItemUI::ORDER_BACK);
	}
}

//=====================================
// �A�C�e��UI�̐ݒ菈��
//=====================================
void CCat::SetItemUI(void)
{
	if (m_pItemUI == nullptr)
	{ // �A�C�e��UI�� NULL �̏ꍇ

		// �A�C�e��UI�̐�������
		m_pItemUI = CItemUI::Create(ITEMUI_POS[GetPlayerIdx()]);
	}
}

//=====================================
// �A�C�e��UI�̎擾����
//=====================================
CItemUI* CCat::GetItemUI(void) const
{
	// �A�C�e��UI�̏���Ԃ�
	return m_pItemUI;
}

//=====================================
// �A�C�e��UI�̏�������
//=====================================
void CCat::DeleteItemUI(void)
{
	if (m_pItemUI != nullptr)
	{ // �A�C�e��UI�� NULL ����Ȃ��ꍇ

		// �A�C�e��UI�̏I������
		m_pItemUI->Uninit();
		m_pItemUI = nullptr;
	}
}