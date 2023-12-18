//============================================
//
// 画面の枠ヘッダー[screen_frame.h]
// Author：小原立暉
//
//============================================
#ifndef _SCREEN_FRAME_H_					// このマクロ定義がされていなかったら
#define _SCREEN_FRAME_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object2D.h"

//--------------------------------------------
// クラス定義(画面の枠)
//--------------------------------------------
class CScreenFrame : public CObject2D
{
public:				// 誰でもアクセスできる

	CScreenFrame();			// コンストラクタ
	~CScreenFrame();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	static CScreenFrame* Create(void);		// 生成処理

private:			// 自分だけアクセスできる

};

#endif