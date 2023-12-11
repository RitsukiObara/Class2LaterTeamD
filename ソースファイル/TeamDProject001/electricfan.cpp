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
#include "Effect.h"
#include "collision.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define FAN_SHIFT		(175.0f)		// 扇風機の羽根のずらす高さ
#define WIND_RANGE		(1600.0f)		// 扇風機の風の範囲
#define WIND_MOVE		(11)			// 風エフェクトの移動量の幅
#define WIND_LIFE		(50)			// 風エフェクトの寿命
#define WIND_RADIUS		(40.0f)			// 風エフェクトの半径
#define FAN_MOVE_OFF	(0.0f)			// スイッチOFFの羽根の移動量
#define FAN_MOVE_ON		(0.5f)			// スイッチONの羽根の移動量

//==============================
// コンストラクタ
//==============================
CElecFan::CElecFan() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pFan = nullptr;			// 扇風機のファン
	m_bPower = false;			// 電源状況
	SetCatUse(true);
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
	if (m_bPower == true)
	{ // 電源がついている場合

		//D3DXVECTOR3 pos;		// 位置
		//D3DXVECTOR3 move;		// 移動量

		//// 位置を設定する
		//pos.x = GetPos().x + sinf(GetRot().y + (D3DX_PI * 0.5f)) * (rand() % (int)(GetFileData().vtxMax.x) - (int)(GetFileData().vtxMax.x * 0.5f));
		//pos.y = GetPos().y + rand() % (int)(GetFileData().vtxMax.y) + (int)(GetFileData().vtxMin.y);
		//pos.z = GetPos().z + cosf(GetRot().y + (D3DX_PI * 0.5f)) * (rand() % (int)(GetFileData().vtxMax.z) - (int)(GetFileData().vtxMax.z * 0.5f));

		//// 移動量を設定する
		//move.x = sinf(GetRot().y + D3DX_PI) * (rand() % WIND_MOVE + (WIND_MOVE * 0.5f));
		//move.y = 0.0f;
		//move.z = cosf(GetRot().y + D3DX_PI) * (rand() % WIND_MOVE + (WIND_MOVE * 0.5f));

		//// エフェクトを出す
		//CEffect::Create(pos, move, WIND_LIFE, WIND_RADIUS, CEffect::TYPE_WIND, NONE_D3DXCOLOR, true);
	}

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
void CElecFan::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

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
bool CElecFan::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置と最大値と最小値を設定する
	D3DXVECTOR3 playPos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(GetFileData().fRadius, GetFileData().vtxMax.y, GetFileData().fRadius);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-GetFileData().fRadius, GetFileData().vtxMin.y, -GetFileData().fRadius);
	D3DXVECTOR3 playMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 playMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	// 六面体の当たり判定
	if (collision::HexahedronCollision(&playPos, GetPos(), pPlayer->GetPosOld(), GetPosOld(), playMin, vtxMin, playMax, vtxMax) == true)
	{ // 当たり判定が true の場合

		// 位置を適用する
		pPlayer->SetPos(playPos);

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CElecFan::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_bPower == true)
	{ // 電源状況が true の場合

		// 各最大値・最小値を宣言
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(sinf(GetRot().y) * -WIND_RANGE, 0.0f, cosf(GetRot().y) * -WIND_RANGE);
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, GetFileData().vtxMax.y, 0.0f);
		D3DXVECTOR3 playerMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
		D3DXVECTOR3 playerMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);

		if (useful::RectangleCollisionXY(pPlayer->GetPos(), GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(pPlayer->GetPos(), GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(pPlayer->GetPos(), GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true)
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
bool CElecFan::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{//円の範囲内の場合trueを返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CElecFan::Action(void)
{
	// 電源を設定する
	m_bPower = !m_bPower;

	if (m_bPower == true)
	{ // 電源ONの場合

		// 目的の向きの移動量を設定する
		m_pFan->SetRotMoveDest(FAN_MOVE_ON);
		SetCatUse(false);
		SetRatUse(true);
	}
	else
	{ // 上記以外

		// 目的の向きの移動量を設定する
		m_pFan->SetRotMoveDest(FAN_MOVE_OFF);
		SetCatUse(true);
		SetRatUse(false);
	}
}