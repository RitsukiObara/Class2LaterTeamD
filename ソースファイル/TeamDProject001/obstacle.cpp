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

#include "honey.h"
#include "slime.h"
#include "hairball.h"
#include "flowervase.h"
#include "plastic_case.h"
#include "petbottle.h"
#include "toycar.h"
#include "roomba.h"

//==============================
// コンストラクタ
//==============================
CObstacle::CObstacle() : CModel(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// コンストラクタの箱
	Box();
}

//==============================
// オーバーロードコンストラクタ
//==============================
CObstacle::CObstacle(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// コンストラクタの箱
	Box();
}

//==============================
// デストラクタ
//==============================
CObstacle::~CObstacle()
{

}

//==============================
// コンストラクタの箱
//==============================
void CObstacle::Box(void)
{
	// 全ての値をクリアする
	m_type = TYPE_HONEY;	// 種類
	m_pPrev = nullptr;		// 前のへのポインタ
	m_pNext = nullptr;		// 次のへのポインタ

	if (CObstacleManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CObstacleManager::Get()->Regist(this);
	}
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
	m_type = TYPE_HONEY;	// 種類

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
void CObstacle::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData((CXFile::TYPE)(INIT_OBSTACLE + type));	// モデル情報

	// 全ての値を初期化する
	m_type = type;		// 種類
}

//=======================================
// 生成処理
//=======================================
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ローカルオブジェクトを生成
	CObstacle* pObstacle = nullptr;	// インスタンスを生成

	if (pObstacle == nullptr)
	{ // オブジェクトが NULL の場合

		switch (type)
		{
		case CObstacle::TYPE_HONEY:

			// 蜂蜜を生成する
			pObstacle = new CHoney;

			break;

		case CObstacle::TYPE_SLIME:

			// スライムを生成する
			pObstacle = new CSlime;

			break;

		case CObstacle::TYPE_HAIRBALL:

			// 毬を生成する
			pObstacle = new CHairBall;

			break;

		case CObstacle::TYPE_FLOWERVASE:

			// 花瓶を生成する
			pObstacle = new CFlowerVase;

			break;
			
		case CObstacle::TYPE_PLASTICCASE:

			// プラスチックケースを生成する
			pObstacle = new CPlasticCase;

			break;

		case CObstacle::TYPE::TYPE_PETBOTTLE:

			//ペットボトルを生成する
			pObstacle = new CPetbottle;

			break;

		case CObstacle::TYPE_TOYCAR:

			// おもちゃの車を生成する
			pObstacle = new CToyCar;

			break;

		case CObstacle::TYPE_ROOMBA:

			// ルンバを生成する
			pObstacle = new CRoomba;

			break;

		default:

			//停止
			assert(false);

			break;
		}
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pObstacle != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pObstacle->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pObstacle->SetData(pos, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 障害物のポインタを返す
	return pObstacle;
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