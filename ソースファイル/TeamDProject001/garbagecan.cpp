//===========================================
//
// 蜂蜜のメイン処理[garbage.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "collision.h"
#include "input.h"
#include "fraction.h"
#include "renderer.h"
#include "garbagecan.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CGarbage::CGarbage() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_GARBAGECAN;		// 状態

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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_0) == true)
	{ // ENTERキーを押していた場合

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
	case CGarbage::STATE_BANANA:		// バナナの皮

		break;
	}
}

//=====================================
// 破壊時処理
//=====================================
void CGarbage::Break(void)
{
	if (m_State == STATE_GARBAGECAN)
	{ // ゴミ箱状態の場合

		m_State = STATE_BANANA;

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
	{ // 蜂蜜ボトル状態の場合

		if (collision::HexahedronCollision(pos, GetPos(), posOld, GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax) == true)
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

	if (m_State == STATE_BANANA &&
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