//===========================================
//
// 扇風機のファンのメイン処理[fan_blade.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "fan_blade.h"

//==============================
// コンストラクタ
//==============================
CFanBlade::CFanBlade() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// デストラクタ
//==============================
CFanBlade::~CFanBlade()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CFanBlade::Init(void)
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
void CFanBlade::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CFanBlade::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CFanBlade::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CFanBlade::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CXFile::TYPE_FANBLADE);			// モデル情報
}

//=======================================
// 生成処理
//=======================================
CFanBlade* CFanBlade::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CFanBlade* pFanBlade = nullptr;	// インスタンスを生成

	if (pFanBlade == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pFanBlade = new CFanBlade;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFanBlade != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pFanBlade->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFanBlade->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 扇風機のファンのポインタを返す
	return pFanBlade;
}