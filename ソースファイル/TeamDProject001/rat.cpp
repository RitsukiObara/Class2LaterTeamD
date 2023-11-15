//===========================================
//
// ラットのメイン処理[rat.cpp]
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

#include "motion.h"
#include "player_idUI.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "obstacle_manager.h"
#include "obstacle.h"
#include "Particle.h"
#include "rat_ghost.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY			(1.0f)			// 重力
#define ADD_MOVE_Y		(30.0f)			// 浮力
#define NONE_RATIDX		(-1)			// ネズミの番号の初期値
#define ATTACK_DISTANCE	(200.0f)		// 攻撃範囲までの距離
#define MAX_LIFE		(3)				// 寿命の最大値
#define TIME_DAMAGE		(60 * 1)		// ダメージ食らうまでの時間
#define SPEED			(20.0f)			// 速度
#define SIZE			(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// サイズ

//==============================
// コンストラクタ
//==============================
CRat::CRat() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;				// モーションの情報
	m_pPlayerID = nullptr;				// プレイヤーのID表示
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_nRatIdx = NONE_RATIDX;			// ネズミの番号
	m_nLife = 0;						// 寿命
	m_nDamageCounter = TIME_DAMAGE;		// ダメージ食らうまでのカウンター
	m_fSpeed = 0.0f;					// 速度
	m_bJump = false;					// ジャンプしたか
	m_bAttack = false;					// 攻撃したか
	MotionType = MOTIONTYPE_NEUTRAL;	// モーションの状態
	m_State = STATE_NONE;				// 状態
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
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

	  // 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// ベタ打ち
	SetNumModel(6);

	// データの設定処理
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // モーションが NULL だった場合

	  // モーションの生成処理
		m_pMotion = CMotion::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (m_pMotion != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ロード処理
		m_pMotion->Load(CMotion::TYPE_CAT);
	}
	else
	{ // ポインタが NULL じゃない場合

	  // 停止
		assert(false);
	}

	// モーションの設定処理
	m_pMotion->Set(MotionType);

	// 全ての値を初期化する
	m_pPlayerID = nullptr;				// プレイヤーのID表示
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_nRatIdx = NONE_RATIDX;			// ネズミの番号
	m_fSpeed = 0.0f;					// 速度
	m_nLife = MAX_LIFE;					// 寿命
	m_nDamageCounter = TIME_DAMAGE;		// ダメージ食らうまでのカウンター
	m_bJump = false;					// ジャンプしたか
	m_bAttack = false;					// 攻撃したか
	m_State = STATE_NONE;				// 状態

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CRat::Uninit(void)
{
	if (m_pMotion != nullptr)
	{ // モーションが NULL じゃない場合

		// モーションのメモリを開放する
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_pPlayerID != nullptr)
	{ // プレイヤーのID表示が NULL じゃない場合

		// プレイヤーのID表示の終了処理
		m_pPlayerID->Uninit();
		m_pPlayerID = nullptr;
	}

	// ネズミを消去する
	CGame::DeleteRat(m_nRatIdx);

	// 終了処理
	CCharacter::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CRat::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 移動量を設定する(移動量を常に一定にするため)
	m_fSpeed = SPEED;

	// 障害物との当たり判定
	collision::ObstacleHit(this, SIZE.x, SIZE.y, SIZE.z);

	if (m_State != STATE_DEATH)
	{ // 死亡状態以外のとき

		// 移動処理
		Move();

		// ジャンプ処理
		Jump();

		// 攻撃処理
		Attack();

		//// モーションの設定処理
		MotionManager();

		if (Hit() == true)
		{ // ヒット処理で死んだ場合

			// この先の処理を行わない
			return;
		}
	}

	// 起伏地面の当たり判定
	Elevation();

	// 障害物との当たり判定
	ObstacleCollision();

	// 状態更新処理
	UpdateState();

	if (m_pMotion != nullptr)
	{ // モーションが NULL じゃない場合

		// モーションの更新処理
		m_pMotion->Update();
	}

	if (m_pPlayerID != nullptr)
	{ // プレイヤーのID表示が NULL じゃない場合

		// 位置を取得する
		D3DXVECTOR3 pos = GetPos();

		// 位置を設定する
		m_pPlayerID->SetPos(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z));
	}

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n向き：%f %f %f\nジャンプ状況：%d\n寿命：%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump, m_nLife);
}

//=====================================
// 破片の描画処理
//=====================================
void CRat::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::MotionManager(void)
{
	if (m_bJump == true)
	{
		if (MotionType != MOTIONTYPE_JUMP)
		{
			MotionType = MOTIONTYPE_JUMP;

			// モーションの設定処理
			m_pMotion->Set(MotionType);
		}
	}
	else if (m_move.x > 0.05f || m_move.x < -0.05f ||
			m_move.z > 0.05f || m_move.z < -0.05f)
	{
		if (MotionType != MOTIONTYPE_MOVE)
		{
			MotionType = MOTIONTYPE_MOVE;

			// モーションの設定処理
			m_pMotion->Set(MotionType);
		}
	}
	else
	{
		if (MotionType != MOTIONTYPE_NEUTRAL)
		{
			MotionType = MOTIONTYPE_NEUTRAL;

			// モーションの設定処理
			m_pMotion->Set(MotionType);
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率

	// 情報を設定する
	m_nRatIdx = nID;					// ネズミの番号
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_fSpeed = 0.0f;					// 速度
	m_nLife = MAX_LIFE;					// 寿命
	m_nDamageCounter = TIME_DAMAGE;		// ダメージ食らうまでのカウンター
	m_bJump = false;					// ジャンプしたか
	m_bAttack = false;					// 攻撃したか
	m_State = STATE_NONE;				// 状態

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_RAT + nCntData));		// データの設定処理
	}

	// モーションの設定処理
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	//if (m_pPlayerID == nullptr)
	//{ // プレイヤーのID表示が NULL の場合

	//	// プレイヤーのID表示の生成処理
	//	m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z), m_nRatIdx);
	//}
}

