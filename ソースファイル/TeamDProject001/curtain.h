//===================================
//
// カーテンヘッダー[curtain.h]
// Author 小原立暉
//
//===================================
#ifndef _CURTAIN_H_
#define _CURTAIN_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(カーテン)
//-----------------------------------
class CCurtain : public CObstacle
{
public:			// 誰でもアクセスできる

	CCurtain();				// コンストラクタ
	~CCurtain();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

private:		// 自分だけアクセスできる

};

#endif