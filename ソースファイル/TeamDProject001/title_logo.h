//===================================
//
// タイトルロゴヘッダー[title_logo.h]
// Author 小原立暉
//
//===================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CObject2D;		// 2Dポリゴン

//-----------------------------------
// クラス定義(タイトルロゴ)
//-----------------------------------
class CTitleLogo : public CObject
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_RAT = 0,// にゃんこ
		TYPE_AND,	 // ＆
		TYPE_CAT,	 // ちゅーちゅー
		TYPE_MAX	 // この列挙型の総数
	};

	CTitleLogo();			// コンストラクタ
	~CTitleLogo();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	// 静的メンバ関数
	static CTitleLogo* Create(void);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CObject2D* m_apTitle[TYPE_MAX];		// タイトルのポリゴン
};

#endif