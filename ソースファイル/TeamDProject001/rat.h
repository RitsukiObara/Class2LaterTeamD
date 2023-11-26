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
#include "player.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CRatState;			// ネズミの状態
class CRatGhost;			// 幽霊ネズミ
class CRessrectionFan;		// 円の範囲

//--------------------------------------------
// クラス(ネズミクラス)
//--------------------------------------------
class CRat : public CPlayer
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
		MOTIONTYPE_ATTACK,			// 攻撃
		MOTIONTYPE_JUMP,			// ジャンプ
		MOTIONTYPE_DEATH,			// 死亡
		MOTIONTYPE_RESURRECTION,	// 蘇生
		MOTIONTYPE_MAX				// この列挙型の総数
	};

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void Hit(void);					// ヒット処理
	void Smash(const float fAngle);	// 吹き飛び状態
	void Stun(void);				// 気絶状態
	void MotionManager(void);		// モーションの管理

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);	// 情報の設定処理

	// セット・ゲット関係
	int GetRatIdx(void) const;				// ネズミの番号の取得処理
	CRatState* GetState(void);				// ネズミの状態の取得処理
	CRatGhost* GetRatGhost(void);			// 幽霊ネズミの取得処理
	void DeleteRatGhost(void);				// 幽霊ネズミの消去処理
	CRessrectionFan* GetRessrectionFan(void);			// 円の範囲の取得処理
	void DeleteRessrectionFan(void);					// 円の範囲の消去処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Jump(void);				// ジャンプ処理
	void Attack(void);				// 攻撃処理
	void Elevation(void);			// 起伏地面の当たり判定
	void ResurrectionCollision(void);		// 生き返りの当たり判定

	// メンバ変数
	CRatState* m_pRatState;		// ネズミの状態の情報
	CRatGhost* m_pRatGhost;		// 幽霊ネズミの情報
	CRessrectionFan* m_pRessrectionFan;		// 円の範囲の情報
	int m_nRatIdx;				// ネズミの番号
	bool m_bJump;				// ジャンプ状況

	// 静的メンバ関数
	static int m_nNumAll;		// ネズミの総数
	static int m_nResurrectionCounter;		// 生き返るまでのカウンター

};

#endif