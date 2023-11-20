//===========================================
//
// 歯車のメイン処理[tarai.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "tarai.h"
#include "useful.h"
#include "Himo.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GEAR_CYCLE_SPEED		(0.1f)		// 回る速度

//==============================
// コンストラクタ
//==============================
CTarai::CTarai() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_move = NONE_D3DXVECTOR3;
	m_nIndex = -1;
}

//==============================
// デストラクタ
//==============================
CTarai::~CTarai()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CTarai::Init(void)
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
// 破片の終了処理
//========================================
void CTarai::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CTarai::Update(void)
{
	// 向きを取得する
	D3DXVECTOR3 pos = GetPos();

	// 向きを加算する
	m_move.y -= 0.98f;

	if (pos.y < 0.0f)
	{
		//m_move.y = 0.0f;
		//m_move.y = -m_move.y * 0.5f;

		CHimo::NULLTarai(m_nIndex);
		Uninit();
		return;
	}

	pos.y += m_move.y;

	// 向きを設定する
	SetPos(pos);
}

//=====================================
// 破片の描画処理
//=====================================
void CTarai::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CTarai::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CXFile::TYPE_TARAI);		// モデル情報
}

//=======================================
// 生成処理
//=======================================
CTarai* CTarai::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CTarai* pTarai = nullptr;	// インスタンスを生成

	if (pTarai == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pTarai = new CTarai;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTarai != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pTarai->Init()))
		{ // 初期化に失敗した場合

		  // 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTarai->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// たらいのギアのポインタを返す
	return pTarai;
}