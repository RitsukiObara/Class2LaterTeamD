//===================================
//
// エントリーのIDヘッダー[entry_ID.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_ID_H_
#define _ENTRY_ID_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス定義(CEntryID)
//-----------------------------------
class CEntryID : public CObject2D
{
public:			// 誰でもアクセスできる

	CEntryID();			// コンストラクタ
	~CEntryID();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nID);				// 情報の設定処理

	// 静的メンバ関数
	static CEntryID* Create(const D3DXVECTOR3& pos, const int nID);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif