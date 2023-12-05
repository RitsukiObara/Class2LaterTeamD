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

#define MAX_NOTE (64)	//音符が画面の中に存在できる最大数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CNote;		// 音符

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

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);	// 当たり判定処理
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);		// ヒット処理
	bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type);
	void Action(void) override;
	void MySetIdx(int Idx){ m_bmySet[Idx] = false; }
	static void NULLNote(int Idx) { m_apNote[Idx] = NULL; }

private:		// 自分だけアクセスできる
	void SetNote(void);

	static CNote *m_apNote[MAX_NOTE];
	bool m_bmySet[MAX_NOTE];
	bool m_bAction;
	int m_nNoteCount;
};

#endif