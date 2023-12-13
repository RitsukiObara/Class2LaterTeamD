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
#include "manager.h"
#include "dynamite.h"
#include "obstacle.h"
#include "useful.h"
#include "Effect.h"
#include "collision.h"

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

		// 爆発の判定時間を加算する
		m_nDelTyming++;

		if (m_nDelTyming > DELEAT_COUNT)
		{ // 一定カウントになった場合

			// 爆弾の削除
			Uninit();
		}
	}

	// 爆発処理
	Explosion();
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
// 当たり判定処理
//=====================================
bool CDynamite::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置と最小値と最大値を設定する
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	// 六面体の当たり判定
	if (collision::HexahedronCollision
	(
		&pos,					// プレイヤーの位置
		GetPos(),				// 位置
		pPlayer->GetPosOld(),	// プレイヤーの前回の位置
		GetPosOld(),			// 前回の位置
		vtxMin,					// プレイヤーの最小値
		GetFileData().vtxMin,	// 最小値
		vtxMax,					// プレイヤーの最大値
		GetFileData().vtxMax	// 最大値
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
// ヒット処理
//=====================================
bool CDynamite::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_state == STATE_EXPLOSION)
	{ // 爆発状態の場合

		if (useful::CylinderInner(pPlayer->GetPos(), GetPos(), collSize.x + EXPLOSION_RADIUS))
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
	D3DXVECTOR3 scale = CObstacle::GetScale();

	switch (m_state)
	{
	case CDynamite::STATE_NONE:	// 通常状態
		break;
	
	case CDynamite::STATE_MINI:	// 縮小状態

		scale += SCALE_SPEED;

		if (scale.x > 1.8f)
		{
			m_state = STATE_BIG;
		}
		break;

	case CDynamite::STATE_BIG:	// 拡大状態

		scale -= SCALE_SPEED;

		if (scale.x <= 1.0f)
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
	SetScale(scale);
}

//=====================================
// 爆発処理
//=====================================
void CDynamite::Explosion(void)
{
	// 爆発までのカウントを加算する
	m_nExplosion++;

	if (m_nExplosion >= EXPLOSION_COUNT)
	{// 爆発の時が来た時

		if (m_state != STATE_EXPLOSION)
		{ // 爆発状態以外の場合

			//爆発状態にする
			m_state = STATE_EXPLOSION;

			// 爆発エフェクトを出す
			CEffect::Create(GetPos(), D3DXVECTOR3(5.0f, 5.0f, 5.0f), 10, 550.0f, CEffect::TYPE_RUPTURE, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), false);
		}
	}
}