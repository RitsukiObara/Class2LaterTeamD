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
			Scale.y -= 0.040f;

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

		SetScale(D3DXVECTOR3(0.5f, 12.0f, 0.5f));
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CHoney::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// モデルの情報を設定する
	SetFileData(CXFile::TYPE_HONEYBOTTLE);
}

//=====================================
// 当たり判定処理
//=====================================
bool CHoney::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CHoney::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	if (m_State == STATE_HONEY)
	{
		// ローカル変数宣言
		D3DXVECTOR3 max = D3DXVECTOR3(fWidth, fHeight, fDepth);		// サイズの最大値
		D3DXVECTOR3 min = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);		// サイズの最小値

		if (useful::RectangleCollisionXY(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
			useful::RectangleCollisionXZ(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
			useful::RectangleCollisionYZ(GetPos(), pos, GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true)
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
	{
		return false;
	}
}