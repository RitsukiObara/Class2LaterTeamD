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
#include "rat.h"
#include "game.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "elevation_manager.h"
#include "objectElevation.h"
#include "obstacle_manager.h"
#include "obstacle.h"
#include "collision.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY		(1.0f)			// 重力
#define ADD_MOVE_Y	(30.0f)			// 浮力
#define NONE_RATIDX	(-1)			// ネズミの番号の初期値
#define ATTACK_DISTANCE	(200.0f)	// 攻撃範囲までの距離
#define MAX_LIFE	(3)				// 寿命の最大値
#define TIME_DAMAGE	(60 * 1)		// ダメージ食らうまでの時間

//==============================
// コンストラクタ
//==============================
CRat::CRat() : CModel(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_nRatIdx = NONE_RATIDX;			// ネズミの番号
	m_nLife = 0;						// 寿命
	m_nDamageCounter = TIME_DAMAGE;		// ダメージ食らうまでのカウンター

	m_bJump = false;					// ジャンプしたか
	m_bLand = true;						// 着地したか
	m_bAttack = false;					// 攻撃したか

}

//==============================
// デストラクタ
//==============================
CRat::~CRat()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CRat::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_nRatIdx = NONE_RATIDX;			// ネズミの番号

	m_nLife = MAX_LIFE;					// 寿命
	m_nDamageCounter = TIME_DAMAGE;		// ダメージ食らうまでのカウンター

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CRat::Uninit(void)
{
	// ネズミを消去する
	CGame::DeleteRat(m_nRatIdx);

	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CRat::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 移動処理
	Move();

	// ジャンプ処理
	Jump();

	// 攻撃処理
	Attack();

	// ヒット処理
	Hit();

	// 起伏地面の当たり判定
	Elevation();

	// 障害物との当たり判定
	ObstacleCollision();

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n向き：%f %f %f\nジャンプ状況：%d\n寿命：%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump, m_nLife);
}

//=====================================
// 破片の描画処理
//=====================================
void CRat::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_KARIPLAYER);	// モデルの情報設定
}

//=======================================
// ネズミの番号の設定処理
//=======================================
void CRat::SetRatIdx(const int nIdx)
{
	// ネズミの番号を設定する
	m_nRatIdx = nIdx;
}

//=======================================
// ネズミの番号の取得処理
//=======================================
int CRat::GetRatIdx(void) const
{
	// ネズミの番号を返す
	return m_nRatIdx;
}

//=======================================
// 生成処理
//=======================================
CRat* CRat::Create(const D3DXVECTOR3& pos)
{
	// ネズミのポインタ
	CRat* pRat = nullptr;

	if (pRat == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pRat = new CRat;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pRat != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pRat->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pRat->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pRat;
}

//=======================================
// 移動処理
//=======================================
void CRat::Move(void)
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
void CRat::Jump(void)
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
void CRat::Attack(void)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_J) == true/* && m_bAttack == false*/)
	{ // Jキーを押した場合

		while (pObstacle != nullptr)
		{ // ブロックの情報が NULL じゃない場合

			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
				GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
				GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
			{ // XYの矩形に当たってたら

				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
					GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
					GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
				{ // XZの矩形に当たってたら

					// 障害物の終了処理
					pObstacle->Uninit();
				}
			}

			// 次のオブジェクトを代入する
			pObstacle = pObstacle->GetNext();
		}

		//m_bAttack = true;		// 攻撃した状態にする
	}
}

//=======================================
// ヒット処理
//=======================================
void CRat::Hit(void)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = GetPos();

	if (m_nDamageCounter >= TIME_DAMAGE)
	{ // ダメージ食らう時間になったら

		while (pObstacle != nullptr)
		{ // ブロックの情報が NULL じゃない場合

			if (useful::RectangleCollisionXY(pos, pObstacle->GetPos(),
				GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
				GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
			{ // XYの矩形に当たってたら

				if (useful::RectangleCollisionXZ(pos, pObstacle->GetPos(),
					GetFileData().vtxMax, pObstacle->GetFileData().vtxMax,
					GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true)
				{ // XZの矩形に当たってたら

					m_nLife--;		// 寿命減らす
					m_nDamageCounter = 0;		// ダメージ食らうまでの時間リセット

					if (m_nLife <= 0)
					{ // 寿命が無いとき

						// 終了処理
						Uninit();
					}
				}
			}

			// 次のオブジェクトを代入する
			pObstacle = pObstacle->GetNext();
		}
	}
	else
	{ // ダメージ食らう時間じゃなかったら

		m_nDamageCounter++;		// ダメージ食らうまでの時間加算
	}
}

//=======================================
// 起伏地面の当たり判定
//=======================================
void CRat::Elevation(void)
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

//=======================================
// 障害物との当たり判定
//=======================================
void CRat::ObstacleCollision(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 障害物との当たり判定
	collision::ObstacleCollision(pos, GetPosOld(), 30.0f, 50.0f, 30.0f);

	// 位置を設定する
	SetPos(pos);
}