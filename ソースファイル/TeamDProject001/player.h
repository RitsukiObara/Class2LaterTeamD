//===================================
//
// プレイヤーヘッダー[player.h]
// Author 小原立暉
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//********************************************
// インクルードファイル
//********************************************
#include "character.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMotion;				// モーション
class CPlayerID;			// プレイヤーのID
class CStun;				// 気絶

//--------------------------------------------
// クラス(プレイヤークラス)
//--------------------------------------------
class CPlayer : public CCharacter
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_CAT = 0,		// ネコ
		TYPE_RAT,			// ネズミ
		TYPE_MAX			// この列挙型の総数
	};

	// 列挙型定義(気絶用状態)
	enum STUNSTATE
	{
		STUNSTATE_NONE = 0,
		STUNSTATE_STUN,
		STUNSTATE_WAIT,
		STUNSTATE_MAX,
	};

	// 列挙型定義(気絶用状態)
	enum STATE
	{
		STATE_NONE = 0,
		STATE_WAIT,
		STATE_DEATH,
		STATE_MAX,
	};

	CPlayer();				// コンストラクタ
	CPlayer(CObject::TYPE type, PRIORITY priority = PRIORITY_PLAYER);				// オーバーロードコンストラクタ
	virtual ~CPlayer();		// デストラクタ
	void Box(void);			// コンストラクタの箱

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	virtual void Hit(void) = 0;					// ヒット処理
	virtual void Smash(const float fAngle);		// 吹き飛び状態
	void Stun(int StunTime);					// 気絶状態
	virtual void MotionManager(void) = 0;		// モーションマネージャー

	virtual void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// 情報の設定処理

	// セット・ゲット関係
	void SetMotion(CMotion* pMotion);			// モーションの設定処理
	CMotion* GetMotion(void) const;				// モーションの取得処理

	CPlayerID* GetPlayerID(void) const;			// プレイヤーIDの情報の取得処理

	void SetStun(const D3DXVECTOR3& pos);		// 気絶演出の設定処理
	CStun* GetStun(void) const;					// 気絶演出の取得処理
	void DeleteStun(void);						// 気絶演出の消去処理

	void SetMove(const D3DXVECTOR3& move);		// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;			// 移動量の取得処理

	void SetSizeColl(const D3DXVECTOR3& size);	// 当たり判定サイズの設定処理

	void SetType(const TYPE type);				// 種類の設定処理
	TYPE GetType(void) const;					// 種類の取得処理

	void SetLife(const int nLife);				// 寿命の設定処理
	int GetLife(void) const;					// 寿命の取得処理

	int GetPlayerIdx(void) const;				// プレイヤーのIDの取得処理

	void SetSpeed(const float fSpeed);			// 速度の設定処理
	float GetSpeed(void) const;					// 速度の取得処理

	void SetEnableAttack(const bool bAttack);	// 攻撃判定の設定処理
	bool IsAttack(void) const;					// 攻撃判定の取得処理

	void SetEnableMove(const bool bMove);		// 移動状況の設定処理
	bool IsMove(void) const;					// 移動状況の取得処理

	void SetStunState(STUNSTATE StunState) { m_StunState = StunState; }	// 気絶状態の設定処理
	STUNSTATE GetStunState(void) { return m_StunState; }				// 気絶状態の取得処理

	void SetState(STATE State) { m_State = State; }		// 状態の設定処理
	STATE GetState(void) { return m_State; }			// 状態の取得処理

	// 静的メンバ関数
	static CPlayer* Create(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// 生成処理

protected:		// 自分と派生クラスだけがアクセスできる

	// メンバ関数
	void Move(void);		// 移動処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void ObstacleCollision(void);		// 障害物との当たり判定
	void StunStateManager(void);		// 気絶状態の管理
	void StateManager(void);			// 状態の管理
	void CameraUpdate(void);			// カメラ情報の更新

	// メンバ変数
	CMotion* m_pMotion;			// モーションの情報
	CPlayerID* m_pPlayerID;		// プレイヤーのID
	CStun* m_pStun;				// 気絶の情報
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_sizeColl;		// 当たり判定のサイズ
	TYPE m_type;				// 種類
	int m_nLife;				// 寿命
	int m_nPlayerIdx;			// プレイヤーのインデックス
	float m_fSpeed;				// 速度
	bool m_bAttack;				// 攻撃したか
	bool m_bMove;				// 移動しているか
	bool m_bDeath;				// 死亡しているか
	STUNSTATE m_StunState;		// 気絶の状態管理
	int m_StunStateCount;		// 状態管理用カウント
	STATE m_State;				// 状態管理
	int m_StateCount;			// 状態管理用カウント
	D3DXVECTOR3 m_CameraRot;	// カメラの向き
};

#endif