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
class CRat : public CModel
{
public:			// 誰でもアクセスできる

	CRat();			// コンストラクタ
	~CRat();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// セット・ゲット関係
	void SetRatIdx(const int nIdx);			// ネズミの番号の設定処理
	int GetRatIdx(void) const;				// ネズミの番号の取得処理

	// 静的メンバ関数
	static CRat* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Move(void);			// 移動処理
	void Jump(void);			// ジャンプ処理
	void Attack(void);			// 攻撃処理
	void Elevation(void);		// 起伏地面の当たり判定
	void Hit(void);				// ヒット処理

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
	int m_nRatIdx;				// ネズミの番号
	int m_nLife;				// 寿命
	int m_nDamageCounter;		// ダメージ食らうまでのカウンター

	bool m_bJump;				// ジャンプしたか
	bool m_bLand;				// 着地したか
	bool m_bAttack;				// 攻撃したか
};

#endif