////===========================================
////
//// 武器の選択UIヘッダー[weapon_selectUI.h]
//// Author 小原立暉
////
////===========================================
//#ifndef _WEAPON_SELECT_UI_H_
//#define _WEAPON_SELECT_UI_H_
//
////-------------------------------------------
//// インクルードファイル
////-------------------------------------------
//#include "object.h"
//
////-------------------------------------------
//// 前方宣言
////-------------------------------------------
//class CObject2D;
//
////-------------------------------------------
//// クラス定義(武器選択UI)
////-------------------------------------------
//class CWeaponSelectUI : public CObject
//{
//public:		// 誰でもアクセスできる
//
//	// 列挙型定義(種類)
//	enum TYPE
//	{
//		TYPE_ONE = 0,	// 1つ目
//		TYPE_TWO,		// 2つ目
//		TYPE_THREE,		// 3つ目
//		TYPE_MAX		// この列挙型の総数
//	};
//
//	CWeaponSelectUI();			// コンストラクタ
//	~CWeaponSelectUI();			// デストラクタ
//
//	// メンバ関数
//	HRESULT Init(void);			// 初期化処理
//	void Uninit(void);			// 終了処理
//	void Update(void);			// 更新処理
//	void Draw(void);			// 描画処理
//
//	// セット・ゲット関係
//
//	// 静的メンバ関数
//	static CWeaponSelectUI* Create(void);	// 生成処理
//
//private:		// 自分だけアクセスできる
//
//	// メンバ変数
//	CObject2D* m_pScreen;					// スクリーンの情報
//	CObject2D* m_apWeapon[TYPE_MAX];		// 武器の情報
//};
//
//#endif