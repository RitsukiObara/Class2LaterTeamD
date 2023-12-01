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
#include "game.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"
#include "MultiCamera.h"

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "collision.h"
#include "recoveringUI.h"
#include "speech_message.h"
#include "death_arrow.h"

#include "Cat.h"
#include "rat.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY				(1.0f)			// 重力
#define ADD_MOVE_Y			(30.0f)			// 浮力
#define NONE_PLAYERIDX		(-1)			// プレイヤーの番号の初期値
#define STUN_HEIGHT			(80.0f)			// 気絶演出が出てくる高さ
#define ID_HEIGHT			(150.0f)		// IDが出てくる高さ
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// 吹き飛び状態の移動量
#define STUN_WAIT			(120)			// オブジェクト無効の待機時間
#define DEATH_WAIT			(120)			// 死亡時の待機時間
#define SMASH_WAIT			(40)			// 吹き飛び状態のカウント数
#define CAT_CAMERA_HEIGHT	(200.0f)		// 猫のカメラの高さ
#define CAT_CAMERA_DIS		(300.0f)		// 猫のカメラの視点と注視点の高さの差分(角度)
#define RAT_CAMERA_HEIGHT	(30.0f)			// ネズミのカメラの高さ
#define RAT_CAMERA_DIS		(60.0f)			// ネズミのカメラの視点と注視点の高さの差分(角度)

//==============================
// コンストラクタ
//==============================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// コンストラクタの箱
	Box();
}

//==============================
// オーバーロードコンストラクタ
//==============================
CPlayer::CPlayer(CObject::TYPE type, PRIORITY priority) : CCharacter(type, priority)
{
	// コンストラクタの箱
	Box();
}

//==============================
// デストラクタ
//==============================
CPlayer::~CPlayer()
{

}

//==============================
// コンストラクタの箱
//==============================
void CPlayer::Box(void)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;				// モーションの情報
	m_pPlayerID = nullptr;				// プレイヤーのID表示
	m_pStun = nullptr;					// 気絶の情報
	m_pRatGhost = nullptr;				// 幽霊ネズミの情報
	m_pRessrectionFan = nullptr;		// 円の範囲の情報
	m_pRecoveringUI = nullptr;			// 回復中のUIの情報
	m_pSpeechMessage = nullptr;			// 伝達メッセージの情報
	m_pDeathArrow[MAX_PLAY] = {};		// 死亡矢印の情報
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_type = TYPE_CAT;					// 種類
	m_nPlayerIdx = NONE_PLAYERIDX;		// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか
	m_CameraRot = NONE_D3DXVECTOR3;		// カメラの向き
	m_nResurrectionTime = 0;			// 復活するまでの時間

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		m_apLog[nCnt] = NULL;
	}
	m_nLogNumber = 0;
}

//==============================
// プレイヤーの初期化処理
//==============================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pMotion = nullptr;				// モーションの情報
	m_pPlayerID = nullptr;				// プレイヤーのID表示
	m_pStun = nullptr;					// 気絶の情報
	m_pRatGhost = nullptr;				// 幽霊ネズミの情報
	m_pRessrectionFan = nullptr;		// 円の範囲の情報
	m_pRecoveringUI = nullptr;			// 回復中のUIの情報
	m_pSpeechMessage = nullptr;			// 伝達メッセージの情報
	m_pDeathArrow[MAX_PLAY] = {};		// 死亡矢印の情報
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_type = TYPE_CAT;					// 種類
	m_nPlayerIdx = NONE_PLAYERIDX;		// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか
	m_nResurrectionTime = 0;			// 復活するまでの時間

	// 値を返す
	return S_OK;
}

