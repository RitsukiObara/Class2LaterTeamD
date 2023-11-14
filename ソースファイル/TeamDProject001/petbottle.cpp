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
#define GRAVITY		(0.5f)		// 重力

//==============================
// コンストラクタ
//==============================
CPetbottle::CPetbottle() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;
}

//==============================
// デストラクタ
//==============================
CPetbottle::~CPetbottle()
{

}

//==============================
// 転がるの初期化処理
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

	// 値を返す
	return S_OK;
}

//========================================
// 転がるの終了処理
//========================================
void CPetbottle::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 転がるの更新処理
//=====================================
void CPetbottle::Update(void)
{
	//ペットボトルが周る処理
	D3DXVECTOR3 rot = GetRot();
	rot.z += 0.01f;
	SetRot(rot);

	D3DXVECTOR3 pos = GetPos();
	pos.x += m_move.x;
	SetPos(pos);

	m_move.x = - 10.0f;

	// 重力処理
	Gravity();

	// 起伏地面との当たり判定
	Elevation();
}

//=====================================
// 転がるの描画処理
//=====================================
void CPetbottle::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CPetbottle::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// モデルの情報を設定する
	SetFileData(CXFile::TYPE_PETBOTTLE);
}

//=====================================
// ヒット処理
//=====================================
bool CPetbottle::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	// false を返す
	return false;
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

			// 移動量を減算する
			m_move.y *= -0.6f;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}