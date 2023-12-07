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

//==============================
// コンストラクタ
//==============================
CBook::CBook() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		m_apBook[nCnt] = nullptr;
	}
	SetCatUse(true);		// ネコの使用条件
	SetRatUse(true);		// ネズミの使用条件
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

}

//=====================================
// 本の描画処理
//=====================================
void CBook::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // 本の情報が NULL じゃない場合

			// 本の描画処理
			m_apBook[nCnt]->Draw();
		}
	}
}

//=====================================
// 両端起動時の処理
//=====================================
void CBook::Action(void)
{

}

//=====================================
// 情報の設定処理
//=====================================
void CBook::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // 本の情報が NULL じゃない場合

			// 情報を設定する
			m_apBook[nCnt]->SetPos(D3DXVECTOR3(pos.x, pos.y + (nCnt * 50.0f), pos.z));
			m_apBook[nCnt]->SetPosOld(m_apBook[nCnt]->GetPos());
			m_apBook[nCnt]->SetRot(NONE_D3DXVECTOR3);
			m_apBook[nCnt]->SetScale(NONE_SCALE);
			m_apBook[nCnt]->SetFileData(CXFile::TYPE_ACADAPTER);
		}
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CBook::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CBook::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CBook::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{ // 円の範囲内の場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}