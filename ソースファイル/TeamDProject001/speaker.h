//===================================
//
// スピーカーヘッダー[Himo.h]
// Author 坂本翔唯
//
//===================================
#ifndef _SPEAKER_H_
#define _SPEAKER_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

#define MAX_NOTE (32)

class CNote;
//-----------------------------------
// クラス定義(スピーカー)
//-----------------------------------
class CSpeaker : public CObstacle
{
public:			// 誰でもアクセスできる

	CSpeaker();				// コンストラクタ
	~CSpeaker();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// ヒット処理

	static void NULLNote(int Idx) { m_apNote[Idx] = NULL; }

private:		// 自分だけアクセスできる
	void Action(void);
	void SetNote(void);

	static CNote *m_apNote[MAX_NOTE];
	bool m_bAction;
	int m_nNoateCount;
};

#endif