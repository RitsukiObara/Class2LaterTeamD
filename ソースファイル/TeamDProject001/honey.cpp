//===========================================
//
// 蜂蜜のメイン処理[honey.cpp]
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
#include "honey.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CHoney::CHoney() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	m_State = STATE_HONEYBOTTLE;
}

//==============================
// デストラクタ
//==============================
CHoney::~CHoney()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CHoney::Init(void)
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
void CHoney::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CHoney::Update(void)
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
void CHoney::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 状態管理
//=====================================
void CHoney::StateManager(void)
{
	switch (m_State)
	{
	case CHoney::STATE_HONEYBOTTLE:



		break;
	case CHoney::STATE_HONEY:

		D3DXVECTOR3 Scale = GetScale();

		if (Scale.x <= 1.0f)
		{
			Scale.x += 0.005f;
			Scale.z += 0.005f;

			SetScale(Scale);
		}

		break;
	}
}

//=====================================
// 破壊時処理
//=====================================
void CHoney::Break(void)
{
	if (m_State == STATE_HONEYBOTTLE)
	{
		m_State = STATE_HONEY;

		CFraction::Create(GetPos(), CFraction::TYPE_FLOWERVASE);

		// モデルの情報を設定する
		SetFileData(CXFile::TYPE_HONEY);

		SetScale(D3DXVECTOR3(0.5f, 1.0f, 0.5f));
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CHoney::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CHoney::Collision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// 最大値と最小値を設定する
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (m_State == STATE_HONEYBOTTLE)
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
bool CHoney::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// ローカル変数宣言
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// サイズの最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// サイズの最小値

	if (m_State == STATE_HONEYBOTTLE)
	{ // 蜂蜜ボトル状態の場合

		if (type == CPlayer::TYPE_CAT)
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
	else if (m_State == STATE_HONEY)
	{ // 蜂蜜状態の場合

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
		{ // 四角の当たり判定の中に入っていた場合

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

		// 停止
		assert(false);

		// false を返す
		return false;
	}
}