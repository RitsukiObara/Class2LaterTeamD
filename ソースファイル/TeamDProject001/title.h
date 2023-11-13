//============================================
//
// タイトル画面ヘッダー[title.h]
// Author：小原立暉
//
//============================================
#ifndef _TITLE_H_			//このマクロ定義がされていなかったら
#define _TITLE_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "scene.h"

//前方宣言
class C2DUIEdit;

//--------------------------------------------
// クラス(タイトルクラス)
//--------------------------------------------
class CTitle : public CScene
{
public:				// 誰でもアクセスできる

	CTitle();		// コンストラクタ
	~CTitle();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

private:					// 自分だけアクセスできる

	// メンバ変数
	C2DUIEdit *m_pUIEdit;
	int m_nTransCount;		// 遷移カウント
};

#endif