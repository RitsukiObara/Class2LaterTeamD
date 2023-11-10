//============================================
//
// 猫ヘッダー[Cat.h]
// Author：坂本翔唯
//
//============================================
#ifndef _CAT_H_					// このマクロ定義がされていなかったら
#define _CAT_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "character.h"
#include "scene.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMotion;				// モーション
class CCatAct;			// プレイヤーの行動
class CAbility;				// 能力
class CScrewUI;				// ネジUI
class CCombo;				// コンボ
class CBlock;				// ブロック
class CLifeUI;				// 体力UI
class CPushTiming;			// 押すタイミング

//--------------------------------------------
// クラス(プレイヤークラス)
//--------------------------------------------
class CCat : public CCharacter
{
public:			// 誰でもアクセスできる

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

	CCat();				// コンストラクタ
	~CCat();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void Hit(void);			// ヒット処理
	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

												// セット・ゲット関係
	void SetMove(const D3DXVECTOR3& move);		// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;			// 移動量の取得処理
	void SetRotDest(const D3DXVECTOR3& rot);	// 目標の向きの設定処理
	D3DXVECTOR3 GetRotDest(void) const;			// 目標の向きの取得処理
	void SetSpeed(float fSpeed);				// 速度の設定処理
	float GetSpeed(void) const;					// 速度の取得処理
	void SetAlpha(const float fAlpha);			// 透明度の設定処理
	void SwapAlpha(void);						// 透明度の入れ替え処理
	float GetAlpha(void) const;					// 透明度の取得処理
	void SetEnableMove(bool bMove);				// 移動状況の設定処理
	bool IsMove(void) const;					// 移動状況の取得処理

	CMotion* GetMotion(void) const;				// モーションの情報の取得処理
	CCatAct* GetAction(void) const;			// アクションの情報の取得処理

	// 静的メンバ関数
	static CCat* Get(void);					// 取得処理
	static CCat* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void CollisionMagicWall(void);	// 移動制限判定

	void StartProcess(void);		// スタート状態の処理
	void GoalProcess(void);			// ゴール状態の処理
	void LeaveProcess(void);		// 退場状態の処理
	void FinishProcess(void);		// 終了状態の処理

	// メンバ変数
	CMotion* m_pMotion;				// モーションの情報
	CCatAct* m_pAction;			// プレイヤーの行動の情報

	D3DXVECTOR3 m_posDest;			// 目的の位置
	D3DXVECTOR3 m_move;				// 移動量
	D3DXVECTOR3 m_rotDest;			// 目的の向き
	int m_nShadowIdx;				// 影のインデックス
	int m_nStartCount;				// スタートカウント
	int m_nGoalCount;				// ゴール時のカウント
	float m_fSpeed;					// 速度
	float m_fAlpha;					// 透明度
	bool m_bMove;					// 移動状況

	// 静的メンバ変数
	static CCat* m_pPlayer;		// プレイヤーのポインタ
};

#endif