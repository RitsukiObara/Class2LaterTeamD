//===========================================
//
// 武器の選択UIヘッダー[weapon_selectUI.h]
// Author 小原立暉
//
//===========================================
#ifndef _WEAPON_SELECT_UI_H_
#define _WEAPON_SELECT_UI_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object.h"

//-------------------------------------------
// 前方宣言
//-------------------------------------------
class CWeaponCage;		// 武器小屋

//-------------------------------------------
// クラス定義(武器選択UI)
//-------------------------------------------
class CWeaponSelectUI : public CObject
{
public:		// 誰でもアクセスできる

	CWeaponSelectUI();			// コンストラクタ
	~CWeaponSelectUI();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	void SetData(void);			// 情報の設定処理

	// 静的メンバ関数
	static CWeaponSelectUI* Create(void);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CWeaponCage* m_pWeaponCage;		// 武器小屋の情報
};

#endif