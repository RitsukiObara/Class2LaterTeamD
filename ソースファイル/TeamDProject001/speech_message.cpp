//=======================================
//
// 伝達メッセージのメイン処理[speech_message.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "speech_message.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define HELP_TEXTURE		"data\\TEXTURE\\HelpMessage.png"		// 救助要請のテクスチャ
#define MESSAGE_NONE_LIFE	(-1)		// 寿命無し(無限)の値

//=========================
// コンストラクタ
//=========================
CSpeechMessage::CSpeechMessage() : CBillboard(CObject::TYPE_EFFECT, CObject::PRIORITY_EFFECT)
{
	// 全ての値をクリアする
	m_nLife = 0;			// 寿命
	m_type = TYPE_HELP;		// 種類
}

//=========================
// デストラクタ
//=========================
CSpeechMessage::~CSpeechMessage()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CSpeechMessage::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_nLife = 0;			// 寿命
	m_type = TYPE_HELP;		// 種類

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CSpeechMessage::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//=========================
// 更新処理
//=========================
void CSpeechMessage::Update(void)
{
	
}

//=========================
// 描画処理
//=========================
void CSpeechMessage::Draw(void)
{
	// 描画処理
	CBillboard::DrawLightOff();
}

//=========================
// 情報の設定処理
//=========================
void CSpeechMessage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const TYPE type)
{
	// スクロールの設定処理
	SetPos(pos);			// 位置設定
	SetSize(size);			// サイズ設定

	// 全ての値を初期化する
	m_type = type;			// 種類
	m_nLife = nLife;		// 寿命

	// 頂点情報の初期化
	SetVertex();

	switch (m_type)
	{
	case CSpeechMessage::TYPE_HELP:

		// テクスチャの割り当て処理
		BindTexture(CManager::Get()->GetTexture()->Regist(HELP_TEXTURE));

		break;

	default:

		// 特になし

		break;
	}
}

//=========================
// 生成処理
//=========================
CSpeechMessage* CSpeechMessage::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const TYPE type)
{
	// ローカルオブジェクトを生成
	CSpeechMessage* pMessage = nullptr;	// プレイヤーのインスタンスを生成

	if (pMessage == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pMessage = new CSpeechMessage;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pMessage != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pMessage->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pMessage->SetData(pos, size, nLife, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 伝達メッセージのポインタを返す
	return pMessage;
}