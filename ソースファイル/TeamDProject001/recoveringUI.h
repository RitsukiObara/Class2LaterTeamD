//===================================
//
// 回復中UIヘッダー[recoveringUI.h]
// Author 佐藤根詩音
//
//===================================
#ifndef _RECOVERINGUI_H_
#define _RECOVERINGUI_H_

//***********************************
// インクルードファイル
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// クラス定義(サンプル)
//-----------------------------------
class CRecoveringUI : public CBillboard
{
public:			// 誰でもアクセスできる

	CRecoveringUI();			// コンストラクタ
	~CRecoveringUI();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(D3DXVECTOR3& pos, D3DXVECTOR3& posOld);		// 情報の設定処理

	// 静的メンバ関数
	static CRecoveringUI* Create(D3DXVECTOR3& pos, D3DXVECTOR3& posOld);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif