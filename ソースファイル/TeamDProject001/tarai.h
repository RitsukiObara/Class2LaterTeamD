//===================================
//
// たらいヘッダー[tarai.h]
// Author 坂本翔唯
//
//===================================
#ifndef _TARAI_H_
#define _TARAI_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(歯車)
//-----------------------------------
class CTarai : public CModel
{
public:			// 誰でもアクセスできる

	CTarai();			// コンストラクタ
	~CTarai();		// デストラクタ

						// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理
	void SetIndex(int Idx) { m_nIndex = Idx; }			// 使用番号の設定

	// 静的メンバ関数
	static CTarai* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	D3DXVECTOR3 m_move;
	int m_nIndex;

};

#endif