//========================================
// プレイヤーの終了処理
//========================================
void CPlayer::Uninit(void)
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

	if (m_pRessrectionFan != nullptr)
	{ // 円の範囲が NULL じゃない場合

		//円の範囲の終了処理
		m_pRessrectionFan = nullptr;
	}

	if (m_pRecoveringUI != nullptr)
	{ // 回復中のUIが NULL じゃない場合

		//回復中のUIの終了処理
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}

	if (m_pSpeechMessage != nullptr)
	{ // 伝達メッセージが NULL じゃないとき

		//伝達メッセージの終了処理
		m_pSpeechMessage = nullptr;
	}

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (m_pDeathArrow[nCnt] != nullptr)
		{ // 死亡矢印が NULL じゃないとき

			//死亡矢印の終了処理
			m_pDeathArrow[nCnt]->Uninit();
			m_pDeathArrow[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Uninit();
			m_apLog[nCnt] = NULL;
		}
	}

	// プレイヤーを消去する
	CGame::DeletePlayer(m_nPlayerIdx);

	// 終了処理
	CCharacter::Uninit();
}

//=====================================
// プレイヤーの更新処理
//=====================================
void CPlayer::Update(void)
{
	// 障害物との当たり判定
	collision::ObstacleHit(this, m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	// 障害物との当たり判定
	ObstacleCollision();

	// 気絶状態の管理
	StunStateManager();

	// 状態の管理
	StateManager();

	if (m_type == TYPE_CAT)
	{
		collision::ObstacleSearch(this, 30.0f * 2.0f, m_type, m_nPlayerIdx);
	}
	else if (m_type == TYPE_RAT)
	{
		collision::ObstacleSearch(this, 30.0f * 2.0f, m_type, m_nPlayerIdx);
	}

#if CAMERA != 0
	//カメラ情報の更新
	CameraUpdate();
#endif // CAMERA

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E))
	{
		collision::ObstacleAction(this, m_sizeColl.x, m_type);
	}

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1))
	{
		SetLog(CLog::TYPE::TYPE_DEATH);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2))
	{
		SetLog(CLog::TYPE::TYPE_STUN);
	}

#endif // _DEBUG

	if (m_pMotion != nullptr)
	{ // モーションが NULL じゃない場合

		// モーションの更新処理
		m_pMotion->Update();
	}

	if (m_pPlayerID != nullptr)
	{ // プレイヤーのID表示が NULL じゃない場合

		// 位置情報の取得
		D3DXVECTOR3 pos = GetPos();

		// 位置を設定する
		m_pPlayerID->SetPos(D3DXVECTOR3(pos.x, pos.y + ID_HEIGHT, pos.z));
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Update();
		}
	}

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n向き：%f %f %f\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z);
}

//=====================================
// プレイヤーの描画処理
//=====================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Draw();
		}
	}
}

//=====================================
// 吹き飛び状態
//=====================================
void CPlayer::Smash(const float fAngle)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	D3DXVECTOR3 move = GetMove();	// 移動量を取得する

	if (m_State == STATE_NONE &&
		m_StunState == STUNSTATE_NONE)
	{ // ダメージ受ける状態だった場合

		// 移動量を算出する
		move.x = sinf(fAngle) * SMASH_MOVE.x;
		move.y = SMASH_MOVE.y;
		move.z = cosf(fAngle) * SMASH_MOVE.z;

		// 吹き飛び状態にする
		m_StunState = STUNSTATE_SMASH;

		// 気絶状態カウントを設定する
		m_StunStateCount = SMASH_WAIT;
	}

	// 移動量を適用する
	SetMove(move);
}

//=====================================
// 情報の設定処理
//=====================================
void CPlayer::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率

	// 全ての値をクリアする
	m_pStun = nullptr;					// 気絶の情報
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_type = type;						// 種類
	m_nPlayerIdx = nID;					// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか

	if (m_pPlayerID == nullptr)
	{ // プレイヤーのID表示が NULL の場合

		// プレイヤーのID表示の生成処理
		m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + ID_HEIGHT, pos.z), nID);
	}
}

