//===========================================
//
// �����o�̃��C������[roomba.cpp]
// Author ��������
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

//==============================
// �R���X�g���N�^
//==============================
CRoomba::CRoomba() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CRoomba::~CRoomba()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CRoomba::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CRoomba::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CRoomba::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
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

	//// ���f���̏���ݒ肷��
	//SetFileData(CXFile::TYPE_PLASTICCASE);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CRoomba::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CRoomba::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	//// �j�Ђ̏o�鍂��
	//float fFracHeight;

	//for (int nCnt = 0; nCnt < NUM_FRAC; nCnt++)
	//{
	//	fFracHeight = (float)(rand() % (int)(GetFileData().vtxMax.y) - (int)(GetFileData().vtxMin.y));

	//	// �j�Ђ𐶐�
	//	CFraction::Create(D3DXVECTOR3(GetPos().x, GetPos().y + fFracHeight, GetPos().z), CFraction::TYPE::TYPE_PRASTICRVASE);
	//}

	//// �I������
	//Uninit();

	// false ��Ԃ�
	return false;
}