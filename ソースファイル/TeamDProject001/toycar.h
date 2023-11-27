//===================================
//
// おもちゃの車ヘッダー[toycar.h]
// Author 小原立暉
//
//===================================
#ifndef _TOYCAR_H_
#define _TOYCAR_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CCarGear;			// 車の歯車

//-----------------------------------
// クラス定義(おもちゃの車)
//-----------------------------------
class CToyCar : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_DRIVE = 0,	// ドライブ状態
		STATE_CURVE,		// カーブ状態
		STATE_MAX			// この列挙型の総数
	};

	CToyCar();				// コンストラクタ
	~CToyCar();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);		// ヒット処理
	void Action(void) override;										// ギミック起動処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Drive(void);			// 走行処理
	void Curve(void);			// カービング処理
	void Check(void);			// 位置の確認処理
	void RotCalc(void);			// 方向の設定処理

	// メンバ変数
	D3DXVECTOR3 m_pPosInit;		// 初期位置
	CCarGear* m_pGear;			// 歯車の情報
	D3DXVECTOR3* m_pPosDest;	// 目的の位置
	STATE m_state;				// 状態
	int m_nPosDestNum;			// 目的の位置の総数
	int m_nPosDestIdx;			// 目的の位置の番号
	float m_fRotDest;			// 目的の向き
	bool m_bRight;				// 右向き状況
};

#endif