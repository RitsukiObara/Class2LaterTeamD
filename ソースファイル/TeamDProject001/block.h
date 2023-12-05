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

	// 向きの種類
	enum ROTTYPE
	{
		ROTTYPE_FRONT = 0,		// 正面
		ROTTYPE_RIGHT,			// 右
		ROTTYPE_BACK,			// 後ろ
		ROTTYPE_LEFT,			// 左
		ROTTYPE_MAX				// この列挙型の総数
	};

	// 列挙型定義(当たり判定の種類)
	enum COLLISION
	{
		COLLISION_SQUARE = 0,		// 四角
		COLLISION_CIRCLE,			// 円
		COLLISION_MAX				// この列挙型の総数
	};

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_CARDBOARD = 0,		// 段ボール
		TYPE_TISSUE,			// ティッシュ箱
		TYPE_PENHOLDER,			// ペン立て
		TYPE_REMOCON,			// リモコン
		TYPE_BEAR,				// テディベア
		TYPE_CLOCK,				// 時計
		TYPE_RUBBISH,			// チリ紙
		TYPE_MILKPACK,			// 牛乳パック
		TYPE_OBAPHONE,			// オバフォン
		TYPE_WII,				// Wii
		TYPE_DS,				// DS
		TYPE_HEADPHONE,			// ヘッドフォン
		TYPE_PEN,				// ペン
		TYPE_ACADAPTER,			// ACアダプター
		TYPE_BUILDINGBLOCK,		// 積み木
		TYPE_GLASSES,			// 眼鏡ケース
		TYPE_PENCIL,			// 鉛筆
		TYPE_PICTUREFRAME,		// 写真立て
		TYPE_SHELF,				// 戸棚
		TYPE_PULLSHELF,			// 引き出し棚
		TYPE_KITCHEN,			//キッチン
		TYPE_REIZOUKO,			//冷蔵庫
		TYPE_TABLE,				//テーブル
		TYPE_CHAIR,				// 机の椅子
		TYPE_CORKBOARD,			// コルクボード
		TYPE_DESK,				// デスク
		TYPE_DESKBOOK,			// デスク用の本
		TYPE_EXTIMGISHER,		// 消火器
		TYPE_KATEN,				// カーテン
		TYPE_KATENRAIL,			// カーテンのレール
		TYPE_TANSU02,			// たんす
		TYPE_MAX				// この列挙型の総数
	};

	CBlock();			// コンストラクタ
	~CBlock();			// デストラクタ

	// リスト構造関係
	void SetPrev(CBlock* pPrev);		// 前のポインタの設定処理
	void SetNext(CBlock* pNext);		// 後のポインタの設定処理
	CBlock* GetPrev(void) const;		// 前のポインタの設定処理
	CBlock* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type);			// 情報の設定処理

	// セット・ゲット関係
	void SetCollision(const COLLISION collsion);	// 当たり判定の種類の設定処理
	COLLISION GetCollision(void) const;				// 当たり判定の種類の取得処理
	ROTTYPE GetRotType(void) const;					// 向きの種類の取得処理
	TYPE GetType(void) const;						// 種類の取得処理
	D3DXVECTOR3 GetVtxMax(void) const;				// 最大値の取得処理
	D3DXVECTOR3 GetVtxMin(void) const;				// 最小値の取得処理

	// 静的メンバ関数
	static CBlock* Create(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void CollisionSetting(void);		// 向きによる最大値・最小値の設定処理

	// メンバ変数
	COLLISION m_collision;	// 当たり判定の種類
	ROTTYPE m_rotType;		// 向きの種類
	TYPE m_type;			// 種類
	D3DXVECTOR3 m_vtxMax;	// 最大値
	D3DXVECTOR3 m_vtxMin;	// 最小値

	// リスト構造関係
	CBlock* m_pPrev;	// 前へのポインタ
	CBlock* m_pNext;	// 次へのポインタ
};

#endif