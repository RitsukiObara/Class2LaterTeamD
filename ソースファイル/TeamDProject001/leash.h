//===================================
//
// リードヘッダー[Himo.h]
// Author 坂本翔唯
//
//===================================
#ifndef _LEASH_H_
#define _LEASH_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(リード)
//-----------------------------------
class CLeash : public CObstacle
{
public:			// 誰でもアクセスできる

	CLeash();				// コンストラクタ
	~CLeash();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// ヒット処理
	void CollisionHead(bool Set) { m_bSetHead = Set; }
	void CollisionToes(bool Set) { m_bSetToes = Set; }

private:		// 自分だけアクセスできる
	void Action(void);
	void SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	D3DXVECTOR3 ActionPosHead;	//先端の位置
	D3DXVECTOR3 ActionPosToes;	//末端の位置

	bool m_bSetHead;	//先端の準備完了
	bool m_bSetToes;	//末端の準備完了
	bool m_bAction;		//ギミックが起動しているかどうか
};

#endif