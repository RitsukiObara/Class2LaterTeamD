//===========================================
//
// コップの処理[cup.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "cup.h"
#include "useful.h"
#include "objectX.h"
#include "consent.h"
#include "object3D.h"
#include "input.h"
#include "texture.h"

//==============================
// コンストラクタ
//==============================
CCup::CCup() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;
	m_State = STATE_FALSE;
	m_pWater = NULL;
	m_pConsent = NULL;
	m_WaterSize = NONE_D3DXVECTOR3;
}

//==============================
// デストラクタ
//==============================
CCup::~CCup()
{

}

//==============================
// コップの初期化処理
//==============================
HRESULT CCup::Init(void)
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
// コップの終了処理
//========================================
void CCup::Uninit(void)
{
	if (m_pConsent != NULL)
	{ // コンセントが NULL の場合

	  // コンセントの終了処理
		m_pConsent->Uninit();
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// コップの更新処理
//=====================================
void CCup::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	StateManager(&pos, &rot);

	//位置更新
	pos += m_move;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0ボタンを押した場合
		Action();
	}

	SetPos(pos);
	SetRot(rot);
}

//=====================================
// コップの描画処理
//=====================================
void CCup::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	if (m_pConsent != NULL)
	{
		m_pConsent->Draw();
	}
}

//=====================================
// 状態管理
//=====================================
void CCup::StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	switch (m_State)
	{
	case CCup::STATE_FALSE:

		break;

	case CCup::STATE_FALLWAIT:	//ギミック起動から効果発動までの準備時間
		rot->z += 0.07;
		m_move.y -= 0.75f;
		m_move.x = sinf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;

		if (pos->y < 15.0f)
		{
			pos->y = 15.0f;
			m_State = STATE_TRUE;

			m_pWater = CObject3D::Create(CObject3D::TYPE_3DPOLYGON);
			m_pWater->SetPos(GetPos());
			m_pWater->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
			m_pWater->SetSize(m_WaterSize);
			m_pWater->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\water.png"));
		}
		break;

	case CCup::STATE_TRUE:	//ギミックの効果発動から停止までの処理
		m_move = NONE_D3DXVECTOR3;
		pos->y = 15.0f;

		D3DXVECTOR3 WaterPos = m_pWater->GetPos();

		if (m_WaterSize.x < 150.0f)
		{
			WaterPos.x += sinf(0.0f + (D3DX_PI * -0.5f)) * 0.5f;
			WaterPos.z += cosf(0.0f + (D3DX_PI * -0.5f)) * 0.5f;
			m_WaterSize.x += 0.5f;
			m_WaterSize.y += 0.5f;
		}

		m_pWater->SetPos(WaterPos);
		m_pWater->SetSize(m_WaterSize);
		break;
	}
}

//=====================================
// 紐を引っ張られた時の処理
//=====================================
void CCup::Action(void)
{
	if (m_State == STATE_FALSE)
	{
		m_State = STATE_FALLWAIT;
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CCup::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	if (m_pConsent == NULL)
	{
		m_pConsent = CConsent::Create(D3DXVECTOR3(
			pos.x + sinf(0.0f + (D3DX_PI * -0.5f)) * 200.0f,
			0.0f,
			pos.z + cosf(0.0f + (D3DX_PI * -0.5f)) * 200.0f));
		m_pConsent->SetMain(this);
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CCup::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CCup::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	if (m_pConsent != nullptr)
	{ // コンセントが NULL じゃない場合

		if (pos.y <= m_pConsent->GetPos().y + m_pConsent->GetFileData().vtxMax.y &&
			pos.y + fHeight >= m_pConsent->GetPos().y + m_pConsent->GetFileData().vtxMin.y &&
			useful::CylinderInner(pos, m_pConsent->GetPos(), m_pConsent->GetFileData().fRadius + fWidth) == true)
		{ // 当たり判定の中に入った場合

		  // true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CCup::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{//円の範囲内の場合tureを返す
		return true;
	}

	// false を返す
	return false;
}