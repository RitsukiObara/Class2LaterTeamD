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
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "elevation_manager.h"
#include "objectElevation.h"
#include "collision.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY		(1.0f)			// �d��
#define ADD_MOVE_Y	(30.0f)			// ����

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CPlayer* CPlayer::m_pPlayer = nullptr;		// �v���C���[�̏��

//==============================
// �R���X�g���N�^
//==============================
CPlayer::CPlayer() : CModel(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;			// �ړ���

	m_bJump = false;					// �W�����v������
	m_bLand = true;						// ���n������
	m_bAttack = false;					// �U��������
}

//==============================
// �f�X�g���N�^
//==============================
CPlayer::~CPlayer()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;			// �ړ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CPlayer::Uninit(void)
{
	// �I������
	CModel::Uninit();

	// �v���C���[�̏��� NULL �ɂ���
	m_pPlayer = nullptr;
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CPlayer::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// �ړ�����
	Move();

	// �W�����v����
	Jump();

	// �U������
	Attack();

	// �N���n�ʂ̓����蔻��
	Elevation();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n�W�����v�󋵁F%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump);
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPlayer::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_KARIPLAYER);	// ���f���̏��ݒ�
}

//=======================================
// �擾����
//=======================================
CPlayer* CPlayer::Get(void)
{
	if (m_pPlayer != nullptr)
	{ // �v���C���[�� NULL ����Ȃ��ꍇ

		// �v���C���[�̏���Ԃ�
		return m_pPlayer;
	}
	else
	{ // ��L�ȊO

		// NULL ��Ԃ�
		return nullptr;
	}
}

//=======================================
// ��������
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos)
{
	if (m_pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		m_pPlayer = new CPlayer;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (m_pPlayer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pPlayer->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return m_pPlayer;
}

//=======================================
// �ړ�����
//=======================================
void CPlayer::Move(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // D�L�[���������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
		{ // W�L�[���������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.25f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
		{ // S�L�[���������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.75f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			rot.y = D3DX_PI * 0.5f;
		}

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[���������ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
		{ // W�L�[���������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * -0.25f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
		{ // S�L�[���������ꍇ

			// ������ݒ肷��
			rot.y = D3DX_PI * -0.75f;
		}
		else
		{ // ��L�ȊO

			// ������ݒ肷��
			rot.y = D3DX_PI * -0.5f;
		}

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // W�L�[���������ꍇ

		// ������ݒ肷��
		rot.y = 0.0f;

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // S�L�[���������ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI;

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else
	{ // ��L�ȊO

		// �ړ��ʂ�ݒ肷��
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}

	// ������K�p����
	SetRot(rot);
}

//=======================================
// �W�����v����
//=======================================
void CPlayer::Jump(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		m_bJump == false && m_bLand == true)
	{ // SPACE�L�[���������ꍇ

		m_move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
		m_bLand = false;	// ���n���ĂȂ���Ԃɂ���
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
void CPlayer::Attack(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 posOld = GetPosOld();

	//if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_J) == true/* && m_bAttack == false*/)
	{ // J�L�[���������ꍇ

		collision::ObstacleRectCollision(pos, 50.0f, 50.0f, 50.0f);

		//m_bAttack = true;		// �U��������Ԃɂ���
	}

	// ����K�p����
	SetPos(pos);
}

//=======================================
// �N���n�ʂ̓����蔻��
//=======================================
void CPlayer::Elevation(void)
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

			m_bJump = false;		// �W�����v���ĂȂ���Ԃɂ���
			m_bLand = true;			// ���n������Ԃɂ���
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}