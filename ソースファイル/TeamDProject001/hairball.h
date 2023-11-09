//===================================
//
// 毬ヘッダー[hairball.h]
// Author 小原立暉
//
//===================================
#ifndef _HAIRBALL_H_
#define _HAIRBALL_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(毬)
//-----------------------------------
class CHairBall : public CObstacle
{
public:			// 誰でもアクセスできる

	CHairBall();			// コンストラクタ
	~CHairBall();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// ヒット処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Gravity(void);			// 重力処理
	void Elevation(void);		// 起伏地面の当たり判定

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
};

#endif