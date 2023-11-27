//=======================================
//
// マッチングの枠チーム処理[match_frame.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "match_frame.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define TEAM_SIZE		(D3DXVECTOR3(120.0f, 60.0f, 0.0f))		// チームのサイズ

//=========================
// コンストラクタ
//=========================
CMatchFrame::CMatchFrame() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{

}

//=========================
// デストラクタ
//=========================
CMatchFrame::~CMatchFrame()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CMatchFrame::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CMatchFrame::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CMatchFrame::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CMatchFrame::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CMatchFrame::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(TEAM_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 頂点情報の初期化
	SetVertex();

	// 頂点カラーの設定処理
	SetVtxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

//=========================
// 生成処理
//=========================
CMatchFrame* CMatchFrame::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CMatchFrame* pEntryTeam = nullptr;	// プレイヤーのインスタンスを生成

	if (pEntryTeam == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntryTeam = new CMatchFrame;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntryTeam != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntryTeam->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntryTeam->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーチームのポインタを返す
	return pEntryTeam;
}