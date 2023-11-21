//===================================
//
// アイテムヘッダー[item.h]
// Author 小原立暉
//
//===================================
#ifndef _ITEM_H_
#define _ITEM_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(アイテム)
//-----------------------------------
class CItem : public CModel
{
public:			// 誰でもアクセスできる

	CItem();			// コンストラクタ
	~CItem();			// デストラクタ

	// リスト構造関係
	void SetPrev(CItem* pPrev);		// 前のポインタの設定処理
	void SetNext(CItem* pNext);		// 後のポインタの設定処理
	CItem* GetPrev(void) const;		// 前のポインタの設定処理
	CItem* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);			// 情報の設定処理

	// 静的メンバ関数
	static CItem* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// リスト構造関係
	CItem* m_pPrev;	// 前へのポインタ
	CItem* m_pNext;	// 次へのポインタ
};

#endif