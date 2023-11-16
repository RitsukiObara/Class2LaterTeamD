//===================================
//
// カウントダウンヘッダー[countdown.h]
// Author 小原立暉
//
//===================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

//***********************************
// インクルードファイル
//***********************************
#include "number.h"

//-----------------------------------
// クラス定義(カウントダウン)
//-----------------------------------
class CCountdown : public CNumber
{
public:			// 誰でもアクセスできる

	CCountdown();			// コンストラクタ
	~CCountdown();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);					// 情報の設定処理

	// 静的メンバ関数
	static CCountdown* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
};

#endif