//===========================================
//
// 地形ブロックのメイン処理[block.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CBlock::CBlock() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_type = TYPE_WOODBLOCK;		// 種類
}

//==============================
// デストラクタ
//==============================
CBlock::~CBlock()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CBlock::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_type = TYPE_WOODBLOCK;		// 種類

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CBlock::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CBlock::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CBlock::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CBlock::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(rot);							// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_WOODBLOCK);	// モデルの情報

	// 全ての値を初期化する
	m_type = type;			// 種類
}

//=====================================
// 生成処理
//=====================================
CBlock* CBlock::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ローカルオブジェクトを生成
	CBlock* pBlock = nullptr;	// インスタンスを生成

	if (pBlock == nullptr)
	{ // オブジェクトが NULL の場合

		// 毬を生成する
		pBlock = new CBlock;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBlock != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBlock->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBlock->SetData(pos, rot, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ブロックのポインタを返す
	return pBlock;
}