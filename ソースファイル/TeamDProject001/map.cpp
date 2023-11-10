#include "map.h"

CMap::CMap()
{

}

CMap::~CMap()
{

}

HRESULT CMap::Init(void)
{
	//キッチンの生成と初期化
	m_Model[0]->Create();
	m_Model[0]->SetFileData(CXFile::TYPE_KITCHEN);

	//キッチンの生成と初期化
	m_Model[1]->Create();
	m_Model[1]->SetFileData(CXFile::TYPE_IH);

	//キッチンの生成と初期化
	m_Model[2]->Create();
	m_Model[21]->SetFileData(CXFile::TYPE_IH);

	//キッチンの生成と初期化
	m_Model[3]->Create();
	m_Model[3]->SetFileData(CXFile::TYPE_TAP);

}
CMap* CMap::Create(D3DXVECTOR3 pos)
{
	CMap *pMap;

	pMap = new CMap;

	pMap->m_pos = pos;

	pMap->SetType(TYPE_MAP);

	pMap->Init();

	return pMap;
}