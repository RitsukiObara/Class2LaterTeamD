//===========================================
//
// スピーカーの処理[Himo.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "speaker.h"
#include "useful.h"
#include "objectX.h"
#include "note.h"
#include "input.h"

#define NOTE_INTERVAL (20)	//音符の出現間隔(フレーム)
#define NOTE_LIFE (120)		//音符の寿命
#define NOTE_SPEED (15.0f)	//音符の速さ

CNote* CSpeaker::m_apNote[MAX_NOTE] = {};							// 音符の情報
//==============================
// コンストラクタ
//==============================
CSpeaker::CSpeaker() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		m_apNote[nCnt] = NULL;
	}
	m_bAction = false;
	m_nNoateCount = 0;
}

//==============================
// デストラクタ
//==============================
CSpeaker::~CSpeaker()
{

}

//==============================
// スピーカーの初期化処理
//==============================
HRESULT CSpeaker::Init(void)
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
// スピーカーの終了処理
//========================================
void CSpeaker::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// スピーカーの更新処理
//=====================================
void CSpeaker::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_bAction == true)
	{
		SetNote();
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // Aボタンを押した場合
		m_bAction = m_bAction ? false : true;
	}

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != NULL)
		{
			m_apNote[nCnt]->Update();
		}
	}

	SetPos(pos);
}

//=====================================
// スピーカーの描画処理
//=====================================
void CSpeaker::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != NULL)
		{
			m_apNote[nCnt]->Draw();
		}
	}
}

//=====================================
// 音符の生成処理
//=====================================
void CSpeaker::SetNote(void)
{
	m_nNoateCount++;

	if (m_nNoateCount % NOTE_INTERVAL == 0)
	{
		for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
		{
			if (m_apNote[nCnt] == NULL)
			{
				D3DXVECTOR3 pos = GetPos();
				D3DXVECTOR3 rot = GetRot();

				m_apNote[nCnt] = CNote::Create(D3DXVECTOR3(pos.x, pos.y + 20.0f, pos.z));
				m_apNote[nCnt]->SetIndex(nCnt);
				m_apNote[nCnt]->SetLife(NOTE_LIFE);
				m_apNote[nCnt]->SetMove(D3DXVECTOR3(
					sinf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED,
					0.0f,
					cosf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED));
				break;
			}
		}
	}
}

//=====================================
// 紐を引っ張られた時の処理
//=====================================
void CSpeaker::Action(void)
{
	m_bAction = true;
}

//=====================================
// 情報の設定処理
//=====================================
void CSpeaker::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CSpeaker::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CSpeaker::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	//// 終了処理
	//Uninit();

	// false を返す
	return false;
}