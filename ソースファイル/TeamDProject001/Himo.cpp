//===========================================
//
// ひもの処理[Himo.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Himo.h"
#include "useful.h"
#include "objectX.h"
#include "tarai.h"
#include "input.h"

#define TARAI_FALL_AREA_X (3001)	//たらいの落下範囲(X)
#define TARAI_FALL_AREA_Z (2001)	//たらいの落下範囲(Z)

CTarai* CHimo::m_apTarai[MAX_TARAI] = {};							// たらいの情報
//==============================
// コンストラクタ
//==============================
CHimo::CHimo() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for(int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		m_apTarai[nCnt] = NULL;
	}
	m_nTaraiCount = 0;
	m_bAction = false;
	m_fDownPosY = 0.0f;
	m_fUpPosY = 0.0f;
	SetCatUse(true);
}

//==============================
// デストラクタ
//==============================
CHimo::~CHimo()
{

}

//==============================
// ひもの初期化処理
//==============================
HRESULT CHimo::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// ひもの終了処理
//========================================
void CHimo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != nullptr)
		{ // タライが NULL じゃない場合

			// タライの終了処理
			m_apTarai[nCnt]->Uninit();
			m_apTarai[nCnt] = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ひもの更新処理
//=====================================
void CHimo::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_bAction == true)
	{
		if (pos.y > m_fDownPosY)
		{
			pos.y -= 2.0f;
		}

		SetTarai();
	}
	else
	{
		if (pos.y < m_fUpPosY)
		{
			pos.y += 2.0f;
		}
	}

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{
			m_apTarai[nCnt]->Update();
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // Aボタンを押した場合
		m_bAction = m_bAction ? false : true;
	}

	SetPos(pos);
}

//=====================================
// ひもの描画処理
//=====================================
void CHimo::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{
			m_apTarai[nCnt]->Draw();
		}
	}
}

//=====================================
// たらいの生成処理
//=====================================
void CHimo::SetTarai(void)
{
	m_nTaraiCount++;

	if (m_nTaraiCount % 5 == 0)
	{
		for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
		{
			if (m_apTarai[nCnt] == NULL)
			{
				int nRandX = rand() % TARAI_FALL_AREA_X;
				int nRandY = rand() % TARAI_FALL_AREA_Z;

				m_apTarai[nCnt] = CTarai::Create(D3DXVECTOR3((float)nRandX - ((float)TARAI_FALL_AREA_X * 0.5f), 1000.0f, (float)nRandY - ((float)TARAI_FALL_AREA_Z * 0.5f)));
				m_apTarai[nCnt]->SetIndex(nCnt);

				break;
			}
		}
	}
}

//=====================================
// 紐を引っ張られた時の処理
//=====================================
void CHimo::Action(void)
{
	m_bAction = true;
	SetAction(true);
}

//=====================================
// 情報の設定処理
//=====================================
void CHimo::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	m_fDownPosY = pos.y - 50.0f;
	m_fUpPosY = pos.y;
}

//=====================================
// ヒット処理
//=====================================
bool CHimo::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	for (int nCntTarai = 0; nCntTarai < MAX_TARAI; nCntTarai++)
	{
		if (m_apTarai[nCntTarai] != nullptr)
		{ // タライが NULL じゃない場合

			if (pos.y + collSize.y <= m_apTarai[nCntTarai]->GetPosOld().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				pos.y + collSize.y >= m_apTarai[nCntTarai]->GetPos().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				useful::CylinderInner(pos, m_apTarai[nCntTarai]->GetPos(), m_apTarai[nCntTarai]->GetFileData().fRadius + collSize.x) == true)
			{ // タライが頭上に落ちてきた場合

				// true を返す
				return true;
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CHimo::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{//円の範囲内の場合tureを返す
		return true;
	}

	// false を返す
	return false;
}