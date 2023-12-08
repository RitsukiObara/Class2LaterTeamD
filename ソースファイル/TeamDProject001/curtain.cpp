//===========================================
//
// �J�[�e���̏���[curtain.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "curtain.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CCurtain::CCurtain() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	SetCatUse(false);				// �l�R�̎g�p����
	SetRatUse(true);				// �l�Y�~�̎g�p����
}

//==============================
// �f�X�g���N�^
//==============================
CCurtain::~CCurtain()
{

}

//==============================
// �J�[�e���̏���������
//==============================
HRESULT CCurtain::Init(void)
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
// �J�[�e���̏I������
//========================================
void CCurtain::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �J�[�e���̍X�V����
//=====================================
void CCurtain::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());
}

//=====================================
// �J�[�e���̕`�揈��
//=====================================
void CCurtain::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCurtain::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);
}