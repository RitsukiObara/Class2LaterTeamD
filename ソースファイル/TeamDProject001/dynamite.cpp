//===========================================
//
// ���e�̃��C������[dynamite.cpp]
// Author �x�씋��
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "dynamite.h"
#include "obstacle.h"
#include "useful.h"
#include "Effect.h"
#include "game.h"
#include "manager.h"
#include "input.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define SCALE_SPEED	(D3DXVECTOR3(0.1f,0.1f,0.1f))	// �T�C�Y�̕ύX���x
#define EXPLOSION_COUNT		(300)		// �����܂ł̃J�E���g
#define DELEAT_COUNT		(10)		// �����̔��莞��
#define EXPLOSION_RADIUS	(200.0f)	// �����͈̔�

//==============================
// �R���X�g���N�^
//==============================
CDynamite::CDynamite() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_state =STATE_NONE;							// ���
	m_Scale =D3DXVECTOR3(1.0f,1.0f,1.0f);			// �g�嗦
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			// �ʒu
	m_bCatch = true;								// �����Ă��邩�ǂ���
	m_nExplosion = 0;								// �����^�C�~���O

	// �g�p����
	SetCatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CDynamite::~CDynamite()
{

}

//==============================
// ���e�̏���������
//==============================
HRESULT CDynamite::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	m_state = STATE_NONE;							// ���
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// �g�嗦
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_bCatch = true;								// �����Ă��邩�ǂ���
	m_nExplosion = 0;								// �����^�C�~���O

	// �l��Ԃ�
	return S_OK;
}

//========================================
// ���e�̏I������
//========================================
void CDynamite::Uninit(void)
{

	// �I������
	CObstacle::Uninit();
}

//=====================================
// ���e�̍X�V����
//=====================================
void CDynamite::Update(void)
{
	
	// �L�̎肩����������
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		CPlayer* pPlayer;
		pPlayer = CGame::GetPlayer(nCnt);
		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{
			if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, nCnt) == true)
			{ // �A�C�e���������Ă����Ԃ�Y�{�^���������ꂽ�ꍇ
				m_bCatch = false;
			}
		}
	}

	if (m_bCatch == true)
	{ // �l�R�������Ă���ꍇ

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			// �l�R�̈ʒu�ɐݒ肷��
			CPlayer* pPlayer;
			pPlayer = CGame::GetPlayer(nCnt);
			if (pPlayer->GetType() == CPlayer::TYPE_CAT)
			{
				m_pos = pPlayer->GetPos();
				m_pos.y = 120.0f;
			}

		}
	}
	else
	{ // �n�ʂɒu����Ă���ꍇ
		m_pos.y = 0.0f;

	}

	
	if (m_nExplosion > EXPLOSION_COUNT-120 && m_state != STATE_EXPLOSION)
	{ // �c��2�b�ɂȂ����ꍇ

		if (m_state == STATE_NONE)
		{
			m_state = STATE_MINI;
		}
		ChageScale();	// ���f���T�C�Y�ύX����

	}

	if (m_state == STATE_EXPLOSION)
	{// ������
		m_nDelTyming++;
		if (m_nDelTyming > DELEAT_COUNT)
		{
			// ���e�̍폜
			Uninit();
		}
	}

	Explosion();	// ��������

	// �ʒu��ݒ肷��
	SetPos(m_pos);

}

//=====================================
// ���e�̕`�揈��
//=====================================
void CDynamite::Draw(void)
{
	if (m_state != STATE_EXPLOSION)
	{// �����̃^�C�~���O�ŕ`�������
		// �`�揈��
		CObstacle::Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CDynamite::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, rot, type);

}

//=====================================
// �q�b�g����
//=====================================
bool CDynamite::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_state == STATE_EXPLOSION)
	{
		D3DXVECTOR3 objPos = GetPos();
		if (useful::CylinderInner(pPlayer->GetPos(), objPos, collSize.x + EXPLOSION_RADIUS))
		{ // �~�̒��ɓ������ꍇ

		  // true ��Ԃ�
			return true;
		}

	}
	// false ��Ԃ�
	return false;
}

//=====================================
// ���f���T�C�Y�ύX����
//=====================================
void CDynamite::ChageScale(void)
{
	// �g��T�C�Y���擾
	m_Scale = CObstacle::GetScale();

	switch (m_state)
	{
	case CDynamite::STATE_NONE:	// �ʏ���
		break;
	
	case CDynamite::STATE_MINI:	// �k�����
		m_Scale += SCALE_SPEED;

		if (m_Scale.x > 1.8f)
		{
			m_state = STATE_BIG;
		}
		break;

	case CDynamite::STATE_BIG:	// �g����
		m_Scale -= SCALE_SPEED;	

		if (m_Scale.x <= 1.0f)
		{
			m_state = STATE_MINI;
		}
		break;
	case CDynamite::STATE_EXPLOSION:	// �������

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �g��T�C�Y��ݒ�
	CObstacle::SetScale(m_Scale);
}

//=====================================
// ��������
//=====================================
void CDynamite::Explosion(void)
{
	m_nExplosion++;
	if (m_nExplosion >= EXPLOSION_COUNT)
	{// �����̎���������

		if (m_state != STATE_EXPLOSION)
		{
			//������Ԃɂ���
			m_state = STATE_EXPLOSION;
			// �����G�t�F�N�g���o��
			CEffect::Create(m_pos, D3DXVECTOR3(5.0f, 5.0f, 5.0f), 10, 550.0f, CEffect::TYPE_RUPTURE, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), false);
		}
	}
}