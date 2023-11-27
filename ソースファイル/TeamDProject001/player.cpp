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

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "collision.h"

#include "Cat.h"
#include "rat.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY				(1.0f)			// 重力
#define ADD_MOVE_Y			(30.0f)			// 浮力
#define NONE_PLAYERIDX		(-1)			// プレイヤーの番号の初期値
#define MAX_LIFE			(1)				// 寿命の最大値
#define STUN_HEIGHT			(80.0f)			// 気絶演出が出てくる高さ
#define ID_HEIGHT			(90.0f)			// IDが出てくる高さ
#define SMASH_MOVE			(D3DXVECTOR3(10.0f, 20.0f, 10.0f))		// 吹き飛び状態の移動量

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
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_type = TYPE_CAT;					// 種類
	m_nLife = 0;						// 寿命
	m_nPlayerIdx = NONE_PLAYERIDX;		// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか
}

//==============================
// ネズミの初期化処理
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
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_type = TYPE_CAT;					// 種類
	m_nLife = 0;						// 寿命
	m_nPlayerIdx = NONE_PLAYERIDX;		// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか

	// 値を返す
	return S_OK;
}

//========================================
// ネズミの終了処理
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

	// 終了処理
	CCharacter::Uninit();
}

//=====================================
// ネズミの更新処理
//=====================================
void CPlayer::Update(void)
{
	// 障害物との当たり判定
	collision::ObstacleHit(this, m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	//壁との当たり判定
	SetPos(collision::WallCollision(GetPosOld(), GetPos()));

	// 障害物との当たり判定
	ObstacleCollision();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_E))
	{
		collision::ObstacleAction(this, m_sizeColl.x, m_type);
	}

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

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n向き：%f %f %f\n寿命：%d\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_nLife);
}

//=====================================
// ネズミの描画処理
//=====================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=====================================
// 吹き飛び状態
//=====================================
void CPlayer::Smash(const float fAngle)
{
	// 移動量を設定する
	m_move.x = sinf(fAngle) * SMASH_MOVE.x;
	m_move.y = SMASH_MOVE.y;
	m_move.z = cosf(fAngle) * SMASH_MOVE.z;
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
	m_nLife = MAX_LIFE;					// 寿命
	m_nPlayerIdx = nID;					// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか

	if (m_pPlayerID == nullptr)
	{ // プレイヤーのID表示が NULL の場合

		// プレイヤーのID表示の生成処理
		m_pPlayerID = CPlayerID::Create(D3DXVECTOR3(pos.x, pos.y + 90.0f, pos.z), nID);
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
// 寿命の設定処理
//=======================================
void CPlayer::SetLife(const int nLife)
{
	// 寿命を設定する
	m_nLife = nLife;
}

//=======================================
// 寿命の取得処理
//=======================================
int CPlayer::GetLife(void) const
{
	// 寿命を返す
	return m_nLife;
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
// 生成処理
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// ネズミのポインタ
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
// 移動処理
//=======================================
void CPlayer::Move(void)
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
			rot.y = D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
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
		CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) < 0)
	{ // 左を押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // 上を押した場合

			// 向きを設定する
			rot.y = D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
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
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
	{ // 上を押した場合

		// 向きを設定する
		rot.y = D3DX_PI;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
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
	//collision::ObstacleCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z, m_type);

	// ブロックとの当たり判定
	collision::BlockCollision(pos, GetPosOld(), m_sizeColl.x, m_sizeColl.y, m_sizeColl.z);

	// 位置を設定する
	SetPos(pos);
}