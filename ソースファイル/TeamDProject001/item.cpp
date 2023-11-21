//===========================================
//
// アイテムのメイン処理[item.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "item.h"
#include "item_manager.h"

//==============================
// コンストラクタ
//==============================
CItem::CItem() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pPrev = nullptr;				// 前のへのポインタ
	m_pNext = nullptr;				// 次のへのポインタ

	if (CItemManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CItemManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CItem::~CItem()
{

}

//============================
// 前のポインタの設定処理
//============================
void CItem::SetPrev(CItem* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CItem::SetNext(CItem* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CItem* CItem::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CItem* CItem::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
// 初期化処理
//==============================
HRESULT CItem::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// 終了処理
//========================================
void CItem::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CItemManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CItemManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// 更新処理
//=====================================
void CItem::Update(void)
{

}

//=====================================
// 描画処理
//=====================================
void CItem::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CItem::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_TRAPITEM);		// モデルの情報
}

//=====================================
// 生成処理
//=====================================
CItem* CItem::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CItem* pItem = nullptr;	// インスタンスを生成

	if (pItem == nullptr)
	{ // オブジェクトが NULL の場合

		// 毬を生成する
		pItem = new CItem;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pItem != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pItem->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pItem->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// アイテムのポインタを返す
	return pItem;
}