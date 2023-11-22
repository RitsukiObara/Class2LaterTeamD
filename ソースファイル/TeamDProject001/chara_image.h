//============================================
//
// キャラクターの画像ヘッダー[chara_image.h]
// Author：小原立暉
//
//============================================
#ifndef _CHARA_IMAGE_H_					// このマクロ定義がされていなかったら
#define _CHARA_IMAGE_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object2D.h"

//--------------------------------------------
// クラス定義(キャラクターの画像)
//--------------------------------------------
class CCharaImage : public CObject2D
{
public:				// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_CAT = 0,		// ネコ
		TYPE_RAT,			// ネズミ
		TYPE_MAX			// この列挙型の総数
	};

	CCharaImage();						// コンストラクタ
	~CCharaImage();						// デストラクタ

	// メンバ関数
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);					// 情報の設定処理

	// 静的メンバ関数
	static CCharaImage* Create(const D3DXVECTOR3& pos, const TYPE type);	// 生成処理

private:			// 自分だけアクセスできる

};

#endif