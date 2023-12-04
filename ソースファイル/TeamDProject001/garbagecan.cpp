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
	m_State = STATE_GARBAGECAN;
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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RETURN) == true)
	{ // ENTER�L�[�������Ă����ꍇ
		//�j�󎞏���
		Break();
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
	case CGarbage::STATE_GARBAGECAN:



		break;
	case CGarbage::STATE_GARBAGE:

		break;
	}
}

//=====================================
// �j�󎞏���
//=====================================
void CGarbage::Break(void)
{
	if (m_State == STATE_GARBAGECAN)
	{
		m_State = STATE_GARBAGE;

		CFraction::Create(GetPos(), CFraction::TYPE_FLOWERVASE);

		// ���f���̏���ݒ肷��
		SetFileData(CXFile::TYPE_GARBAGE);

		SetScale(D3DXVECTOR3(2, 1.0f, 2));
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
bool CGarbage::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);

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
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}
//=====================================
// �q�b�g����
//=====================================
bool CGarbage::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);		// �T�C�Y�̍ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);		// �T�C�Y�̍ŏ��l

	if (m_State == STATE_GARBAGECAN)
	{ // �I���{�g����Ԃ̏ꍇ

		if (type == CPlayer::TYPE_RAT)
		{ // �l�R�̏ꍇ

			if (useful::RectangleCollisionXY(pos, GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
				useful::RectangleCollisionYZ(pos, GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true)
			{ // ��`�̓����蔻��ɒʂ����ꍇ

				// �j�󎞏���
				Break();

				// true ��Ԃ�
				return false;
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
	else if (m_State == STATE_GARBAGE)
	{ // �I����Ԃ̏ꍇ

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
		{ // �l�p�̓����蔻��̒��ɓ����Ă����ꍇ
			if (type == CPlayer::TYPE_CAT)
			{
				// true ��Ԃ�
				return true;
			}
			else
			{
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
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// false ��Ԃ�
		return false;
	}
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CGarbage::Action(void)
{

}