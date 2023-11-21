//===================================
//
// 結果の文字の処理[result_letter.h]
// Author 佐藤根詩音
//
//===================================
#ifndef _RESULT_LETTER_H_
#define _RESULT_LETTER_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(サンプル)
//-----------------------------------
class CResultLetter : public CObject/*親クラス*/
{
public:			// 誰でもアクセスできる

	CResultLetter();			// コンストラクタ
	~CResultLetter();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void/*引数*/);		// 情報の設定処理

	// 静的メンバ関数
	static CResultLetter* Create(void/*引数*/);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif