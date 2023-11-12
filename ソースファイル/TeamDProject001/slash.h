//============================================
//
// 斬撃演出ヘッダー[slash.h]
// Author：小原立暉
//
//============================================
#ifndef _SLASH_H_			//このマクロ定義がされていなかったら
#define _SLASH_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// クラス(斬撃演出クラス)
//--------------------------------------------
class CSlash : public CBillboardAnim
{
public:			// 誰でもアクセスできる

	CSlash();				// コンストラクタ
	~CSlash();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 設定処理

	// 静的メンバ関数
	static CSlash* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	int m_nLife;			// 寿命
};

#endif