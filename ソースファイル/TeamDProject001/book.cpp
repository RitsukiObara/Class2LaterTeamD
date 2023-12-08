//===========================================
//
// 本の処理[book.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "book.h"
#include "useful.h"
#include "collision.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define BOOK_SHIFT_HEIGHT		(27.5f)			// 本のずらす高さ
#define BOOK_COLLAPSE_RANGE		(80.0f)			// 本のヒット判定の範囲

//==============================
// コンストラクタ
//==============================
CBook::CBook() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		m_apBook[nCnt] = nullptr;	// 本の情報
	}
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
	SetCatUse(true);				// ネコの使用条件
	SetRatUse(true);				// ネズミの使用条件
}

//==============================
// デストラクタ
//==============================
CBook::~CBook()
{

}

//==============================
// 本の初期化処理
//==============================
HRESULT CBook::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] == nullptr)
		{ // 本の情報が NULL の場合

			// 本を生成する
			m_apBook[nCnt] = new CModel(TYPE_NONE, PRIORITY_BLOCK);
		}
	}
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態

	// 値を返す
	return S_OK;
}

//========================================
// 本の終了処理
//========================================
void CBook::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // 本の情報が NULL じゃない場合

			// 本の終了処理
			m_apBook[nCnt]->Uninit();
			m_apBook[nCnt] = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 本の更新処理
//=====================================
void CBook::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 状態マネージャー
	StateManager();
}

//=====================================
// 本の描画処理
//=====================================
void CBook::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // 本の情報が NULL じゃない場合

			// 本の描画処理
			m_apBook[nCnt]->Draw();
		}
	}

	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CBook::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 向きの変数を宣言する
	float fRot;

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // 本の情報が NULL じゃない場合

			// 向きをランダムで算出
			fRot = (rand() % 81 - 40) * 0.01f;

			// 情報を設定する
			m_apBook[nCnt]->SetPos(D3DXVECTOR3(pos.x, pos.y + ((nCnt + 1) * BOOK_SHIFT_HEIGHT), pos.z));
			m_apBook[nCnt]->SetPosOld(m_apBook[nCnt]->GetPos());
			m_apBook[nCnt]->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
			m_apBook[nCnt]->SetScale(NONE_SCALE);
			m_apBook[nCnt]->SetFileData((CXFile::TYPE)(CXFile::TYPE_BOOKBLUE + nCnt));
		}
	}
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
}

//=====================================
// 状態マネージャー
//=====================================
void CBook::StateManager(void)
{
	switch (m_state)
	{
	case CBook::STATE_STOP:			// 停止状態

		// 特になし

		break;

	case CBook::STATE_COLLAPSE:		// 倒れ状態



		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CBook::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	D3DXVECTOR3 objMax = D3DXVECTOR3(GetFileData().vtxMax.x, GetFileData().vtxMax.y + (GetFileData().collsize.y * MAX_BOOK), GetFileData().vtxMax.z);

	// 六面体の当たり判定
	if (collision::HexahedronCollision
	(
		&pos,					// 位置
		GetPos(),				// 本の位置
		posOld,					// 前回の位置
		GetPosOld(),			// 本の前回の位置
		vtxMin,					// 最小値
		GetFileData().vtxMin,	// 本の最小値
		vtxMax,					// 最大値
		objMax					// 本の最小値
	) == true)
	{ // 当たり判定に当たった場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CBook::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	if (m_state == STATE_COLLAPSE &&
		useful::CircleCollisionXZ(pos, GetPos(), collSize.x, GetFileData().fRadius) == true)
	{ // 倒れ状態で一定範囲内にいた場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CBook::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (m_state == STATE_STOP &&
		useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{ // 停止状態かつ、円の範囲内の場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// 起動時の処理
//=====================================
void CBook::Action(void)
{
	if (m_state == STATE_STOP)
	{ // 停止状態の場合

		// 向きを取得する
		D3DXVECTOR3 rot = GetRot();

		// 倒れ状態にする
		m_state = STATE_COLLAPSE;

		// 移動量を設定する
		m_move.x = sinf(rot.y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot.y + (D3DX_PI * -0.5f)) * 4.0f;
	}
}