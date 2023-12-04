//===================================
//
// 蜂蜜ヘッダー[honey.h]
// Author 小原立暉
//
//===================================
#ifndef _GARBAGECAN_H_
#define _GARBAGECAN_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(蜂蜜)
//-----------------------------------
class CGarbage : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum State
	{
		STATE_GARBAGECAN = 0,	// ボトル
		STATE_GARBAGE,			// 液体
		STATE_MAX				// この列挙型の総数
	};

	CGarbage();				// コンストラクタ
	~CGarbage();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);		// ヒット処理
	void Action(void) override;										// ギミック起動処理

private:		// 自分だけアクセスできる
	void Break(void);
	void StateManager(void);

	State m_State;
};

#endif