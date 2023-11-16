//===========================================
//
// プラスチックケースのメイン処理[plastic_case.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "plastic_case.h"
#include "useful.h"
#include "fraction.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY		(0.5f)		// 重力
#define NUM_FRAC	(4)			// 破片の数

//==============================
// コンストラクタ
//==============================
CPlasticCase::CPlasticCase() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
}

//==============================
// デストラクタ
//==============================
CPlasticCase::~CPlasticCase()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CPlasticCase::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CPlasticCase::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CPlasticCase::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CPlasticCase::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CPlasticCase::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CPlasticCase::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CPlasticCase::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth)
{
	//// 破片の出る高さ
	//float fFracHeight;

	//for (int nCnt = 0; nCnt < NUM_FRAC; nCnt++)
	//{
	//	fFracHeight = (float)(rand() % (int)(GetFileData().vtxMax.y) - (int)(GetFileData().vtxMin.y));

	//	// 破片を生成
	//	CFraction::Create(D3DXVECTOR3(GetPos().x, GetPos().y + fFracHeight, GetPos().z), CFraction::TYPE::TYPE_PRASTICRVASE);
	//}

	//// 終了処理
	//Uninit();

	// false を返す
	return false;
}