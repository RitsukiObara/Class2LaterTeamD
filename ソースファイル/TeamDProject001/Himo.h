//===================================
//
// ひもヘッダー[Himo.h]
// Author 坂本翔唯
//
//===================================
#ifndef _HIMO_H_
#define _HIMO_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

#define MAX_TARAI (5)

class CTarai;
//-----------------------------------
// クラス定義(ひも)
//-----------------------------------
class CHimo : public CObstacle
{
public:			// 誰でもアクセスできる

	CHimo();				// コンストラクタ
	~CHimo();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// ヒット処理
	void Action(void) override;										// ギミック起動処理

	static void NULLTarai(int Idx) { m_apTarai[Idx] = NULL; }

private:		// 自分だけアクセスできる
	void SetTarai(void);

	static CTarai *m_apTarai[MAX_TARAI];
	int m_nTaraiCount;
	bool m_bAction;
	float m_fDownPosY;
	float m_fUpPosY;
};

#endif