//=======================================
// 移動量の設定処理
//=======================================
void CRat::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CRat::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 速度の設定処理
//=======================================
void CRat::SetSpeed(const float fSpeed)
{
	// 速度を設定する
	m_fSpeed = fSpeed;
}

//=======================================
// 速度の取得処理
//=======================================
float CRat::GetSpeed(void) const
{
	// 速度を返す
	return m_fSpeed;
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
CRat* CRat::Create(const D3DXVECTOR3& pos, const int nID)
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
		pRat->SetData(pos, nID);
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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nRatIdx) > 0)
	{ // 右を押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
		{ // 上を押した場合

			// 向きを設定する
			rot.y = D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
		{ // 下を押した場合

			// 向きを設定する
			rot.y = D3DX_PI * -0.25f;
		}
		else
		{ // 上記以外

			// 向きを設定する
			rot.y = D3DX_PI * -0.5f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nRatIdx) < 0)
	{ // 左を押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
		{ // 上を押した場合

			// 向きを設定する
			rot.y = D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
		{ // 下を押した場合

			// 向きを設定する
			rot.y = D3DX_PI * 0.25f;
		}
		else
		{ // 上記以外

			// 向きを設定する
			rot.y = D3DX_PI * 0.5f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
	{ // 上を押した場合

		// 向きを設定する
		rot.y = D3DX_PI;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
	{ // 下を押した場合

		// 向きを設定する
		rot.y = 0.0f;
	}
	else
	{ // 上記以外

		// 速度を設定する
		m_fSpeed = 0.0f;
	}

	// 移動量を設定する
	m_move.x = -sinf(rot.y) * m_fSpeed;
	m_move.z = -cosf(rot.y) * m_fSpeed;

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

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		m_bJump == false)
	{ // Aボタンを押した場合

		m_move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, m_nRatIdx) == true &&
		m_bJump == false)
	{ // Aボタンを押した場合

		m_move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
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

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B,m_nRatIdx) == true/* && m_bAttack == false*/)
	{ // Bボタンを押した場合

		while (pObstacle != nullptr)
		{ // ブロックの情報が NULL じゃない場合

			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
				SIZE, pObstacle->GetFileData().vtxMax,
				-SIZE, pObstacle->GetFileData().vtxMin) == true)
			{ // XYの矩形に当たってたら

				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
					SIZE, pObstacle->GetFileData().vtxMax,
					-SIZE, pObstacle->GetFileData().vtxMin) == true)
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
// 状態更新処理
//=======================================
void CRat::UpdateState(void)
{
	switch (m_State)
	{
	case CRat::STATE_NONE:		// 何でもない状態
		break;
	case CRat::STATE_WAIT:		// 待機状態
		break;
	case CRat::STATE_RUN:		// 走行状態
		break;
	case CRat::STATE_ATTACK:	// 攻撃状態
		break;
	case CRat::STATE_MUTEKI:	// 無敵状態
		break;
	case CRat::STATE_DAMAGE:	// ダメージ状態
		break;
	case CRat::STATE_DEATH:		// 死亡状態

		// ネズミの幽霊の生成
		CRatGhost::Create(GetPos());

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=======================================
// ヒット処理
//=======================================
bool CRat::Hit(void)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = GetPos();

	if (m_nDamageCounter >= TIME_DAMAGE)
	{ // ダメージ食らう時間になったら

		while (pObstacle != nullptr)
		{ // ブロックの情報が NULL じゃない場合

			/*if (useful::RectangleCollisionXY(pos, pObstacle->GetPos(),
				SIZE, pObstacle->GetFileData().vtxMax,
				-SIZE, pObstacle->GetFileData().vtxMin) == true)*/
			{ // XYの矩形に当たってたら

				if (useful::RectangleCollisionXZ(pos, pObstacle->GetPos(),
					SIZE, pObstacle->GetFileData().vtxMax,
					-SIZE, pObstacle->GetFileData().vtxMin) == true)
				{ // XZの矩形に当たってたら

					m_nLife--;		// 寿命減らす
					m_nDamageCounter = 0;		// ダメージ食らうまでの時間リセット

					CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //パーティクル

					if (m_nLife <= 0)
					{ // 寿命が無いとき

						m_State = STATE_DEATH;		// 死亡状態にする

						// 終了処理
						//Uninit();

						// 死を返す
						return true;
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

	// 生を返す
	return false;
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

			m_move.y = 0.0f;

			m_bJump = false;		// ジャンプしてない状態にする
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

	// 障害物との衝突判定
	collision::ObstacleCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z);

	// ブロックとの当たり判定
	collision::BlockCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z);

	// 位置を設定する
	SetPos(pos);
}

//=======================================
// ネズミの状態の設定処理
//=======================================
void CRat::SetState(STATE state)
{
	m_State = state;
}

//=======================================
// ネズミの状態の取得処理
//=======================================
CRat::STATE CRat::GetState(void)
{
	return m_State;
}