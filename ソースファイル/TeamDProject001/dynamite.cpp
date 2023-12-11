//===========================================
//
// 爆弾のメイン処理[dynamite.cpp]
// Author 堀川萩大
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "dynamite.h"
#include "obstacle.h"
#include "useful.h"
#include "Effect.h"
#include "game.h"
#include "manager.h"
#include "input.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SCALE_SPEED	(D3DXVECTOR3(0.1f,0.1f,0.1f))	// サイズの変更速度
#define EXPLOSION_COUNT		(300)		// 爆発までのカウント
#define DELEAT_COUNT		(10)		// 爆発の判定時間
#define EXPLOSION_RADIUS	(200.0f)	// 爆発の範囲

//==============================
// コンストラクタ
//==============================
CDynamite::CDynamite() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_state =STATE_NONE;							// 状態
	m_Scale =D3DXVECTOR3(1.0f,1.0f,1.0f);			// 拡大率
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			// 位置
	m_bCatch = true;								// 持っているかどうか
	m_nExplosion = 0;								// 爆発タイミング

	// 使用条件
	SetCatUse(true);
}

//==============================
// デストラクタ
//==============================
CDynamite::~CDynamite()
{

}

//==============================
// 爆弾の初期化処理
//==============================
HRESULT CDynamite::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	m_state = STATE_NONE;							// 状態
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 拡大率
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_bCatch = true;								// 持っているかどうか
	m_nExplosion = 0;								// 爆発タイミング

	// 値を返す
	return S_OK;
}

//========================================
// 爆弾の終了処理
//========================================
void CDynamite::Uninit(void)
{

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 爆弾の更新処理
//=====================================
void CDynamite::Update(void)
{
	
	// 猫の手から手放す処理
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		CPlayer* pPlayer;
		pPlayer = CGame::GetPlayer(nCnt);
		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{
			if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, nCnt) == true)
			{ // アイテムを持っている状態でYボタンが押された場合
				m_bCatch = false;
			}
		}
	}

	if (m_bCatch == true)
	{ // ネコが持っている場合

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			// ネコの位置に設定する
			CPlayer* pPlayer;
			pPlayer = CGame::GetPlayer(nCnt);
			if (pPlayer->GetType() == CPlayer::TYPE_CAT)
			{
				m_pos = pPlayer->GetPos();
				m_pos.y = 120.0f;
			}

		}
	}
	else
	{ // 地面に置かれている場合
		m_pos.y = 0.0f;

	}

	
	if (m_nExplosion > EXPLOSION_COUNT-120 && m_state != STATE_EXPLOSION)
	{ // 残り2秒になった場合

		if (m_state == STATE_NONE)
		{
			m_state = STATE_MINI;
		}
		ChageScale();	// モデルサイズ変更処理

	}

	if (m_state == STATE_EXPLOSION)
	{// 爆発後
		m_nDelTyming++;
		if (m_nDelTyming > DELEAT_COUNT)
		{
			// 爆弾の削除
			Uninit();
		}
	}

	Explosion();	// 爆発処理

	// 位置を設定する
	SetPos(m_pos);

}

//=====================================
// 爆弾の描画処理
//=====================================
void CDynamite::Draw(void)
{
	if (m_state != STATE_EXPLOSION)
	{// 爆発のタイミングで描画を消す
		// 描画処理
		CObstacle::Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CDynamite::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

}

//=====================================
// ヒット処理
//=====================================
bool CDynamite::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_state == STATE_EXPLOSION)
	{
		D3DXVECTOR3 objPos = GetPos();
		if (useful::CylinderInner(pPlayer->GetPos(), objPos, collSize.x + EXPLOSION_RADIUS))
		{ // 円の中に入った場合

		  // true を返す
			return true;
		}

	}
	// false を返す
	return false;
}

//=====================================
// モデルサイズ変更処理
//=====================================
void CDynamite::ChageScale(void)
{
	// 拡大サイズを取得
	m_Scale = CObstacle::GetScale();

	switch (m_state)
	{
	case CDynamite::STATE_NONE:	// 通常状態
		break;
	
	case CDynamite::STATE_MINI:	// 縮小状態
		m_Scale += SCALE_SPEED;

		if (m_Scale.x > 1.8f)
		{
			m_state = STATE_BIG;
		}
		break;

	case CDynamite::STATE_BIG:	// 拡大状態
		m_Scale -= SCALE_SPEED;	

		if (m_Scale.x <= 1.0f)
		{
			m_state = STATE_MINI;
		}
		break;
	case CDynamite::STATE_EXPLOSION:	// 爆発状態

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 拡大サイズを設定
	CObstacle::SetScale(m_Scale);
}

//=====================================
// 爆発処理
//=====================================
void CDynamite::Explosion(void)
{
	m_nExplosion++;
	if (m_nExplosion >= EXPLOSION_COUNT)
	{// 爆発の時が来た時

		if (m_state != STATE_EXPLOSION)
		{
			//爆発状態にする
			m_state = STATE_EXPLOSION;
			// 爆発エフェクトを出す
			CEffect::Create(m_pos, D3DXVECTOR3(5.0f, 5.0f, 5.0f), 10, 550.0f, CEffect::TYPE_RUPTURE, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), false);
		}
	}
}