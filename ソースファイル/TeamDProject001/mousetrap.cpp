//===========================================
//
// ネズミ捕りのメイン処理[mousetrap.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "mousetrap.h"
#include "obstacle.h"
#include "mousetrap_iron.h"
#include "danger_mark.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define IRON_SHIFT			(10.0f)		// 鉄部分のずらす位置
#define DANGER_SHIFT		(200.0f)	// 危険マークのずらす位置

//==============================
// コンストラクタ
//==============================
CMouseTrap::CMouseTrap() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pIron = nullptr;			// 鉄部分
	m_pMark = nullptr;			// 危険マークの情報
}

//==============================
// デストラクタ
//==============================
CMouseTrap::~CMouseTrap()
{

}

//==============================
// ネズミ捕りの初期化処理
//==============================
HRESULT CMouseTrap::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	m_pIron = nullptr;			// 鉄部分
	m_pMark = nullptr;			// 危険マークの情報

	// 値を返す
	return S_OK;
}

//========================================
// ネズミ捕りの終了処理
//========================================
void CMouseTrap::Uninit(void)
{
	if (m_pIron != nullptr)
	{ // 鉄部分が NULL じゃない場合

		// 鉄部分の終了処理
		m_pIron->Uninit();
		m_pIron = nullptr;
	}

	if (m_pMark != nullptr)
	{ // マークが NULL じゃない場合

		// マークの終了処理
		m_pMark->Uninit();
		m_pMark = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ネズミ捕りの更新処理
//=====================================
void CMouseTrap::Update(void)
{
	if (m_pIron != nullptr)
	{ // 鉄部分が NULL じゃない場合

		// 鉄部分の位置設定処理
		IronPosSet();

		// 鉄部分の更新処理
		m_pIron->Update();
	}
}

//=====================================
// ネズミ捕りの描画処理
//=====================================
void CMouseTrap::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	if (m_pIron != nullptr)
	{ // 鉄部分が NULL じゃない場合

		// 鉄部分の描画処理
		m_pIron->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CMouseTrap::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);

	// 全ての値を設定する
	if (m_pIron == nullptr)
	{ // 鉄部分が NULL の場合

		// 鉄部分を生成
		m_pIron = CTrapIron::Create(D3DXVECTOR3(pos.x, pos.y + IRON_SHIFT, pos.z));
	}

	if (m_pMark == nullptr)
	{ // マークが NULL の場合

		// 危険マークの生成
		m_pMark = CDangerMark::Create(D3DXVECTOR3(pos.x, pos.y + DANGER_SHIFT, pos.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CMouseTrap::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CMouseTrap::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CMouseTrap::Action(void)
{

}

//=====================================
// 鉄部分の位置の設定処理
//=====================================
void CMouseTrap::IronPosSet(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();					// 位置を取得する
	D3DXVECTOR3 posIron = NONE_D3DXVECTOR3;		// 鉄の部分

	// 鉄の部分の位置を設定する
	posIron.x = pos.x;
	posIron.y = pos.y + IRON_SHIFT;
	posIron.z = pos.z;

	// 位置を適用する
	m_pIron->SetPos(posIron);
}