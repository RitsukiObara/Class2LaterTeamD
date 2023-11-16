//===========================================
//
// �v���X�`�b�N�P�[�X�̃��C������[plastic_case.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "plastic_case.h"
#include "useful.h"
#include "fraction.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY		(0.5f)		// �d��
#define NUM_FRAC	(4)			// �j�Ђ̐�

//==============================
// �R���X�g���N�^
//==============================
CPlasticCase::CPlasticCase() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CPlasticCase::~CPlasticCase()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CPlasticCase::Init(void)
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
void CPlasticCase::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CPlasticCase::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CPlasticCase::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPlasticCase::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CPlasticCase::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CPlasticCase::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
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