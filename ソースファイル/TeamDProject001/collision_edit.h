//===================================
//
// 当たり判定エディットヘッダー[collision_edit.h]
// Author 小原立暉
//
//===================================
#ifndef _COLLISION_EDIT_H_
#define _COLLISION_EDIT_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// マクロ定義
//-----------------------------------
#define MIN_NUMCOLL			(1)			// 当たり判定の最小数
#define MAX_NUMCOLL			(10)		// 当たり判定の最大数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CModel;			// モデル

//-----------------------------------
// クラス定義(当たり判定エディット)
//-----------------------------------
class CCollisionEdit : public CObject
{
public:			// 誰でもアクセスできる

	CCollisionEdit();		// コンストラクタ
	~CCollisionEdit();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理

	// 静的メンバ関数
	static CCollisionEdit* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Move(void);			// 移動処理
	void Adjust(void);			// 微調整処理
	void PosReset(void);		// 位置のリセット処理

	// メンバ変数
	CModel* m_apModel[MAX_NUMCOLL];		// 当たり判定の情報
	D3DXVECTOR3 m_posInit;				// 初期位置
	int m_nNumColl;						// 当たり判定の総数
	int m_nIdx;							// インデックス
};

#endif