//===================================
//
// プラスチックケースヘッダー[plastic_case.h]
// Author 堀川萩大
//
//===================================
#ifndef _PLASTICCASE_H_
#define _PLASTICCASE_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(プラスチックケース)
//-----------------------------------
class CPlasticCase : public CObstacle
{
public:			// 誰でもアクセスできる

	CPlasticCase();			// コンストラクタ
	~CPlasticCase();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// ヒット処理

private:		// 自分だけアクセスできる

};

#endif