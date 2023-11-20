//===================================
//
// エントリーチームヘッダー[entry_team.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_TEAM_H_
#define _ENTRY_TEAM_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス定義(CEntryTeam)
//-----------------------------------
class CEntryTeam : public CObject2D
{
public:			// 誰でもアクセスできる

	CEntryTeam();			// コンストラクタ
	~CEntryTeam();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理

	// 静的メンバ関数
	static CEntryTeam* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif