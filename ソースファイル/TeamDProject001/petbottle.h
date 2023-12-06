//===================================
//
// ペットボトルヘッダー[petbottle.h]
// Author 大野祥平
//
//===================================
#ifndef _PETBOTTLE_H_
#define _PETBOTTLE_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(ペットボトル)
//-----------------------------------
class CPetbottle : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_STAND = 0,	// 通常状態
		STATE_COLLAPSE,		// 倒れ状態
		STATE_MAX			// この列挙型の総数
	};

	CPetbottle();			// コンストラクタ
	~CPetbottle();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;		// ヒット処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Cycle(void);								// 回転処理
	void Gravity(void);								// 重力処理
	void Elevation(void);							// 起伏地面の当たり判定
	void Collapse(const D3DXVECTOR3& posPlayer);	// 倒れる処理
	bool MagicWall(void);							// 魔法の壁処理

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
	STATE m_state;				// 状態
};
#endif