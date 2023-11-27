//====================================================================
//
//	扇風機の風処理 [fan_wind.cpp]
//	Author：小原立暉
//
//====================================================================
//********************************************************************
//	インクルードファイル
//********************************************************************
#include "fan_wind.h"

//--------------------------------------------------------------------
// マクロ定義
//--------------------------------------------------------------------
#define FAN_CIRCUM		(8)			// 風の円周の分割数
#define FAN_HEIGHT		(1)			// 風の縦の分割数

//================================
// コンストラクタ
//================================
CFanWind::CFanWind() : CMeshCylinder(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY)
{
	
}

//================================
// デストラクタ
//================================
CFanWind::~CFanWind()
{

}

//================================
// 初期化処理
//================================
HRESULT CFanWind::Init(void)
{
	if (FAILED(CMeshCylinder::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//================================
// 終了処理
//================================
void CFanWind::Uninit(void)
{
	// 終了処理
	CMeshCylinder::Uninit();
}

//================================
// 更新処理
//================================
void CFanWind::Update(void)
{

}

//================================
// 描画処理
//================================
void CFanWind::Draw(void)
{
	// 描画処理
	CMeshCylinder::Draw();
}

//================================
// 情報の設定処理
//================================
void CFanWind::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize)
{
	// メッシュシリンダーの設定処理
	CMeshCylinder::SetDataCylinder(pos, rot, fCircumSize, fHeightSize, FAN_CIRCUM, FAN_HEIGHT);
}

//================================
// 生成処理
//================================
CFanWind* CFanWind::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize)
{
	// ローカルオブジェクトを生成
	CFanWind* pFanWind = nullptr;	// インスタンスを生成

	// おもちゃの車を生成する
	pFanWind = new CFanWind;

	if (pFanWind != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 情報の設定処理
		pFanWind->SetData(pos, rot, fCircumSize, fHeightSize);

		// 初期化処理
		if (FAILED(pFanWind->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 扇風機の風のポインタを返す
	return pFanWind;
}