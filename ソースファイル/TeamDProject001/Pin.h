//===================================
//
// ピンヘッダー[Pin.h]
// Author 坂本翔唯
//
//===================================
#ifndef _PIN_H_
#define _PIN_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(リード)
//-----------------------------------
class CPin : public CObstacle
{
public:			// 誰でもアクセスできる

	CPin();				// コンストラクタ
	~CPin();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// ヒット処理
	void Action(void) override;

private:		// 自分だけアクセスできる
	D3DXVECTOR3 m_move;			//移動量
	bool m_bAction;				//起動しているかどうか
};

#endif