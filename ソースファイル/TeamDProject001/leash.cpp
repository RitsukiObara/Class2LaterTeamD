//===========================================
//
// リードの処理[Himo.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "leash.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"

#define ACTION_TIME (120)
#define WAIT_TIME (20)

//==============================
// コンストラクタ
//==============================
CLeash::CLeash() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_State = STATE_FALSE;
	m_bSetHead = false;
	m_bSetToes = false;
	m_StateCount = 0;
}

//==============================
// デストラクタ
//==============================
CLeash::~CLeash()
{

}

//==============================
// リードの初期化処理
//==============================
HRESULT CLeash::Init(void)
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
// リードの終了処理
//========================================
void CLeash::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// リードの更新処理
//=====================================
void CLeash::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//ギミック起動時の処理
	if ((m_bSetHead == true && m_bSetToes == true) && m_State == STATE_FALSE)
	{//起動していない時にネズミが両端を持ったら
		Action();
	}

	StateManager(&pos);

	//重力
	m_move.y -= 1.0f;

	//位置更新
	pos.y += m_move.y;

	//地面判定
	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
	}

	SetActionPos(pos, rot);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // Aボタンを押した場合
		m_bSetHead = true;
		m_bSetToes = true;
	}

	SetPos(pos);
}

//=====================================
// リードの描画処理
//=====================================
void CLeash::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 両端起動時の処理
//=====================================
void CLeash::Action(void)
{
	m_State = STATE_JUMPWAIT;
	m_StateCount = WAIT_TIME;
	m_move.y = 30.0f;
}

//=====================================
// ギミック起動位置の設定
//=====================================
void CLeash::SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ActionPosHead = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 1.0f)) * 300.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 1.0f)) * 300.0f);

	ActionPosToes = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.0f)) * 350.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.0f)) * 350.0f);

	CEffect::Create(ActionPosHead, NONE_D3DXVECTOR3, 20, 30.0f, CEffect::TYPE::TYPE_NONE, NONE_D3DXCOLOR, true);
	CEffect::Create(ActionPosToes, NONE_D3DXVECTOR3, 20, 30.0f, CEffect::TYPE::TYPE_NONE, NONE_D3DXCOLOR, true);
}

//=====================================
// 状態管理
//=====================================
void CLeash::StateManager(D3DXVECTOR3 *pos)
{
	switch (m_State)
	{
	case CLeash::STATE_FALSE:

		break;

	case CLeash::STATE_JUMPWAIT:	//ギミック起動から効果発動までの準備時間
		m_StateCount--;
		if (m_StateCount <= 0)
		{
			m_State = STATE_TRUE;
			m_StateCount = ACTION_TIME;
			SetFileData(CXFile::TYPE_LEASHSET);
		}
		break;

	case CLeash::STATE_TRUE:	//ギミックの効果発動から停止までの処理
		m_StateCount--;

		if (pos->y < 200.0f)
		{
			pos->y = 200.0f;
			m_move.y = 0.0f;
		}

		if (m_StateCount <= 0)
		{
			m_State = STATE_FALSE;
			m_bSetHead = false;
			m_bSetToes = false;
			SetFileData(CXFile::TYPE_LEASH);
		}
		break;
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CLeash::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CLeash::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CLeash::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	//// 終了処理
	//Uninit();

	// false を返す
	return false;
}