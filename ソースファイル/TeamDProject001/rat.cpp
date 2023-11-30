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
#include "player.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "obstacle_manager.h"
#include "obstacle.h"
#include "Particle.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "object3Dfan.h"
#include "recoveringUI.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY				(1.0f)			// 重力
#define ADD_MOVE_Y			(30.0f)			// 浮力
#define NONE_RATIDX			(-1)			// ネズミの番号の初期値
#define ATTACK_DISTANCE		(230.0f)		// 攻撃範囲までの距離
#define SPEED				(20.0f)			// 速度
#define SIZE				(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// 当たり判定でのサイズ
#define STUN_HEIGHT			(80.0f)			// 気絶演出が出てくる高さ
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// 吹き飛び状態の移動量
#define TIME_RESURRECTION	(60 * 4)		// 復活時間
#define INVINCIBLE_COUNT	(60)			// 無敵カウント

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
//int CRat::m_nNumAll = 0;				// ネズミの総数
bool CRat::m_bResurrection = false;		// 復活させてるのか

//==============================
// コンストラクタ
//==============================
CRat::CRat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_nRezCounter = 0;					// 回復するまでのカウンター
	m_bJump = false;					// ジャンプ状況
	//m_nNumAll++;						// ネズミの総数加算
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
	if (FAILED(CPlayer::Init()))
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

	// モーションのポインタを宣言
	CMotion* pMotion = nullptr;

	if (pMotion == nullptr)
	{ // モーションが NULL だった場合

		// モーションの生成処理
		pMotion = CMotion::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (pMotion != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ロード処理
		pMotion->Load(CMotion::TYPE_RAT);
	}
	else
	{ // ポインタが NULL じゃない場合

	  // 停止
		assert(false);
	}

	// モーションの設定処理
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	// モーションの情報を設定する
	SetMotion(pMotion);

	// 全ての値を初期化する
	m_bJump = false;				// ジャンプ状況

	// 値を返す
	return S_OK;
}

//========================================
// ネズミの終了処理
//========================================
void CRat::Uninit(void)
{
	// プレイヤーを消去する
	CGame::DeletePlayer(GetPlayerIdx());

	// 終了処理
	CPlayer::Uninit();
}

//=====================================
// ネズミの更新処理
//=====================================
void CRat::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 移動量を設定する(移動量を常に一定にするため)
	SetSpeed(SPEED);

	// 重力処理
	Gravity();

	if (CPlayer::GetStunState() != CPlayer::STUNSTATE_STUN &&
		CPlayer::GetState() != CPlayer::STATE_DEATH)
	{ // 気絶状態or死亡状態じゃない場合

		// ジャンプ処理
		Jump();

		if (GetStunState() != STUNSTATE_SMASH)
		{ // 吹き飛び状態の場合

			// 移動操作処理
			MoveControl();
		}

		// 攻撃処理
		Attack();

		// モーションの設定処理
		MotionManager();

		// 生き返りの当たり判定
		ResurrectionCollision();

		//移動処理
		Move();
	}

	// 起伏地面の当たり判定
	Elevation();

	//壁との当たり判定
	SetPos(collision::WallCollision(GetPosOld(), GetPos()));

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E))
	{
		collision::ObstacleAction(this, SIZE.x * 2.0f, CPlayer::TYPE_RAT);
	}

	// プレイヤーの更新処理
	CPlayer::Update();

	// デバッグ表示
	//CManager::Get()->GetDebugProc()->Print("\nネズミの総数:%d\n", m_nNumAll);
	CManager::Get()->GetDebugProc()->Print("蘇生カウント：%d\n", CPlayer::GetResurrectionTime());
}

