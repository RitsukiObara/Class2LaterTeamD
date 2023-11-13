#include "map.h"

CMap::CMap() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BLOCK)
{

}
CMap::~CMap()
{

}

HRESULT CMap::Init(void)
{
	//�L�b�`���̐����Ə�����
	m_Model[0]=CModel::Create();
	m_Model[0]->SetFileData(CXFile::TYPE_KITCHEN);

	//�L�b�`���̐����Ə�����
	m_Model[1]=CModel::Create();
	m_Model[1]->SetFileData(CXFile::TYPE_IH_OFF);

	//�L�b�`���̐����Ə�����
	m_Model[2]=CModel::Create();
	m_Model[2]->SetFileData(CXFile::TYPE_IH_ON);

	//�L�b�`���̐����Ə�����
	m_Model[3]=CModel::Create();
	m_Model[3]->SetFileData(CXFile::TYPE_TAP);

	return S_OK;
}
void CMap::Uninit(void)
{
	for (int nCnt = 0; 4 > nCnt; nCnt++)
	{
		if (m_Model[nCnt] != NULL)
		{
			//m_Model[nCnt]->Uninit();
			m_Model[nCnt] = NULL;
		}
	}
}
void CMap::Update(void)
{
	for (int nCnt = 0; 4 > nCnt; nCnt++)
	{
		if (m_Model[nCnt] != NULL)
		{
			m_Model[nCnt]->Update();
		}
	}
}
void CMap::Draw(void)
{
	for (int nCnt = 0; 4 > nCnt; nCnt++)
	{
		if (m_Model[nCnt] != NULL)
		{
			m_Model[nCnt]->Draw();
		}
	}
}
CMap* CMap::Create(void)
{
	CMap *pMap;

	pMap = new CMap;

	pMap->SetType(TYPE_MAP);

	pMap->Init();

	return pMap;
}