//===========================================
//
// �I���̃��C������[honey.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "collision.h"
#include "input.h"
#include "fraction.h"
#include "renderer.h"
#include "honey.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define HONEY_SCALE			(D3DXVECTOR3(0.5f, 1.0f, 0.5f))		// �I����Ԃ̊g�嗦
#define HONEY_FRAC_COUNT	(15)								// �I���̔j�Ђ̐�
#define HONEY_ADD_SCALE		(0.005f)							// �I���̊g�嗦�̉��Z��

//==============================
// �R���X�g���N�^
//==============================
CHoney::CHoney() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_HONEYBOTTLE;
	SetCatUse(true);
	SetRatUse(false);
}

//==============================
// �f�X�g���N�^
//==============================
CHoney::~CHoney()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CHoney::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CHoney::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CHoney::Update(void)
{
	//��ԊǗ�
	StateManager();
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CHoney::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ��ԊǗ�
//=====================================
void CHoney::StateManager(void)
{
	switch (m_State)
	{
	case CHoney::STATE_HONEYBOTTLE:

		break;

	case CHoney::STATE_HONEY:

		D3DXVECTOR3 Scale = GetScale();

		if (Scale.x <= 1.0f)
		{
			Scale.x += HONEY_ADD_SCALE;
			Scale.z += HONEY_ADD_SCALE;

			SetScale(Scale);
		}

		break;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHoney::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CHoney::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ���W�֌W�̕ϐ���ݒ肷��
	D3DXVECTOR3 pos = pPlayer->GetPos();			// �ʒu
	D3DXVECTOR3 posOld = pPlayer->GetPosOld();		// �O��̈ʒu
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// �ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// �ŏ��l

	if (m_State == STATE_HONEYBOTTLE)
	{ // �I���{�g����Ԃ̏ꍇ

		if (collision::HexahedronCollision(&pos, GetPos(), posOld, GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax) == true)
		{ // �Z�ʑ̂̓����蔻�肪 true �̏ꍇ

			// �ʒu��K�p����
			pPlayer->SetPos(pos);

			// true ��Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}

//=====================================
// �q�b�g����
//=====================================
bool CHoney::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// �T�C�Y�̍ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// �T�C�Y�̍ŏ��l

	if (m_State == STATE_HONEY &&
		useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
	{ // �l�p�̓����蔻��̒��ɓ����Ă����ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}

//=====================================
// �q�b�g����
//=====================================
bool CHoney::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (pPlayer->GetType() == CPlayer::TYPE_CAT &&
		GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // �~�͈͓̔��ɂ���ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CHoney::Action(void)
{
	if (m_State == STATE_HONEYBOTTLE)
	{ // �I���{�g����Ԃ̏ꍇ

		// �I����Ԃɂ���
		m_State = STATE_HONEY;

		// ���f���̏���ݒ肷��
		SetFileData(CXFile::TYPE_HONEY);

		for (int nCnt = 0; nCnt < HONEY_FRAC_COUNT; nCnt++)
		{
			// �j�Ђ̐�������
			CFraction::Create(GetPos(), CFraction::TYPE::TYPE_PRASTICRVASE);
		}

		// �g�嗦��ݒ肷��
		SetScale(HONEY_SCALE);

		// �A�N�V�����󋵂� false �ɂ���
		SetAction(false);
	}
}