//===================================
//
// 蜂蜜ヘッダー[honey.h]
// Author 小原立暉
//
//===================================
#ifndef _HONEY_H_
#define _HONEY_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(蜂蜜)
//-----------------------------------
class CHoney : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum State
	{
		STATE_HONEYBOTTLE = 0,	// ボトル
		STATE_HONEY,			// 液体
		STATE_MAX				// この列挙型の総数
	};

	CHoney();				// コンストラクタ
	~CHoney();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// ヒット処理

private:		// 自分だけアクセスできる
	void Break(void);
	void StateManager(void);

	State m_State;
};

#endif