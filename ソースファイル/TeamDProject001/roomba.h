//===================================
//
// ルンバヘッダー[roomba.h]
// Author 坂本翔唯
//
//===================================
#ifndef _ROOMBA_H_
#define _ROOMBA_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

class CModel;

//-----------------------------------
// クラス定義(ルンバ)
//-----------------------------------
class CRoomba : public CObstacle
{
public:			// 誰でもアクセスできる

	CRoomba();				// コンストラクタ
	~CRoomba();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);		// ヒット処理
	void Action(void) override;										// ギミック起動処理

private:		// 自分だけアクセスできる

	void SubUpdate(void);	// プロペラの更新の処理
	void Move(D3DXVECTOR3 rot);		// 移動処理

	CModel *m_apSub[2];
	D3DXVECTOR3 m_move;

};

#endif