//===================================
//
// ひもヘッダー[Himo.h]
// Author 坂本翔唯
//
//===================================
#ifndef _HIMO_H_
#define _HIMO_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

#define MAX_TARAI		(5)	// たらいの落下最大数

class CModel;

//-----------------------------------
// クラス定義(ひも)
//-----------------------------------
class CHimo : public CObstacle
{
public:			// 誰でもアクセスできる

	CHimo();				// コンストラクタ
	~CHimo();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// ヒット処理

private:		// 自分だけアクセスできる
	void ActionDown(void);

	CModel *m_apSub[MAX_TARAI];
	bool m_bAction;
};

#endif