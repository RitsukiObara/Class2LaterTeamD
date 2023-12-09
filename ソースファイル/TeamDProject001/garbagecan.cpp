//===========================================
//
// ゴミ箱のメイン処理[garbage.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "collision.h"
#include "fraction.h"
#include "renderer.h"
#include "garbagecan.h"
#include "useful.h"
#include "player.h"
#include "block.h"
#include "block_manager.h"

//==============================
// コンストラクタ
//==============================
CGarbage::CGarbage() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_GARBAGECAN;		// 状態
	m_Slide = SLIDE_STOP;
	m_pPlayer = NULL;
	m_SlideMove = NONE_D3DXVECTOR3;
	m_PlayerPos = NONE_D3DXVECTOR3;

	// ネズミだけ動かせるようにする
	SetCatUse(false);
	SetRatUse(true);
}

//==============================
// デストラクタ
//==============================
CGarbage::~CGarbage()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CGarbage::Init(void)
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
// 破片の終了処理
//========================================
void CGarbage::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CGarbage::Update(void)
{
	//状態管理
	StateManager();

	if (m_Slide == SLIDE_ON)
	{
		D3DXVECTOR3 pos = GetPos();
		SetPosOld(pos);
		D3DXVECTOR3 posold = GetPosOld();

		pos += m_SlideMove;
		m_pPlayer->SetPos(pos + m_PlayerPos);

		if (Collision(pos, posold, GetFileData().vtxMax, CPlayer::TYPE::TYPE_CAT) == true)
		{
			m_Slide = SLIDE_BREAK;
			m_SlideMove = D3DXVECTOR3(-m_SlideMove.x * 0.1f, 30.0f, -m_SlideMove.z * 0.1f);
		}

		SetPos(pos);
	}
	else if(m_Slide == SLIDE_BREAK)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		SetPosOld(pos);
		D3DXVECTOR3 posold = GetPosOld();

		m_SlideMove.y -= 1.0f;
		rot.x += 0.1f;
		rot.z += 0.3f;

		pos += m_SlideMove;

		SetPos(pos);
		SetRot(rot);

		if (pos.y < 0.0f)
		{
			Uninit();
		}
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CGarbage::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 状態管理
//=====================================
void CGarbage::StateManager(void)
{
	switch (m_State)
	{
	case CGarbage::STATE_GARBAGECAN:	// ゴミ箱



		break;
	case CGarbage::STATE_BANANA_NORMAL:		// バナナの皮

		break;
	}
}

//=====================================
// 破壊時処理
//=====================================
void CGarbage::SlideOn(D3DXVECTOR3 pos, D3DXVECTOR3 move, CPlayer *pPlayer)
{
	m_Slide = SLIDE_ON;
	m_State = STATE_BANANA_SLIDE;
	m_PlayerPos = pos - GetPos();
	m_SlideMove = move;
	m_pPlayer = pPlayer;
}

//=====================================
// 破壊時処理
//=====================================
void CGarbage::Break(void)
{
	if (m_State == STATE_GARBAGECAN)
	{ // ゴミ箱状態の場合

		m_State = STATE_BANANA_NORMAL;

		// モデルの情報を設定する
		SetFileData(CXFile::TYPE_GARBAGE);
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CGarbage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CGarbage::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// 最大値と最小値を設定する
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (m_State == STATE_GARBAGECAN)
	{ //ゴミ箱状態の場合

		if (collision::HexahedronCollision(&pos, GetPos(), posOld, GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax) == true)
		{ // 六面体の当たり判定が true の場合

			// true を返す
			return true;
		}
		else
		{ // 上記以外

			// false を返す
			return false;
		}
	}
	else if(m_Slide == SLIDE_ON)
	{
		// 先頭のブロックの情報を取得する
		CBlock* pBlock = CBlockManager::Get()->GetTop();
		bool bJump = false;			// ジャンプ状況

		while (pBlock != nullptr)
		{ // ブロックが NULL の場合

			if (collision::HexahedronCollision(&pos, pBlock->GetPos(), posOld, pBlock->GetPosOld(), vtxMin, pBlock->GetFileData().vtxMin, vtxMax, pBlock->GetFileData().vtxMax) == true)
			{ // 六面体の当たり判定が true の場合

			  // true を返す
				return true;
			}

		  // 次のブロックの情報を取得する
			pBlock = pBlock->GetNext();
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CGarbage::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// ローカル変数宣言
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// サイズの最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// サイズの最小値

	if (m_State == STATE_BANANA_NORMAL &&
		type == CPlayer::TYPE_CAT &&
		useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
	{ // ネコがバナナの皮に引っかかった場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒットの円処理
//=====================================
bool CGarbage::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{ // 範囲内に入っている場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CGarbage::Action(void)
{
	//破壊時処理
	Break();
}