//=======================================
//
// カウントダウンのメイン処理[countdown.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "countdown.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define COUNTDOWN_TIME		(5)		// カウントダウンの時間

//=========================
// コンストラクタ
//=========================
CCountdown::CCountdown() : CNumber(CObject::TYPE_COUNTDOWN, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
}

//=========================
// デストラクタ
//=========================
CCountdown::~CCountdown()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CCountdown::Init(void)
{
	if (FAILED(CNumber::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CCountdown::Uninit(void)
{
	// 終了
	CNumber::Uninit();
}

//=========================
// 更新処理
//=========================
void CCountdown::Update(void)
{
	// 頂点情報の初期化
	SetVertexRot();
}

//=========================
// 描画処理
//=========================
void CCountdown::Draw(void)
{
	// 描画処理
	CNumber::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CCountdown::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// 数字の設定処理
	SetPos(pos);				// 位置
	SetPosOld(pos);				// 前回の位置
	SetRot(NONE_D3DXVECTOR3);	// 向き
	SetSize(size);				// サイズ
	SetLength();				// 長さ
	SetAngle();					// 方向
	SetNumber(COUNTDOWN_TIME);	// 数字
	SetType(TYPE_DECIMAL);		// 種類

	// 頂点情報の初期化
	SetVertexRot();

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\Number.png"));
}

//=========================
// 生成処理
//=========================
CCountdown* CCountdown::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ローカルオブジェクトを生成
	CCountdown* pCountdown = nullptr;	// プレイヤーのインスタンスを生成

	if (pCountdown == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCountdown = new CCountdown;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCountdown != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCountdown->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCountdown->SetData(pos, size);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// カウントダウンのポインタを返す
	return pCountdown;
}