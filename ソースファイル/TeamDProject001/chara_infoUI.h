//============================================
//
// キャラクターの情報UIヘッダー[chara_infoUI.h]
// Author：小原立暉
//
//============================================
#ifndef _CHARA_INFOUI_H_			// このマクロ定義がされていなかったら
#define _CHARA_INFOUI_H_			// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object.h"
#include "chara_icon.h"

//--------------------------------------------
// クラス定義(キャラクターの情報UI)
//--------------------------------------------
class CCharaInfoUI : public CObject
{
public:				// 誰でもアクセスできる

	CCharaInfoUI();					// コンストラクタ
	~CCharaInfoUI();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaIcon::TYPE type);						// 情報の設定処理

	// 静的メンバ関数
	static CCharaInfoUI* Create(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaIcon::TYPE type);		// 生成処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CCharaIcon* m_pIcon;	// アイコンの情報
};

#endif