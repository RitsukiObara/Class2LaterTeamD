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
#include "renderer.h"
#include "tv.h"
#include "useful.h"
#include "objectX.h"
#include "consent.h"
#include "object3D.h"
#include "input.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"
#include "block.h"
#include "player.h"
#include "game.h"
//------------------------------
// �}�N����`
//------------------------------
#define COOL_TIME	(300)	// �N�[���^�C��
#define CHANGE_TIME	(120)	// ��ʕω����x
#define NONE_TEXTURE ("data\\TEXTURE\\SkyBox.jpg")				// ���ł��Ȃ���ʂ̃e�N�X�`��
#define TRAP_TEXTURE ("data\\TEXTURE\\SkyBox.jpg")				// �l�Y�~�߂�̉�ʂ̃e�N�X�`��
#define BOMB_TEXTURE ("data\\TEXTURE\\SkyBox.jpg")				// ���a�̉�ʂ̃e�N�X�`��
#define COOLTIME_TEXTURE ("data\\TEXTURE\\obanyanPhoto.jpg")	// �N�[���^�C�����̃e�N�X�`��

//==============================
// �R���X�g���N�^
//==============================
CTv::CTv() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_NONE;							// �A�C�e���������Ԃ�
	m_pVision = nullptr;							// �|���S������nullptr
	m_pRemocn = nullptr;							// �����R������nullptr
	m_VisionSize = D3DXVECTOR3(150.0f,80.0f,0.0f);	// �|���S���T�C�Y
	m_nCoolTime = 0;								// �N�[���^�C��
	SetRatUse(false);								// �l�Y�~���g�p�ł��邩
	SetCatUse(true);								// �l�R���g�p�ł��邩
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
	m_State = STATE_NONE;							// �A�C�e���������Ԃ�
	m_pVision = nullptr;							// �|���S������nullptr
	m_pRemocn = nullptr;							// �����R������nullptr
	m_VisionSize = D3DXVECTOR3(150.0f, 80.0f, 0.0f);// �|���S���T�C�Y
	m_nCoolTime = 0;								// �N�[���^�C��

	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	m_pRemocn = CBlock::Create(D3DXVECTOR3(100.0f, 0.0f, 200.0f), CBlock::ROTTYPE_FRONT, CBlock::TYPE_REMOCON);

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
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �e���r�̍X�V����
//=====================================
void CTv::Update(void)
{
	StateManager();
	VisionChange();
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�{�^�����������ꍇ
		m_nChangeVision;
	}

	if (m_pVision != nullptr)
	{ // �e���r��ʂ� NULL ����Ȃ��ꍇ

	  // �e���r��ʂ̍X�V����
		m_pVision->Update();
	}
	if (m_pRemocn != nullptr)
	{	// �����R���̃��f����null�ł͂Ȃ��Ƃ�
		if (HitRemocon() == true )
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
	}
}

//=====================================
// �e���r�̕`�揈��
//=====================================
void CTv::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	if (m_pVision != NULL)
	{
		m_pVision->Draw();
	}
}

//=====================================
// ��ԊǗ�
//=====================================
void CTv::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NONE:	// ���ł��Ȃ���ʂ̎�
		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(NONE_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
		}
	break;

	case STATE_TRAP:	// �l�Y�~�߂�̉�ʂ̎�
		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(TRAP_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(TRAP_TEXTURE));
			}
		}
		break;

	case STATE_BOMB:	// ���e�̉�ʂ̎�
		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
			}
		}
		break;

	case STATE_COOLDOWN:	// �N�[���^�C����

		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
			}
		}
		m_nCoolTime--;
		if (m_nCoolTime <= 0)
		{
			m_State = STATE_NONE;
		}
		break;
	default:

		// ��~
		assert(false);

		break;
	}
}

//=====================================
// �e���r�̓d���̏���
//=====================================
void CTv::Action(void)
{
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		pPlayer = CGame::GetPlayer(nCnt);
		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{
			switch(m_State)
			{
			case STATE_TRAP:
				pPlayer->GetItem(CItem::TYPE_MOUSETRAP);
				// �A�C�e���������̏�Ԃɂ���
				m_State = STATE_COOLDOWN;
				m_nCoolTime = COOL_TIME;
				break;
			case STATE_BOMB:
				// �A�C�e���������̏�Ԃɂ���
				m_State = STATE_COOLDOWN;
				m_nCoolTime = COOL_TIME;
				break;

	
			}
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
}

//=====================================
// �����蔻�菈��
//=====================================
bool CTv::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g�T�[�N������
//=====================================
bool CTv::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (m_bPower == true && m_State != STATE_COOLDOWN)
	{
		if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
		{//�~�͈͓̔��̏ꍇture��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
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
		m_bPower = false;
		break;

	case false:
		// �e���r�̓d�������Ă������_����
		if (m_pVision == nullptr)
		{	// �|���S�������݂��Ă��Ȃ��Ƃ���������

			D3DXVECTOR3 pPos = GetPos();
			m_pVision = CObject3D::Create(CObject3D::TYPE_NONE);
			m_pVision->SetPos(D3DXVECTOR3(pPos.x, pPos.y + 160.0f, pPos.z - 18.0f));
			m_pVision->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pVision->SetSize(m_VisionSize);
			if (m_State == STATE_NONE)
			{	// ���ł��Ȃ���ʂ̎�
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));

			}
			else if (m_State == STATE_TRAP)
			{	// �l�Y�~�߂�̉�ʂ̎�
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
			else if (m_State == STATE_BOMB)
			{	// ���e�̉�ʂ̎�
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
			else
			{	// �N�[���^�C����
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
			}
		}
		m_bPower = true;
		break;
	}
}

//=====================================
// �����R���̃q�b�g�T�[�N������
//=====================================
bool CTv::HitRemocon(void)
{
	CPlayer* pPlayer;
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		pPlayer = CGame::GetPlayer(nCnt);
		if (useful::CircleCollisionXZ(pPlayer->GetPos(), m_pRemocn->GetPos(), 200.0f, m_pRemocn->GetFileData().fRadius) == true)
		{//�~�͈͓̔��̏ꍇture��Ԃ�
			return true;
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
	{
		if (m_State != STATE_COOLDOWN)
		{
			m_nChangeVision++;
			if (m_nChangeVision %CHANGE_TIME == 0 && m_nChangeVision > 0)
			{
				switch (m_State)
				{
				case STATE_NONE:
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(TRAP_TEXTURE));
					m_State = STATE_TRAP;
					break;
				case STATE_TRAP:
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