//===========================================
//
// おもちゃの車のメイン処理[toycar.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "toycar.h"
#include "renderer.h"
#include "input.h"
#include "useful.h"

#include "car_gear.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define CAR_GEAR_SHIFT		(D3DXVECTOR3(0.0f, 200.0f, 0.0f))		// 車の歯車のずらす幅

//==============================
// コンストラクタ
//==============================
CToyCar::CToyCar() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pGear = nullptr;			// 歯車の情報
}

//==============================
// デストラクタ
//==============================
CToyCar::~CToyCar()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CToyCar::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pGear = nullptr;		// 歯車の値

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CToyCar::Uninit(void)
{
	if (m_pGear != nullptr)
	{ // 歯車の情報が NULL じゃない場合

		// 終了処理
		m_pGear->Uninit();
		m_pGear = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CToyCar::Update(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	pos.x -= sinf(rot.y) * 10.0f;
	pos.z -= cosf(rot.y) * 10.0f;

	rot.y -= 0.02f;

	// 位置を適用する
	SetPos(pos);
	SetRot(rot);

	if (m_pGear != nullptr)
	{ // 歯車が NULL じゃない場合

		// 位置を決定する
		m_pGear->SetPos(GetPos() + CAR_GEAR_SHIFT);

		// 更新処理
		m_pGear->Update();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CToyCar::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	if (m_pGear != nullptr)
	{ // 歯車が NULL じゃない場合

		// 描画処理
		m_pGear->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CToyCar::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// モデルの情報を設定する
	SetFileData(CXFile::TYPE_TOYCARBODY);

	if (m_pGear == nullptr)
	{ // 歯車の情報が NULL の場合

		// 歯車の生成
		m_pGear = CCarGear::Create(GetPos() + CAR_GEAR_SHIFT);
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CToyCar::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CToyCar::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	// false を返す
	return false;
}