//===================================
//
// エントリーUIヘッダー[entry_UI.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_UI_H_
#define _ENTRY_UI_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CEntryFrame;			// エントリーの枠
class CEntryTeam;			// エントリーチーム
class CEntryID;				// エントリーID
class CEntryArrow;			// エントリーの矢印

//-----------------------------------
// クラス定義(CEntryUI)
//-----------------------------------
class CEntryUI : public CObject
{
public:

	CEntryUI();				// コンストラクタ
	~CEntryUI();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nID);				// 情報の設定処理

	// 静的メンバ関数
	static CEntryUI* Create(const D3DXVECTOR3& pos, const int nID);	// 生成処理

private:

	// メンバ変数
	CEntryFrame* m_pFrame;			// 枠の情報
	CEntryTeam* m_pTeam;			// チームの情報
	CEntryID* m_pID;				// プレイヤーIDの情報
	CEntryArrow* m_apArrow[2];		// 矢印の情報
	int m_nID;						// インデックス
};

#endif