//=======================================
// 生成処理
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// プレイヤーのポインタ
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

		switch (type)
		{
		case TYPE::TYPE_CAT:		// ネコ

			// ネコを生成
			pPlayer = new CCat;

			break;

		case TYPE::TYPE_RAT:		// ネズミ

			// ネズミを生成
			pPlayer = new CRat;

			break;

		default:					// 上記以外

			// 停止
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

	if (pPlayer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPlayer->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPlayer->SetData(pos, nID, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}

//=======================================
// 移動操作処理
//=======================================
void CPlayer::MoveControl(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) > 0)
	{ // 右を押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // 上を押した場合

			// 向きを設定する
			rot.y = m_CameraRot.y + D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
		{ // 下を押した場合

			// 向きを設定する
			rot.y = m_CameraRot.y + D3DX_PI * -0.25f;
		}
		else
		{ // 上記以外

			// 向きを設定する
			rot.y = m_CameraRot.y + D3DX_PI * -0.5f;
		}
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) < 0)
	{ // 左を押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // 上を押した場合

			// 向きを設定する
			rot.y = m_CameraRot.y + D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
		{ // 下を押した場合

			// 向きを設定する
			rot.y = m_CameraRot.y + D3DX_PI * 0.25f;
		}
		else
		{ // 上記以外

			// 向きを設定する
			rot.y = m_CameraRot.y + D3DX_PI * 0.5f;
		}
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
	{ // 上を押した場合

		// 向きを設定する
		rot.y = m_CameraRot.y + D3DX_PI * 1.0f;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
	{ // 下を押した場合

		// 向きを設定する
		rot.y = m_CameraRot.y + D3DX_PI * 0.0f;
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

	// 位置と向きを適用する
	SetRot(rot);
}

//=======================================
// 移動処理
//=======================================
void CPlayer::Move(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 移動量を加算する
	pos += m_move;

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// それぞれのプレイヤーのカメラの更新
//=======================================
void CPlayer::CameraUpdate(void)
{
	CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
	D3DXVECTOR3 Pos = GetPos();

	if (m_type == TYPE::TYPE_CAT)
	{ //猫のカメラの位置
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + CAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}
	else
	{ //ネズミのカメラの位置
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + RAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{
		m_CameraRot.y -= 0.05f;
	}
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true)
	{
		m_CameraRot.y += 0.05f;
	}
}

////=======================================
//// 攻撃処理
////=======================================
//void CPlayer::Attack(void)
//{
//	// ローカル変数宣言
//	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
//	D3DXVECTOR3 pos = GetPos();
//	D3DXVECTOR3 rot = GetRot();
//
//	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B,m_nRatIdx) == true/* && m_bAttack == false*/)
//	{ // Bボタンを押した場合
//
//		while (pObstacle != nullptr)
//		{ // ブロックの情報が NULL じゃない場合
//
//			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//				SIZE, pObstacle->GetFileData().vtxMax,
//				-SIZE, pObstacle->GetFileData().vtxMin) == true)
//			{ // XYの矩形に当たってたら
//
//				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//					SIZE, pObstacle->GetFileData().vtxMax,
//					-SIZE, pObstacle->GetFileData().vtxMin) == true)
//				{ // XZの矩形に当たってたら
//
//					// 障害物の終了処理
//					pObstacle->Uninit();
//				}
//			}
//
//			// 次のオブジェクトを代入する
//			pObstacle = pObstacle->GetNext();
//		}
//
//		//m_bAttack = true;		// 攻撃した状態にする
//	}
//}

//=======================================
// 障害物との当たり判定
//=======================================
void CPlayer::ObstacleCollision(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 障害物との衝突判定
	collision::ObstacleCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	// ブロックとの当たり判定
	collision::BlockCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z);

	// 位置を設定する
	SetPos(pos);
}

//=======================================
// 気絶処理
//=======================================
void CPlayer::Stun(int StunTime)
{
	if (m_StunState == STUNSTATE_NONE &&
		m_State == STATE_NONE)
	{ // 通常状態だった場合

		// 気絶状態にする
		m_StunState = STUNSTATE_STUN;
		m_StunStateCount = StunTime;

		// 気絶演出の設定処理
		SetStun(GetPos());
	}

	////猫とネズミで気絶の仕様を変える場合は使って
	//if (m_type == TYPE_CAT)
	//{ // 猫の場合
	//}
	//else if (m_type == TYPE_RAT)
	//{ // ネズミの場合
	//}
}

//=======================================
// アイテムの取得処理
//=======================================
void CPlayer::GetItem(const CItem::TYPE type)
{

}

//=======================================
// 気絶状態の管理
//=======================================
void CPlayer::StunStateManager(void)
{
	switch (m_StunState)
	{
	case STUNSTATE_NONE:	// 無状態

		break;

	case STUNSTATE_SMASH:	// 吹き飛び状態

		// カウントを減算する
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // カウントが一定数以下になった場合

			// 気絶状態にする
			m_StunState = STUNSTATE_STUN;
			m_StunStateCount = STUN_WAIT;

			// 気絶演出の設定処理
			SetStun(GetPos());
		}

		break;

	case STUNSTATE_STUN:	//気絶状態

		// カウントを減算する
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // カウントが一定数以下になった場合

			// 無敵状態にする
			m_StunState = STUNSTATE_WAIT;
			m_StunStateCount = STUN_WAIT;

			if (m_pStun != nullptr)
			{ // 気絶演出が NULL の場合

				// 気絶演出を削除する
				m_pStun->Uninit();
				m_pStun = nullptr;
			}
		}
		break;

	case STUNSTATE_WAIT:	//障害物のみ無敵状態

		// カウントを減算する
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // カウントが一定数以下になった場合

			// 無状態にする
			m_StunState = STUNSTATE_NONE;
		}
		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=======================================
// 状態の管理
//=======================================
void CPlayer::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NONE:

		break;

	case STATE_INVINCIBLE:	//無敵状態

		// カウントを減算する
		m_StateCount--;

		if (m_StateCount <= 0)
		{ // カウントが一定数以下になった場合
			
			// 無状態にする
			m_State = STATE_NONE;
		}
		break;

	case STATE_DEATH:	//死亡状態


		break;
	}
}

