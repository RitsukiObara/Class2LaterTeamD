//===========================================
//
// ��e�̏���[Pin.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Pin.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"
#include "fraction.h"

#define ACTION_TIME (120)
#define WAIT_TIME (20)

//==============================
// �R���X�g���N�^
//==============================
CPin::CPin() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_FALSE;
	m_move = NONE_D3DXVECTOR3;
}

//==============================
// �f�X�g���N�^
//==============================
CPin::~CPin()
{

}

//==============================
// ���[�h�̏���������
//==============================
HRESULT CPin::Init(void)
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
// ���[�h�̏I������
//========================================
void CPin::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// ���[�h�̍X�V����
//=====================================
void CPin::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	StateManager(&pos,&rot);

	//�ʒu�X�V
	pos += m_move;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�{�^�����������ꍇ
		Action();
	}

	SetPos(pos);
	SetRot(rot);
}

//=====================================
// ���[�h�̕`�揈��
//=====================================
void CPin::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ��ԊǗ�
//=====================================
void CPin::StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	switch (m_State)
	{
	case CPin::STATE_FALSE:

		break;

	case CPin::STATE_FALLWAIT:	//�M�~�b�N�N��������ʔ����܂ł̏�������
		rot->z += 0.1f;
		m_move.y -= 0.75f;
		m_move.x = sinf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;

		if (pos->y < 0)
		{
			pos->y = 0.0f;
			rot->z = 0.0f;
			m_State = STATE_TRUE;
			SetFileData(CXFile::TYPE_PINSET);
			CFraction::Create(GetPos(), CFraction::TYPE_FLOWERVASE);
		}
		break;

	case CPin::STATE_TRUE:	//�M�~�b�N�̌��ʔ��������~�܂ł̏���
		m_move = NONE_D3DXVECTOR3;
		pos->y = 0.0f;
		break;
	}
}

//=====================================
// ���[�N�����̏���
//=====================================
void CPin::Action(void)
{
	if (m_State == STATE_FALSE)
	{
		m_State = STATE_FALLWAIT;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPin::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CPin::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CPin::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	//// �I������
	//Uninit();

	// false ��Ԃ�
	return false;
}