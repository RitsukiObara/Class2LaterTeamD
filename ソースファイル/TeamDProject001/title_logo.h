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

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_ESCAPE = 0,		// 逃走状態
		STATE_WAIT,				// 待機状態
		STATE_MAX				// この列挙型の総数
	};

	// 構造体定義(タイトルロゴ)
	struct STitleLogo
	{
		D3DXVECTOR3 move;		// 移動量
		CObject2D* pLogo;		// タイトルのポリゴン
		bool bDisp;				// 表示状況
		bool bMove;				// 移動状況
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

	// メンバ関数
	void EscapeProcess(void);			// 逃走状態の処理

	void Move(const TYPE type);			// 移動処理
	void EscapeRatPosSet(void);			// 逃走状態のネズミの位置関係処理
	void EscapeCatPosSet(void);			// 逃走状態のネコの位置関係処理

	// メンバ変数
	STitleLogo m_aTitle[TYPE_MAX];		// タイトルのポリゴン
	STATE m_state;						// 状態
};

#endif