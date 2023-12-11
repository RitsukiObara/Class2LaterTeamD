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
#include "block_manager.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CBlock::CBlock() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_collision = COLLISION_SQUARE;	// 当たり判定の種類
	m_rotType = ROTTYPE_FRONT;		// 向きの種類
	m_type = TYPE_CARDBOARD;		// 種類
	m_vtxMax = NONE_D3DXVECTOR3;	// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;	// 最小値
	m_pPrev = nullptr;				// 前のへのポインタ
	m_pNext = nullptr;				// 次のへのポインタ

	if (CBlockManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CBlockManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CBlock::~CBlock()
{

}

//============================
// 前のポインタの設定処理
//============================
void CBlock::SetPrev(CBlock* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CBlock::SetNext(CBlock* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CBlock* CBlock::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CBlock* CBlock::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
// 初期化処理
//==============================
HRESULT CBlock::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_collision = COLLISION_SQUARE;	// 当たり判定の種類
	m_rotType = ROTTYPE_FRONT;		// 向きの種類
	m_type = TYPE_CARDBOARD;		// 種類
	m_vtxMax = NONE_D3DXVECTOR3;	// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;	// 最小値

	// 値を返す
	return S_OK;
}

//========================================
// 終了処理
//========================================
void CBlock::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CBlockManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CBlockManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
// 終了処理
//========================================
void CBlock::UninitAll(void)
{
	// ローカル変数宣言
	CBlock* pObj = nullptr;		// 現在のオブジェクトのポインタ

	for (int nCnt = 0; nCnt < CObject::PRIORITY_MAX; nCnt++)
	{
		 pObj->GetTop(((CObject::PRIORITY)nCnt));
	}
	Uninit();
}

//=====================================
// 更新処理
//=====================================
void CBlock::Update(void)
{

}

//=====================================
// 描画処理
//=====================================
void CBlock::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CBlock::SetData(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetScale(NONE_SCALE);					// 拡大率

	// 全ての値を初期化する
	m_type = type;			// 種類
	m_rotType = rotType;	// 向きの種類

	switch (m_rotType)
	{
	case CBlock::ROTTYPE_FRONT:		// 前向き

		// 向きを設定する
		SetRot(NONE_D3DXVECTOR3);

		break;

	case CBlock::ROTTYPE_RIGHT:		// 右向き

		// 向きを設定する
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

		break;

	case CBlock::ROTTYPE_BACK:		// 後ろ向き

		// 向きを設定する
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

		break;

	case CBlock::ROTTYPE_LEFT:		// 左向き

		// 向きを設定する
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	if (m_type >= TYPE_MAX)
	{ // タイプにある場合

		// 停止
		assert(false);
	}
	else
	{ // 上記以外

		// ブロックの種類を設定する
		SetFileData((CXFile::TYPE)(INIT_BLOCK + m_type));
	}

	if (m_type == TYPE_PENHOLDER ||
		m_type == TYPE_RUBBISH ||
		m_type == TYPE_HEADPHONE)
	{ // 一定の数値の場合

		// 円の当たり判定を設定する
		m_collision = COLLISION_CIRCLE;
	}
	else
	{ // 上記以外

		// 四角の当たり判定を設定する
		m_collision = COLLISION_SQUARE;

		// 向きによる最大値・最小値の設定処理
		CollisionSetting();
	}
}

//=====================================
// 生成処理
//=====================================
CBlock* CBlock::Create(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type)
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
		pBlock->SetData(pos, rotType, type);
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

//=====================================
// 当たり判定の種類の設定処理
//=====================================
void CBlock::SetCollision(const COLLISION collsion)
{
	// 当たり判定を設定する
	m_collision = collsion;
}

//=====================================
// 当たり判定の種類の取得処理
//=====================================
CBlock::COLLISION CBlock::GetCollision(void) const
{
	// 当たり判定を返す
	return m_collision;
}

//=====================================
// 向きの種類の取得処理
//=====================================
CBlock::ROTTYPE CBlock::GetRotType(void) const
{
	// 向きの種類を設定する
	return m_rotType;
}

//=====================================
// 種類の取得処理
//=====================================
CBlock::TYPE CBlock::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//=====================================
// 最大値の取得処理
//=====================================
D3DXVECTOR3 CBlock::GetVtxMax(void) const
{
	// 最大値を返す
	return m_vtxMax;
}

//=====================================
// 最小値の取得処理
//=====================================
D3DXVECTOR3 CBlock::GetVtxMin(void) const
{
	// 最小値を返す
	return m_vtxMin;
}

//=====================================
// 向きによる最大値・最小値の設定処理
//=====================================
void CBlock::CollisionSetting(void)
{
	// 最小値と最大値を取得する
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	switch (m_rotType)
	{
	case CBlock::ROTTYPE_FRONT:		// 正面

		// 最大値と最小値を設定する
		m_vtxMax = vtxMax;			// 最大値
		m_vtxMin = vtxMin;			// 最小値

		break;

	case CBlock::ROTTYPE_RIGHT:		// 右

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, vtxMax.x);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.x);

		break;

	case CBlock::ROTTYPE_BACK:		// 後ろ

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);

		break;

	case CBlock::ROTTYPE_LEFT:		// 左

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, -vtxMin.x);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, -vtxMax.x);

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}