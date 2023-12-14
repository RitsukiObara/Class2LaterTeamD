//===========================================
//
// �e���r�̏���[cup.cpp]
// Author �x�씋��
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "tv.h"
#include "useful.h"
#include "object3D.h"
#include "input.h"
#include "texture.h"
#include "collision.h"
#include "block.h"
#include "player.h"
#include "game.h"

//------------------------------
// �}�N����`
//------------------------------
#define COOL_TIME			(300)	// �N�[���^�C��
#define CHANGE_TIME			(120)	// ��ʕω����x
#define VISION_SIZE			(D3DXVECTOR3(150.0f, 80.0f, 0.0f))		// �r�W�����̃T�C�Y
#define NONE_TEXTURE		("data\\TEXTURE\\TV000.png")			// ���ł��Ȃ���ʂ̃e�N�X�`��
#define BOMB_TEXTURE		("data\\TEXTURE\\TV001.png")			// ���a�̉�ʂ̃e�N�X�`��
#define COOLTIME_TEXTURE	("data\\TEXTURE\\TV_sandstorm.jpg")		// �N�[���^�C�����̃e�N�X�`��
#define CAT_RADIUS			(70.0f)		// �l�R�̔��a
#define RAT_RADIUS			(30.0f)		// �l�R�̔��a

//==============================
// �R���X�g���N�^
//==============================
CTv::CTv() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_NONE;				// �A�C�e���������Ԃ�
	m_pVision = nullptr;				// �|���S������nullptr
	m_pRemocon = nullptr;				// �����R������nullptr
	m_vtxMax = NONE_D3DXVECTOR3;		// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;		// �ŏ��l
	m_nCoolTime = 0;					// �N�[���^�C��
	SetRatUse(false);					// �l�Y�~���g�p�ł��邩
	SetCatUse(true);					// �l�R���g�p�ł��邩
}

//==============================
// �f�X�g���N�^
//==============================
CTv::~CTv()
{

}

//==============================
// �e���r�̏���������
//==============================
HRESULT CTv::Init(void)
{

	// �S�Ă̒l���N���A����
	m_State = STATE_NONE;				// �A�C�e���������Ԃ�
	m_pVision = nullptr;				// �|���S������nullptr
	m_pRemocon = nullptr;				// �����R������nullptr
	m_vtxMax = NONE_D3DXVECTOR3;		// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;		// �ŏ��l
	m_nCoolTime = 0;					// �N�[���^�C��

	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	m_pRemocon = CBlock::Create(D3DXVECTOR3(100.0f, 0.0f, 200.0f), CBlock::ROTTYPE_FRONT, CBlock::TYPE_REMOCON);

	// �g�p����
	SetRatUse(false);								// �l�Y�~���g�p�ł��邩
	SetCatUse(true);								// �l�R���g�p�ł��邩

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �e���r�̏I������
//========================================
void CTv::Uninit(void)
{
	if (m_pVision != nullptr)
	{ // �e���r��ʂ� NULL �̏ꍇ

		// �e���r��ʂ̏I������
		m_pVision->Uninit();
		m_pVision = nullptr;
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �e���r�̍X�V����
//=====================================
void CTv::Update(void)
{
	// ��ԃ}�l�[�W���[
	StateManager();

	// �e���r��ʐ؂�ւ�����
	VisionChange();

	if (m_pVision != nullptr)
	{ // �e���r��ʂ� NULL ����Ȃ��ꍇ

		// �e���r��ʂ̍X�V����
		m_pVision->Update();
	}

	if (m_pRemocon != nullptr)
	{	// �����R���̃��f����null�ł͂Ȃ��Ƃ�

		if (HitRemocon() == true)
		{	// ����Ƀv���C���[��������

			if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 0) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 1) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 2) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 3) == true ||
				CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_E) == true)
			{	// �{�^���������ꂽ�Ƃ�

				//�@�e���r�̓d������
				PowerAction();
			}
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
		{	// �{�^���������ꂽ�Ƃ�

			//�@�e���r�̓d������
			PowerAction();
		}
	}
}

//=====================================
// �e���r�̕`�揈��
//=====================================
void CTv::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	if (m_pVision != nullptr)
	{ // �r�W������ NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pVision->DrawLightOff();
	}
}

