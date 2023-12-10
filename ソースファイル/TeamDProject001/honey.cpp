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

//==============================
// �R���X�g���N�^
//==============================
CHoney::CHoney() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	m_State = STATE_HONEYBOTTLE;
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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RETURN) == true)
	{ // ENTER�L�[�������Ă����ꍇ
		//�j�󎞏���
		Break();
	}
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
			Scale.x += 0.005f;
			Scale.z += 0.005f;

			SetScale(Scale);
		}

		break;
	}
}

//=====================================
// �j�󎞏���
//=====================================
void CHoney::Break(void)
{
	if (m_State == STATE_HONEYBOTTLE)
	{
		m_State = STATE_HONEY;

		CFraction::Create(GetPos(), CFraction::TYPE_FLOWERVASE);

		// ���f���̏���ݒ肷��
		SetFileData(CXFile::TYPE_HONEY);

		SetScale(D3DXVECTOR3(0.5f, 1.0f, 0.5f));
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
bool CHoney::Collision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (m_State == STATE_HONEYBOTTLE)
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
bool CHoney::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// �T�C�Y�̍ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// �T�C�Y�̍ŏ��l

	if (m_State == STATE_HONEYBOTTLE)
	{ // �I���{�g����Ԃ̏ꍇ

		if (type == CPlayer::TYPE_CAT)
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
	else if (m_State == STATE_HONEY)
	{ // �I����Ԃ̏ꍇ

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
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
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// false ��Ԃ�
		return false;
	}
}