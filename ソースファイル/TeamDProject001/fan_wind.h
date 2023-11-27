//=====================================================
//
// 扇風機の風ヘッダー [fan_wind.h]
// Author：小原立暉
//
//=====================================================
#ifndef _FAN_WIND_H_			// このマクロ定義がされていない場合
#define _FAN_WIND_H_			// 二重インクルード防止のマクロを定義する

//*****************************************************
// インクルードファイル
//*****************************************************
#include "mesh_cylinder.h"

//-----------------------------------------------------
// クラス定義(CFanWind)
//-----------------------------------------------------
class CFanWind : public CMeshCylinder
{
public:		// 誰でもアクセスできる

	CFanWind();				// コンストラクタ
	~CFanWind();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize);					// 情報の設定処理

	// 静的メンバ関数
	static CFanWind* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize);		// 生成処理

private:		// 自分だけアクセスできる

};


#endif