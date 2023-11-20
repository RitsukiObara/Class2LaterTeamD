//===========================================
//
// 毬のメイン処理[hairball.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "hairball.h"
#include "collision.h"
#include "useful.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "block.h"
#include "block_manager.h"
#include "input.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY		(0.5f)		// 重力

//==============================
// コンストラクタ
//==============================
CHairBall::CHairBall() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
}

//==============================
// デストラクタ
//==============================
CHairBall::~CHairBall()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CHairBall::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CHairBall::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CHairBall::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_STOP:

		// 特になし

		break;

	case STATE_SMASH:

		// 移動処理
		Move();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 重力処理
	Gravity();

	// 起伏地面との当たり判定
	Elevation();

	// ブロックとの当たり判定
	Block();
}

//=====================================
// 破片の描画処理
//=====================================
void CHairBall::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CHairBall::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// 全ての値を設定する
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
}

//=====================================
// 当たり判定処理
//=====================================
bool CHairBall::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	if (pos.y <= GetPos().y + GetFileData().vtxMax.y &&
		pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y)
	{ // 毬と衝突した場合

		// 円柱の当たり判定処理
		if (useful::CylinderCollision(&pos, GetPos(), GetFileData().fRadius + fWidth) == true)
		{ // 当たり判定が false の場合

			if (posOld.y >= GetPos().y + GetFileData().vtxMax.y &&
				pos.y <= GetPos().y + GetFileData().vtxMax.y)
			{ // 上からの当たり判定

				// 縦の位置を設定する
				pos.y = GetPos().y + GetFileData().vtxMax.y + 0.01f;
			}
			else if (posOld.y + fHeight <= GetPos().y + GetFileData().vtxMin.y &&
				pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y)
			{ // 下からの当たり判定

				// 縦の位置を設定する
				pos.y = GetPos().y + GetFileData().vtxMin.y - fHeight - 0.01f;
			}
		}
	}

	// false の場合
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CHairBall::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// ターゲットの位置を設定する
	D3DXVECTOR3 Targetpos = pos;

	if (m_state == STATE_SMASH &&
		type == COLLTYPE_RAT &&
		pos.y <= GetPos().y + GetFileData().vtxMax.y &&
		pos.y + fHeight >= GetPos().y + GetFileData().vtxMin.y &&
		useful::CylinderCollision(&Targetpos, GetPos(), GetFileData().fRadius + fWidth) == true)
	{ // 毬と衝突した場合

		// true を返す
		return true;
	}
	else
	{ // 上記以外

		// false を返す
		return false;
	}
}

//=====================================
// 移動処理
//=====================================
void CHairBall::Move(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 位置を移動する
	pos.x += m_move.x;
	pos.z += m_move.z;

	// 位置を適用する
	SetPos(pos);
}

//=====================================
// 重力処理
//=====================================
void CHairBall::Gravity(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 重力処理
	useful::Gravity(&m_move.y, pos, GRAVITY);
	
	// 位置を設定する
	SetPos(pos);
}

//=====================================
// 起伏地面の当たり判定
//=====================================
void CHairBall::Elevation(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	float fHeight = 0.0f;					// 高さ
	bool bLand = false;						// 着地状況

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight - GetFileData().vtxMin.y;

			// 移動量を減算する
			m_move.x *= 0.6f;
			m_move.y *= -0.6f;
			m_move.z *= 0.6f;

			if (m_move.y <= 5.0f)
			{ // 移動量が一定以下の場合

				// 重力を補正する
				m_move.y = 0.0f;

				// 着地する
				bLand = true;
			}
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	if (bLand == true)
	{ // 着地状況を true にする

		// 停止状態にする
		m_state = STATE_STOP;
	}
	else
	{ // 上記以外

		// 吹き飛ばし状態にする
		m_state = STATE_SMASH;
	}

	// 位置を更新する
	SetPos(pos);
}

//=====================================
// ブロックの当たり判定
//=====================================
void CHairBall::Block(void)
{
	// ローカル変数宣言
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// ブロックの先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	bool bLand = false;						// 着地状況

	while (pBlock != nullptr)
	{ // 地面の情報がある限り回す

		if (collision::HexahedronCollision(pos, pBlock->GetPos(), GetPosOld(), pBlock->GetPosOld(), GetFileData().vtxMin, pBlock->GetFileData().vtxMin, GetFileData().vtxMax, pBlock->GetFileData().vtxMax) == true)
		{ // 当たり判定が true の場合

		}

		// 次のポインタを取得する
		pBlock = pBlock->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}