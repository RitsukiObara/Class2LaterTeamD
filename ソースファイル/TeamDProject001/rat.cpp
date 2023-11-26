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
#include "rat_state.h"
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

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY				(1.0f)			// 重力
#define ADD_MOVE_Y			(30.0f)			// 浮力
#define NONE_RATIDX			(-1)			// ネズミの番号の初期値
#define ATTACK_DISTANCE		(230.0f)		// 攻撃範囲までの距離
#define MAX_LIFE			(1)				// 寿命の最大値
#define SPEED				(20.0f)			// 速度
#define SIZE				(D3DXVECTOR3(30.0f, 50.0f, 30.0f))		// 当たり判定でのサイズ
#define STUN_HEIGHT			(80.0f)			// 気絶演出が出てくる高さ
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// 吹き飛び状態の移動量
#define TIME_RESURRECTION	(60 * 4)		// 復活時間

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
int CRat::m_nNumAll = 0;				// ネズミの総数
int CRat::m_nResurrectionCounter = 0;	// 生き返るまでのカウンター

//==============================
// コンストラクタ
//==============================
CRat::CRat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pRatState = nullptr;				// ネズミの状態の情報
	m_pRatGhost = nullptr;				// 幽霊ネズミの情報
	m_pRessrectionFan = nullptr;		// 円の範囲の情報
	m_nRatIdx = NONE_RATIDX;			// ネズミの番号
	m_bJump = false;					// ジャンプ状況
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
	m_nRatIdx = NONE_RATIDX;		// ネズミの番号
	m_bJump = false;				// ジャンプ状況

	// 値を返す
	return S_OK;
}

