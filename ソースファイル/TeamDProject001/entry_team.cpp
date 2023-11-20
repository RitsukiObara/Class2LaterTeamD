//=======================================
//
// エントリーチーム処理[entry_team.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_team.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define TEAM_SIZE		(D3DXVECTOR3(80.0f, 40.0f, 0.0f))		// チームのサイズ
#define TEAM_TEXTURE	"data\\TEXTURE\\Entry_Team.png"			// チームのテクスチャ

//=========================
// コンストラクタ
//=========================
CEntryTeam::CEntryTeam() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{

}

//=========================
// デストラクタ
//=========================
CEntryTeam::~CEntryTeam()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryTeam::Init(void)
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
void CEntryTeam::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CEntryTeam::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CEntryTeam::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CEntryTeam::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(TEAM_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEAM_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	// 頂点カラーの設定処理
	SetVtxColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//=========================
// 生成処理
//=========================
CEntryTeam* CEntryTeam::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CEntryTeam* pEntryTeam = nullptr;	// プレイヤーのインスタンスを生成

	if (pEntryTeam == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntryTeam = new CEntryTeam;
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