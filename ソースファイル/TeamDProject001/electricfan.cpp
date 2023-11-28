//===========================================
//
// 扇風機の処理[electricfan.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "electricfan.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"

#include "fan_blade.h"
#include "input.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define FAN_SHIFT		(175.0f)		// 扇風機の羽根のずらす高さ
#define WIND_CIRCUM		(80.0f)			// 扇風機の風の円周の大きさ
#define WIND_HEIGHT		(1600.0f)		// 扇風機の風の高さ

//==============================
// コンストラクタ
//==============================
CElecFan::CElecFan() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pFan = nullptr;			// 扇風機のファン
	m_bPower = false;			// 電源状況
}

//==============================
// デストラクタ
//==============================
CElecFan::~CElecFan()
{

}

//==============================
// 扇風機の初期化処理
//==============================
HRESULT CElecFan::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pFan = nullptr;			// 扇風機のファン
	m_bPower = false;			// 電源状況

	// 値を返す
	return S_OK;
}

//========================================
// 扇風機の終了処理
//========================================
void CElecFan::Uninit(void)
{
	if (m_pFan != nullptr)
	{ // ファンが NULL じゃない場合

		// ファンの終了処理
		m_pFan->Uninit();
		m_pFan = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 扇風機の更新処理
//=====================================
void CElecFan::Update(void)
{
	if (m_pFan != nullptr)
	{ // ファンが NULL じゃない場合

		// ファンの更新処理
		m_pFan->Update();
	}
}

//=====================================
// 扇風機の描画処理
//=====================================
void CElecFan::Draw(void)
{	
	// 描画処理
	CObstacle::Draw();

	if (m_pFan != nullptr)
	{ // ファンが NULL じゃない場合

		// ファンの描画処理
		m_pFan->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CElecFan::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// 全ての値を設定する
	if (m_pFan == nullptr)
	{ // ファンが NULL だった場合

		// 羽根の位置
		D3DXVECTOR3 posFan;

		// 羽根の位置を設定する
		posFan.x = pos.x;
		posFan.y = pos.y + FAN_SHIFT;
		posFan.z = pos.z;

		// ファンを生成する
		m_pFan = CFanBlade::Create(posFan);
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CElecFan::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CElecFan::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	if (m_bPower == true)
	{ // 電源状況が true の場合

		// 各最大値・最小値を宣言
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(sinf(GetRot().y) * -WIND_HEIGHT, 0.0f, cosf(GetRot().y) * -WIND_HEIGHT);
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, GetFileData().vtxMax.y, 0.0f);
		D3DXVECTOR3 playerMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);
		D3DXVECTOR3 playerMax = D3DXVECTOR3(fWidth, fHeight, fDepth);

		if (useful::RectangleCollisionXY(pos, GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(pos, GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(pos, GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true)
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
bool CElecFan::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	// false を返す
	return true;
}

//=====================================
// ギミック起動処理
//=====================================
void CElecFan::Action(void)
{
	// 電源ONにする
	m_bPower = true;
}