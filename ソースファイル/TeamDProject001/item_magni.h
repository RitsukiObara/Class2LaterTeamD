//============================================
//
// アイテムの持っている数ヘッダー[item_magni.h]
// Author：小原立暉
//
//============================================
#ifndef _ITEM_MAGNI_H_			// このマクロ定義がされていなかったら
#define _ITEM_MAGNI_H_			// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CObject2D;			// 2Dポリゴン
class CNumber;				// 数字

//--------------------------------------------
// クラス定義(アイテムの倍率)
//--------------------------------------------
class CItemMagni : public CObject
{
public:				// 誰でもアクセスできる

	CItemMagni();			// コンストラクタ
	~CItemMagni();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nNum);					// 情報の設定処理

	// 静的メンバ関数
	static CItemMagni* Create(const D3DXVECTOR3& pos, const int nNum);		// 生成処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CObject2D* m_pMagni;		// ×マークの情報
	CNumber* m_pNumber;			// 数字の情報
};

#endif