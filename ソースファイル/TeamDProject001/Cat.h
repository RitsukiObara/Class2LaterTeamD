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

	void Hit(void);			// ヒット処理
	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	// セット・ゲット関係

	CMotion* GetMotion(void) const;				// モーションの情報の取得処理

	// 静的メンバ関数
	static CCat* Get(void);					// 取得処理
	static CCat* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void MoveAttackPos();
	void Attack();
	void AttackStateManager();
	void CollisionMagicWall();
	void DebugMessage();

	// メンバ変数
	CMotion* m_pMotion;				// モーションの情報

	D3DXVECTOR3 m_AttackPos;		// 攻撃の位置
	D3DXVECTOR3 m_posDest;			// 目的の位置
	D3DXVECTOR3 m_move;				// 移動量
	D3DXVECTOR3 m_rotDest;			// 目的の向き
	int m_nShadowIdx;				// 影のインデックス

	ATTACKSTATE m_AttackState;		// 攻撃の状態
	int m_nAtkStateCount;			// 攻撃の状態のカウント

	// 静的メンバ変数
	static CCat* m_pPlayer;		// プレイヤーのポインタ
};

#endif