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
#include "renderer.h"
#include "honey.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CHoney::CHoney() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{

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
// ���̐ݒ菈��
//=====================================
void CHoney::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// ���f���̏���ݒ肷��
	SetFileData(CXFile::TYPE_HONEY);
}

//=====================================
// �q�b�g����
//=====================================
bool CHoney::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
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