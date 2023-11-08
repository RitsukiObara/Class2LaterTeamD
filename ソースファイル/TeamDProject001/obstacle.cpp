//===========================================
//
// 障害物のメイン処理[obstacle.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "obstacle.h"
#include "obstacle_manager.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CObstacle::CObstacle() : CModel(CObject::TYPE_WOODBLOCK, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_type = TYPE_WOODBLOCK;	// 種類
	m_pPrev = nullptr;			// 前のへのポインタ
	m_pNext = nullptr;			// 次のへのポインタ

	if (CObstacleManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CObstacleManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CObstacle::~CObstacle()
{

}

//============================
// 前のポインタの設定処理
//============================
void CObstacle::SetPrev(CObstacle* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CObstacle::SetNext(CObstacle* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CObstacle* CObstacle::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CObstacle* CObstacle::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
// 破片の初期化処理
//==============================
HRESULT CObstacle::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_type = TYPE_WOODBLOCK;	// 種類

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CObstacle::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CObstacleManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CObstacleManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// 破片の更新処理
//=====================================
void CObstacle::Update(void)
{
	
}

//=====================================
// 破片の描画処理
//=====================================
void CObstacle::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CObstacle::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_WOODBLOCK);	// モデルの情報設定

	// 全ての値を初期化する
	m_type = TYPE_WOODBLOCK;	// 種類
}

//=======================================
// 生成処理
//=======================================
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CObstacle* pFrac = nullptr;	// インスタンスを生成

	if (pFrac == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pFrac = new CObstacle;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFrac != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pFrac->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFrac->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 破片のポインタを返す
	return pFrac;
}

//=======================================
// 種類の設定処理
//=======================================
void CObstacle::SetType(const TYPE type)
{
	// 種類を設定する
	m_type = type;
}

//=======================================
// 種類の取得処理
//=======================================
CObstacle::TYPE CObstacle::GetType(void)
{
	// 種類を返す
	return m_type;
}