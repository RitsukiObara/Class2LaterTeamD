#include "map.h"
//========================
//�}�N����`
//========================
#define WALLSIZE_LONG D3DXVECTOR3(800,0,600)
#define WALLSIZE_SHORT D3DXVECTOR3(600,0,600)

CMap::CMap() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BLOCK)
{

}
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
	m_Wall[0] = CWall::Create(D3DXVECTOR3(0, 300, 600), D3DXVECTOR3(-1.57f, 0, 0), WALLSIZE_LONG);
	m_Wall[1] = CWall::Create(D3DXVECTOR3(0, 300, -600), D3DXVECTOR3(1.57f, 0, 0), WALLSIZE_LONG);
	m_Wall[2] = CWall::Create(D3DXVECTOR3(800, 300, 0), D3DXVECTOR3(1.57f, 0, 1.57f), WALLSIZE_SHORT);
	m_Wall[3] = CWall::Create(D3DXVECTOR3(-800, 300, 0), D3DXVECTOR3(1.57f, 0, -1.57f), WALLSIZE_SHORT);
	//================================
	//���f���̏�����
	//================================
	//�L�b�`���̐����Ə�����
	m_Model[0]=CModel::Create();
	m_Model[0]->SetFileData(CXFile::TYPE_KITCHEN);
	m_Model[0]->SetPos(D3DXVECTOR3(50, 0, 500));

	//�①�ɂ̐����Ə�����
	m_Model[1]=CModel::Create();
	m_Model[1]->SetFileData(CXFile::TYPE_REIZOUKO);
	m_Model[1]->SetPos(D3DXVECTOR3(-600, 0, 530));

	//�e�[�u���̐����Ə�����
	m_Model[2]=CModel::Create();
	m_Model[2]->SetFileData(CXFile::TYPE_TABLE);
	m_Model[2]->SetPos(D3DXVECTOR3(100, 0, -100));

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
	//���f���̏I��
	//================================
	for (int nCnt = 0; MAX_MAPMODEL > nCnt; nCnt++)
	{
		if (m_Model[nCnt] != NULL)
		{
			//m_Model[nCnt]->Uninit();
			m_Model[nCnt] = NULL;
		}
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
	for (int nCnt = 0; MAX_MAPMODEL > nCnt; nCnt++)
	{
		if (m_Model[nCnt] != NULL)
		{
			m_Model[nCnt]->Update();
		}
	}

	m_Ground->Update();
}
void CMap::Draw(void)
{
	for (int nCnt = 0; MAX_MAPMODEL > nCnt; nCnt++)
	{
		if (m_Model[nCnt] != NULL)
		{
			m_Model[nCnt]->Draw();
		}
	}

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