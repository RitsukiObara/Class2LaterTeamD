//============================================
//
// 猫のメイン処理[Cat.cpp]
// Author：坂本翔唯
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "Cat.h"
#include "manager.h"
#include "game.h"
#include "result.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "sound.h"
#include "useful.h"
#include "texture.h"

#include "camera.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "effect.h"
#include "Particle.h"
#include "motion.h"
#include "shadowCircle.h"
#include "destruction.h"
#include "ripple.h"
#include "obstacle_manager.h"
#include "rat.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MOVE_SPEED			(20.0f)			// 体力の最大数
#define ATTACK_DISTANCE		(160.0f)		// 攻撃範囲までの距離
#define CAT_SIZE			(D3DXVECTOR3(70.0f, 200.0f, 70.0f))		// 当たり判定のサイズ
#define GRAVITY				(1.0f)			// 重力

//=========================================
// コンストラクタ
//=========================================
CCat::CCat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_AttackPos = NONE_D3DXVECTOR3;	//攻撃の位置
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス
}

//=========================================
// デストラクタ
//=========================================
CCat::~CCat()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CCat::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // 初期化処理に失敗した場合

	  // 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// ベタ打ち
	SetNumModel(10);

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
		pMotion->Load(CMotion::TYPE_CAT);
	}
	else
	{ // ポインタが NULL じゃない場合

	  // 停止
		assert(false);
	}

	// モーションの設定処理
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	// モーション情報を設定する
	SetMotion(pMotion);

	// 全ての値を初期化する
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CCat::Uninit(void)
{
	// 終了処理
	CPlayer::Uninit();

	// プレイヤーを消去する
	CGame::DeletePlayer(3);
}

//===========================================
// 更新処理
//===========================================
void CCat::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	// 重力処理
	Gravity();

	if (m_AttackState == ATTACKSTATE_MOVE)
	{// 移動状態の時

		// 速度を設定する
		SetSpeed(MOVE_SPEED);

		// 攻撃位置の移動入力処理
		Move();

		// 攻撃入力の処理
		Attack();

		// モーション状態の管理
		MotionManager();
	}
	else
	{
		// 移動量を初期化する
		SetMove(NONE_D3DXVECTOR3);
	}

	// 攻撃状態の管理
	AttackStateManager();

	 // 影の位置向きの設定処理
	CShadowCircle::SetPosRot(m_nShadowIdx, GetPos(), GetRot());

	// アイテムとの当たり判定処理
	collision::ItemCollision(*this);

	// 起伏地面の当たり判定
	Elevation();

	// 更新処理
	CPlayer::Update();

	// デバッグ表示
	DebugMessage();
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CCat::Draw(void)
{
	// 描画処理
	CPlayer::Draw();
}

//===========================================
// 重力処理
//===========================================
void CCat::Gravity(void)
{
	// 移動量を取得する
	D3DXVECTOR3 move = GetMove();

	// 重力加算
	move.y -= GRAVITY;

	// 情報を適用する
	SetMove(move);
}

//===========================================
// 攻撃処理
//===========================================
void CCat::Attack(void)
{
	// ローカル変数宣言
	CPlayer* pPlayer = nullptr;
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // ENTERキーを押していた場合

		// 状態を攻撃準備にする
		m_AttackState = ATTACKSTATE_STANDBY;
		m_nAtkStateCount = 20;
		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			// プレイヤーの情報を取得する
			pPlayer = CGame::GetPlayer(nCnt);

			if (pPlayer != nullptr &&
				pPlayer->GetType() == CPlayer::TYPE_RAT)
			{ // プレイヤーがネズミの場合

				if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE),
					pPlayer->GetPos(),
					D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
				{ // XYの矩形に当たってたら

					if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE), 
						pPlayer->GetPos(),
						D3DXVECTOR3(30.0f, 50.0f, 30.0f), D3DXVECTOR3(30.0f, 50.0f, 30.0f),
						D3DXVECTOR3(-30.0f, -50.0f, -30.0f), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
					{ // XZの矩形に当たってたら

						// プレイヤーのヒット処理
						pPlayer->Hit();
					}
				}
			}
		}
	}

	//m_bAttack = true;		// 攻撃した状態にする
}

//===========================================
// 攻撃状態の管理
//===========================================
void CCat::AttackStateManager(void)
{
	switch (m_AttackState)
	{
	case ATTACKSTATE_MOVE:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.8f), true);

		break;

	case ATTACKSTATE_STANDBY:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), true);

		if (m_nAtkStateCount <= 0)
		{//状態カウントが0になった時
			m_AttackState = ATTACKSTATE_ATTACK;
			m_nAtkStateCount = 10;
		}
		break;

	case ATTACKSTATE_ATTACK:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), true);

		if (useful::CircleCollisionXZ(m_AttackPos, m_AttackPos,10.0f,10.0f) == true)
		{

		}

		if (m_nAtkStateCount <= 0)
		{//状態カウントが0になった時
			m_AttackState = ATTACKSTATE_MOVE;
		}
		break;
	}

	if (m_nAtkStateCount > 0)
	{
		m_nAtkStateCount--;
	}
}

//=======================================
// 起伏地面の当たり判定
//=======================================
void CCat::Elevation(void)
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
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置と移動量を更新する
	SetPos(pos);
	SetMove(move);
}

//===========================================
// デバッグ表示
//===========================================
void CCat::DebugMessage(void)
{
	CManager::Get()->GetDebugProc()->Print("\n 猫情報--------------------------------------------\n");

	// 猫の攻撃位置情報を表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n", m_AttackPos.x, m_AttackPos.y, m_AttackPos.z);

	// 猫の操作方法を表示
	CManager::Get()->GetDebugProc()->Print("移動入力：上:[I] / 左:[J] / 下:[K] / 右:[L] \n");
	CManager::Get()->GetDebugProc()->Print("攻撃 : [ENTER] \n");
}

//=======================================
// ヒット処理
//=======================================
void CCat::Hit(void)
{

}

//=======================================
// 情報の設定処理
//=======================================
void CCat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// 情報の設定処理
	CPlayer::SetData(pos, nID, type);

	// 当たり判定のサイズの設定
	SetSizeColl(CAT_SIZE);

	// 全ての値を初期化する
	m_posDest = pos;		// 目的の位置
	m_rotDest = GetRot();	// 目的の向きを設定する

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_CAT + nCntData));				// データの設定処理
	}

	// ローカル変数宣言
	CShadowCircle* pShadow = nullptr;		// 影へのポインタ

	// 影の設定処理
	pShadow = CShadowCircle::Create(pos, GetRot(), 40.0f);

	if (pShadow != nullptr)
	{ // 影のポインタが NULL以外の場合

		// 影のインデックス設定
		m_nShadowIdx = pShadow->GetNumID();
	}

	// モーションの設定処理
	GetMotion()->Set(MOTIONTYPE_NEUTRAL);
}

//=====================================
// 情報の設定処理
//=====================================
void CCat::MotionManager(void)
{
	// モーションの種類を取得する
	int nMotionType = GetMotion()->GetType();

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // リザルト && ねこのかち

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // ねずみのかち

			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // ねこのかち

			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
	}
	else
	{ // リザルト以外のとき

		if (m_AttackState == ATTACKSTATE_STANDBY)
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