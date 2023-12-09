//===================================
//
// スイッチヘッダー[switch.h]
// Author 小原立暉
//
//===================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CModel;		// モデル

//-----------------------------------
// クラス定義(スイッチ)
//-----------------------------------
class CSwitch : public CObject
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_BASE = 0,		// 土台
		TYPE_LEVER,			// レバー
		TYPE_MAX			// この列挙型の総数
	};

	CSwitch();				// コンストラクタ
	~CSwitch();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理

	// セット・ゲット関数
	void SetBoot(const bool bBoot);			// 起動状況の設定処理
	bool GetBoot(void) const;				// 起動状況の取得処理

	// 静的メンバ関数
	static CSwitch* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CModel* m_apModel[TYPE_MAX];		// モデルの情報
	bool m_bMove;						// 移動状況
	bool m_bBoot;						// 起動状況
};

#endif