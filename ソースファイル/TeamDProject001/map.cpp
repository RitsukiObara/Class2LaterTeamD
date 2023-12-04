#include "map.h"
//========================
//マクロ定義
//========================
#define WALLSIZE_LONG D3DXVECTOR3(1600,0,600)
#define WALLSIZE_SHORT D3DXVECTOR3(1000,0,600)

//========================
//静的メンバ変数
//========================
CWall* CMap::m_Wall[WALL_NUM] = {};

//コンストラクタ
CMap::CMap() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BLOCK)
{

}
//デストラクタ
CMap::~CMap()
{

}

HRESULT CMap::Init(void)
{
	//================================
	//地面の初期化
	//================================
	m_Ground = CGround::Create();

	//================================
	//壁の初期化
	//================================
	m_Wall[0] = CWall::Create(D3DXVECTOR3(0, 300, 1000), D3DXVECTOR3(-1.57f, 0, 0), WALLSIZE_LONG);
	m_Wall[1] = CWall::Create(D3DXVECTOR3(0, 300, -1000), D3DXVECTOR3(1.57f, 0, 0), WALLSIZE_LONG);
	m_Wall[2] = CWall::Create(D3DXVECTOR3(1600, 300, 0), D3DXVECTOR3(1.57f, 0, 1.57f), WALLSIZE_SHORT);
	m_Wall[3] = CWall::Create(D3DXVECTOR3(-1600, 300, 0), D3DXVECTOR3(1.57f, 0, -1.57f), WALLSIZE_SHORT);

	//================================
	//モデルの初期化
	//================================
	//キッチンの生成と初期化
	m_Model[0]= CBlock::Create(D3DXVECTOR3(-630, 0, 900), D3DXVECTOR3(0, 0, 0),CBlock::TYPE::TYPE_KITCHEN);
	m_Model[0]->SetFileData(CXFile::TYPE_KITCHEN);

	//冷蔵庫の生成と初期化
	m_Model[1]= CBlock::Create(D3DXVECTOR3(-1480, 0, 900), D3DXVECTOR3(0, 0, 0), CBlock::TYPE::TYPE_REIZOUKO);
	m_Model[1]->SetFileData(CXFile::TYPE_REIZOUKO);

	//テーブルの生成と初期化
	m_Model[2]= CBlock::Create(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, 0, 0), CBlock::TYPE::TYPE_TABLE);
	m_Model[2]->SetFileData(CXFile::TYPE_TABLE);

	return S_OK;
}
void CMap::Uninit(void)
{
	//================================
	//地面の終了
	//================================
	if (m_Ground != NULL)
	{
		m_Ground->Uninit();
		m_Ground = NULL;
	}
	//================================
	//モデルの終了
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
	//壁の終了
	//================================
	for (int nCnt = 0; nCnt < WALL_NUM; nCnt++)
	{
		if (m_Wall[nCnt] != nullptr)
		{
			m_Wall[nCnt]->Uninit();
			m_Wall[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
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
CWall*CMap:: GetWall(void)
{
	return m_Wall[0];
}