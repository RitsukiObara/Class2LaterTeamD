//===================================
//
// 障害物ヘッダー[obstacle.h]
// Author 小原立暉
//
//===================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(障害物)
//-----------------------------------
class CObstacle : public CModel
{
public:			// 誰でもアクセスできる

	CObstacle();			// コンストラクタ
	~CObstacle();			// デストラクタ

	// リスト構造関係
	void SetPrev(CObstacle* pPrev);		// 前のポインタの設定処理
	void SetNext(CObstacle* pNext);		// 後のポインタの設定処理
	CObstacle* GetPrev(void) const;		// 前のポインタの設定処理
	CObstacle* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// 静的メンバ関数
	static CObstacle* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// リスト構造関係
	CObstacle* m_pPrev;	// 前へのポインタ
	CObstacle* m_pNext;	// 次へのポインタ
};

#endif