//===================================
//
// ログヘッダー[log.h]
// Author 坂本翔唯
//
//===================================
#ifndef _LOG_H_
#define _LOG_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

class CObject2D;

//-----------------------------------
// クラス定義(サンプル)
//-----------------------------------
class CLog : public CObject/*親クラス*/
{
public:			// 誰でもアクセスできる

	CLog();			// コンストラクタ
	~CLog();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(int nIdex, int nCreateNumber);		// 情報の設定処理

	// 静的メンバ関数
	static CLog* Create(int nIdex, int nCreateNumber);		// 生成処理

private:		// 自分だけアクセスできる

	D3DXVECTOR3 LogPos;
	int m_nPlayerNumber;
	int m_CreateNumber;
	CObject2D *m_pLogBG;
	CObject2D *m_pLogPlayerID;
	CObject2D *m_pLogMessage;
};
#endif