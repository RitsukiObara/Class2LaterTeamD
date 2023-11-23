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
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "motion.h"
#include "player_idUI.h"
#include "rat_state.h"
#include "stun.h"
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
#define GRAVITY				(1.0f)			// 重力
#define ADD_MOVE_Y			(30.0f)			// 浮力
#define NONE_RATIDX			(-1)			// ネズミの番号の初期値
#define ATTACK_DISTANCE		(200.0f)		// 攻撃範囲までの距離
#define MAX_LIFE			(1)				// 寿命の最大値
#define SPEED				(20.0f)			// 速度
#define SIZE				(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// 当たり判定でのサイズ
#define STUN_HEIGHT			(80.0f)			// 気絶演出が出てくる高さ
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// 吹き飛び状態の移動量

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
int CRat::m_nNumAll = 0;				// ネズミの総数

//==============================
// コンストラクタ
//==============================
CRat::CRat() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;				// モーションの情報
	m_pPlayerID = nullptr;				// プレイヤーのID表示
	m_pRatState = nullptr;				// ネズミの状態の情報
	m_pStun = nullptr;					// 気絶の情報
	m_pRatGhost = nullptr;				// 幽霊ネズミの情報
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_nRatIdx = NONE_RATIDX;			// ネズミの番号
	m_nLife = 0;						// 寿命
	m_fSpeed = 0.0f;					// 速度
	m_bJump = false;					// ジャンプしたか
	m_bAttack = false;					// 攻撃したか
	m_nNumAll++;						// ネズミの総数加算
}

//==============================
// デストラクタ
//==============================
CRat::~CRat()
{

}

//==============================
// ネズミの初期化処理
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
		m_pMotion->Load(CMotion::TYPE_RAT);
	}
	else
	{ // ポインタが NULL じゃない場合

	  // 停止
		assert(false);
	}

	// モーションの設定処理
	m_pMotion->Set(MotionType);

	if (m_pRatState == nullptr)
	{ // ネズミの状態が NULL の場合
		
		// ネズミの状態の情報を生成する
		m_pRatState = new CRatState;
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}

	// 全ての値を初期化する
	m_pPlayerID = nullptr;			// プレイヤーのID表示
	m_pStun = nullptr;				// 気絶の情報
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_nRatIdx = NONE_RATIDX;		// ネズミの番号
	m_fSpeed = 0.0f;				// 速度
	m_nLife = MAX_LIFE;				// 寿命
	m_bJump = false;				// ジャンプしたか
	m_bAttack = false;				// 攻撃したか

	// 値を返す
	return S_OK;
}

//========================================
// ネズミの終了処理
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

	if (m_pRatState != nullptr)
	{ // ネズミの状態が NULL じゃない場合

		// ネズミの状態の終了処理
		delete m_pRatState;
		m_pRatState = nullptr;
	}

	if (m_pStun != nullptr)
	{ // 気絶演出が NULL じゃない場合

		// 気絶演出の終了処理
		m_pStun->Uninit();
		m_pStun = nullptr;
	}

	if (m_pRatGhost != nullptr)
	{ // 幽霊ネズミが NULL じゃない場合

		//幽霊ネズミの終了処理
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}

	// ネズミを消去する
	CGame::DeleteRat(m_nRatIdx);

	// 終了処理
	CCharacter::Uninit();
}

//=====================================
// ネズミの更新処理
//=====================================
void CRat::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 移動量を設定する(移動量を常に一定にするため)
	m_fSpeed = SPEED;

	// 障害物との当たり判定
	collision::ObstacleHit(this, SIZE.x, SIZE.y, SIZE.z, CObstacle::COLLTYPE_RAT);

	if (m_pRatState->GetState() != CRatState::STATE_DEATH &&
		m_pRatState->GetState() != CRatState::STATE_STUN)
	{ // 幽霊状態と気絶状態以外のとき

		if (m_pRatState->GetState() != CRatState::STATE_SMASH)
		{ // 吹き飛び状態の場合

			// 移動処理
			Move();
		}

		// ジャンプ処理
		Jump();

		// 攻撃処理
		Attack();

		// モーションの設定処理
		MotionManager();

		// 生き返りの当たり判定
		ResurrectionCollision();
	}

	// 起伏地面の当たり判定
	Elevation();

	//壁との当たり判定
	SetPos(collision::WallCollision(GetPosOld(), GetPos()));

	// 障害物との当たり判定
	ObstacleCollision();

	if (m_pRatState != nullptr)
	{ // ネズミの状態が NULL じゃない場合

		// ネズミの状態の更新処理
		m_pRatState->Update(*this);
	}

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
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n向き：%f %f %f\nジャンプ状況：%d\n寿命：%d\nネズミの状態：%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_bJump, m_nLife, m_pRatState->GetState());
	CManager::Get()->GetDebugProc()->Print("\nネズミの総数:%d\n", m_nNumAll);
}

