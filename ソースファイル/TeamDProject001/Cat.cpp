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

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CCat* CCat::m_pPlayer = nullptr;		// �v���C���[�̃|�C���^

//=========================================
// �R���X�g���N�^
//=========================================
CCat::CCat() : CCharacter(CObject::TYPE_CAT, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;			// ���[�V�����̏��
	m_AttackPos = NONE_D3DXVECTOR3;	//�U���̈ʒu
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
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
	if (FAILED(CCharacter::Init()))
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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	// �S�Ă̒l������������
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
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
	// ���[�V�����̃��������J������
	delete m_pMotion;
	m_pMotion = nullptr;

	// �I������
	CCharacter::Uninit();

	// �v���C���[�� NULL �ɂ���
	m_pPlayer = nullptr;
}

//===========================================
// �X�V����
//===========================================
void CCat::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(pos);

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	if (m_AttackState == ATTACKSTATE_MOVE)
	{// �ړ���Ԃ̎�
		m_fSpeed = MOVE_SPEED;

		// �U���ʒu�̈ړ����͏���
		Move();

		// �U�����͂̏���
		Attack();

		// ���[�V������Ԃ̊Ǘ�
		MotionManager();
	}
	else
	{
		m_move = NONE_D3DXVECTOR3;
	}

	// �U����Ԃ̊Ǘ�
	AttackStateManager();

	//�ʒu�X�V
	pos += m_move;

	 // �e�̈ʒu�����̐ݒ菈��
	CShadowCircle::SetPosRot(m_nShadowIdx, pos, GetRot());

	SetPos(pos);

	// �f�o�b�O�\��
	DebugMessage();
}

//===========================================
// �v���C���[�̕`�揈��
//===========================================
void CCat::Draw(void)
{
	//// �f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//// Z�e�X�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);					//Z�e�X�g�̐ݒ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//Z�e�X�g�̗L��/�����ݒ�

	//																		// �`�揈��
	//CCharacter::Draw(m_fAlpha);

	//// Z�e�X�g��L���ɂ���
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z�e�X�g�̐ݒ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Z�e�X�g�̗L��/�����ݒ�

	// �`�揈��
	CCharacter::Draw();
}

//===========================================
// �U���ʒu�̈ړ�����
//===========================================
void CCat::Move(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_L) == true)
	{ // �E���������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_I) == true)
		{ // ����������ꍇ

		  // ������ݒ肷��
			rot.y = D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_K) == true)
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
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_J) == true)
	{ // �����������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_I) == true)
		{ // ����������ꍇ

		  // ������ݒ肷��
			rot.y = D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_K) == true)
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
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_I) == true)
	{ // ����������ꍇ

	  // ������ݒ肷��
		rot.y = D3DX_PI;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_K) == true)
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

//===========================================
// �U������
//===========================================
void CCat::Attack(void)
{
	// ���[�J���ϐ��錾
	CRat *pRat[3];
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // W�L�[�������Ă����ꍇ

		// ��Ԃ��U�������ɂ���
		m_AttackState = ATTACKSTATE_STANDBY;
		m_nAtkStateCount = 20;
		for (int nCnt = 0; nCnt < 3; nCnt++)

		{
			pRat[nCnt] = CGame::GetRat(nCnt);
			while (pRat[nCnt] != nullptr)
			{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

				if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE),
					pRat[nCnt]->GetPos(),
					D3DXVECTOR3(30.0f, 50.0f, 30.0f), 
					D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f), 
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
				{ // XY�̋�`�ɓ������Ă���

					if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pRat[nCnt]->GetPos(),
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

//===========================================
// ���[�V�����̏��̐ݒ菈��
//===========================================
CMotion* CCat::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//===========================================
// �擾����
//===========================================
CCat* CCat::Get(void)
{
	if (m_pPlayer != nullptr)
	{ // �v���C���[�̏�񂪂���ꍇ

	  // �v���C���[�̃|�C���^��Ԃ�
		return m_pPlayer;
	}
	else
	{ // ��L�ȊO

	  // ��~
		assert(false);

		// �v���C���[�̃|�C���^��Ԃ�
		return m_pPlayer;
	}
}

//===========================================
// ��������
//===========================================
CCat* CCat::Create(const D3DXVECTOR3& pos)
{
	if (m_pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ���������m�ۂ���
		m_pPlayer = new CCat;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // NULL ��Ԃ�
		return m_pPlayer;
	}

	if (m_pPlayer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(m_pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // �x����
			MessageBox(NULL, "�v���C���[�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pPlayer->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return m_pPlayer;
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
void CCat::SetData(const D3DXVECTOR3& pos)
{
	// �S�Ă̒l������������
	m_posDest = pos;	// �ړI�̈ʒu
	SetPos(pos);		// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦

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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCat::MotionManager(void)
{
	if (m_AttackState == ATTACKSTATE_STANDBY)
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