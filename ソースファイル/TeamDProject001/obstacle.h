//===================================
//
// 障害物ヘッダー[obstacle.h]
// Author 小原立暉
//
//===================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "player.h"

class CBillboard;

//-----------------------------------
// クラス定義(障害物)
//-----------------------------------
class CObstacle : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_HONEY = 0,		// 蜂蜜
		TYPE_SLIME,			// スライム
		TYPE_HAIRBALL,		// 毬
		TYPE_FLOWERVASE,	// 花瓶
		TYPE_PETBOTTLE,		// ペットボトル
		TYPE_TOYCAR,		// おもちゃの車
		TYPE_ROOMBA,		// ルンバ
		TYPE_HIMO,			// ひも
		TYPE_SPEAKER,		// スピーカー
		TYPE_MOUSETRAP,		// ネズミ捕り
		TYPE_LEASH,			// リード
		TYPE_PIN,			// 画鋲
		TYPE_FAN,			// 扇風機
		TYPE_CUP,			// コップ
		TYPE_GARBAGECAN,	// ゴミ
		TYPE_TV,			// テレビ
		TYPE_DYNAMITE,		// ダイナマイト
		TYPE_BOOK,			// 本
		TYPE_REDKATEN,		// 赤のカーテン
		TYPE_MAX			// この列挙型の総数
	};

	CObstacle();			// コンストラクタ
	CObstacle(CObject::TYPE type, PRIORITY priority = PRIORITY_BLOCK);			// コンストラクタ
	virtual ~CObstacle();	// デストラクタ
	void Box(void);			// コンストラクタの箱

	// リスト構造関係
	void SetPrev(CObstacle* pPrev);		// 前のポインタの設定処理
	void SetNext(CObstacle* pNext);		// 後のポインタの設定処理
	CObstacle* GetPrev(void) const;		// 前のポインタの設定処理
	CObstacle* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	virtual void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	virtual bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type);	// 当たり判定処理
	virtual bool Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type);			// ヒット処理
	virtual bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type) { return false; }							// ヒット処理
	virtual void Action(void) {}											// ギミック起動処理
	virtual void HitMultiCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type, int nIdx, bool bInput) {}				// ヒット処理
	virtual void MultiAction(void) {}										// ギミック同時起動処理
	void GimmickUI(bool Set, int Player_Idx);								// ギミック起動UIの表示
	void MultiGimmickUI(bool Set, int Player_Idx);							// ギミック起動UIの表示

	// セット・ゲット関係
	void SetType(const TYPE type);		// 種類の設定処理
	TYPE GetType(void);					// 種類の取得処理

	void SetCatUse(const bool Set) { m_bCatUse = Set; }		// 起動可能の設定処理
	bool GetCatUse(void) { return m_bCatUse; }				// 起動可能の取得処理
	void SetRatUse(const bool Set) { m_bRatUse = Set; }		// 起動可能の設定処理
	bool GetRatUse(void) { return m_bRatUse; }				// 起動可能の取得処理

	virtual D3DXVECTOR3 GetPosHead(void) { return NONE_D3DXVECTOR3; }
	virtual D3DXVECTOR3 GetPosToes(void) { return NONE_D3DXVECTOR3; }
	virtual void SlideOn(D3DXVECTOR3 pos, D3DXVECTOR3 move, CPlayer *pPlayer) {}

	// 静的メンバ関数
	static CObstacle* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	TYPE m_type;		// 種類
	CBillboard *m_pGimmickUI;
	CBillboard *m_pMultiGimmickUI[2];
	bool m_pGimmickUIFalse[MAX_PLAY];	//全部[False]の時にUIを削除する
	bool m_bCatUse;						//猫が起動できるかどうか
	bool m_bRatUse;						//ネズミが起動できるかどうか

	// リスト構造関係
	CObstacle* m_pPrev;	// 前へのポインタ
	CObstacle* m_pNext;	// 次へのポインタ
};

#endif