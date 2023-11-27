//===================================
//
// マッチングの枠ヘッダー[match_frame.h]
// Author 小原立暉
//
//===================================
#ifndef _MATCH_FRAME_H_
#define _MATCH_FRAME_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス定義(CMatchFrame)
//-----------------------------------
class CMatchFrame : public CObject2D
{
public:			// 誰でもアクセスできる

	CMatchFrame();			// コンストラクタ
	~CMatchFrame();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理

	// 静的メンバ関数
	static CMatchFrame* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif