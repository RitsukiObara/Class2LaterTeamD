#include "map.h"
#include "block.h"
//========================
//�}�N����`
//========================
#define WALLSIZE_LONG D3DXVECTOR3(1600,0,600)
#define WALLSIZE_SHORT D3DXVECTOR3(1000,0,600)

//========================
//�ÓI�����o�ϐ�
//========================
CWall* CMap::m_Wall[WALL_NUM] = {};

//�R���X�g���N�^
CMap::CMap() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BLOCK)
{

}
//�f�X�g���N�^
CMap::~CMap()
{

}

HRESULT CMap::Init(void)
{
	//================================
	//�n�ʂ̏�����
	//================================
	m_Ground = CGround::Create();

	//================================
	//�ǂ̏�����
	//================================
	m_Wall[0] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, 1000.0f), D3DXVECTOR3(-1.57f, 0.0f, 0.0f), WALLSIZE_LONG);
	m_Wall[1] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, -1000.0f), D3DXVECTOR3(1.57f, 0.0f, 0.0f), WALLSIZE_LONG);
	m_Wall[2] = CWall::Create(D3DXVECTOR3(1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, 1.57f), WALLSIZE_SHORT);
	m_Wall[3] = CWall::Create(D3DXVECTOR3(-1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, -1.57f), WALLSIZE_SHORT);

	return S_OK;
}
void CMap::Uninit(void)
{
	//================================
	//�n�ʂ̏I��
	//================================
	if (m_Ground != NULL)
	{
		m_Ground->Uninit();
		m_Ground = NULL;
	}

	//================================
	//�ǂ̏I��
	//================================
	for (int nCnt = 0; nCnt < WALL_NUM; nCnt++)
	{
		if (m_Wall[nCnt] != nullptr)
		{
			m_Wall[nCnt]->Uninit();
			m_Wall[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}
void CMap::Update(void)
{
	m_Ground->Update();
}
void CMap::Draw(void)
{
	m_Ground->Draw();
	m_Wall[0]->Draw();
}
CMap* CMap::Create(void)
{
	CMap *pMap;

	pMap = new CMap;

	pMap->SetType(TYPE_MAP);

	pMap->Init();

	return pMap;
}
CWall*CMap:: GetWall(void)
{
	return m_Wall[0];
}