//=======================================
// ログの生成番号の加算
//=======================================
void CPlayer::SetLog(CLog::TYPE Type)
{
	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] == NULL)
		{
			m_apLog[nCnt] = CLog::Create(m_nPlayerIdx, m_nLogNumber, Type);
			m_apLog[nCnt]->SetLogIdx(nCnt);
			m_apLog[nCnt]->SetMain(this);
			break;
		}
	}

	m_nLogNumber++;
}

//=======================================
// ログの生成番号の減算
//=======================================
void CPlayer::DelLogNumber(int nLogIdex)
{
	m_nLogNumber--;

	if (m_apLog[nLogIdex] != NULL)
	{
		m_apLog[nLogIdex]->Uninit();
		m_apLog[nLogIdex] = NULL;
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->DelCreateNumber();
		}
	}
}

//=======================================
// モーションの設定処理
//=======================================
void CPlayer::SetMotion(CMotion* pMotion)
{
	// モーションの情報を設定する
	m_pMotion = pMotion;
}

//=======================================
// モーションの取得処理
//=======================================
CMotion* CPlayer::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//=======================================
// プレイヤーのIDの取得処理
//=======================================
CPlayerID* CPlayer::GetPlayerID(void) const
{
	// プレイヤーのIDの情報を返す
	return m_pPlayerID;
}

//=======================================
// 気絶演出の設定処理
//=======================================
void CPlayer::SetStun(const D3DXVECTOR3& pos)
{
	if (m_pStun == nullptr)
	{ // 気絶演出が NULL の場合

		// 気絶演出を生成する
		m_pStun = CStun::Create(D3DXVECTOR3(pos.x, pos.y + STUN_HEIGHT, pos.z));
	}
}

//=======================================
// 気絶演出の取得処理
//=======================================
CStun* CPlayer::GetStun(void) const
{
	// 気絶の情報を返す
	return m_pStun;
}

//=======================================
// 気絶演出の消去処理
//=======================================
void CPlayer::DeleteStun(void)
{
	if (m_pStun != nullptr)
	{ // 気絶の情報が NULL じゃない場合

		// 気絶の終了処理
		m_pStun->Uninit();
		m_pStun = nullptr;
	}
}

