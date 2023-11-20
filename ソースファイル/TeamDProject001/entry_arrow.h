//===================================
//
// エントリーの矢印ヘッダー[entry_arrow.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_ARROW_H_
#define _ENTRY_ARROW_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス定義(CEntryArrow)
//-----------------------------------
class CEntryArrow : public CObject2D
{
public:			// 誰でもアクセスできる

	CEntryArrow();			// コンストラクタ
	~CEntryArrow();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const bool bRight);					// 情報の設定処理

	// 静的メンバ関数
	static CEntryArrow* Create(const D3DXVECTOR3& pos, const bool bRight);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif