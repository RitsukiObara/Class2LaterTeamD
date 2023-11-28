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
#include "player.h"

//--------------------------------------------
// クラス(プレイヤークラス)
//--------------------------------------------
class CCat : public CPlayer
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

	enum ATTACKSTATE
	{
		ATTACKSTATE_MOVE = 0,		// 移動
		ATTACKSTATE_STANDBY,		// スタンバイ
		ATTACKSTATE_ATTACK,			// 攻撃中
		ATTACKSTATE_MAX				// この列挙型の総数
	};

	CCat();				// コンストラクタ
	~CCat();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void Hit(void);						// ヒット処理
	void Smash(const float fAngle);		// 吹き飛び状態
	void MotionManager(void);			// モーションマネージャー

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// 情報の設定処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Attack();
	void AttackStateManager();
	void DebugMessage();

	// メンバ変数
	D3DXVECTOR3 m_AttackPos;		// 攻撃の位置
	D3DXVECTOR3 m_posDest;			// 目的の位置
	D3DXVECTOR3 m_rotDest;			// 目的の向き
	int m_nShadowIdx;				// 影のインデックス

	ATTACKSTATE m_AttackState;		// 攻撃の状態
	int m_nAtkStateCount;			// 攻撃の状態のカウント
};

#endif