//=====================================
// ��ԊǗ�
//=====================================
void CTv::StateManager(void)
{
	if (m_pVision != nullptr)
	{ // ��ʂ� NULL ����Ȃ��ꍇ

		switch (m_State)
		{
		case STATE_NONE:	// ���ł��Ȃ���ʂ̎�

			break;

		case STATE_BOMB:	// ���e�̉�ʂ̎�

			break;

		case STATE_COOLDOWN:	// �N�[���^�C����

			// �N�[���^�C�������Z����
			m_nCoolTime--;

			if (m_nCoolTime <= 0)
			{ // �N�[���^�C���� 0 �ȉ��ɂȂ����ꍇ

				// �ʏ��Ԃɂ���
				m_State = STATE_NONE;
			}

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTv::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, rot, type);

	// �ő�l�ƍŏ��l���擾����
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // ��������O����̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = vtxMax;
		m_vtxMin = vtxMin;
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // ������������̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, -vtxMin.x);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, -vtxMax.x);
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // �������E����̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, vtxMax.x);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.x);
	}
	else
	{ // ��L�ȊO(������������̏ꍇ)

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CTv::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu�ƍŏ��l�ƍő�l��ݒ肷��
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	// �Z�ʑ̂̓����蔻��
	if (collision::HexahedronCollision
	(
		&pos,					// �v���C���[�̈ʒu
		GetPos(),				// �ʒu
		pPlayer->GetPosOld(),	// �v���C���[�̑O��̈ʒu
		GetPosOld(),			// �O��̈ʒu
		vtxMin,					// �v���C���[�̍ŏ��l
		m_vtxMin,				// �ŏ��l
		vtxMax,					// �v���C���[�̍ő�l
		m_vtxMax				// �ő�l
	) == true)
	{ // ���������ꍇ

	  // �ʒu��K�p����
		pPlayer->SetPos(pos);

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g�T�[�N������
//=====================================
bool CTv::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (m_bPower == true && 
		m_State != STATE_COOLDOWN &&
		m_State != STATE_NONE &&
		pPlayer->GetType() == CPlayer::TYPE_CAT)
	{ // �A�C�e���������Ԃ��A�l�R�̏ꍇ

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
		{ // �~�͈͓̔��̏ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �e���r�̓d���̏���
//=====================================
void CTv::Action(void)
{
	// �v���C���[�̃|�C���^��錾
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// �v���C���[���擾����
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{ // �l�R�̏ꍇ

			// �A�C�e���̎擾����
			pPlayer->GetItem(CItem::TYPE_DYNAMITE);

			// �A�C�e���������̏�Ԃɂ���
			m_State = STATE_COOLDOWN;
			m_nCoolTime = COOL_TIME;

			// �e�N�X�`���̊��蓖�ď���
			m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
		}
	}
}

//=====================================
// �d������
//=====================================
void CTv::PowerAction(void)
{
	switch (m_bPower)
	{
	case true:

		// �e���r�̓d�����Ă�������
		if (m_pVision != nullptr)
		{	// �|���S�������݂��Ă�����null�ɂ���
			m_pVision->Uninit();
			m_pVision = nullptr;

		}

		// �d��OFF�ɂ���
		m_bPower = false;

		break;

	case false:

		// �e���r�̓d�������Ă������_����
		if (m_pVision == nullptr)
		{	// �|���S�������݂��Ă��Ȃ��Ƃ���������

			D3DXVECTOR3 pPos = GetPos();
			m_pVision = CObject3D::Create(CObject::TYPE_NONE, PRIORITY_BLOCK);
			m_pVision->SetPos(D3DXVECTOR3(pPos.x - sinf(GetRot().y) * 18.0f, pPos.y + 160.0f, pPos.z - cosf(GetRot().y) * 18.0f));
			m_pVision->SetRot(GetRot());
			m_pVision->SetSize(VISION_SIZE);

			// ���_���W�̐ݒ菈��
			m_pVision->SetVertex();

			if (m_State == STATE_NONE)
			{ // ���ł��Ȃ���ʂ̎�

				// �ʏ�e�N�X�`���̊��蓖�ď���
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
			else if (m_State == STATE_BOMB)
			{ // ���e�̉�ʂ̎�

				// ���e�e�N�X�`���̊��蓖�ď���
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
			}
			else
			{ // �N�[���^�C����

				// �����e�N�X�`���̊��蓖�ď���
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
			}
		}

		// �d��ON�ɂ���
		m_bPower = true;

		break;
	}
}

//=====================================
// �����R���̃q�b�g�T�[�N������
//=====================================
bool CTv::HitRemocon(void)
{
	// �v���C���[�̃|�C���^��錾
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// �v���C���[���擾����
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer != nullptr &&
			pPlayer->GetState() != CPlayer::STATE_DEATH &&
			pPlayer->GetStunState() != CPlayer::STUNSTATE::STUNSTATE_STUN &&
			pPlayer->GetStunState() != CPlayer::STUNSTATE::STUNSTATE_WAIT)
		{ // �v���C���[�� NULL ����Ȃ��ꍇ

			switch (pPlayer->GetType())
			{
			case CPlayer::TYPE_CAT:

				if (m_bPower == false &&
					useful::CircleCollisionXZ(pPlayer->GetPos(), m_pRemocon->GetPos(), CAT_RADIUS, m_pRemocon->GetFileData().fRadius) == true)
				{ // �d��OFF���A�~�͈͓̔��̏ꍇ

					// true ��Ԃ�
					return true;
				}

				break;

			case CPlayer::TYPE_RAT:

				if (m_bPower == true &&
					useful::CircleCollisionXZ(pPlayer->GetPos(), m_pRemocon->GetPos(), RAT_RADIUS, m_pRemocon->GetFileData().fRadius) == true)
				{ // �d��ON���A�~�͈͓̔��̏ꍇ

					// true ��Ԃ�
					return true;
				}

				break;

			default:

				// ��~
				assert(false);

				break;
			}
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �e���r��ʐ؂�ւ�����
//=====================================
void CTv::VisionChange(void)
{
	if (m_bPower == true)
	{ // �d��ON��Ԃ̏ꍇ

		if (m_State != STATE_COOLDOWN)
		{ // �N�[���_�E����ԈȊO�̏ꍇ

			m_nChangeVision++;
			if (m_nChangeVision % CHANGE_TIME == 0 && m_nChangeVision > 0)
			{
				switch (m_State)
				{
				case STATE_NONE:
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
					m_State = STATE_BOMB;
					break;

				case STATE_BOMB:
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
					m_State = STATE_NONE;

					break;

				default:

					// ��~
					assert(false);

					break;
				}
			}
		}
		else
		{
			if (m_nChangeVision != 0)
			{
				m_nChangeVision = 0;
			}
		}
	}
	
}