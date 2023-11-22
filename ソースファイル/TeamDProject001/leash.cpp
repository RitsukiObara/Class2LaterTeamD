//===========================================
//
// ���[�h�̏���[Himo.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "leash.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"

//==============================
// �R���X�g���N�^
//==============================
CLeash::CLeash() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_bAction = false;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_bSetHead = false;
	m_bSetToes = false;
}

//==============================
// �f�X�g���N�^
//==============================
CLeash::~CLeash()
{

}

//==============================
// ���[�h�̏���������
//==============================
HRESULT CLeash::Init(void)
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
void CLeash::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// ���[�h�̍X�V����
//=====================================
void CLeash::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (m_bSetHead == true && m_bSetToes == true)
	{
		m_bAction = true;
	}

	SetActionPos(pos, rot);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // A�{�^�����������ꍇ
		m_bAction = m_bAction ? false : true;
	}

	SetPos(pos);
}

//=====================================
// ���[�h�̕`�揈��
//=====================================
void CLeash::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// �M�~�b�N�N���ʒu�̐ݒ�
//=====================================
void CLeash::SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
// �R����������ꂽ���̏���
//=====================================
void CLeash::Action(void)
{
	m_bAction = true;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CLeash::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CLeash::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CLeash::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	//// �I������
	//Uninit();

	// false ��Ԃ�
	return false;
}