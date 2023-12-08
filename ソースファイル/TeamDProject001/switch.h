//===================================
//
// スイッチヘッダー[switch.h]
// Author 小原立暉
//
//===================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(スイッチ)
//-----------------------------------
class CSwitch : public CModel
{
public:			// 誰でもアクセスできる

	CSwitch();				// コンストラクタ
	~CSwitch();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理

	// 静的メンバ関数
	static CSwitch* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif