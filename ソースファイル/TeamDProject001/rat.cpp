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
#include "rat.h"
#include "game.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "elevation_manager.h"
#include "objectElevation.h"
#include "obstacle_manager.h"
#include "obstacle.h"
#include "collision.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY		(1.0f)			// �d��
#define ADD_MOVE_Y	(30.0f)			// ����
#define NONE_RATIDX	(-1)			// �l�Y�~�̔ԍ��̏����l
#define ATTACK_DISTANCE	(200.0f)	// �U���͈͂܂ł̋���
#define MAX_LIFE	(3)				// �����̍ő�l
#define TIME_DAMAGE	(60 * 1)		// �_���[�W�H�炤�܂ł̎���

//==============================
// �R���X�g���N�^
//==============================
CRat::CRat() : CModel(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_nRatIdx = NONE_RATIDX;			// �l�Y�~�̔ԍ�
	m_nLife = 0;						// ����
	m_nDamageCounter = TIME_DAMAGE;		// �_���[�W�H�炤�܂ł̃J�E���^�[

	m_bJump = false;					// �W�����v������
	m_bLand = true;						// ���n������
	m_bAttack = false;					// �U��������

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
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_nRatIdx = NONE_RATIDX;			// �l�Y�~�̔ԍ�

	m_nLife = MAX_LIFE;					// ����
	m_nDamageCounter = TIME_DAMAGE;		// �_���[�W�H�炤�܂ł̃J�E���^�[

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CRat::Uninit(void)
{
	// �l�Y�~����������
	CGame::DeleteRat(m_nRatIdx);

	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CRat::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// �ړ�����
	Move();

	// �W�����v����
	Jump();

	// �U������
	Attack();

	// �q�b�g����
	Hit();

	// �N���n�ʂ̓����蔻��
	Elevation();

	// ��Q���Ƃ̓����蔻��
	ObstacleCollision();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n�W�����v�󋵁F%d\n�����F%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump, m_nLife);
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CRat::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_KARIPLAYER);	// ���f���̏��ݒ�
}

//=======================================
// �l�Y�~�̔ԍ��̐ݒ菈��
//=======================================
void CRat::SetRatIdx(const int nIdx)
{
	// �l�Y�~�̔ԍ���ݒ肷��
	m_nRatIdx = nIdx;
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
CRat* CRat::Create(const D3DXVECTOR3& pos)
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
		pRat->SetData(pos);
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
void CRat::Jump(void)
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
void CRat::Attack(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_J) == true/* && m_bAttack == false*/)
	{ // J�L�[���������ꍇ

		while (pObstacle != nullptr)
		{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
				GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
				GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
			{ // XY�̋�`�ɓ������Ă���

				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
					GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
					GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
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
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	D3DXVECTOR3 pos = GetPos();

	if (m_nDamageCounter >= TIME_DAMAGE)
	{ // �_���[�W�H�炤���ԂɂȂ�����

		while (pObstacle != nullptr)
		{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

			if (useful::RectangleCollisionXY(pos, pObstacle->GetPos(),
				GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
				GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
			{ // XY�̋�`�ɓ������Ă���

				if (useful::RectangleCollisionXZ(pos, pObstacle->GetPos(),
					GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
					GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
				{ // XZ�̋�`�ɓ������Ă���

					m_nLife--;		// �������炷
					m_nDamageCounter = 0;		// �_���[�W�H�炤�܂ł̎��ԃ��Z�b�g

					if (m_nLife <= 0)
					{ // �����������Ƃ�

						// �I������
						Uninit();
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

			m_bJump = false;		// �W�����v���ĂȂ���Ԃɂ���
			m_bLand = true;			// ���n������Ԃɂ���
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

	// ��Q���Ƃ̓����蔻��
	collision::ObstacleCollision(pos, GetPosOld(), 30.0f, 50.0f, 30.0f);

	// �ʒu��ݒ肷��
	SetPos(pos);
}