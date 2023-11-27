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
// マクロ定義
//-----------------------------------
#define MATCH_ID_MAX		(4)		// 選択肢の最大数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CMatchFrame;		// エントリーの枠
class CMatchChara;		// キャラクター
class CMatchVS;			// VSマーク
class CMatchSelect;		// 選択肢

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

	void SetData(const D3DXVECTOR3& pos, const int nID);				// 情報の設定処理

	// 静的メンバ関数
	static CEntryMatch* Create(const D3DXVECTOR3& pos, const int nID);	// 生成処理

private:

	// メンバ変数
	CMatchFrame* m_pFrame;					// 枠の情報
	CMatchChara* m_pChara;					// キャラクター
	CMatchVS* m_pVS;						// VSマーク
	CMatchSelect* m_apSelect[MATCH_ID_MAX];	// 選択肢
};

#endif