//===========================================
//
// ラットの状態のメイン処理[rat_state.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "rat_state.h"
#include "rat.h"

// マクロ定義
#define INVINCIBLE_COUNT	(60)			// 無敵状態のカウント数
#define SMASH_COUNT			(40)			// 吹き飛び状態のカウント数
#define DAMAGE_COUNT		(10)			// ダメージ状態のカウント数

//==============================
// コンストラクタ
//==============================
CRatState::CRatState()
{
	// 全ての値をクリアする
	m_State = STATE_WAIT;	// 状態
	m_nStateCount = 0;		// 状態カウント
}

//==============================
// デストラクタ
//==============================
CRatState::~CRatState()
{

}

//==============================
// 初期化処理
//==============================
HRESULT CRatState::Init(void)
{
	// 全ての値をクリアする
	m_State = STATE_WAIT;	// 状態
	m_nStateCount = 0;		// 状態カウント

	// OKを返す
	return S_OK;
}

//==============================
// 終了処理
//==============================
void CRatState::Uninit(void)
{

}

//==============================
// 更新処理
//==============================
void CRatState::Update(CRat& pRat)
{
	// 状態カウントを加算する
	m_nStateCount++;

	switch (m_State)
	{
	case STATE_WAIT:		// 待機状態
		break;
	case STATE_RUN:			// 走行状態
		break;
	case STATE_ATTACK:		// 攻撃状態
		break;
	case STATE_INVINCIBLE:	// 無敵状態

		if (m_nStateCount >= INVINCIBLE_COUNT)
		{ // 状態カウントが一定以上になった場合

			// 通常状態にする
			m_State = STATE_WAIT;

			// 状態カウントを初期化する
			m_nStateCount = 0;
		}

		break;

	case STATE_DAMAGE:		// ダメージ状態

		if (m_nStateCount >= DAMAGE_COUNT)
		{ // 状態カウントが一定数に達した場合

			// 無敵状態にする
			m_State = STATE_INVINCIBLE;

			// 状態カウントを初期化する
			m_nStateCount = 0;
		}

		break;

	case STATE_SMASH:		// 吹き飛び状態

		if (m_nStateCount >= SMASH_COUNT)
		{ // 状態カウントが一定以上になった場合

			// 通常状態にする
			m_State = STATE_WAIT;

			// 状態カウントを初期化する
			m_nStateCount = 0;
		}

		break;

	case STATE_STUN:		// 気絶状態

		break;

	case STATE_DEATH:		// 死亡状態

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//==============================
// 状態の設定処理
//==============================
void CRatState::SetState(const STATE state)
{
	// 状態を設定する
	m_State = state;

	// 状態カウントを初期化する
	m_nStateCount = 0;
}

//==============================
// 状態の取得処理
//==============================
CRatState::STATE CRatState::GetState(void)
{
	// 状態を返す
	return m_State;
}