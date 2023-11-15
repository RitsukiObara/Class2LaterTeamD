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
#include "file.h"
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
	m_pPosInit = NONE_D3DXVECTOR3;	// 初期位置
	m_pGear = nullptr;				// 歯車の情報
	m_pPosDest = nullptr;			// 目的の位置
	m_nPosDestNum = 0;				// 目的の位置の総数
	m_nPosDestIdx = 0;				// 目的の位置の番号
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
	m_pPosInit = NONE_D3DXVECTOR3;	// 初期位置
	m_pGear = nullptr;				// 歯車の値
	m_pPosDest = nullptr;			// 目的の位置
	m_nPosDestNum = 0;				// 目的の位置の総数
	m_nPosDestIdx = 0;				// 目的の位置の番号

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
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 走行処理
	CarDrive();

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
	// 車の経路を設定する
	int nType = rand() % CManager::Get()->GetFile()->GetCarRouteNum();

	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// モデルの情報を設定する
	SetFileData(CXFile::TYPE_TOYCARBODY);

	if (m_pGear == nullptr)
	{ // 歯車の情報が NULL の場合

		// 歯車の生成
		m_pGear = CCarGear::Create(GetPos() + CAR_GEAR_SHIFT);
	}

	// 全ての値を設定する
	m_pPosInit = pos;		// 初期位置
	m_nPosDestIdx = 0;		// 目的の位置の番号
	m_nPosDestNum = CManager::Get()->GetFile()->GetCarRouteNumPos(nType);		// 目的の位置の総数
	m_pPosDest = CManager::Get()->GetFile()->GetCarRoute(nType);				// 目的の位置のポインタ

	// 目的地への向きの計算処理
	RotCalc();
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

//=====================================
// 走行処理
//=====================================
void CToyCar::CarDrive(void)
{
	// 情報を取得する
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き

	// 移動させる
	pos.x += sinf(rot.y) * -6.0f;
	pos.z += cosf(rot.y) * -6.0f;

	// 位置を適用する
	SetPos(pos);

	if (m_pPosDest != nullptr)
	{ // 位置が NULL じゃない場合

		// 位置の確認処理
		Check();
	}
}

//=====================================
// 位置の確認処理
//=====================================
void CToyCar::Check(void)
{
	// 情報を取得する
	D3DXVECTOR3 pos = GetPos();			// 位置を取得する
	D3DXVECTOR3 posOld = GetPosOld();	// 前回の位置を取得する

	if (((m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x >= posOld.x && m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x <= pos.x) ||
		(m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x <= posOld.x && m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x >= pos.x)) ||
		((m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z >= posOld.z && m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z <= pos.z) ||
		(m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z <= posOld.z && m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z >= pos.z)))
	{ // 位置が目的地を超えた場合

		// 位置を補正する
		pos = m_pPosInit + m_pPosDest[m_nPosDestIdx];

		// 総数を変える
		m_nPosDestIdx = (m_nPosDestIdx + 1) % m_nPosDestNum;

		// 向きの設定処理
		RotCalc();
	}
}

//=====================================
// 方向の設定処理
//=====================================
void CToyCar::RotCalc(void)
{
	// 情報を取得する
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き

	// 向きを設定する
	rot.y = atan2f(pos.x - (m_pPosInit.x + m_pPosDest[m_nPosDestIdx].x), pos.z - (m_pPosInit.z + m_pPosDest[m_nPosDestIdx].z));

	// 向きを設定する
	SetRot(rot);
}