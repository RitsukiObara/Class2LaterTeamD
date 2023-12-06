//===========================================
//
// スピーカーの処理[Himo.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "speaker.h"
#include "manager.h"
#include "useful.h"

#include "note.h"
#include "collision.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SPEAKER_RADIUS	(50.0f)		// 音符の出現間隔(フレーム)
#define NOTE_INTERVAL	(20)		// 音符の出現間隔(フレーム)
#define NOTE_LIFE		(120)		// 音符の寿命
#define NOTE_SPEED		(15.0f)		// 音符の速さ
#define NOTE_HEIGHT		(100.0f)	// 音符の高さ
#define NOTE_SHIFT		(100.0f)	// 音符のずらす幅
#define STOP_SCALE		(1.0f)		// 通常時の拡大率
#define SHRINK_SCALE	(0.85f)		// 縮み状態の拡大率
#define EXTEND_SCALE	(1.15f)		// 伸び状態の拡大率
#define ADD_SCALE		(0.05f)		// 拡大率の加算数
#define ADD_HIT_RADIUS	(40.0f)		// 追加の当たり判定の半径

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CNote* CSpeaker::m_apNote[MAX_NOTE] = {};		// 音符の情報

//==============================
// コンストラクタ
//==============================
CSpeaker::CSpeaker() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		m_apNote[nCnt] = NULL;
		m_bmySet[nCnt] = false;
	}
	m_state = STATE_STOP;		// 状態
	m_bAction = false;
	m_nNoteCount = 0;
	SetCatUse(true);
	SetRatUse(true);
}

//==============================
// デストラクタ
//==============================
CSpeaker::~CSpeaker()
{

}

//==============================
// スピーカーの初期化処理
//==============================
HRESULT CSpeaker::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// スピーカーの終了処理
//========================================
void CSpeaker::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != nullptr)
		{ // 音符が NULL の場合

			// 音符の終了処理
			m_apNote[nCnt]->Uninit();
			m_apNote[nCnt] = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// スピーカーの更新処理
//=====================================
void CSpeaker::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_bAction == true)
	{
		SetNote();
	}
	else
	{ // 上記以外

		// 停止状態にする
		m_state = STATE_STOP;
	}

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_bmySet[nCnt] == true)
		{
			if (m_apNote[nCnt] != NULL)
			{
				m_apNote[nCnt]->Update();
			}
		}
	}

	SetPos(pos);

	// 状態による処理
	State();
}

//=====================================
// スピーカーの描画処理
//=====================================
void CSpeaker::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != NULL)
		{
			m_apNote[nCnt]->Draw();
		}
	}
}

//=====================================
// 音符の生成処理
//=====================================
void CSpeaker::SetNote(void)
{
	m_nNoteCount++;

	if (m_nNoteCount % NOTE_INTERVAL == 0)
	{
		for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
		{
			if (m_apNote[nCnt] == NULL)
			{
				D3DXVECTOR3 pos = GetPos();
				D3DXVECTOR3 rot = GetRot();

				m_apNote[nCnt] = CNote::Create(D3DXVECTOR3(pos.x - (sinf(rot.y) * NOTE_SHIFT), pos.y + NOTE_HEIGHT, pos.z - (cosf(rot.y) * NOTE_SHIFT)));
				m_apNote[nCnt]->SetMain(this);
				m_apNote[nCnt]->SetIndex(nCnt);
				m_apNote[nCnt]->SetLife(NOTE_LIFE);
				m_apNote[nCnt]->SetMove(D3DXVECTOR3(
					sinf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED,
					0.0f,
					cosf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED));
				m_bmySet[nCnt] = true;
				break;
			}
		}
	}
}

//=====================================
// アクション処理
//=====================================
void CSpeaker::Action(void)
{
	// アクション状況を入れ替える
	m_bAction = !m_bAction;

	// 縮み状態にする
	m_state = STATE_SHRINK;
}

//=====================================
// 情報の設定処理
//=====================================
void CSpeaker::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

	// 全ての値を設定する
	m_state = STATE_STOP;		// 状態
}

//=====================================
// 当たり判定処理
//=====================================
bool CSpeaker::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// 最小値と最大値を設定する
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(fWidth, fHeight, fDepth);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-fWidth, 0.0f, -fDepth);

	// 六面体の当たり判定
	if (collision::HexahedronCollision
	(
		pos,					// プレイヤーの位置
		GetPos(),				// 位置
		posOld,					// プレイヤーの前回の位置
		GetPosOld(),			// 前回の位置
		vtxMin,					// プレイヤーの最小値
		GetFileData().vtxMin,	// 最小値
		vtxMax,					// プレイヤーの最大値
		GetFileData().vtxMax	// 最大値
	) == true)
	{ // 当たった場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CSpeaker::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	for (int nCntNote = 0; nCntNote < MAX_NOTE; nCntNote++)
	{
		if (m_apNote[nCntNote] != nullptr)
		{ // 音符が NULL じゃない場合

			if (pos.y <= m_apNote[nCntNote]->GetPos().y + m_apNote[nCntNote]->GetFileData().vtxMax.y &&
				pos.y + fHeight >= m_apNote[nCntNote]->GetPos().y + m_apNote[nCntNote]->GetFileData().vtxMin.y &&
				useful::CylinderInner(pos,m_apNote[nCntNote]->GetPos(),m_apNote[nCntNote]->GetFileData().fRadius + fWidth) == true)
			{ // 当たり判定の中に入った場合

				// true を返す
				return true;
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CSpeaker::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius + ADD_HIT_RADIUS) == true)
	{ // 円の範囲内にいた場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// 状態による処理
//=====================================
void CSpeaker::State(void)
{
	// 拡大率を取得する
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CSpeaker::STATE_STOP:		// 停止状態

		// 均等な数値の補正
		useful::FrameCorrect(STOP_SCALE, &scale.y, ADD_SCALE);

		break;

	case CSpeaker::STATE_SHRINK:	// 縮み状態

		if (useful::FrameCorrect(SHRINK_SCALE,&scale.y, ADD_SCALE) == true)
		{ // 拡大率が一定数になった場合

			// 拡大率を固定する
			scale.y = SHRINK_SCALE;

			// 伸び状態にする
			m_state = STATE_EXTEND;
		}

		break;

	case CSpeaker::STATE_EXTEND:	// 伸び状態

		if (useful::FrameCorrect(EXTEND_SCALE,&scale.y, ADD_SCALE) == true)
		{ // 拡大率が一定数になった場合

			// 拡大率を固定する
			scale.y = EXTEND_SCALE;

			// 縮み状態にする
			m_state = STATE_SHRINK;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 拡大率を適用する
	SetScale(scale);
}