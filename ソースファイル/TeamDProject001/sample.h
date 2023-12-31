//===================================
//
// サンプルヘッダー[sample.h]
// Author 小原立暉
//
//===================================
#ifndef _SAMPLE_H_
#define _SAMPLE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(サンプル)
//-----------------------------------
class CSample : public CObject/*親クラス*/
{
public:			// 誰でもアクセスできる

	CSample();			// コンストラクタ
	~CSample();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void/*引数*/);		// 情報の設定処理

	// 静的メンバ関数
	static CSample* Create(void/*引数*/);		// 生成処理

private:		// 自分だけアクセスできる

};

//====================================================================================================================================================================================================================================================
// ここからはマネージャーがある奴(マネージャーは当たり判定などで使う)
//====================================================================================================================================================================================================================================================

//-----------------------------------------------------
// クラス定義(サンプル)
//-----------------------------------------------------
class CListSample : public CObject/*親クラス*/
{
public:			// 誰でもアクセスできる

	CListSample();		// コンストラクタ
	~CListSample();		// デストラクタ

	// リスト構造関係
	void SetPrev(CListSample* pPrev);	// 前のポインタの設定処理
	void SetNext(CListSample* pNext);	// 後のポインタの設定処理
	CListSample* GetPrev(void) const;	// 前のポインタの設定処理
	CListSample* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void/*引数*/);			// 情報の設定処理

	// 静的メンバ変数
	static CListSample* Create(void/*引数*/);		// 生成処理

private:		// 自分だけアクセスできる

	// リスト構造関係
	CListSample* m_pPrev;	// 前へのポインタ
	CListSample* m_pNext;	// 次へのポインタ
};

#endif