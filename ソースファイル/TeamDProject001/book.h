//===================================
//
// 本ヘッダー[book.h]
// Author 小原立暉
//
//===================================
#ifndef _BOOK_H_
#define _BOOK_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// マクロ定義
//-----------------------------------
#define MAX_BOOK	(3)		// 本の最大数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CModel;			// モデル

//-----------------------------------
// クラス定義(リード)
//-----------------------------------
class CBook : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_STOP = 0,		// 停止状態
		STATE_COLLAPSE,		// 倒れ状態
		STATE_MAX			// この列挙型の総数
	};

	CBook();				// コンストラクタ
	~CBook();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;		// ヒット処理
	bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type) override;
	void Action(void) override;

private:		// 自分だけアクセスできる

	// メンバ関数
	void StateManager(void);		// 状態マネージャー

	// メンバ変数
	CModel* m_apBook[MAX_BOOK];		// 上に載っている本の情報
	D3DXVECTOR3 m_move;				// 移動量
	STATE m_state;					// 状態
};

#endif