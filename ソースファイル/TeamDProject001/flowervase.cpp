//===========================================
//
// �ԕr�̃��C������[flowervase.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "flowervase.h"
#include "useful.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "fraction.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY		(0.5f)		// �d��

//==============================
// �R���X�g���N�^
//==============================
CFlowerVase::CFlowerVase() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CFlowerVase::~CFlowerVase()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CFlowerVase::Init(void)
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
void CFlowerVase::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CFlowerVase::Update(void)
{
	// �N���n�ʂƂ̓����蔻��
	Elevation();
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CFlowerVase::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CFlowerVase::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CFlowerVase::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CFlowerVase::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	//// �j�Ђ̏o�鍂��
	//float fFracHeight;

	//for (int nCnt = 0; nCnt < 20; nCnt++)
	//{
	//	fFracHeight = (float)(rand() % (int)(GetFileData().vtxMax.y) - (int)(GetFileData().vtxMin.y));

	//	// �j�Ђ𐶐�
	//	CFraction::Create(D3DXVECTOR3(GetPos().x, GetPos().y + fFracHeight, GetPos().z), CFraction::TYPE::TYPE_FLOWERVASE);
	//}

	//// �I������
	//Uninit();

	// false ��Ԃ�
	return false;
}

//=====================================
// �N���n�ʂ̓����蔻��
//=====================================
void CFlowerVase::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);		// �ʒu���擾����
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight - GetFileData().vtxMin.y;
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}