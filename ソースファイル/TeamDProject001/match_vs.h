//===================================
//
// マッチングのVSヘッダー[match_vs.h]
// Author 小原立暉
//
//===================================
#ifndef _MATCH_VS_H_
#define _MATCH_VS_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス定義(CMatchVS)
//-----------------------------------
class CMatchVS : public CObject2D
{
public:			// 誰でもアクセスできる

	CMatchVS();				// コンストラクタ
	~CMatchVS();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理

	// 静的メンバ関数
	static CMatchVS* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif