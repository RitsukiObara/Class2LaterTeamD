//===================================
//
// エントリーマッチングUIヘッダー[entry_match.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_MATCH_H_
#define _ENTRY_MATCH_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CMatchFrame;		// エントリーの枠

//-----------------------------------
// クラス定義(CEntryMatch)
//-----------------------------------
class CEntryMatch : public CObject
{
public:

	CEntryMatch();			// コンストラクタ
	~CEntryMatch();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// 静的メンバ関数
	static CEntryMatch* Create(const D3DXVECTOR3& pos);	// 生成処理

private:

	// メンバ変数
	CMatchFrame* m_pFrame;		// 枠の情報
};

#endif