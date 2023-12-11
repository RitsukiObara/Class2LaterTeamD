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
#define COOL_TIME	(300)	// クールタイム
#define CHANGE_TIME	(120)	// 画面変化速度
#define NONE_TEXTURE ("data\\TEXTURE\\SkyBox.jpg")				// 何でもない画面のテクスチャ
#define TRAP_TEXTURE ("data\\TEXTURE\\SkyBox.jpg")				// ネズミ捕りの画面のテクスチャ
#define BOMB_TEXTURE ("data\\TEXTURE\\SkyBox.jpg")				// 爆誕の画面のテクスチャ
#define COOLTIME_TEXTURE ("data\\TEXTURE\\obanyanPhoto.jpg")	// クールタイム中のテクスチャ

//==============================
// コンストラクタ
//==============================
CTv::CTv() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_NONE;							// アイテムが取れる状態に
	m_pVision = nullptr;							// ポリゴン情報をnullptr
	m_pRemocn = nullptr;							// リモコン情報をnullptr
	m_VisionSize = D3DXVECTOR3(150.0f,80.0f,0.0f);	// ポリゴンサイズ
	m_nCoolTime = 0;								// クールタイム
	SetRatUse(false);								// ネズミが使用できるか
	SetCatUse(true);								// ネコが使用できるか
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
	m_State = STATE_NONE;							// アイテムが取れる状態に
	m_pVision = nullptr;							// ポリゴン情報をnullptr
	m_pRemocn = nullptr;							// リモコン情報をnullptr
	m_VisionSize = D3DXVECTOR3(150.0f, 80.0f, 0.0f);// ポリゴンサイズ
	m_nCoolTime = 0;								// クールタイム

	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	m_pRemocn = CBlock::Create(D3DXVECTOR3(100.0f, 0.0f, 200.0f), CBlock::ROTTYPE_FRONT, CBlock::TYPE_REMOCON);

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
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// テレビの更新処理
//=====================================
void CTv::Update(void)
{
	StateManager();
	VisionChange();
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0ボタンを押した場合
		m_nChangeVision;
	}

	if (m_pVision != nullptr)
	{ // テレビ画面が NULL じゃない場合

	  // テレビ画面の更新処理
		m_pVision->Update();
	}
	if (m_pRemocn != nullptr)
	{	// リモコンのモデルがnullではないとき
		if (HitRemocon() == true )
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

	if (m_pVision != NULL)
	{
		m_pVision->Draw();
	}
}

//=====================================
// 状態管理
//=====================================
void CTv::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NONE:	// 何でもない画面の時
		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(NONE_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
		}
	break;

	case STATE_TRAP:	// ネズミ捕りの画面の時
		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(TRAP_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(TRAP_TEXTURE));
			}
		}
		break;

	case STATE_BOMB:	// 爆弾の画面の時
		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
			}
		}
		break;

	case STATE_COOLDOWN:	// クールタイム中

		if (m_pVision != nullptr)
		{
			if (m_pVision->GetTexIdx() != CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE))
			{
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
			}
		}
		m_nCoolTime--;
		if (m_nCoolTime <= 0)
		{
			m_State = STATE_NONE;
		}
		break;
	default:

		// 停止
		assert(false);

		break;
	}
}

//=====================================
// テレビの電源の処理
//=====================================
void CTv::Action(void)
{
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		pPlayer = CGame::GetPlayer(nCnt);
		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{
			switch(m_State)
			{
			case STATE_TRAP:
				pPlayer->GetItem(CItem::TYPE_MOUSETRAP);
				// アイテム取った後の状態にする
				m_State = STATE_COOLDOWN;
				m_nCoolTime = COOL_TIME;
				break;
			case STATE_BOMB:
				// アイテム取った後の状態にする
				m_State = STATE_COOLDOWN;
				m_nCoolTime = COOL_TIME;
				break;

	
			}
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
}

//=====================================
// 当たり判定処理
//=====================================
bool CTv::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// false を返す
	return false;
}

//=====================================
// ヒットサークル処理
//=====================================
bool CTv::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (m_bPower == true && m_State != STATE_COOLDOWN)
	{
		if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
		{//円の範囲内の場合tureを返す
			return true;
		}
	}

	// false を返す
	return false;
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
		m_bPower = false;
		break;

	case false:
		// テレビの電源消えていた時点ける
		if (m_pVision == nullptr)
		{	// ポリゴンが存在していないとき生成する

			D3DXVECTOR3 pPos = GetPos();
			m_pVision = CObject3D::Create(CObject3D::TYPE_NONE);
			m_pVision->SetPos(D3DXVECTOR3(pPos.x, pPos.y + 160.0f, pPos.z - 18.0f));
			m_pVision->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pVision->SetSize(m_VisionSize);
			if (m_State == STATE_NONE)
			{	// 何でもない画面の時
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));

			}
			else if (m_State == STATE_TRAP)
			{	// ネズミ捕りの画面の時
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
			else if (m_State == STATE_BOMB)
			{	// 爆弾の画面の時
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
			else
			{	// クールタイム中
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
			}
		}
		m_bPower = true;
		break;
	}
}

//=====================================
// リモコンのヒットサークル処理
//=====================================
bool CTv::HitRemocon(void)
{
	CPlayer* pPlayer;
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		pPlayer = CGame::GetPlayer(nCnt);
		if (useful::CircleCollisionXZ(pPlayer->GetPos(), m_pRemocn->GetPos(), 200.0f, m_pRemocn->GetFileData().fRadius) == true)
		{//円の範囲内の場合tureを返す
			return true;
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
	{
		if (m_State != STATE_COOLDOWN)
		{
			m_nChangeVision++;
			if (m_nChangeVision %CHANGE_TIME == 0 && m_nChangeVision > 0)
			{
				switch (m_State)
				{
				case STATE_NONE:
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(TRAP_TEXTURE));
					m_State = STATE_TRAP;
					break;
				case STATE_TRAP:
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