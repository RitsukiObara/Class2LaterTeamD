#include "map.h"
#include "block.h"
//========================
//�}�N����`
//========================
#define WALLSIZE_LONG D3DXVECTOR3(1600,0,1000)
#define WALLSIZE_SHORT D3DXVECTOR3(1000,0,1000)

//========================
//�ÓI�����o�ϐ�
//========================
CWall* CMap::m_Wall[WALL_NUM] = {};
CModel* CMap::m_Model[2] = {};

//�R���X�g���N�^
<<<<<<< HEAD
CMap::CMap() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_PAUSE)
=======
CMap::CMap() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BG)
>>>>>>> a6d35c5daae5407901398af745c3cdbb2ce6ef47
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
	/*m_Ground = CGround::Create();*/

	//// ���_���W�̐ݒ菈��
	//m_Ground->SetVertex();

	//================================
	//�ǂ̏�����
	//================================
	m_Wall[0] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, 1000.0f), D3DXVECTOR3(-1.57f, 0.0f, 0.0f), WALLSIZE_LONG, CObject::PRIORITY_PAUSE);
	m_Wall[1] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, -1000.0f), D3DXVECTOR3(1.57f, 0.0f, 0.0f), WALLSIZE_LONG, CObject::PRIORITY_PAUSE);
	m_Wall[2] = CWall::Create(D3DXVECTOR3(1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, 1.57f), WALLSIZE_SHORT, CObject::PRIORITY_PAUSE);
	m_Wall[3] = CWall::Create(D3DXVECTOR3(-1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, -1.57f), WALLSIZE_SHORT, CObject::PRIORITY_PAUSE);

	m_Wall[4] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, 1000.0f), D3DXVECTOR3(1.57f, 0.0f, 0.0f), WALLSIZE_LONG, CObject::PRIORITY_PAUSE);
	m_Wall[5] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, -1000.0f), D3DXVECTOR3(-1.57f, 0.0f, 0.0f), WALLSIZE_LONG, CObject::PRIORITY_PAUSE);
	m_Wall[6] = CWall::Create(D3DXVECTOR3(1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, -1.57f), WALLSIZE_SHORT, CObject::PRIORITY_PAUSE);
	m_Wall[7] = CWall::Create(D3DXVECTOR3(-1600.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, 1.57f), WALLSIZE_SHORT, CObject::PRIORITY_PAUSE);

	m_Wall[8] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, 1500.0f), D3DXVECTOR3(-1.57f, 0.0f, 0.0f), D3DXVECTOR3(2100, 0, 1100), CObject::PRIORITY_PAUSE);
	m_Wall[9] = CWall::Create(D3DXVECTOR3(0.0f, 300.0f, -1500.0f), D3DXVECTOR3(1.57f, 0.0f, 0.0f), D3DXVECTOR3(2100, 0, 1100), CObject::PRIORITY_PAUSE);
	m_Wall[10] = CWall::Create(D3DXVECTOR3(2100.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, 1.57f), D3DXVECTOR3(1500, 0, 1100), CObject::PRIORITY_PAUSE);
	m_Wall[11] = CWall::Create(D3DXVECTOR3(-2100.0f, 300.0f, 0.0f), D3DXVECTOR3(1.57f, 0.0f, -1.57f), D3DXVECTOR3(1500,0,1100), CObject::PRIORITY_PAUSE);

	m_Wall[4]->SetVtxColor(D3DXCOLOR(255, 255, 255, 0.2f));
	m_Wall[5]->SetVtxColor(D3DXCOLOR(255, 255, 255, 0.2f));
	m_Wall[6]->SetVtxColor(D3DXCOLOR(255, 255, 255, 0.2f));
	m_Wall[7]->SetVtxColor(D3DXCOLOR(255, 255, 255, 0.2f));

	for (int nCnt = 0; nCnt < WALL_NUM; nCnt++)
	{
		// ���_���W�̐ݒ菈��
		m_Wall[nCnt]->SetVertex();
	}

	//�������f���̐ݒ�
	//m_Model[0]=CModel::Create()

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
			m_Wall[nCnt] = NULL;
		}
	}

	// �{�̂̏I������
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