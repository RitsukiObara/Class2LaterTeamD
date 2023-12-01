//============================================
//
// アイテムUIヘッダー[item_UI.h]
// Author：小原立暉
//
//============================================
#ifndef _ITEM_UI_H_			// このマクロ定義がされていなかったら
#define _ITEM_UI_H_			// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object.h"
#include "item.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CItemMark;			// アイテムのマーク
class CItemFrame;			// アイテムの枠

//--------------------------------------------
// クラス定義(アイテムUI)
//--------------------------------------------
class CItemUI : public CObject
{
public:				// 誰でもアクセスできる

	CItemUI();				// コンストラクタ
	~CItemUI();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理

	// セット・ゲット関係
	void SetMark(const CItem::TYPE type);		// マークの生成処理

	// 静的メンバ関数
	static CItemUI* Create(const D3DXVECTOR3& pos);			// 生成処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CItemMark* m_pMark;		// マークの情報
	CItemFrame* m_pFrame;	// 枠の情報
};

#endif