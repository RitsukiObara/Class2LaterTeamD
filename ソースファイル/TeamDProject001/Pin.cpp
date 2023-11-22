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
	if (m_bAction == true)
	{//�N�����Ă��Ȃ����Ƀl�Y�~�����[����������

	}

	//�d��
	m_move.y -= 1.0f;

	//�ʒu�X�V
	pos.y += m_move.y;

	//�n�ʔ���
	if (pos.y < 0.0f)
	{

	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // A�{�^�����������ꍇ

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
	m_bAction = true;
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