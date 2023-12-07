//===========================================
//
// �I���̃��C������[garbage.cpp]
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
#include "garbagecan.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CGarbage::CGarbage() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_GARBAGECAN;		// ���

	// �l�Y�~������������悤�ɂ���
	SetCatUse(false);
	SetRatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CGarbage::~CGarbage()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CGarbage::Init(void)
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
void CGarbage::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CGarbage::Update(void)
{
	//��ԊǗ�
	StateManager();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_0) == true)
	{ // ENTER�L�[�������Ă����ꍇ

	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CGarbage::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ��ԊǗ�
//=====================================
void CGarbage::StateManager(void)
{
	switch (m_State)
	{
	case CGarbage::STATE_GARBAGECAN:	// �S�~��



		break;
	case CGarbage::STATE_BANANA:		// �o�i�i�̔�

		break;
	}
}

//=====================================
// �j�󎞏���
//=====================================
void CGarbage::Break(void)
{
	if (m_State == STATE_GARBAGECAN)
	{ // �S�~����Ԃ̏ꍇ

		m_State = STATE_BANANA;

		// ���f���̏���ݒ肷��
		SetFileData(CXFile::TYPE_GARBAGE);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CGarbage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CGarbage::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (m_State == STATE_GARBAGECAN)
	{ // �I���{�g����Ԃ̏ꍇ

		if (collision::HexahedronCollision(pos, GetPos(), posOld, GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax) == true)
		{ // �Z�ʑ̂̓����蔻�肪 true �̏ꍇ

			// true ��Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CGarbage::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// �T�C�Y�̍ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// �T�C�Y�̍ŏ��l

	if (m_State == STATE_BANANA &&
		type == CPlayer::TYPE_CAT &&
		useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
	{ // �l�R���o�i�i�̔�Ɉ������������ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g�̉~����
//=====================================
bool CGarbage::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{ // �͈͓��ɓ����Ă���ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CGarbage::Action(void)
{
	//�j�󎞏���
	Break();
}