//=====================================
// ネズミの描画処理
//=====================================
void CRat::Draw(void)
{
	// 描画処理
	CPlayer::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::MotionManager(void)
{
	// モーションの種類を取得する
	int nMotionType = GetMotion()->GetType();

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // リザルト

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // ねずみのかち

			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // ねこのかち

			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
	}
	else
	{ // リザルト以外のとき

		if (m_bJump == true)
		{
			if (nMotionType != MOTIONTYPE_JUMP)
			{
				nMotionType = MOTIONTYPE_JUMP;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (GetMove().x > 0.05f || GetMove().x < -0.05f ||
			GetMove().z > 0.05f || GetMove().z < -0.05f)
		{
			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else
		{
			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// 情報の設定処理
	CPlayer::SetData(pos, nID, type);

	// 当たり判定のサイズの設定
	SetSizeColl(SIZE);

	// 情報を設定する
	m_bJump = false;				// ジャンプしたか

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
	GetMotion()->Set(MOTIONTYPE_NEUTRAL);

	//if (m_pPlayerID == nullptr)
	//{ // プレイヤーのID表示が NULL の場合

	//	// プレイヤーのID表示の生成処理
	//	m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z), m_nRatIdx);
	//}
}

//=======================================
// ジャンプ処理
//=======================================
void CRat::Jump(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 move = GetMove();

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		GetStunState() != STUNSTATE_SMASH &&
		m_bJump == false)
	{ // Aボタンを押した場合

		move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, GetPlayerIdx()) == true &&
		GetStunState() != STUNSTATE_SMASH &&
		m_bJump == false)
	{ // Aボタンを押した場合

		move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
	}

	// 情報を適用する
	SetMove(move);
}

//=======================================
// 重力処理
//=======================================
void CRat::Gravity(void)
{
	// 移動量を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// 重力を加算する
	move.y -= GRAVITY;

	// 位置を加算する
	pos.y += move.y;

	// 移動量を適用する
	SetPos(pos);
	SetMove(move);
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

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, GetPlayerIdx()) == true/* && m_bAttack == false*/)
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
void CRat::Hit(void)
{
	// ローカル変数宣言
	CPlayer *pPlayer;						// ネズミの情報
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	STATE state = GetState();				// 状態を取得する
	STUNSTATE stunState = GetStunState();	// 気絶状態を取得する
	int nCntDeath = 0;						// 死亡した数

	if (state == STATE_NONE &&
		stunState == STUNSTATE_NONE)
	{ // ダメージ受ける状態だった場合

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //パーティクル

		SetState(STATE_DEATH);				// 死亡状態にする

		// 生き返りの円の範囲生成
		CPlayer::SetRessrectionFan(pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// ネズミの幽霊の生成
		CPlayer::SetRatGhost(pos);

		// 回復中UIの生成
		CPlayer::SetRecoveringUI(pos, GetPosOld());

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			// プレイヤーの情報を取得する
			pPlayer = CGame::GetPlayer(nCnt);

			if (pPlayer != nullptr &&
				pPlayer->GetType() == TYPE_RAT && 
				pPlayer->GetState() == STATE_DEATH)
			{ // 死亡してるネズミの時

				nCntDeath++;
			}
		}

		if (nCntDeath >= (MAX_PLAY - 1))
		{ // ネズミ全匹死んだら

			// ネコが勝利した状態にする
			CGame::SetState(CGame::STATE_CAT_WIN);
		}

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
	D3DXVECTOR3 move = GetMove();			// 移動量を取得する
	float fHeight = 0.0f;					// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight;

			move.y = 0.0f;

			m_bJump = false;		// ジャンプしてない状態にする
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置と移動量を更新する
	SetPos(pos);
	SetMove(move);
}

//=======================================
// 生き返りの当たり判定
//=======================================
void CRat::ResurrectionCollision(void)
{
	CPlayer *pPlayer;						// ネズミの情報
	bool bCollXY = false;					// XYの範囲に入ったか
	bool bCollXZ = false;					// XZの範囲に入ったか
	bool abRez[MAX_PLAY];					// 回復してるか
	STATE state = GetState();				// 状態を取得する
	STUNSTATE stunState = GetStunState();	// 気絶状態を取得する

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// プレイヤーの情報を取得する
		pPlayer = CGame::GetPlayer(nCnt);
		abRez[nCnt] = false;

		if (pPlayer != nullptr &&
			pPlayer->GetType() == TYPE_RAT &&
			GetPlayerIdx() != pPlayer->GetPlayerIdx())
		{ // 操作してるネズミじゃないとき

			if (pPlayer->GetState() == STATE_DEATH &&
				state != STATE_DEATH && 
				stunState != STUNSTATE::STUNSTATE_SMASH &&
				stunState != STUNSTATE::STUNSTATE_STUN)
			{ // 他のネズミが死亡状態 && 操作してるネズミが復活させれる状態の時

				// 円の当たり判定(XY平面)取得
				bCollXY = useful::CircleCollisionXY(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// 円の当たり判定(XZ平面)取得
				bCollXZ = useful::CircleCollisionXZ(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// 他のネズミとの当たり判定
				if (bCollXY == true && bCollXZ == true)
				{ // 円の当たり判定(XY平面)と(XZ平面)の範囲にいる場合

					if (m_bResurrection == false)
					{ // 復活させてない状態だったら

						// 復活させてる状態にする
						m_bResurrection = true;
						//pPlayer->SetDispRecoveringUI(m_bResurrection);
					}

					// 回復させてる状態にする
					abRez[nCnt] = true;

					// 現在の生き返りの時間取得
					m_nRezCounter = pPlayer->GetResurrectionTime();
							
					// 生き返りのカウンター加算
					m_nRezCounter++;

					pPlayer->SetResurrectionTime(m_nRezCounter);

					if (pPlayer->GetResurrectionTime() >= TIME_RESURRECTION)
					{ // 一定時間経ったら

						// 無敵状態にする
						pPlayer->SetState(STATE_INVINCIBLE);
						pPlayer->SetStateCount(INVINCIBLE_COUNT);

						// 円の範囲の破棄
						pPlayer->DeleteRessrectionFan();

						// 幽霊ネズミの破棄
						pPlayer->DeleteRatGhost();

						// 回復中UIの破棄
						pPlayer->DeleteRecoveringUI();

						// 生き返りのカウンター初期化
						pPlayer->SetResurrectionTime(0);
						m_nRezCounter = 0;

						// 復活させてない状態にする
						m_bResurrection = false;
					}
				}
				else if (m_bResurrection == false && (bCollXY == false || bCollXZ == true))
				{ // 復活させてない状態 && 円の当たり判定(XY平面)か(XZ平面)の範囲にいない場合

					if (pPlayer->GetResurrectionTime() > 0)
					{ // 生き返りのカウンターが加算されてたら

						pPlayer->AddResurrectionTime(-1);		// カウンター減算
					}
					else
					{ // 生き返りのカウンターが0以下だったら

						// 生き返りのカウンター初期化
						pPlayer->SetResurrectionTime(0);
					}
				}

				// 回復する範囲の情報取得
				CRessrectionFan *pResurrectionFan = pPlayer->GetRessrectionFan();

				if (pResurrectionFan != nullptr)
				{ // 回復する範囲が NULLのとき

					// 回復の範囲の時間設定
					pResurrectionFan->SetResurrectionFan(pPlayer->GetResurrectionTime());
				}

				// 回復中UI表示設定
				pPlayer->SetDispRecoveringUI(abRez[nCnt]);
			}
		}
	}

	if (abRez[0] == false && abRez[1] == false && abRez[2] == false && abRez[3] == false)
	{ // 全員が誰も助けてないとき

		// 復活させてない状態にする
		m_bResurrection = false;
	}
}