//=====================================
// ネズミの描画処理
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
	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // リザルト

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // ねずみのかち

			if (MotionType != MOTIONTYPE_MOVE)
			{
				MotionType = MOTIONTYPE_MOVE;

				// モーションの設定処理
				m_pMotion->Set(MotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // ねこのかち

			if (MotionType != MOTIONTYPE_NEUTRAL)
			{
				MotionType = MOTIONTYPE_NEUTRAL;

				// モーションの設定処理
				m_pMotion->Set(MotionType);
			}
		}
	}
	else
	{ // リザルト以外のとき

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
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率

	// 情報を設定する
	m_pStun = nullptr;				// 気絶の情報
	m_nRatIdx = nID;				// ネズミの番号
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_fSpeed = 0.0f;				// 速度
	m_nLife = MAX_LIFE;				// 寿命
	m_bJump = false;				// ジャンプしたか
	m_bAttack = false;				// 攻撃したか

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
// // 移動状況の取得処理
//=======================================
bool CRat::IsMove(void)
{
	// 移動状況を返す
	return m_bMove;
}

//=======================================
// ネズミの状態の取得処理
//=======================================
CRatState* CRat::GetState(void)
{
	// ネズミの状態を返す
	return m_pRatState;
}

//=======================================
// 気絶演出の設定処理
//=======================================
void CRat::SetStun(void)
{
	if (m_pStun == nullptr)
	{ // 気絶の情報が NULL だった場合

		// 気絶演出を生成する
		m_pStun = CStun::Create(D3DXVECTOR3(GetPos().x, GetPos().y + STUN_HEIGHT, GetPos().z));
	}
}

//=======================================
// 気絶演出の取得処理
//=======================================
CStun* CRat::GetStun(void)
{
	// 気絶演出を返す
	return m_pStun;
}

//=======================================
// 気絶演出の消去処理
//=======================================
void CRat::DeleteStun(void)
{
	if (m_pStun != nullptr)
	{ // 気絶演出が NULL じゃない場合

		// 気絶演出の終了処理
		m_pStun->Uninit();
		m_pStun = nullptr;
	}
}

//=======================================
// 幽霊ネズミの取得処理
//=======================================
CRatGhost* CRat::GetRatGhost(void)
{
	return m_pRatGhost;
}

//=======================================
// 幽霊ネズミの消去処理
//=======================================
void CRat::DeleteRatGhost(void)
{
	if (m_pRatGhost != nullptr)
	{ // 幽霊ネズミが NULL じゃない場合

		//幽霊ネズミの終了処理
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}
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
		m_bMove = true;
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
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) > 0)
	{ // 上を押した場合

		// 向きを設定する
		rot.y = D3DX_PI;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nRatIdx) < 0)
	{ // 下を押した場合

		// 向きを設定する
		rot.y = 0.0f;
		m_bMove = true;
	}
	else
	{ // 上記以外
		m_bMove = false;
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
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
		m_bJump == false)
	{ // Aボタンを押した場合

		m_move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, m_nRatIdx) == true &&
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
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
// ヒット処理
//=======================================
bool CRat::Hit(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	CRatState::STATE state = m_pRatState->GetState();	// 状態を取得する

	if (state != CRatState::STATE_DAMAGE && 
		state != CRatState::STATE_INVINCIBLE)
	{ // ダメージ受ける状態だった場合
		m_nLife--;			// 寿命減らす

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //パーティクル

		if (m_nLife <= 0)
		{ // 寿命が無いとき

			m_pRatState->SetState(CRatState::STATE_DEATH);		// 死亡状態にする

			// ネズミの幽霊の生成
			if (m_pRatGhost == nullptr)
			{ // 幽霊ネズミが NULL のとき

				m_pRatGhost = CRatGhost::Create(GetPos());

				m_nNumAll--;						// ネズミの総数減算
			}

#if 0	// デバッグの為の処理↓

			// 終了状態にする
			Uninit();
#endif

			if (m_nNumAll <= 0)
			{ // ネズミが全滅したら

				// ネコが勝利した状態にする
				CGame::SetState(CGame::STATE_CAT_WIN);
			}

			// 死を返す
			return true;
		}
		else
		{ // 上記以外

			m_pRatState->SetState(CRatState::STATE_DAMAGE);		// ダメージ状態にする
		}

		// 死を返す
		return true;
	}

	// 生を返す
	return false;
}

