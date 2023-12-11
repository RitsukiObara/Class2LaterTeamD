//===================================
//
// 爆弾ヘッダー[dynamite.h]
// Author 堀川萩大
//
//===================================
#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// 前方宣言
//-----------------------------------


//-----------------------------------
// クラス定義(爆弾)
//-----------------------------------
class CDynamite : public CObstacle
{
public:			// 誰でもアクセスできる

				// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,		// 通常状態
		STATE_MINI,			// 縮小状態
		STATE_BIG,			// 拡大状態
		STATE_EXPLOSION,	// 爆発状態
		STATE_MAX			// この列挙型の総数
	};

	CDynamite();			// コンストラクタ
	~CDynamite();			// デストラクタ

							// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;						// ヒット処理
	void ChageScale(void);	// モデルサイズ変更処理
	void Explosion(void);	// 爆発処理
private:		// 自分だけアクセスできる
	
	// メンバ変数
	STATE m_state;				// 状態
	D3DXVECTOR3 m_Scale;		// 拡大率
	D3DXVECTOR3 m_pos;			// 位置
	bool m_bCatch;				// 持っているかどうか
	int m_nExplosion;			// 爆発タイミング
	int m_nDelTyming;			// 爆発の判定時間
};

#endif