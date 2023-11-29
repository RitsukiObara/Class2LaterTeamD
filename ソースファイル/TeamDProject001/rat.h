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
	void MotionManager(void);		// モーションの管理

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);	// 情報の設定処理

	// セット・ゲット関係
	int GetRatIdx(void) const;				// ネズミの番号の取得処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Jump(void);				// ジャンプ処理
	void Attack(void);				// 攻撃処理
	void Elevation(void);			// 起伏地面の当たり判定
	void ResurrectionCollision(void);		// 生き返りの当たり判定

	// メンバ変数
	int m_nRezCounter;				// 回復するまでのカウンター
	bool m_bJump;					// ジャンプ状況

	// 静的メンバ関数
	//static int m_nNumAll;			// ネズミの総数
	static bool m_bResurrection;	// 復活させてるのか

};

#endif