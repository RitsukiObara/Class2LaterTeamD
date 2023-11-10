//===================================
//
// ブロックヘッダー[block.h]
// Author 小原立暉
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(地形用ブロック)
//-----------------------------------
class CBlock : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_WOODBLOCK = 0,		// 木箱
		TYPE_MAX				// この列挙型の総数
	};

	CBlock();			// コンストラクタ
	~CBlock();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	// 静的メンバ関数
	static CBlock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	TYPE m_type;		// 種類
};

#endif