//========================================
// ネズミの終了処理
//========================================
void CRat::Uninit(void)
{
	if (m_pRatState != nullptr)
	{ // ネズミの状態が NULL じゃない場合

		// ネズミの状態の終了処理
		delete m_pRatState;
		m_pRatState = nullptr;
	}

	if (m_pRatGhost != nullptr)
	{ // 幽霊ネズミが NULL じゃない場合

		//幽霊ネズミの終了処理
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}

	if (m_pRessrectionFan != nullptr)
	{ // 円の範囲が NULL じゃない場合

		//円の範囲の終了処理
		//m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}

	// ネズミを消去する
	CGame::DeleteRat(m_nRatIdx);

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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E))
	{
		collision::ObstacleAction(this, SIZE.x, CObstacle::COLLTYPE_RAT);
	}

	if (m_pRatState != nullptr)
	{ // ネズミの状態が NULL じゃない場合

		// ネズミの状態の更新処理
		m_pRatState->Update(*this);
	}

	// プレイヤーの更新処理
	CPlayer::Update();

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("\nネズミの総数:%d\n", m_nNumAll);
	CManager::Get()->GetDebugProc()->Print("蘇生カウント：%d\n", m_nResurrectionCounter);
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

	// 情報を設定する
	m_nRatIdx = nID;				// ネズミの番号
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
// ネズミの番号の取得処理
//=======================================
int CRat::GetRatIdx(void) const
{
	// ネズミの番号を返す
	return m_nRatIdx;
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
// 幽霊ネズミの情報取得処理
//=======================================
CRatGhost* CRat::GetRatGhost(void)
{
	// 幽霊ネズミの情報を返す
	return m_pRatGhost;
}

//=======================================
// 幽霊ネズミの情報消去処理
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
// 円の範囲の情報取得処理
//=======================================
CRessrectionFan* CRat::GetRessrectionFan(void)
{
	// 円の範囲の情報を返す
	return m_pRessrectionFan;
}

//=======================================
// 円の範囲の情報消去処理
//=======================================
void CRat::DeleteRessrectionFan(void)
{
	if (m_pRessrectionFan != nullptr)
	{ // 円の範囲が NULL じゃない場合

		//円の範囲の終了処理
		m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}
}

//=======================================
// ジャンプ処理
//=======================================
void CRat::Jump(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = GetMove();

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
		m_bJump == false)
	{ // Aボタンを押した場合

		move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
	}

#endif // _DEBUG

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, m_nRatIdx) == true &&
		m_pRatState->GetState() != CRatState::STATE_SMASH &&
		m_bJump == false)
	{ // Aボタンを押した場合

		move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
	}

	move.y -= GRAVITY;		// 重力加算

	// 位置を加算する
	pos += move;

	// 情報を適用する
	SetPos(pos);
	SetRot(rot);
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
void CRat::Hit(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	int nLife = GetLife();			// 寿命を取得する
	CRatState::STATE state = m_pRatState->GetState();	// 状態を取得する

	if (state != CRatState::STATE_DAMAGE && 
		state != CRatState::STATE_INVINCIBLE)
	{ // ダメージ受ける状態だった場合
		nLife--;			// 寿命減らす

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //パーティクル

		if (nLife <= 0)
		{ // 寿命が無いとき

			m_pRatState->SetState(CRatState::STATE_DEATH);		// 死亡状態にする

			// 生き返りの円の範囲生成
			if (m_pRessrectionFan == nullptr)
			{ // 円の範囲が NULL のとき

				m_pRessrectionFan = CRessrectionFan::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			// ネズミの幽霊の生成
			if (m_pRatGhost == nullptr)
			{ // 幽霊ネズミが NULL のとき

				m_pRatGhost = CRatGhost::Create(pos);

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
		}
		else
		{ // 上記以外

			m_pRatState->SetState(CRatState::STATE_DAMAGE);		// ダメージ状態にする
		}
	}

	// 寿命を設定する
	SetLife(nLife);
}

//=======================================
// 吹き飛び状態
//=======================================
void CRat::Smash(const float fAngle)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	D3DXVECTOR3 move = GetMove();	// 移動量を取得する
	CRatState::STATE state = m_pRatState->GetState();	// 状態を取得する

	if (state != CRatState::STATE_DAMAGE &&
		state != CRatState::STATE_INVINCIBLE &&
		state != CRatState::STATE_SMASH &&
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // ダメージ受ける状態だった場合

		// 移動量を算出する
		move.x = sinf(fAngle) * SMASH_MOVE.x;
		move.y = SMASH_MOVE.y;
		move.z = cosf(fAngle) * SMASH_MOVE.z;

		// 吹き飛び状態にする
		m_pRatState->SetState(CRatState::STATE_SMASH);
	}

	// 移動量を適用する
	SetMove(move);
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
		state != CRatState::STATE_DEATH &&
		state != CRatState::STATE_STUN)
	{ // ダメージ受ける状態だった場合

		// 気絶状態にする
		m_pRatState->SetState(CRatState::STATE_STUN);

		// 気絶演出の設定処理
		SetStun(GetPos());
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
	//CPlayer *pRat;		// ネズミの情報
	//bool bCollYZ = false;		// 当たったか

	//// 状態を取得する
	//CRatState::STATE state = m_pRatState->GetState();

	//for (int nCntRat = 0; nCntRat < MAX_RAT; nCntRat++)
	//{
	//	if (m_nRatIdx != nCntRat)
	//	{ // 操作してるネズミじゃないとき

	//		// 他のネズミの情報取得
	//		pRat = CGame::GetRat(nCntRat);

	//		if (pRat->GetState()->GetState() == CRatState::STATE_DEATH && 
	//			state != CRatState::STATE_STUN && state != CRatState::STATE_DEATH)
	//		{ // 他のネズミが死亡状態 && 操作してるネズミが復活させれる状態の時

	//			// 他のネズミとの当たり判定
	//			if (useful::CircleCollisionXY(GetPos(), pRat->GetPos(), 30.0f, ATTACK_DISTANCE) == true)
	//			{ // 円の当たり判定(XY平面)

	//				// 円の当たり判定(XZ平面)
	//				bCollYZ = useful::CircleCollisionXZ(GetPos(), pRat->GetPos(), 30.0f, ATTACK_DISTANCE);

	//				if (bCollYZ == true)
	//				{ // 円の当たり判定(XZ平面)

	//					// 生き返りのカウンター加算
	//					m_nResurrectionCounter++;

	//					if (m_nResurrectionCounter >= TIME_RESURRECTION)
	//					{ // 一定時間経ったら

	//						// 無敵状態にする
	//						pRat->GetState()->SetState(CRatState::STATE_INVINCIBLE);

	//						// 円の範囲の破棄
	//						pRat->DeleteRessrectionFan();

	//						// 幽霊ネズミの破棄
	//						pRat->DeleteRatGhost();

	//						// 生き返りのカウンター初期化
	//						m_nResurrectionCounter = 0;

	//						m_nNumAll++;		// 総数増やす
	//					}
	//				}
	//				else if(bCollYZ == false)
	//				{
	//					// 生き返りのカウンター初期化
	//					m_nResurrectionCounter = 0;
	//				}

	//			}
	//		}
	//	}
	//}
}