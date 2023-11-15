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
			Scale.y -= 0.040f;

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

		SetScale(D3DXVECTOR3(0.5f, 12.0f, 0.5f));
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHoney::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// ���f���̏���ݒ肷��
	SetFileData(CXFile::TYPE_HONEYBOTTLE);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CHoney::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CHoney::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	if (m_State == STATE_HONEY)
	{
		// ���[�J���ϐ��錾
		D3DXVECTOR3 max = D3DXVECTOR3(fWidth, fHeight, fDepth);		// �T�C�Y�̍ő�l
		D3DXVECTOR3 min = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);		// �T�C�Y�̍ŏ��l

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true)
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
	{
		return false;
	}
}