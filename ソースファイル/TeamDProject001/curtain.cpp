//===========================================
//
// カーテンの処理[curtain.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "curtain.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CCurtain::CCurtain() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	SetCatUse(false);				// ネコの使用条件
	SetRatUse(true);				// ネズミの使用条件
}

//==============================
// デストラクタ
//==============================
CCurtain::~CCurtain()
{

}

//==============================
// カーテンの初期化処理
//==============================
HRESULT CCurtain::Init(void)
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
// カーテンの終了処理
//========================================
void CCurtain::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// カーテンの更新処理
//=====================================
void CCurtain::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());
}

//=====================================
// カーテンの描画処理
//=====================================
void CCurtain::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CCurtain::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);
}