//=======================================
// 幽霊ネズミの設定処理
//=======================================
void CPlayer::SetRatGhost(const D3DXVECTOR3& pos)
{
	if (m_pRatGhost == nullptr)
	{ // 幽霊ネズミが NULL のとき

		// ネズミの幽霊の生成
		m_pRatGhost = CRatGhost::Create(pos);
	}
}

//=======================================
// 幽霊ネズミの情報取得処理
//=======================================
CRatGhost* CPlayer::GetRatGhost(void)
{
	// 幽霊ネズミの情報を返す
	return m_pRatGhost;
}

//=======================================
// 幽霊ネズミの情報消去処理
//=======================================
void CPlayer::DeleteRatGhost(void)
{
	if (m_pRatGhost != nullptr)
	{ // 幽霊ネズミが NULL じゃない場合

		//幽霊ネズミの終了処理
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}
}

//=======================================
// 円の範囲の設定処理
//=======================================
void CPlayer::SetRessrectionFan(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	if (m_pRessrectionFan == nullptr)
	{ // 円の範囲が NULL のとき

		// 生き返りの円の範囲生成
		m_pRessrectionFan = CRessrectionFan::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), col);
	}
}

//=======================================
// 円の範囲の情報取得処理
//=======================================
CRessrectionFan* CPlayer::GetRessrectionFan(void)
{
	// 円の範囲の情報を返す
	return m_pRessrectionFan;
}

//=======================================
// 円の範囲の情報消去処理
//=======================================
void CPlayer::DeleteRessrectionFan(void)
{
	if (m_pRessrectionFan != nullptr)
	{ // 円の範囲が NULL じゃない場合

		//円の範囲の終了処理
		m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}
}

//=======================================
// 回復中UIの設定処理
//=======================================
void CPlayer::SetRecoveringUI(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	if (m_pRecoveringUI == nullptr)
	{ // 回復中UIが NULL のとき

		// 回復中UIの範囲生成
		m_pRecoveringUI = CRecoveringUI::Create(D3DXVECTOR3(pos.x + 80.0f, pos.y + 100.0f, pos.z), posOld);
	}
}

//=======================================
// 回復中UIの情報取得処理
//=======================================
CRecoveringUI* CPlayer::GetRecoveringUI(void)
{
	// 回復中UIの情報を返す
	return m_pRecoveringUI;
}

//=======================================
// 回復中UIの情報消去処理
//=======================================
void CPlayer::DeleteRecoveringUI(void)
{
	if (m_pRecoveringUI != nullptr)
	{ // 回復中UIが NULL じゃない場合

		//回復中UIの終了処理
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}
}

//=======================================
// 伝達メッセージの設定処理
//=======================================
void CPlayer::SetSpeechMessage(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const int type)
{
	if (m_pSpeechMessage == nullptr)
	{ // 伝達メッセージが NULLのとき

		m_pSpeechMessage = CSpeechMessage::Create(pos, size, nLife, (CSpeechMessage::TYPE)type);
	}
}

//=======================================
// 伝達メッセージの取得処理
//=======================================
CSpeechMessage* CPlayer::GetSpeechMessage(void)
{
	// 伝達メッセージを返す
	return m_pSpeechMessage;
}

//=======================================
// 伝達メッセージの消去処理
//=======================================
void CPlayer::DeleteSpeechMessage(void)
{
	if (m_pSpeechMessage != nullptr)
	{ // 伝達メッセージが NULL じゃないとき

		// 伝達メッセージの終了処理
		m_pSpeechMessage->Uninit();
		m_pSpeechMessage = nullptr;
	}
}

//=======================================
// 死亡矢印の設定処理
//=======================================
void CPlayer::SetDeathArrow(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx)
{
	if (m_pDeathArrow[nIdx] == nullptr)
	{ // 死亡矢印が NULL の時

	  // 死亡矢印の生成
		m_pDeathArrow[nIdx] = CDeathArrow::Create(pos, posOld, rot);
	}
	else if (m_pDeathArrow[nIdx] != nullptr)
	{ // 死亡矢印が NULL じゃないとき

		m_pDeathArrow[nIdx]->SetPos(pos);			// 位置設定
		m_pDeathArrow[nIdx]->SetPosOld(posOld);		// 前回の位置設定
		m_pDeathArrow[nIdx]->SetRot(rot);			// 向き設定
	}
}

