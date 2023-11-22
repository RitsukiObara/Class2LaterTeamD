//===========================================
//
// リードの処理[Himo.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "leash.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"

//==============================
// コンストラクタ
//==============================
CLeash::CLeash() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_bAction = false;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_bSetHead = false;
	m_bSetToes = false;
}

//==============================
// デストラクタ
//==============================
CLeash::~CLeash()
{

}

//==============================
// リードの初期化処理
//==============================
HRESULT CLeash::Init(void)
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
// リードの終了処理
//========================================
void CLeash::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// リードの更新処理
//=====================================
void CLeash::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (m_bSetHead == true && m_bSetToes == true)
	{
		m_bAction = true;
	}

	SetActionPos(pos, rot);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // Aボタンを押した場合
		m_bAction = m_bAction ? false : true;
	}

	SetPos(pos);
}

//=====================================
// リードの描画処理
//=====================================
void CLeash::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// ギミック起動位置の設定
//=====================================
void CLeash::SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ActionPosHead = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 1.0f)) * 300.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 1.0f)) * 300.0f);

	ActionPosToes = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.0f)) * 350.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.0f)) * 350.0f);

	CEffect::Create(ActionPosHead, NONE_D3DXVECTOR3, 20, 30.0f, CEffect::TYPE::TYPE_NONE, NONE_D3DXCOLOR, true);
	CEffect::Create(ActionPosToes, NONE_D3DXVECTOR3, 20, 30.0f, CEffect::TYPE::TYPE_NONE, NONE_D3DXCOLOR, true);
}

//=====================================
// 紐を引っ張られた時の処理
//=====================================
void CLeash::Action(void)
{
	m_bAction = true;
}

//=====================================
// 情報の設定処理
//=====================================
void CLeash::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CLeash::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CLeash::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	//// 終了処理
	//Uninit();

	// false を返す
	return false;
}