//============================================
//
// アイテムの持っている数処理[item_magni.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "item_magni.h"
#include "texture.h"
#include "useful.h"

#include "object2D.h"
#include "number.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAGNI_TEXTURE		"data\\TEXTURE\\Magni.png"			// ×マークのテクスチャ
#define NUMBER_TEXTURE		"data\\TEXTURE\\Number.png"			// 数字のテクスチャ
#define MAGNI_SIZE			(D3DXVECTOR3(10.0f, 10.0f, 0.0f))	// ×マークのサイズ
#define NUMBER_SIZE			(D3DXVECTOR3(10.0f, 20.0f, 0.0f))	// 数字のサイズ

//========================
// コンストラクタ
//========================
CItemMagni::CItemMagni() : CObject(TYPE_CHARAINFO, PRIORITY_UI)
{
	// 全ての値をクリアする
	m_pMagni = nullptr;
	m_pNumber = nullptr;
}

//========================
// デストラクタ
//========================
CItemMagni::~CItemMagni()
{

}

//========================
// 初期化処理
//========================
HRESULT CItemMagni::Init(void)
{
	if (m_pMagni == nullptr)
	{ // ×マークが NULL じゃない場合

		// ×マークを生成する
		m_pMagni = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);
	}
	else
	{ // 上記以外

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	if (m_pNumber == nullptr)
	{ // 数字が NULL じゃない場合

		// 数字を生成する
		m_pNumber = new CNumber(TYPE_NONE, PRIORITY_UI);

		if (m_pNumber != nullptr)
		{ // 数字が NULL じゃない場合
			
			if (FAILED(m_pNumber->Init()))
			{ // 初期化処理に失敗した場合

				// 停止
				assert(false);

				// 失敗を返す
				return E_FAIL;
			}
		}
		else
		{ // 上記以外

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}
	}
	else
	{ // 上記以外

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CItemMagni::Uninit(void)
{
	if (m_pMagni != nullptr)
	{ // ×マークが NULL じゃない場合

		// ×マークの終了処理
		m_pMagni->Uninit();
		m_pMagni = nullptr;
	}

	if (m_pNumber != nullptr)
	{ // 数字が NULL じゃない場合

		// 数字の終了処理
		m_pNumber->Uninit();
		m_pNumber = nullptr;
	}

	// 本体の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CItemMagni::Update(void)
{

}

//========================
// 描画処理
//========================
void CItemMagni::Draw(void)
{
	if (m_pMagni != nullptr)
	{ // ×マークが NULL じゃない場合

		// 描画処理
		m_pMagni->Draw();
	}

	if (m_pNumber != nullptr)
	{ // 数字が NULL じゃない場合

		// 描画処理
		m_pNumber->Draw();
	}
}

//========================
// 情報の設定処理
//========================
void CItemMagni::SetData(const D3DXVECTOR3& pos, const int nNum)
{
	if (m_pMagni != nullptr)
	{ // ×マークが NULL じゃない場合

		// 情報を設定する
		m_pMagni->SetPos(pos);					// 位置
		m_pMagni->SetPosOld(pos);				// 前回の位置
		m_pMagni->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pMagni->SetSize(MAGNI_SIZE);			// サイズ
		m_pMagni->SetAngle();					// 方向
		m_pMagni->SetLength();					// 長さ

		// テクスチャの割り当て処理
		m_pMagni->BindTexture(CManager::Get()->GetTexture()->Regist(MAGNI_TEXTURE));

		// 頂点座標の設定処理
		m_pMagni->SetVertex();
	}

	if (m_pNumber != nullptr)
	{ // 数字が NULL じゃない場合

		// 情報を設定する
		m_pNumber->SetPos(pos);						// 位置
		m_pNumber->SetPosOld(pos);					// 前回の位置
		m_pNumber->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pNumber->SetSize(NUMBER_SIZE);			// サイズ
		m_pNumber->SetAngle();						// 方向
		m_pNumber->SetLength();						// 長さ

		m_pNumber->SetNumber(nNum);					// 数字
		m_pNumber->SetType(CNumber::TYPE_DECIMAL);	// 種類

		// テクスチャの割り当て処理
		m_pNumber->BindTexture(CManager::Get()->GetTexture()->Regist(NUMBER_TEXTURE));

		// 頂点座標の設定処理
		m_pNumber->SetVertex();

		// テクスチャの設定処理(アニメーションバージョン)
		m_pNumber->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, nNum);
	}
}

//========================
// 生成処理
//========================
CItemMagni* CItemMagni::Create(const D3DXVECTOR3& pos, const int nNum)
{
	// ローカルオブジェクトを生成
	CItemMagni* pInfoUI = nullptr;		// キャラクター情報UIのインスタンスを生成

	if (pInfoUI == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pInfoUI = new CItemMagni;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pInfoUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pInfoUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pInfoUI->SetData(pos, nNum);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// キャラクターの情報UIのポインタを返す
	return pInfoUI;
}