//===================================
//
// ラットヘッダー[rat.h]
// Author 小原立暉
//
//===================================
#ifndef _RAT_H_
#define _RAT_H_

//********************************************
// インクルードファイル
//********************************************
#include "character.h"
#include "scene.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMotion;				// モーション

//--------------------------------------------
// クラス(ネズミクラス)
//--------------------------------------------
class CRat : public CCharacter
{
public:			// 誰でもアクセスできる

	CRat();			// コンストラクタ
	~CRat();			// デストラクタ

	//************************************************************
	//	列挙型定義(モーションの種類)
	//************************************************************
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// 待機
		MOTIONTYPE_MOVE,			// 移動
		MOTIONTYPE_JUMP,			// ジャンプ
		MOTIONTYPE_MAX				// この列挙型の総数
	};

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0, // 何でもない状態
		STATE_WAIT,     // 待機状態
		STATE_RUN,      // 走行状態
		STATE_ATTACK,   // 攻撃状態
		STATE_MUTEKI,	// 無敵状態
		STATE_DAMAGE,	// ダメージ状態
		STATE_DEATH,    // 死亡状態
		STATE_MAX
	};

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// セット・ゲット関係
	void SetMove(const D3DXVECTOR3& move);	// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;		// 移動量の取得処理
	void SetSpeed(const float fSpeed);		// 速度の設定処理
	float GetSpeed(void) const;				// 速度の取得処理
	void SetRatIdx(const int nIdx);			// ネズミの番号の設定処理
	int GetRatIdx(void) const;				// ネズミの番号の取得処理
	void SetState(STATE state);				// ネズミの状態の設定処理
	STATE GetState(void);					// ネズミの状態の取得処理

	// 静的メンバ関数
	static CRat* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Move(void);				// 移動処理
	void Jump(void);				// ジャンプ処理
	void Attack(void);				// 攻撃処理
	void Elevation(void);			// 起伏地面の当たり判定
	void ObstacleCollision(void);	// 障害物との当たり判定
	void Hit(void);					// ヒット処理

	// メンバ変数
	CMotion* m_pMotion;			// モーションの情報
	D3DXVECTOR3 m_move;			// 移動量
	int m_nRatIdx;				// ネズミの番号
	int m_nLife;				// 寿命
	int m_nDamageCounter;		// ダメージ食らうまでのカウンター
	float m_fSpeed;				// 速度
	bool m_bJump;				// ジャンプしたか
	bool m_bLand;				// 着地したか
	bool m_bAttack;				// 攻撃したか
	STATE m_State;				// ネズミの状態
};

#endif