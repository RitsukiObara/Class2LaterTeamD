//===========================================
//
// テレビの処理[cup.cpp]
// Author 堀川萩大
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "tv.h"
#include "useful.h"
#include "objectX.h"
#include "consent.h"
#include "object3D.h"
#include "input.h"
#include "texture.h"
#include "effect.h"
#include "collision.h"
#include "block.h"
#include "player.h"
#include "game.h"

//------------------------------
// マクロ定義
//------------------------------
#define COOL_TIME			(300)	// クールタイム
#define CHANGE_TIME			(120)	// 画面変化速度
#define VISION_SIZE			(D3DXVECTOR3(150.0f, 80.0f, 0.0f))		// ビジョンのサイズ
#define NONE_TEXTURE		("data\\TEXTURE\\SkyBox.jpg")			// 何でもない画面のテクスチャ
#define BOMB_TEXTURE		("data\\TEXTURE\\dynamite.png")			// 爆誕の画面のテクスチャ
#define COOLTIME_TEXTURE	("data\\TEXTURE\\obanyanPhoto.jpg")		// クールタイム中のテクスチャ
#define CAT_RADIUS			(70.0f)		// ネコの半径
#define RAT_RADIUS			(30.0f)		// ネコの半径

//==============================
// コンストラクタ
//==============================
CTv::CTv() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_NONE;				// アイテムが取れる状態に
	m_pVision = nullptr;				// ポリゴン情報をnullptr
	m_pRemocon = nullptr;				// リモコン情報をnullptr
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_nCoolTime = 0;					// クールタイム
	SetRatUse(false);					// ネズミが使用できるか
	SetCatUse(true);					// ネコが使用できるか
}

//==============================
// デストラクタ
//==============================
CTv::~CTv()
{

}

//==============================
// テレビの初期化処理
//==============================
HRESULT CTv::Init(void)
{

	// 全ての値をクリアする
	m_State = STATE_NONE;				// アイテムが取れる状態に
	m_pVision = nullptr;				// ポリゴン情報をnullptr
	m_pRemocon = nullptr;				// リモコン情報をnullptr
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_nCoolTime = 0;					// クールタイム

	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	m_pRemocon = CBlock::Create(D3DXVECTOR3(100.0f, 0.0f, 200.0f), CBlock::ROTTYPE_FRONT, CBlock::TYPE_REMOCON);

	// 使用条件
	SetRatUse(false);								// ネズミが使用できるか
	SetCatUse(true);								// ネコが使用できるか

	// 値を返す
	return S_OK;
}

//========================================
// テレビの終了処理
//========================================
void CTv::Uninit(void)
{
	if (m_pVision != nullptr)
	{ // テレビ画面が NULL の場合

		// テレビ画面の終了処理
		m_pVision->Uninit();
		m_pVision = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// テレビの更新処理
//=====================================
void CTv::Update(void)
{
	// 状態マネージャー
	StateManager();

	// テレビ画面切り替え処理
	VisionChange();

	if (m_pVision != nullptr)
	{ // テレビ画面が NULL じゃない場合

		// テレビ画面の更新処理
		m_pVision->Update();
	}

	if (m_pRemocon != nullptr)
	{	// リモコンのモデルがnullではないとき

		if (HitRemocon() == true)
		{	// 周りにプレイヤーがいたら

			if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 0) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 1) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 2) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 3) == true ||
				CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_E) == true)
			{	// ボタンが押されたとき

				//　テレビの電源操作
				PowerAction();
			}
		}
	}
}

//=====================================
// テレビの描画処理
//=====================================
void CTv::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	if (m_pVision != nullptr)
	{ // ビジョンが NULL じゃない場合

		// 描画処理
		m_pVision->DrawLightOff();
	}
}

