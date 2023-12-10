//===========================================
//
// ペットボトルのメイン処理[petbottle.cpp]
// Author 大野祥平
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "hairball.h"
#include "useful.h"
#include "petbottle.h"

#include "objectElevation.h"
#include "elevation_manager.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define STAND_ROT	(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f))		// 直立状態の向き
#define GRAVITY		(0.5f)											// 重力

//==============================
// コンストラクタ
//==============================
CPetbottle::CPetbottle() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;
	m_state = STATE_STAND;
}

//==============================
// デストラクタ
//==============================
CPetbottle::~CPetbottle()
{

}

//==============================
// ペットボトルの初期化処理
//==============================
HRESULT CPetbottle::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;
	m_state = STATE_STAND;

	// 値を返す
	return S_OK;
}

//========================================
// ペットボトルの終了処理
//========================================
void CPetbottle::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ペットボトルの更新処理
//=====================================
void CPetbottle::Update(void)
{
	switch (m_state)
	{
	case CPetbottle::STATE_STAND:

		// 向きを設定する
		SetRot(STAND_ROT);

		break;

	case CPetbottle::STATE_COLLAPSE:

		// 回転処理
		Cycle();

		// 重力処理
		Gravity();

		if (MagicWall() == true)
		{ // 部屋の端に当たった場合

			// 終了処理
			Uninit();

			// この先の処理を行わない
			return;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 起伏地面との当たり判定
	Elevation();
}

//=====================================
// ペットボトルの描画処理
//=====================================
void CPetbottle::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CPetbottle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 向きを設定する
	SetRot(STAND_ROT);

	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STAND;			// 状態
}

//=====================================
// 当たり判定処理
//=====================================
bool CPetbottle::Collision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	if (m_state == STATE_STAND)
	{ // 直立状態の場合

		if (pos->y <= GetPos().y + GetFileData().vtxMax.y &&
			pos->y + collSize.y >= GetPos().y + GetFileData().vtxMin.y)
		{ // ペットボトルと衝突した場合

			// 円柱の当たり判定処理
			if (useful::CylinderCollision(pos, GetPos(), GetFileData().vtxMax.x + collSize.x) == true)
			{ // 当たり判定が false の場合

				if (posOld.y >= GetPos().y + GetFileData().vtxMax.y &&
					pos->y <= GetPos().y + GetFileData().vtxMax.y)
				{ // 上からの当たり判定

					// 縦の位置を設定する
					pos->y = GetPos().y + GetFileData().vtxMax.y + 0.01f;
				}
				else if (posOld.y + collSize.y <= GetPos().y + GetFileData().vtxMin.y &&
					pos->y + collSize.y >= GetPos().y + GetFileData().vtxMin.y)
				{ // 下からの当たり判定

					// 縦の位置を設定する
					pos->y = GetPos().y + GetFileData().vtxMin.y - collSize.y - 0.01f;
				}
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CPetbottle::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// 最大値と最小値を設定する
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	switch (m_state)
	{
	case CPetbottle::STATE_STAND:

		if (type == CPlayer::TYPE_CAT &&
			pos.y <= GetPos().y + GetFileData().vtxMax.y &&
			pos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.y &&
			useful::CylinderInner(pos, GetPos(), GetFileData().vtxMax.x + collSize.x) == true)
		{ // ペットボトルに衝突した場合

			// 倒れる処理
			Collapse(pos);
		}

		break;

	case CPetbottle::STATE_COLLAPSE:

		if (type == CPlayer::TYPE_RAT &&
			useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
		{ // 倒れ状態かつ、当たり判定が true の場合

			// true を返す
			return true;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// false を返す
	return false;
}

//=====================================
// 回転処理
//=====================================
void CPetbottle::Cycle(void)
{
	// 情報を取得する
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き

	// 移動量を設定する
	m_move.x = sinf(rot.y - (D3DX_PI * 0.5f)) * 8.0f;
	m_move.z = cosf(rot.y - (D3DX_PI * 0.5f)) * 8.0f;

	// 向きを加算する
	rot.z += 0.01f;

	// 位置を移動する
	pos.x += m_move.x;
	pos.z += m_move.z;

	// 情報を適用する
	SetPos(pos);		// 位置
	SetRot(rot);		// 向き
}

//=====================================
// 重力処理
//=====================================
void CPetbottle::Gravity(void)
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
void CPetbottle::Elevation(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);		// 位置を取得する
	float fHeight = 0.0f;					// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight - GetFileData().vtxMin.y;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}

//=====================================
// 倒れる処理
//=====================================
void CPetbottle::Collapse(const D3DXVECTOR3& posPlayer)
{
	// 位置と向きと方向を宣言する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fAngle = 0.0f;

	// 倒れ状態にする
	m_state = STATE_COLLAPSE;

	// 方向を設定する
	fAngle = atan2f((pos.x - posPlayer.x), (pos.z - posPlayer.z));

	// 向きを設定する
	rot.x = 0.0f;
	rot.z = 0.0f;

	if (fAngle >= D3DX_PI * -0.25f &&
		fAngle <= D3DX_PI * 0.25f)
	{ // 方向が手前からの場合

		// 向きを設定する
		rot.y = D3DX_PI * 0.5f;
	}
	else if (fAngle >= D3DX_PI * 0.25f &&
		fAngle <= D3DX_PI * 0.75f)
	{ // 方向が左からの場合

		// 向きを設定する
		rot.y = D3DX_PI;
	}
	else if (fAngle >= D3DX_PI * -0.75f &&
		fAngle <= D3DX_PI * -0.25f)
	{ // 方向が右からの場合

		// 向きを設定する
		rot.y = 0.0f;
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 向きを設定する
		rot.y = D3DX_PI * -0.5f;
	}

	// 向きを適用する
	SetRot(rot);
}

//=====================================
// 魔法の壁処理
//=====================================
bool CPetbottle::MagicWall(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 Max = GetFileData().vtxMax;
	D3DXVECTOR3 Min = GetFileData().vtxMin;

	if (pos.x + Min.x <= -1600.0f)
	{ // 位置が左から出そうな場合

		// true を返す
		return true;
	}

	if (pos.x + Max.x >= 1600.0f)
	{ // 位置が右から出そうな場合

		// true を返す
		return true;
	}

	if (pos.z + Min.z <= -1000.0f)
	{ // 位置が右から出そうな場合

		// true を返す
		return true;
	}

	if (pos.z + Max.z >= 1000.0f)
	{ // 位置が右から出そうな場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}