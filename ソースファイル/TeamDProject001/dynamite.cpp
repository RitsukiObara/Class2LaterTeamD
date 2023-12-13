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
#include "manager.h"
#include "dynamite.h"
#include "obstacle.h"
#include "useful.h"
#include "Effect.h"
#include "collision.h"

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

		// �����̔��莞�Ԃ����Z����
		m_nDelTyming++;

		if (m_nDelTyming > DELEAT_COUNT)
		{ // ���J�E���g�ɂȂ����ꍇ

			// ���e�̍폜
			Uninit();
		}
	}

	// ��������
	Explosion();
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
// �����蔻�菈��
//=====================================
bool CDynamite::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu�ƍŏ��l�ƍő�l��ݒ肷��
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	// �Z�ʑ̂̓����蔻��
	if (collision::HexahedronCollision
	(
		&pos,					// �v���C���[�̈ʒu
		GetPos(),				// �ʒu
		pPlayer->GetPosOld(),	// �v���C���[�̑O��̈ʒu
		GetPosOld(),			// �O��̈ʒu
		vtxMin,					// �v���C���[�̍ŏ��l
		GetFileData().vtxMin,	// �ŏ��l
		vtxMax,					// �v���C���[�̍ő�l
		GetFileData().vtxMax	// �ő�l
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
// �q�b�g����
//=====================================
bool CDynamite::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_state == STATE_EXPLOSION)
	{ // ������Ԃ̏ꍇ

		if (useful::CylinderInner(pPlayer->GetPos(), GetPos(), collSize.x + EXPLOSION_RADIUS))
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
	D3DXVECTOR3 scale = CObstacle::GetScale();

	switch (m_state)
	{
	case CDynamite::STATE_NONE:	// �ʏ���
		break;
	
	case CDynamite::STATE_MINI:	// �k�����

		scale += SCALE_SPEED;

		if (scale.x > 1.8f)
		{
			m_state = STATE_BIG;
		}
		break;

	case CDynamite::STATE_BIG:	// �g����

		scale -= SCALE_SPEED;

		if (scale.x <= 1.0f)
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
	SetScale(scale);
}

//=====================================
// ��������
//=====================================
void CDynamite::Explosion(void)
{
	// �����܂ł̃J�E���g�����Z����
	m_nExplosion++;

	if (m_nExplosion >= EXPLOSION_COUNT)
	{// �����̎���������

		if (m_state != STATE_EXPLOSION)
		{ // ������ԈȊO�̏ꍇ

			//������Ԃɂ���
			m_state = STATE_EXPLOSION;

			// �����G�t�F�N�g���o��
			CEffect::Create(GetPos(), D3DXVECTOR3(5.0f, 5.0f, 5.0f), 10, 550.0f, CEffect::TYPE_RUPTURE, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), false);
		}
	}
}