//=====================================
// 状態管理
//=====================================
void CTv::StateManager(void)
{
	if (m_pVision != nullptr)
	{ // 画面が NULL じゃない場合

		switch (m_State)
		{
		case STATE_NONE:	// 何でもない画面の時

			break;

		case STATE_BOMB:	// 爆弾の画面の時

			break;

		case STATE_COOLDOWN:	// クールタイム中

			// クールタイムを減算する
			m_nCoolTime--;

			if (m_nCoolTime <= 0)
			{ // クールタイムが 0 以下になった場合

				// 通常状態にする
				m_State = STATE_NONE;
			}

			break;

		default:

			// 停止
			assert(false);

			break;
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CTv::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

	// 最大値と最小値を取得する
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // 方向が手前からの場合

		// 最大値と最小値を設定する
		m_vtxMax = vtxMax;
		m_vtxMin = vtxMin;
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // 方向が左からの場合

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, -vtxMin.x);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, -vtxMax.x);
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // 方向が右からの場合

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, vtxMax.x);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.z);
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CTv::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置と最小値と最大値を設定する
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	// 六面体の当たり判定
	if (collision::HexahedronCollision
	(
		&pos,					// プレイヤーの位置
		GetPos(),				// 位置
		pPlayer->GetPosOld(),	// プレイヤーの前回の位置
		GetPosOld(),			// 前回の位置
		vtxMin,					// プレイヤーの最小値
		m_vtxMin,				// 最小値
		vtxMax,					// プレイヤーの最大値
		m_vtxMax				// 最大値
	) == true)
	{ // 当たった場合

	  // 位置を適用する
		pPlayer->SetPos(pos);

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒットサークル処理
//=====================================
bool CTv::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (m_bPower == true && 
		m_State != STATE_COOLDOWN &&
		m_State != STATE_NONE &&
		pPlayer->GetType() == CPlayer::TYPE_CAT)
	{ // アイテムが取れる状態かつ、ネコの場合

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
		{ // 円の範囲内の場合

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// テレビの電源の処理
//=====================================
void CTv::Action(void)
{
	// プレイヤーのポインタを宣言
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// プレイヤーを取得する
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{ // ネコの場合

			// アイテムの取得処理
			pPlayer->GetItem(CItem::TYPE_DYNAMITE);

			// アイテム取った後の状態にする
			m_State = STATE_COOLDOWN;
			m_nCoolTime = COOL_TIME;

			// テクスチャの割り当て処理
			m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
		}
	}
}

//=====================================
// 電源処理
//=====================================
void CTv::PowerAction(void)
{
	switch (m_bPower)
	{
	case true:

		// テレビの電源ついてた時消す
		if (m_pVision != nullptr)
		{	// ポリゴンが存在していた時nullにする
			m_pVision->Uninit();
			m_pVision = nullptr;

		}

		// 電源OFFにする
		m_bPower = false;

		break;

	case false:

		// テレビの電源消えていた時点ける
		if (m_pVision == nullptr)
		{	// ポリゴンが存在していないとき生成する

			D3DXVECTOR3 pPos = GetPos();
			m_pVision = CObject3D::Create(CObject::TYPE_NONE);
			m_pVision->SetPos(D3DXVECTOR3(pPos.x - sinf(GetRot().y) * 18.0f, pPos.y + 160.0f, pPos.z - cosf(GetRot().y) * 18.0f));
			m_pVision->SetRot(GetRot());
			m_pVision->SetSize(VISION_SIZE);

			// 頂点座標の設定処理
			m_pVision->SetVertex();

			if (m_State == STATE_NONE)
			{ // 何でもない画面の時

				// 通常テクスチャの割り当て処理
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
			else if (m_State == STATE_BOMB)
			{ // 爆弾の画面の時

				// 爆弾テクスチャの割り当て処理
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
			}
			else
			{ // クールタイム中

				// 砂嵐テクスチャの割り当て処理
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
			}
		}

		// 電源ONにする
		m_bPower = true;

		break;
	}
}

//=====================================
// リモコンのヒットサークル処理
//=====================================
bool CTv::HitRemocon(void)
{
	// プレイヤーのポインタを宣言
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// プレイヤーを取得する
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer != nullptr &&
			pPlayer->GetState() != CPlayer::STATE_DEATH &&
			pPlayer->GetStunState() != CPlayer::STUNSTATE::STUNSTATE_STUN &&
			pPlayer->GetStunState() != CPlayer::STUNSTATE::STUNSTATE_WAIT)
		{ // プレイヤーが NULL じゃない場合

			switch (pPlayer->GetType())
			{
			case CPlayer::TYPE_CAT:

				if (m_bPower == false &&
					useful::CircleCollisionXZ(pPlayer->GetPos(), m_pRemocon->GetPos(), CAT_RADIUS, m_pRemocon->GetFileData().fRadius) == true)
				{ // 電源OFFかつ、円の範囲内の場合

					// true を返す
					return true;
				}

				break;

			case CPlayer::TYPE_RAT:

				if (m_bPower == true &&
					useful::CircleCollisionXZ(pPlayer->GetPos(), m_pRemocon->GetPos(), RAT_RADIUS, m_pRemocon->GetFileData().fRadius) == true)
				{ // 電源ONかつ、円の範囲内の場合

					// true を返す
					return true;
				}

				break;

			default:

				// 停止
				assert(false);

				break;
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// テレビ画面切り替え処理
//=====================================
void CTv::VisionChange(void)
{
	if (m_bPower == true)
	{ // 電源ON状態の場合

		if (m_State != STATE_COOLDOWN)
		{ // クールダウン状態以外の場合

			m_nChangeVision++;
			if (m_nChangeVision % CHANGE_TIME == 0 && m_nChangeVision > 0)
			{
				switch (m_State)
				{
				case STATE_NONE:
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
					m_State = STATE_BOMB;
					break;

				case STATE_BOMB:
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
					m_State = STATE_NONE;

					break;

				default:

					// 停止
					assert(false);

					break;
				}
			}
		}
		else
		{
			if (m_nChangeVision != 0)
			{
				m_nChangeVision = 0;
			}
		}
	}
	
}