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

#define ACTION_TIME (120)
#define WAIT_TIME (20)

//==============================
// �R���X�g���N�^
//==============================
CPin::CPin() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_State = STATE_FALSE;
	m_bSetHead = false;
	m_bSetToes = false;
	m_StateCount = 0;
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

	//�M�~�b�N�N�����̏���
	if ((m_bSetHead == true && m_bSetToes == true) && m_State == STATE_FALSE)
	{//�N�����Ă��Ȃ����Ƀl�Y�~�����[����������
		Action();
	}

	StateManager(&pos);

	//�d��
	m_move.y -= 1.0f;

	//�ʒu�X�V
	pos.y += m_move.y;

	//�n�ʔ���
	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
	}

	SetActionPos(pos, rot);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // A�{�^�����������ꍇ
		m_bSetHead = true;
		m_bSetToes = true;
	}

	SetPos(pos);
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
// ���[�N�����̏���
//=====================================
void CPin::Action(void)
{
	m_State = STATE_JUMPWAIT;
	m_StateCount = WAIT_TIME;
	m_move.y = 30.0f;
}

//=====================================
// �M�~�b�N�N���ʒu�̐ݒ�
//=====================================
void CPin::SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ActionPosHead = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 1.0f)) * 300.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 1.0f)) * 300.0f);

	ActionPosToes = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.0f)) * 350.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.0f)) * 350.0f);

	CEffect::Create(ActionPosHead, NONE_D3DXVECTOR3, 20, 30.0f, CEffect::TYPE::TYPE_NONE, NONE_D3DXCOLOR, true);
	CEffect::Create(ActionPosToes, NONE_D3DXVECTOR3, 20, 30.0f, CEffect::TYPE::TYPE_NONE, NONE_D3DXCOLOR, true);
}

//=====================================
// ��ԊǗ�
//=====================================
void CPin::StateManager(D3DXVECTOR3 *pos)
{
	switch (m_State)
	{
	case CPin::STATE_FALSE:

		break;

	case CPin::STATE_JUMPWAIT:	//�M�~�b�N�N��������ʔ����܂ł̏�������
		m_StateCount--;
		if (m_StateCount <= 0)
		{
			m_State = STATE_TRUE;
			m_StateCount = ACTION_TIME;
			SetFileData(CXFile::TYPE_LEASHSET);
		}
		break;

	case CPin::STATE_TRUE:	//�M�~�b�N�̌��ʔ��������~�܂ł̏���
		m_StateCount--;

		if (pos->y < 200.0f)
		{
			pos->y = 200.0f;
			m_move.y = 0.0f;
		}

		if (m_StateCount <= 0)
		{
			m_State = STATE_FALSE;
			m_bSetHead = false;
			m_bSetToes = false;
			SetFileData(CXFile::TYPE_LEASH);
		}
		break;
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