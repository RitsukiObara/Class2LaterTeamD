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
#define MOVE_SPEED				(20.0f)			// 体力の最大数
#define ATTACK_DISTANCE	(160.0f)		// 攻撃範囲までの距離

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CCat* CCat::m_pPlayer = nullptr;		// プレイヤーのポインタ

//=========================================
// コンストラクタ
//=========================================
CCat::CCat() : CCharacter(CObject::TYPE_CAT, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;			// モーションの情報
	m_AttackPos = NONE_D3DXVECTOR3;	//攻撃の位置
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_move = NONE_D3DXVECTOR3;		// 移動量
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
	if (FAILED(CCharacter::Init()))
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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	// 全ての値を初期化する
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_move = NONE_D3DXVECTOR3;		// 移動量
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
	// モーションのメモリを開放する
	delete m_pMotion;
	m_pMotion = nullptr;

	// 終了処理
	CCharacter::Uninit();

	// プレイヤーを NULL にする
	m_pPlayer = nullptr;
}

//===========================================
// 更新処理
//===========================================
void CCat::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	// 前回の位置の設定処理
	SetPosOld(pos);

	// モーションの更新処理
	m_pMotion->Update();

	if (m_AttackState == ATTACKSTATE_MOVE)
	{// 移動状態の時
		m_fSpeed = MOVE_SPEED;

		// 攻撃位置の移動入力処理
		Move();

		// 攻撃入力の処理
		Attack();

		// モーション状態の管理
		MotionManager();
	}
	else
	{
		m_move = NONE_D3DXVECTOR3;
	}

	// 攻撃状態の管理
	AttackStateManager();

	//位置更新
	pos += m_move;

	 // 影の位置向きの設定処理
	CShadowCircle::SetPosRot(m_nShadowIdx, pos, GetRot());

	SetPos(pos);

	// デバッグ表示
	DebugMessage();
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CCat::Draw(void)
{
	//// デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//// Zテストを無効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);					//Zテストの設定
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//Zテストの有効/無効設定

	//																		// 描画処理
	//CCharacter::Draw(m_fAlpha);

	//// Zテストを有効にする
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Zテストの設定
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Zテストの有効/無効設定

	// 描画処理
	CCharacter::Draw();
}

//===========================================
// 攻撃位置の移動処理
//===========================================
void CCat::Move(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_L) == true)
	{ // 右を押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_I) == true)
		{ // 上を押した場合

		  // 向きを設定する
			rot.y = D3DX_PI * -0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_K) == true)
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
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_J) == true)
	{ // 左を押した場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_I) == true)
		{ // 上を押した場合

		  // 向きを設定する
			rot.y = D3DX_PI * 0.75f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_K) == true)
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
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_I) == true)
	{ // 上を押した場合

	  // 向きを設定する
		rot.y = D3DX_PI;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_K) == true)
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

//===========================================
// 攻撃処理
//===========================================
void CCat::Attack(void)
{
	// ローカル変数宣言
	CRat *pRat[3];
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // Wキーを押していた場合

		// 状態を攻撃準備にする
		m_AttackState = ATTACKSTATE_STANDBY;
		m_nAtkStateCount = 20;
		for (int nCnt = 0; nCnt < 3; nCnt++)

		{
			pRat[nCnt] = CGame::GetRat(nCnt);
			while (pRat[nCnt] != nullptr)
			{ // ブロックの情報が NULL じゃない場合

				if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE),
					pRat[nCnt]->GetPos(),
					D3DXVECTOR3(30.0f, 50.0f, 30.0f), 
					D3DXVECTOR3(30.0f, 50.0f, 30.0f),
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f), 
					D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
				{ // XYの矩形に当たってたら

					if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pRat[nCnt]->GetPos(),
						D3DXVECTOR3(30.0f, 50.0f, 30.0f), D3DXVECTOR3(30.0f, 50.0f, 30.0f),
						D3DXVECTOR3(-30.0f, -50.0f, -30.0f), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
					{ // XZの矩形に当たってたら
						pRat[nCnt]->Hit();
					}
				}
				break;
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
		{//状態カウントが０になった時
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
		{//状態カウントが０になった時
			m_AttackState = ATTACKSTATE_MOVE;
		}
		break;
	}

	if (m_nAtkStateCount > 0)
	{
		m_nAtkStateCount--;
	}
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

//===========================================
// モーションの情報の設定処理
//===========================================
CMotion* CCat::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//===========================================
// 取得処理
//===========================================
CCat* CCat::Get(void)
{
	if (m_pPlayer != nullptr)
	{ // プレイヤーの情報がある場合

	  // プレイヤーのポインタを返す
		return m_pPlayer;
	}
	else
	{ // 上記以外

	  // 停止
		assert(false);

		// プレイヤーのポインタを返す
		return m_pPlayer;
	}
}

//===========================================
// 生成処理
//===========================================
CCat* CCat::Create(const D3DXVECTOR3& pos)
{
	if (m_pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

	  // メモリを確保する
		m_pPlayer = new CCat;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // NULL を返す
		return m_pPlayer;
	}

	if (m_pPlayer != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(m_pPlayer->Init()))
		{ // 初期化に失敗した場合

		  // 警告文
			MessageBox(NULL, "プレイヤーの初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		m_pPlayer->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

	  // NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return m_pPlayer;
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
void CCat::SetData(const D3DXVECTOR3& pos)
{
	// 全ての値を初期化する
	m_posDest = pos;	// 目的の位置
	SetPos(pos);		// 位置
	SetPosOld(GetPos());			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率

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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);
}

//=====================================
// 情報の設定処理
//=====================================
void CCat::MotionManager(void)
{
	if (m_AttackState == ATTACKSTATE_STANDBY)
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