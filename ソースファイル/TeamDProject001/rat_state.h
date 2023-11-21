//===================================
//
// ネズミの状態ヘッダー[rat_state.h]
// Author 小原立暉
//
//===================================
#ifndef _RAT_STATE_H_
#define _RAT_STATE_H_

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CRat;			// ネズミ

//--------------------------------------------
// クラス(ネズミの状態クラス)
//--------------------------------------------
class CRatState
{
public:			// 誰でもアクセスできる

	CRatState();	// コンストラクタ
	~CRatState();	// デストラクタ

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_WAIT = 0,			// 待機状態
		STATE_RUN,				// 走行状態
		STATE_ATTACK,			// 攻撃状態
		STATE_INVINCIBLE,		// 無敵状態
		STATE_DAMAGE,			// ダメージ状態
		STATE_SMASH,			// 吹き飛び状態
		STATE_STUN,				// 気絶状態
		STATE_DEATH,			// 死亡状態
		STATE_MAX				// この列挙型の総数
	};

	// メンバ関数
	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(CRat& pRat);	// 更新処理

	// セット・ゲット関係
	void SetState(const STATE state);		// 状態の設定処理
	STATE GetState(void);					// 状態の取得処理

private:		// 自分だけアクセスできる

	// メンバ変数
	STATE m_State;				// ネズミの状態
	int m_nStateCount;			// 状態カウント
};

#endif