//=======================================
// 吹き飛び状態
//=======================================
void CRat::Smash(const float fAngle)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	CRatState::STATE state = m_pRatState->GetState();	// 状態を取得する

	if (state != CRatState::STATE_DAMAGE &&
		state != CRatState::STATE_INVINCIBLE &&
		state != CRatState::STATE_SMASH &&
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // ダメージ受ける状態だった場合

		// 移動量を算出する
		m_move.x = sinf(fAngle) * SMASH_MOVE.x;
		m_move.y = SMASH_MOVE.y;
		m_move.z = cosf(fAngle) * SMASH_MOVE.z;

		// 吹き飛び状態にする
		m_pRatState->SetState(CRatState::STATE_SMASH);
	}
}

//=======================================
// 気絶状態
//=======================================
void CRat::Stun(void)
{
	// 状態を取得する
	CRatState::STATE state = m_pRatState->GetState();

	if (state != CRatState::STATE_DAMAGE &&
		state != CRatState::STATE_INVINCIBLE &&
		state != CRatState::STATE_SMASH &&
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // ダメージ受ける状態だった場合

		// 気絶状態にする
		m_pRatState->SetState(CRatState::STATE_STUN);
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
	collision::ObstacleCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z, CObstacle::COLLTYPE_RAT);

	// ブロックとの当たり判定
	collision::BlockCollision(pos, GetPosOld(), SIZE.x, SIZE.y, SIZE.z);

	// 位置を設定する
	SetPos(pos);
}

//=======================================
// 生き返りの当たり判定
//=======================================
void CRat::ResurrectionCollision(void)
{
	CRat *pRat;		// ネズミの情報

	// 状態を取得する
	CRatState::STATE state = m_pRatState->GetState();

	for (int nCntRat = 0; nCntRat < MAX_RAT; nCntRat++)
	{
		if (m_nRatIdx != nCntRat)
		{ // 操作してるネズミじゃないとき

			// 他のネズミの情報取得
			pRat = CGame::GetRat(nCntRat);

			if (pRat->GetState()->GetState() == CRatState::STATE_DEATH && 
				state != CRatState::STATE_STUN && state != CRatState::STATE_DEATH)
			{ // 他のネズミが死亡状態 && 操作してるネズミが復活させれる状態の時

				// 他のネズミとの当たり判定
				if (useful::RectangleCollisionXY(GetPos(), pRat->GetPos(),
					D3DXVECTOR3(30.0f, 50.0f, 30.0f), D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
				{ // XY座標の矩形の当たり判定

					if (useful::RectangleCollisionXZ(GetPos(), pRat->GetPos(),
						D3DXVECTOR3(30.0f, 50.0f, 30.0f), D3DXVECTOR3(30.0f, 50.0f, 30.0f),
						D3DXVECTOR3(-30.0f, -50.0f, -30.0f), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
					{ // XZの矩形に当たってたら

						// 無敵状態にする
						pRat->GetState()->SetState(CRatState::STATE_INVINCIBLE);

						// 幽霊ネズミの破棄
						pRat->DeleteRatGhost();

						m_nNumAll++;		// 総数増やす
					}
				}
			}
		}
	}
}