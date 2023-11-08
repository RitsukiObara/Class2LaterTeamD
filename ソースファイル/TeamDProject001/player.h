//===================================
//
// プレイヤーヘッダー[player.h]
// Author 小原立暉
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(プレイヤー)
//-----------------------------------
class CPlayer : public CModel
{
public:			// 誰でもアクセスできる

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// 静的メンバ関数
	static CPlayer* Get(void);							// 取得処理
	static CPlayer* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

	CPlayer();			// コンストラクタ
	~CPlayer();			// デストラクタ

	// メンバ関数
	void Move(void);			// 移動処理
	void Jump(void);			// ジャンプ処理
	void Elevation(void);		// 起伏地面の当たり判定

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量

	bool m_bJump;				// ジャンプしたか
	bool m_bLand;				// 着地したか

	// 静的メンバ変数
	static CPlayer* m_pPlayer;	// プレイヤーの情報
};

#endif