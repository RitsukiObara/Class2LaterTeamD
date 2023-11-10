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
#include "Particle.h"
#include "motion.h"
#include "shadowCircle.h"
#include "destruction.h"
#include "ripple.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAX_LIFE				(3)			// 体力の最大数
#define COLLISION_WIDTH			(20.0f)		// 当たり判定時に使う時の幅
#define COLLISION_HEIGHT		(150.0f)	// 当たり判定時に使う時の高さ
#define COLLISION_DEPTH			(20.0f)		// 当たり判定時に使う時の奥行
#define START_CAMERA_POSR_Y		(100.0f)	// スタート時のカメラの注視点(Y軸)
#define START_CAMERA_POSV_Y		(130.0f)	// スタート時のカメラの視点(Y軸)
#define START_CAMERA_DISTANCE	(200.0f)	// スタート時のカメラの距離
#define START_COUNT				(40)		// スタートのカウント
#define PUNCH_COUNT				(150)		// パンチ状態のカウント数
#define GOAL_COUNT				(80)		// ゴール状態のカウント数
#define LEAVE_GRAVITY			(0.4f)		// 退場状態の重力
#define FINISH_GRAVITY			(-0.6f)		// 終了状態の重力
#define NEAR_POS				(0.0f)		// 手前の位置
#define FAR_POS					(1000.0f)	// 奥行の位置
#define ADD_GRAVITY				(-50.0f)	// 追加の重力
#define FALL_HEIGHT				(-600.0f)	// 落ちた判定が通る所
#define PUNCH_DSTR_SHIFT		(D3DXVECTOR3(40.0f, 100.0f, 0.0f))		// パンチ時の撃破のずらす幅
#define PUNCH_DSTR_SIZE			(D3DXVECTOR3(100.0f, 100.0f, 0.0f))		// パンチ時の撃破のサイズ
#define PUNCH_DSTR_COL			(D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f))		// パンチ時の撃破の色
#define PUNCH_DSTR_LIFE			(6)			// パンチ時の撃破の寿命
#define PUNCH_RIPPLE_SHIFT		(D3DXVECTOR3(45.0f, 100.0f, 0.0f))		// パンチ時の波紋のずらす幅
#define OUT_RANGE_GRAVITY		(-5.0f)		// 範囲外に出たときの重力
#define ADD_START_POS			(D3DXVECTOR3(20.0f, -20.0f, 0.0f))		// スタート状態の加算する位置

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
	m_pAction = nullptr;			// プレイヤーの行動の情報
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス
	m_nStartCount = 0;				// スタートカウント
	m_nGoalCount = 0;				// ゴール時のカウント
	m_fSpeed = 0.0f;				// 速度
	m_fAlpha = 1.0f;				// 透明度
	m_bMove = false;				// 移動状況
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
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	// 全ての値を初期化する
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス
	m_nStartCount = 0;				// スタートカウント
	m_nGoalCount = 0;				// ゴール時のカウント
	m_fSpeed = 0.0f;				// 速度
	m_fAlpha = 1.0f;				// 透明度
	m_bMove = false;				// 移動状況

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
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	// モーションの更新処理
	m_pMotion->Update();

	 // 影の位置向きの設定処理
	CShadowCircle::SetPosRot(m_nShadowIdx, GetPos(), GetRot());

	// プレイヤーの情報を表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n移動量：%f %f %f\n", GetPos().x, GetPos().y, GetPos().z, m_move.x, m_move.y, m_move.z);
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
// モーションの情報の設定処理
//===========================================
CMotion* CCat::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//===========================================
// アクションの情報の設定処理
//===========================================
CCatAct* CCat::GetAction(void) const
{
	// 行動状態の情報を返す
	return m_pAction;
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

	// カメラを設定する
	CManager::Get()->GetCamera()->SetPosR(D3DXVECTOR3(pos.x, pos.y + START_CAMERA_POSR_Y, pos.z));
	CManager::Get()->GetCamera()->SetPosV(D3DXVECTOR3(pos.x, pos.y + START_CAMERA_POSV_Y, pos.z));
	CManager::Get()->GetCamera()->SetDistance(START_CAMERA_DISTANCE);
}

//=======================================
// 移動量の設定処理
//=======================================
void CCat::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CCat::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 目標の向きの設定処理
//=======================================
void CCat::SetRotDest(const D3DXVECTOR3& rot)
{
	// 目標の向きを設定する
	m_rotDest = rot;
}

//=======================================
// 目標の向きの取得処理
//=======================================
D3DXVECTOR3 CCat::GetRotDest(void) const
{
	// 目標の向きを返す
	return m_rotDest;
}

//=======================================
// 速度の設定処理
//=======================================
void CCat::SetSpeed(float fSpeed)
{
	// 速度を設定する
	m_fSpeed = fSpeed;
}

//=======================================
// 速度の取得処理
//=======================================
float CCat::GetSpeed(void) const
{
	// 速度を返す
	return m_fSpeed;
}

//=======================================
// 透明度の設定処理
//=======================================
void CCat::SetAlpha(const float fAlpha)
{
	// 透明度を設定する
	m_fAlpha = fAlpha;
}

//=======================================
// 透明度の入れ替え処理
//=======================================
void CCat::SwapAlpha(void)
{
	// 透明度を入れ替える
	m_fAlpha = (m_fAlpha >= 1.0f) ? 0.0f : 1.0f;
}

//=======================================
// 透明度の取得処理
//=======================================
float CCat::GetAlpha(void) const
{
	// 透明度を返す
	return m_fAlpha;
}

//=======================================
// 移動状況の設定処理
//=======================================
void CCat::SetEnableMove(bool bMove)
{
	// 移動状況を設定する
	m_bMove = bMove;
}

//=======================================
// 移動状況の取得処理
//=======================================
bool CCat::IsMove(void) const
{
	// 移動状況を返す
	return m_bMove;
}

//=======================================
// 移動制限判定
//=======================================
void CCat::CollisionMagicWall(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

	if (pos.z >= FAR_POS)
	{ // 位置が一定以上になった場合

	  // 位置を補正する
		pos.z = FAR_POS;
	}

	if (pos.z <= NEAR_POS)
	{ // 位置を一定以下になった場合

	  // 位置を補正する
		pos.z = NEAR_POS;
	}

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// スタート状態の処理
//=======================================
void CCat::StartProcess(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

									// 位置を加算する
	pos += ADD_START_POS;

	if (pos.x >= m_posDest.x)
	{ // 位置が目的を超えた場合

	}

	if (m_nStartCount >= START_COUNT)
	{ // スタートカウントを設定する

	}

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// ゴール状態の処理
//=======================================
void CCat::GoalProcess(void)
{

}

//=======================================
// 退場状態の処理
//=======================================
void CCat::LeaveProcess(void)
{

}

//=======================================
// 終了状態の処理
//=======================================
void CCat::FinishProcess(void)
{

}