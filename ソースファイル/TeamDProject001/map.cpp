#include "map.h"

CMap::CMap()
{

}

CMap::~CMap()
{

}

HRESULT CMap::Init(void)
{
	//�L�b�`���̐����Ə�����
	m_Model[0]->Create();
	m_Model[0]->SetFileData(CXFile::TYPE_KITCHEN);

	//�L�b�`���̐����Ə�����
	m_Model[1]->Create();
	m_Model[1]->SetFileData(CXFile::TYPE_IH_OFF);

	//�L�b�`���̐����Ə�����
	m_Model[2]->Create();
	m_Model[21]->SetFileData(CXFile::TYPE_IH_ON);

	//�L�b�`���̐����Ə�����
	m_Model[3]->Create();
	m_Model[3]->SetFileData(CXFile::TYPE_TAP);

}
CMap* CMap::Create(void)
{
	CMap *pMap;

	pMap = new CMap;

	pMap->m_pos = pos;

	pMap->SetType(TYPE_MAP);

	pMap->Init();

	return pMap;
}