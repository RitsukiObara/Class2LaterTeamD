#include "map.h"
#include "block.h"
//========================
//マクロ定義
//========================
#define WALLSIZE_LONG D3DXVECTOR3(1600,0,1000)
#define WALLSIZE_SHORT D3DXVECTOR3(1000,0,1000)

//========================
//静的メンバ変数
//========================
CWall* CMap::m_Wall[WALL_NUM] = {};

//コンストラクタ
CMap::CMap() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BG)
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
	/*m_Ground = CGround::Create();*/

	//// 頂点座標の設定処理
	//m_Ground->SetVertex();

	//================================
	//壁の初期化
	//================================
	m_Wall[0] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, 1000.0f), D3DXVECTOR3(-1.57f, 0.0f, 0.0f), WALLSIZE_LONG);
	m_Wall[1] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, -1000.0f), D3DXVECTOR3(1.57f, 0.0f, 0.0f), WALLSIZE_LONG);
	m_Wall[2] = CWall::Create(D3DXVECTOR3(1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, 1.57f), WALLSIZE_SHORT);
	m_Wall[3] = CWall::Create(D3DXVECTOR3(-1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, -1.57f), WALLSIZE_SHORT);

	for (int nCnt = 0; nCnt < WALL_NUM; nCnt++)
	{
		// 頂点座標の設定処理
		m_Wall[nCnt]->SetVertex();
	}

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
	//壁の終了
	//================================
	for (int nCnt = 0; nCnt < WALL_NUM; nCnt++)
	{
		if (m_Wall[nCnt] != nullptr)
		{
			m_Wall[nCnt]->Uninit();
			m_Wall[nCnt] = NULL;
		}
	}

	// 本体の終了処理
	Release();
}
void CMap::Update(void)
{

}
void CMap::Draw(void)
{

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