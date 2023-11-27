//===================================
//
// マッチングの選択肢ヘッダー[match_select.h]
// Author 小原立暉
//
//===================================
#ifndef _MATCH_SELECT_H_
#define _MATCH_SELECT_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス定義(CMatchSelect)
//-----------------------------------
class CMatchSelect : public CObject2D
{
public:			// 誰でもアクセスできる

	CMatchSelect();			// コンストラクタ
	~CMatchSelect();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nID);				// 情報の設定処理

	// 静的メンバ関数
	static CMatchSelect* Create(const D3DXVECTOR3& pos, const int nID);	// 生成処理

private:		// 自分だけアクセスできる

};

#endif