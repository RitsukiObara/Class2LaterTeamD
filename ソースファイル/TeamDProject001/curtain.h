//===================================
//
// カーテンヘッダー[curtain.h]
// Author 小原立暉
//
//===================================
#ifndef _CURTAIN_H_
#define _CURTAIN_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// マクロ定義
//-----------------------------------
#define MAX_SWITCH		(3)		// スイッチの最大数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CSwitch;			// スイッチ

//-----------------------------------
// クラス定義(カーテン)
//-----------------------------------
class CCurtain : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_CLOSE = 0,	// 閉じる状態
		STATE_OPEN,			// 開いてる状態
		STATE_MAX			// この列挙型の総数
	};

	CCurtain();				// コンストラクタ
	~CCurtain();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	//bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;	// 当たり判定処理
	//bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type) override;			// 円のヒット処理
	//void Action(void) override;										// ギミック起動処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void StateManager(void);	// 状態マネージャー

	// メンバ変数
	CSwitch* m_apSwitch[MAX_SWITCH];	// スイッチの情報
	STATE m_state;						// 状態
};

#endif