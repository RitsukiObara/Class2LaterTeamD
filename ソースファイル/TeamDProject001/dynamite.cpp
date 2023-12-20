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
#include "object3Dfan.h"


//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define SCALE_SPEED	(D3DXVECTOR3(0.1f,0.1f,0.1f))	// �T�C�Y�̕ύX���x
#define COLOR_SPEED	(D3DXCOLOR(0.0f,0.1f,0.1f,0.0f))	// �T�C�Y�̕ύX���x
#define EXPLOSION_COUNT		(300)		// �����܂ł̃J�E���g
#define DELEAT_COUNT		(10)		// �����̔��莞��
#define EXPLOSION_RADIUS	(1000.0f)	// �����͈̔�
#define EXPLOSION_TIME		(300)		// �����܂ł̃J�E���g
#define START_RADIUS		(15.0f)		// �����̔����~�͈̔�

//==============================
// �R���X�g���N�^
//==============================
CDynamite::CDynamite() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_state =STATE_NONE;							// ���
	m_nExplosion = 0;								// �����^�C�~���O
	m_pFan = nullptr;
	m_SizeChangeSpeed = SCALE_SPEED;
	m_ColChangeSpeed = COLOR_SPEED;
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
	m_pFan = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fRadius = START_RADIUS;
	// �l��Ԃ�
	return S_OK;
}

//========================================
// ���e�̏I������
//========================================
void CDynamite::Uninit(void)
{
	if (m_pFan != nullptr)
	{
		m_pFan->Uninit();
		m_pFan = nullptr;
	}
	// �I������
	CObstacle::Uninit();
}

//=====================================
// ���e�̍X�V����
//=====================================
void CDynamite::Update(void)
{
	if (m_nExplosion > EXPLOSION_COUNT- EXPLOSION_TIME && m_state != STATE_EXPLOSION)
	{ // �c��2�b�ɂȂ����ꍇ
		if (m_pFan == nullptr)
		{// �����~�̐���
			m_pFan = CExplosionFan::Create(GetPos(), m_col);
		}
		if (m_state == STATE_NONE)
		{
			m_state = STATE_MINI;
		}

		// ���f���T�C�Y�ύX����
		ChageScale();	


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

		scale += m_SizeChangeSpeed;



		if (m_pFan != nullptr)
		{
			// �ԐF�ɕς��Ă���
			m_col -= m_ColChangeSpeed;

			m_fRadius += (EXPLOSION_RADIUS - START_RADIUS) / EXPLOSION_TIME;
			m_pFan->SetColor(m_col);
			m_pFan->SetRadius(m_fRadius);
		}

		if (scale.x > 2.5f)
		{
			m_state = STATE_BIG;
			m_SizeChangeSpeed += D3DXVECTOR3(0.01f,0.01f,0.01f);
			m_ColChangeSpeed += COLOR_SPEED / 0.1f;
		}




		break;

	case CDynamite::STATE_BIG:	// �g����

		scale -= m_SizeChangeSpeed;

		if (m_pFan != nullptr)
		{
			// ���F�ɕς��Ă���
			m_col += m_ColChangeSpeed;

			m_fRadius += (EXPLOSION_RADIUS - START_RADIUS) / EXPLOSION_TIME;
			m_pFan->SetColor(m_col);
			m_pFan->SetRadius(m_fRadius);
		}


		if (scale.x <= 1.0f)
		{
			m_state = STATE_MINI;
			m_SizeChangeSpeed += D3DXVECTOR3(0.01f, 0.01f, 0.01f);
			m_ColChangeSpeed += COLOR_SPEED / 0.1f;


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
			CEffect::Create(GetPos(), D3DXVECTOR3(5.0f, 5.0f, 5.0f), 10, 1000.0f, CEffect::TYPE_RUPTURE, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), false);
		}
	}
}


//======================================================�����~�̃N���X========================================================================

//==============================
// �R���X�g���N�^
//==============================
CExplosionFan::CExplosionFan() : CObject3DFan(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{

}

//==============================
// �f�X�g���N�^
//==============================
CExplosionFan::~CExplosionFan()
{

}

//==============================
// �����̉~�̏���������
//==============================
HRESULT CExplosionFan::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}
							// �l��Ԃ�
	return S_OK;
}

//========================================
// �����̉~�̏I������
//========================================
void CExplosionFan::Uninit(void)
{
	// �I������
	CObject3DFan::Uninit();
}

//=====================================
// �����̉~�̍X�V����
//=====================================
void CExplosionFan::Update(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(GetColor());		

}

//=====================================
// �����̉~�̕`�揈��
//=====================================
void CExplosionFan::Draw(void)
{
	// �`�揈��
	CObject3DFan::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CExplosionFan::SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	//NONE_SCALE						// �g�嗦��ύX���Ȃ��Ƃ��Ƃ��Ɏg��
	// ���̐ݒ菈��

	//==========================================================================
	// 3D�|���S��
	//==========================================================================
	SetPos(pos);					// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetSize(NONE_SCALE);			// �T�C�Y
	SetNumAngle(120);				// �p�x�̑���
	SetRadius(START_RADIUS);		// ���a
	SetColor(col);					// �F
}

//=======================================
// ��������
//=======================================
CExplosionFan* CExplosionFan::Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CExplosionFan* pExplosionFan = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pExplosionFan == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pExplosionFan = new CExplosionFan;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pExplosionFan != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ���̐ݒ菈��
		pExplosionFan->SetData(pos, col);

		// ����������
		if (FAILED(pExplosionFan->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pExplosionFan;
}