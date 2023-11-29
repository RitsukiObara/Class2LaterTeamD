//===========================================
//
// ルンバのメイン処理[roomba.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "roomba.h"
#include "useful.h"
#include "objectX.h"

#include "player.h"

//==============================
// コンストラクタ
//==============================
CRoomba::CRoomba() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt] = NULL;
	}

	m_move = NONE_D3DXVECTOR3;
}

//==============================
// デストラクタ
//==============================
CRoomba::~CRoomba()
{

}

//==============================
// ルンバの初期化処理
//==============================
HRESULT CRoomba::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_apSub[0] = CModel::Create();
	m_apSub[1] = CModel::Create();
	m_apSub[0]->SetFileData((CXFile::TYPE::TYPE_ROOMBA_SUB));	// モデル情報
	m_apSub[1]->SetFileData((CXFile::TYPE::TYPE_ROOMBA_SUB));	// モデル情報
	
	// 値を返す
	return S_OK;
}

//========================================
// ルンバの終了処理
//========================================
void CRoomba::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ルンバの更新処理
//=====================================
void CRoomba::Update(void)
{
	//位置を向きの取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//本体の向きを動かす
	rot.y -= 0.005f;

	//向いている方向に移動する処理
	Move(rot);

	//プロペラの位置と向きの更新
	SubUpdate();

	//位置更新
	pos += m_move;

	//位置と向きの更新
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// 移動処理
//=====================================
void CRoomba::Move(D3DXVECTOR3 rot)
{
	m_move = D3DXVECTOR3(
		sinf(rot.y + (D3DX_PI * 1.0f)) * 2.0f,
		0.0f,
		cosf(rot.y + (D3DX_PI * 1.0f)) * 2.0f);
}

//=====================================
// プロペラの更新処理
//=====================================
void CRoomba::SubUpdate(void)
{
	//位置と向きの取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//プロペラの向きを取得
	D3DXVECTOR3 Subrot[2] = {};
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		Subrot[nCnt] = m_apSub[nCnt]->GetRot();
	}

	//プロペラを回す
	Subrot[0].y += 0.1f;
	Subrot[1].y -= 0.1f;

	//プロペラの位置更新
	m_apSub[0]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.75f)) * 50.0f));

	m_apSub[1]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * -0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * -0.75f)) * 50.0f));

	//プロペラの向きを更新する
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt]->SetRot(Subrot[nCnt]);
	}
}

//=====================================
// ルンバの描画処理
//=====================================
void CRoomba::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRoomba::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CRoomba::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CRoomba::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 objpos = GetPos();

	D3DXVECTOR3 posDif = pos - objpos;

	float fLength = D3DXVec3Length(&posDif);
	float fSize = GetFileData().vtxMax.z;

	if (fLength <= fSize)
	{
		//オブジェクトからの角度
		float fRot = atan2f(pos.x - objpos.x, pos.z - objpos.z);

		D3DXVECTOR3 SetPos = D3DXVECTOR3(objpos.x + sinf(-D3DX_PI - fRot)*fSize, pos.y, objpos.z + cosf(-D3DX_PI - fRot)*fSize);


		return true;
	}
	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CRoomba::Action(void)
{

}