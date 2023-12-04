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
	m_State = STATE_GARBAGECAN;
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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RETURN) == true)
	{ // ENTERキーを押していた場合
		//破壊時処理
		Break();
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
	case CGarbage::STATE_GARBAGECAN:



		break;
	case CGarbage::STATE_GARBAGE:

		break;
	}
}

//=====================================
// 破壊時処理
//=====================================
void CGarbage::Break(void)
{
	if (m_State == STATE_GARBAGECAN)
	{
		m_State = STATE_GARBAGE;

		CFraction::Create(GetPos(), CFraction::TYPE_FLOWERVASE);

		// モデルの情報を設定する
		SetFileData(CXFile::TYPE_GARBAGE);

		SetScale(D3DXVECTOR3(2, 1.0f, 2));
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
bool CGarbage::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// 最大値と最小値を設定する
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);

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
	else
	{ // 上記以外

		// false を返す
		return false;
	}
}
//=====================================
// ヒット処理
//=====================================
bool CGarbage::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// ローカル変数宣言
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);		// サイズの最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);		// サイズの最小値

	if (m_State == STATE_GARBAGECAN)
	{ // 蜂蜜ボトル状態の場合

		if (type == CPlayer::TYPE_RAT)
		{ // ネコの場合

			if (useful::RectangleCollisionXY(pos, GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
				useful::RectangleCollisionYZ(pos, GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true)
			{ // 矩形の当たり判定に通った場合

				// 破壊時処理
				Break();

				// true を返す
				return false;
			}
			else
			{ // 上記以外

				// false を返す
				return false;
			}
		}
		else
		{ // 上記以外

			// false を返す
			return false;
		}
	}
	else if (m_State == STATE_GARBAGE)
	{ // 蜂蜜状態の場合

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
		{ // 四角の当たり判定の中に入っていた場合
			if (type == CPlayer::TYPE_CAT)
			{
				// true を返す
				return true;
			}
			else
			{
				// false を返す
				return false;
			}
		}
		else
		{ // 上記以外

			// false を返す
			return false;
		}
	}
	else
	{ // 上記以外

		// 停止
		assert(false);

		// false を返す
		return false;
	}
}

//=====================================
// ギミック起動処理
//=====================================
void CGarbage::Action(void)
{

}