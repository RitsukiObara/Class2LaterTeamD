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
// クラス定義(おもちゃの車)
//-----------------------------------
class CToyCar : public CObstacle
{
public:			// 誰でもアクセスできる

	CToyCar();				// コンストラクタ
	~CToyCar();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// ヒット処理

private:		// 自分だけアクセスできる

	// メンバ変数
};

#endif