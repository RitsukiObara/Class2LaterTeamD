//===================================
//
// ネズミの幽霊の処理[rat_ghost.h]
// Author 小原立暉
//
//===================================
#ifndef _RAT_GHOST_H_
#define _RAT_GHOST_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CRat;				// ネズミ

//-----------------------------------
// クラス(ネズミの幽霊クラス)
//-----------------------------------
class CRatGhost : public CModel
{
public:			// 誰でもアクセスできる

	CRatGhost();			// コンストラクタ
	~CRatGhost();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	// 静的メンバ関数
	static CRatGhost* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif