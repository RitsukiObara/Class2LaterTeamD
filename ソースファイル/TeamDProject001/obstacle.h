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

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_HONEY = 0,		// 蜂蜜
		TYPE_SLIME,			// スライム
		TYPE_HAIRBALL,		// 毬
		TYPE_FLOWERVASE,	// 花瓶
		TYPE_PLASTICCASE,	// プラスチックケース
		TYPE_PETBOTTLE,		// ペットボトル
		TYPE_TOYCAR,		// おもちゃの車
		TYPE_MAX			// この列挙型の総数
	};

	CObstacle();			// コンストラクタ
	CObstacle(CObject::TYPE type, PRIORITY priority = PRIORITY_BLOCK);			// コンストラクタ
	virtual ~CObstacle();	// デストラクタ
	void Box(void);			// コンストラクタの箱

	// リスト構造関係
	void SetPrev(CObstacle* pPrev);		// 前のポインタの設定処理
	void SetNext(CObstacle* pNext);		// 後のポインタの設定処理
	CObstacle* GetPrev(void) const;		// 前のポインタの設定処理
	CObstacle* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	virtual void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	virtual bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth) = 0;	// 当たり判定処理
	virtual bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth) = 0;								// ヒット処理

	// セット・ゲット関係
	void SetType(const TYPE type);		// 種類の設定処理
	TYPE GetType(void);					// 種類の取得処理

	// 静的メンバ関数
	static CObstacle* Create(const D3DXVECTOR3& pos, const TYPE type);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	TYPE m_type;		// 種類

	// リスト構造関係
	CObstacle* m_pPrev;	// 前へのポインタ
	CObstacle* m_pNext;	// 次へのポインタ
};

#endif