//=======================================
// 死亡矢印の取得処理
//=======================================
CDeathArrow* CPlayer::GetDeathArrow(const int nIdx)
{
	// 死亡矢印の情報を返す
	return m_pDeathArrow[nIdx];
}

//=======================================
// 死亡矢印の消去処理
//=======================================
void CPlayer::DeleteDeathArrow(const int nIdx)
{
	if (m_pDeathArrow[nIdx] != nullptr)
	{ // 死亡矢印が NULL じゃない時

	  // 死亡矢印の終了処理
		m_pDeathArrow[nIdx]->Uninit();
		m_pDeathArrow[nIdx] = nullptr;
	}
}

//=======================================
// 移動量の設定処理
//=======================================
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CPlayer::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 当たり判定サイズの設定処理
//=======================================
void CPlayer::SetSizeColl(const D3DXVECTOR3& size)
{
	// 当たり判定のサイズを設定する
	m_sizeColl = size;
}

//=======================================
// 種類の設定処理
//=======================================
void CPlayer::SetType(const TYPE type)
{
	// 種類を設定する
	m_type = type;
}

//=======================================
// 種類の取得処理
//=======================================
CPlayer::TYPE CPlayer::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//=======================================
// プレイヤーのIDの取得処理
//=======================================
int CPlayer::GetPlayerIdx(void) const
{
	// プレイヤーのインデックスを返す
	return m_nPlayerIdx;
}

//=======================================
// 速度の設定処理
//=======================================
void CPlayer::SetSpeed(const float fSpeed)
{
	// 速度を設定する
	m_fSpeed = fSpeed;
}

//=======================================
// 速度の取得処理
//=======================================
float CPlayer::GetSpeed(void) const
{
	// 速度を返す
	return m_fSpeed;
}

//=======================================
// 攻撃判定の設定処理
//=======================================
void CPlayer::SetEnableAttack(const bool bAttack)
{
	// 攻撃判定を設定する
	m_bAttack = bAttack;
}

//=======================================
// 攻撃判定の取得処理
//=======================================
bool CPlayer::IsAttack(void) const
{
	// 攻撃判定を返す
	return m_bAttack;
}

//=======================================
// 移動状況の設定処理
//=======================================
void CPlayer::SetEnableMove(const bool bMove)
{
	// 移動状況を設定する
	m_bMove = bMove;
}

//=======================================
// 移動状況の取得処理
//=======================================
bool CPlayer::IsMove(void) const
{
	// 移動状況を返す
	return m_bMove;
}

//=======================================
// 死んだネズミの復活時間の合計設定
//=======================================
void CPlayer::SetResurrectionTime(const int nRezTime)
{
	// 復活時間の合計設定
	m_nResurrectionTime = nRezTime;
}

//=======================================
// 死んだネズミの復活時間の合計追加
//=======================================
void CPlayer::AddResurrectionTime(const int nRezTime)
{
	// 復活時間の合計加算
	m_nResurrectionTime += nRezTime;
}

//=======================================
// 死んだネズミの復活時間の合計取得
//=======================================
int CPlayer::GetResurrectionTime(void)
{
	// 復活時間の合計を返す
	return m_nResurrectionTime;
}

//=======================================
// 回復中表示の判定
//=======================================
void CPlayer::SetDispRecoveringUI(const bool bRez)
{
	if (m_pRecoveringUI != nullptr)
	{ // 回復中UIが NULLじゃなかったら

		// 回復状態を設定する
		m_pRecoveringUI->SetDisplayUI(bRez);
	}
}

//=======================================
// 回復中表示の取得
//=======================================
bool CPlayer::IsDispRecoveringUI(void)
{
	// 回復状態を返す
	return m_pRecoveringUI->GetDisplayUI();
}