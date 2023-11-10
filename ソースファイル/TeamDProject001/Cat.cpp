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
#include "Particle.h"
#include "motion.h"
#include "shadowCircle.h"
#include "destruction.h"
#include "ripple.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_LIFE				(3)			// �̗͂̍ő吔
#define COLLISION_WIDTH			(20.0f)		// �����蔻�莞�Ɏg�����̕�
#define COLLISION_HEIGHT		(150.0f)	// �����蔻�莞�Ɏg�����̍���
#define COLLISION_DEPTH			(20.0f)		// �����蔻�莞�Ɏg�����̉��s
#define START_CAMERA_POSR_Y		(100.0f)	// �X�^�[�g���̃J�����̒����_(Y��)
#define START_CAMERA_POSV_Y		(130.0f)	// �X�^�[�g���̃J�����̎��_(Y��)
#define START_CAMERA_DISTANCE	(200.0f)	// �X�^�[�g���̃J�����̋���
#define START_COUNT				(40)		// �X�^�[�g�̃J�E���g
#define PUNCH_COUNT				(150)		// �p���`��Ԃ̃J�E���g��
#define GOAL_COUNT				(80)		// �S�[����Ԃ̃J�E���g��
#define LEAVE_GRAVITY			(0.4f)		// �ޏ��Ԃ̏d��
#define FINISH_GRAVITY			(-0.6f)		// �I����Ԃ̏d��
#define NEAR_POS				(0.0f)		// ��O�̈ʒu
#define FAR_POS					(1000.0f)	// ���s�̈ʒu
#define ADD_GRAVITY				(-50.0f)	// �ǉ��̏d��
#define FALL_HEIGHT				(-600.0f)	// ���������肪�ʂ鏊
#define PUNCH_DSTR_SHIFT		(D3DXVECTOR3(40.0f, 100.0f, 0.0f))		// �p���`���̌��j�̂��炷��
#define PUNCH_DSTR_SIZE			(D3DXVECTOR3(100.0f, 100.0f, 0.0f))		// �p���`���̌��j�̃T�C�Y
#define PUNCH_DSTR_COL			(D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f))		// �p���`���̌��j�̐F
#define PUNCH_DSTR_LIFE			(6)			// �p���`���̌��j�̎���
#define PUNCH_RIPPLE_SHIFT		(D3DXVECTOR3(45.0f, 100.0f, 0.0f))		// �p���`���̔g��̂��炷��
#define OUT_RANGE_GRAVITY		(-5.0f)		// �͈͊O�ɏo���Ƃ��̏d��
#define ADD_START_POS			(D3DXVECTOR3(20.0f, -20.0f, 0.0f))		// �X�^�[�g��Ԃ̉��Z����ʒu

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
	m_pAction = nullptr;			// �v���C���[�̍s���̏��
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_nStartCount = 0;				// �X�^�[�g�J�E���g
	m_nGoalCount = 0;				// �S�[�����̃J�E���g
	m_fSpeed = 0.0f;				// ���x
	m_fAlpha = 1.0f;				// �����x
	m_bMove = false;				// �ړ���
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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	// �S�Ă̒l������������
	m_posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_rotDest = NONE_D3DXVECTOR3;	// �ړI�̌���
	m_nShadowIdx = INIT_SHADOW;		// �e�̃C���f�b�N�X
	m_nStartCount = 0;				// �X�^�[�g�J�E���g
	m_nGoalCount = 0;				// �S�[�����̃J�E���g
	m_fSpeed = 0.0f;				// ���x
	m_fAlpha = 1.0f;				// �����x
	m_bMove = false;				// �ړ���

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
	// �O��̈ʒu�̐ݒ菈��
	SetPosOld(GetPos());

	// ���[�V�����̍X�V����
	m_pMotion->Update();

	 // �e�̈ʒu�����̐ݒ菈��
	CShadowCircle::SetPosRot(m_nShadowIdx, GetPos(), GetRot());

	// �v���C���[�̏���\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�ړ��ʁF%f %f %f\n", GetPos().x, GetPos().y, GetPos().z, m_move.x, m_move.y, m_move.z);
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
// ���[�V�����̏��̐ݒ菈��
//===========================================
CMotion* CCat::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//===========================================
// �A�N�V�����̏��̐ݒ菈��
//===========================================
CCatAct* CCat::GetAction(void) const
{
	// �s����Ԃ̏���Ԃ�
	return m_pAction;
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

	// �J������ݒ肷��
	CManager::Get()->GetCamera()->SetPosR(D3DXVECTOR3(pos.x, pos.y + START_CAMERA_POSR_Y, pos.z));
	CManager::Get()->GetCamera()->SetPosV(D3DXVECTOR3(pos.x, pos.y + START_CAMERA_POSV_Y, pos.z));
	CManager::Get()->GetCamera()->SetDistance(START_CAMERA_DISTANCE);
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
void CCat::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
D3DXVECTOR3 CCat::GetMove(void) const
{
	// �ړ��ʂ�Ԃ�
	return m_move;
}

//=======================================
// �ڕW�̌����̐ݒ菈��
//=======================================
void CCat::SetRotDest(const D3DXVECTOR3& rot)
{
	// �ڕW�̌�����ݒ肷��
	m_rotDest = rot;
}

//=======================================
// �ڕW�̌����̎擾����
//=======================================
D3DXVECTOR3 CCat::GetRotDest(void) const
{
	// �ڕW�̌�����Ԃ�
	return m_rotDest;
}

//=======================================
// ���x�̐ݒ菈��
//=======================================
void CCat::SetSpeed(float fSpeed)
{
	// ���x��ݒ肷��
	m_fSpeed = fSpeed;
}

//=======================================
// ���x�̎擾����
//=======================================
float CCat::GetSpeed(void) const
{
	// ���x��Ԃ�
	return m_fSpeed;
}

//=======================================
// �����x�̐ݒ菈��
//=======================================
void CCat::SetAlpha(const float fAlpha)
{
	// �����x��ݒ肷��
	m_fAlpha = fAlpha;
}

//=======================================
// �����x�̓���ւ�����
//=======================================
void CCat::SwapAlpha(void)
{
	// �����x�����ւ���
	m_fAlpha = (m_fAlpha >= 1.0f) ? 0.0f : 1.0f;
}

//=======================================
// �����x�̎擾����
//=======================================
float CCat::GetAlpha(void) const
{
	// �����x��Ԃ�
	return m_fAlpha;
}

//=======================================
// �ړ��󋵂̐ݒ菈��
//=======================================
void CCat::SetEnableMove(bool bMove)
{
	// �ړ��󋵂�ݒ肷��
	m_bMove = bMove;
}

//=======================================
// �ړ��󋵂̎擾����
//=======================================
bool CCat::IsMove(void) const
{
	// �ړ��󋵂�Ԃ�
	return m_bMove;
}

//=======================================
// �ړ���������
//=======================================
void CCat::CollisionMagicWall(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	if (pos.z >= FAR_POS)
	{ // �ʒu�����ȏ�ɂȂ����ꍇ

	  // �ʒu��␳����
		pos.z = FAR_POS;
	}

	if (pos.z <= NEAR_POS)
	{ // �ʒu�����ȉ��ɂȂ����ꍇ

	  // �ʒu��␳����
		pos.z = NEAR_POS;
	}

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �X�^�[�g��Ԃ̏���
//=======================================
void CCat::StartProcess(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

									// �ʒu�����Z����
	pos += ADD_START_POS;

	if (pos.x >= m_posDest.x)
	{ // �ʒu���ړI�𒴂����ꍇ

	}

	if (m_nStartCount >= START_COUNT)
	{ // �X�^�[�g�J�E���g��ݒ肷��

	}

	// �ʒu��K�p����
	SetPos(pos);
}

//=======================================
// �S�[����Ԃ̏���
//=======================================
void CCat::GoalProcess(void)
{

}

//=======================================
// �ޏ��Ԃ̏���
//=======================================
void CCat::LeaveProcess(void)
{

}

//=======================================
// �I����Ԃ̏���
//=======================================
void CCat::FinishProcess(void)
{

}