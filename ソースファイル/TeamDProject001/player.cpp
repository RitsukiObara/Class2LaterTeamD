//===========================================
//
// プレイヤーのメイン処理[player.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "player.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "elevation_manager.h"
#include "objectElevation.h"
#include "collision.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY		(1.0f)			// 重力
#define ADD_MOVE_Y	(30.0f)			// 浮力

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CPlayer* CPlayer::m_pPlayer = nullptr;		// プレイヤーの情報

//==============================
// コンストラクタ
//==============================
CPlayer::CPlayer() : CModel(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;			// 移動量

	m_bJump = false;					// ジャンプしたか
	m_bLand = true;						// 着地したか
	m_bAttack = false;					// 攻撃したか
}

//==============================
// デストラクタ
//==============================
CPlayer::~CPlayer()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;			// 移動量

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CPlayer::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	// プレイヤーの情報を NULL にする
	m_pPlayer = nullptr;
}

//=====================================
// 破片の更新処理
//=====================================
void CPlayer::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 移動処理
	Move();

	// ジャンプ処理
	Jump();

	// 攻撃処理
	Attack();

	// 起伏地面の当たり判定
	Elevation();

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n向き：%f %f %f\nジャンプ状況：%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump);
}

//=====================================
// 破片の描画処理
//=====================================
void CPlayer::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CPlayer::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_KARIPLAYER);	// モデルの情報設定
}

//=======================================
// 取得処理
//=======================================
CPlayer* CPlayer::Get(void)
{
	if (m_pPlayer != nullptr)
	{ // プレイヤーが NULL じゃない場合

		// プレイヤーの情報を返す
		return m_pPlayer;
	}
	else
	{ // 上記以外

		// NULL を返す
		return nullptr;
	}
}

//=======================================
// 生成処理
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos)
{
	if (m_pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		m_pPlayer = new CPlayer;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (m_pPlayer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(m_pPlayer->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		m_pPlayer->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return m_pPlayer;
}

//=======================================
// 移動処理
//=======================================
void CPlayer::Move(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // Dキーを押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
		{ // Wキーを押した場合

			// 向きを設定する
			rot.y = D3DX_PI * 0.25f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
		{ // Sキーを押した場合

			// 向きを設定する
			rot.y = D3DX_PI * 0.75f;
		}
		else
		{ // 上記以外

			// 向きを設定する
			rot.y = D3DX_PI * 0.5f;
		}

		// 移動量を設定する
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // Aキーを押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
		{ // Wキーを押した場合

			// 向きを設定する
			rot.y = D3DX_PI * -0.25f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
		{ // Sキーを押した場合

			// 向きを設定する
			rot.y = D3DX_PI * -0.75f;
		}
		else
		{ // 上記以外

			// 向きを設定する
			rot.y = D3DX_PI * -0.5f;
		}

		// 移動量を設定する
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // Wキーを押した場合

		// 向きを設定する
		rot.y = 0.0f;

		// 移動量を設定する
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // Sキーを押した場合

		// 向きを設定する
		rot.y = D3DX_PI;

		// 移動量を設定する
		m_move.x = sinf(rot.y) * 20.0f;
		m_move.z = cosf(rot.y) * 20.0f;
	}
	else
	{ // 上記以外

		// 移動量を設定する
		m_move.x = 0.0f;
		m_move.z = 0.0f;
	}

	// 向きを適用する
	SetRot(rot);
}

//=======================================
// ジャンプ処理
//=======================================
void CPlayer::Jump(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		m_bJump == false && m_bLand == true)
	{ // SPACEキーを押した場合

		m_move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
		m_bLand = false;	// 着地してない状態にする
	}

	m_move.y -= GRAVITY;		// 重力加算

	// 位置を加算する
	pos += m_move;

	// 情報を適用する
	SetPos(pos);
	SetRot(rot);
}

//=======================================
// 攻撃処理
//=======================================
void CPlayer::Attack(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 posOld = GetPosOld();

	//if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_J) == true/* && m_bAttack == false*/)
	{ // Jキーを押した場合

		collision::ObstacleRectCollision(pos, 50.0f, 50.0f, 50.0f);

		//m_bAttack = true;		// 攻撃した状態にする
	}

	// 情報を適用する
	SetPos(pos);
}

//=======================================
// 起伏地面の当たり判定
//=======================================
void CPlayer::Elevation(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	float fHeight = 0.0f;					// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

	  // 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

		  // 高さを設定する
			pos.y = fHeight;

			m_bJump = false;		// ジャンプしてない状態にする
			m_bLand = true;			// 着地した状態にする
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}