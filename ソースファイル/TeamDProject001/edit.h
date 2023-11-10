//===================================
//
// エディットヘッダー[edit.h]
// Author 小原立暉
//
//===================================
#ifndef _EDIT_H_
#define _EDIT_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "obstacle.h"

//-----------------------------------
// クラス定義(エディット)
//-----------------------------------
class CEdit : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_OBSTACLE = 0,		// 障害物
		TYPE_MAX				// この列挙型の総数
	};

	CEdit();			// コンストラクタ
	~CEdit();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);				// 情報の設定処理

	// 静的メンバ関数
	static CEdit* Create(void);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Move(void);		// 移動処理
	void Adjust(void);		// 微調整処理
	void Set(void);			// 設置処理
	void Delete(void);		// 消去処理

	// それぞれの消去処理
	void DeleteObstacle(void);	// 障害物の消去処理

	// メンバ変数宣言
	TYPE m_type;					// 種類
	CObstacle::TYPE m_obstacleType;	// 障害物の種類
};

#endif