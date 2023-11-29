//===========================================
//
// �����o�̃��C������[roomba.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "roomba.h"
#include "useful.h"
#include "objectX.h"

#include "player.h"

//==============================
// �R���X�g���N�^
//==============================
CRoomba::CRoomba() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt] = NULL;
	}

	m_move = NONE_D3DXVECTOR3;
}

//==============================
// �f�X�g���N�^
//==============================
CRoomba::~CRoomba()
{

}

//==============================
// �����o�̏���������
//==============================
HRESULT CRoomba::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_apSub[0] = CModel::Create();
	m_apSub[1] = CModel::Create();
	m_apSub[0]->SetFileData((CXFile::TYPE::TYPE_ROOMBA_SUB));	// ���f�����
	m_apSub[1]->SetFileData((CXFile::TYPE::TYPE_ROOMBA_SUB));	// ���f�����
	
	// �l��Ԃ�
	return S_OK;
}

//========================================
// �����o�̏I������
//========================================
void CRoomba::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �����o�̍X�V����
//=====================================
void CRoomba::Update(void)
{
	//�ʒu�������̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//�{�̂̌����𓮂���
	rot.y -= 0.005f;

	//�����Ă�������Ɉړ����鏈��
	Move(rot);

	//�v���y���̈ʒu�ƌ����̍X�V
	SubUpdate();

	//�ʒu�X�V
	pos += m_move;

	//�ʒu�ƌ����̍X�V
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// �ړ�����
//=====================================
void CRoomba::Move(D3DXVECTOR3 rot)
{
	m_move = D3DXVECTOR3(
		sinf(rot.y + (D3DX_PI * 1.0f)) * 2.0f,
		0.0f,
		cosf(rot.y + (D3DX_PI * 1.0f)) * 2.0f);
}

//=====================================
// �v���y���̍X�V����
//=====================================
void CRoomba::SubUpdate(void)
{
	//�ʒu�ƌ����̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//�v���y���̌������擾
	D3DXVECTOR3 Subrot[2] = {};
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		Subrot[nCnt] = m_apSub[nCnt]->GetRot();
	}

	//�v���y������
	Subrot[0].y += 0.1f;
	Subrot[1].y -= 0.1f;

	//�v���y���̈ʒu�X�V
	m_apSub[0]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.75f)) * 50.0f));

	m_apSub[1]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * -0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * -0.75f)) * 50.0f));

	//�v���y���̌������X�V����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt]->SetRot(Subrot[nCnt]);
	}
}

//=====================================
// �����o�̕`�揈��
//=====================================
void CRoomba::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRoomba::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CRoomba::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CRoomba::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 objpos = GetPos();

	D3DXVECTOR3 posDif = pos - objpos;

	float fLength = D3DXVec3Length(&posDif);
	float fSize = GetFileData().vtxMax.z;

	if (fLength <= fSize)
	{
		//�I�u�W�F�N�g����̊p�x
		float fRot = atan2f(pos.x - objpos.x, pos.z - objpos.z);

		D3DXVECTOR3 SetPos = D3DXVECTOR3(objpos.x + sinf(-D3DX_PI - fRot)*fSize, pos.y, objpos.z + cosf(-D3DX_PI - fRot)*fSize);


		return true;
	}
	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CRoomba::Action(void)
{

}