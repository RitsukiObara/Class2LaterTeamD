//===========================================
//
// カーテンの処理[curtain.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "curtain.h"
#include "useful.h"
#include "input.h"
#include "collision.h"

#include "switch.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	static const D3DXVECTOR3 SWITCH_POS[MAX_SWITCH] =		// スイッチの位置
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
	};
	static const D3DXVECTOR3 SWITCH_ROT[MAX_SWITCH] =		// スイッチの向き
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
	};
	static const float CLOSE_SCALE = 0.03f;					// 閉じた状態の拡大率
	static const float SCALE_CORRECT = 0.01f;				// 拡大率の補正率
	static const float OPEN_SCALE = 1.0f;					// 開いた状態の拡大率
}

//==============================
// コンストラクタ
//==============================
CCurtain::CCurtain() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// スイッチの情報
	}
	m_state = STATE_CLOSE;				// 状態
	m_fVtxMinZ = 0.0f;					// Z軸の最小値
	SetCatUse(false);					// ネコの使用条件
	SetRatUse(true);					// ネズミの使用条件
}

//==============================
// デストラクタ
//==============================
CCurtain::~CCurtain()
{

}

//==============================
// カーテンの初期化処理
//==============================
HRESULT CCurtain::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// モデルの情報
	}
	m_state = STATE_CLOSE;				// 状態
	m_fVtxMinZ = 0.0f;					// Z軸の最小値

	// 値を返す
	return S_OK;
}

//========================================
// カーテンの終了処理
//========================================
void CCurtain::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL じゃない場合

			// スイッチの終了処理
			m_apSwitch[nCnt]->Uninit();
			m_apSwitch[nCnt] = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// カーテンの更新処理
//=====================================
void CCurtain::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 状態マネージャー
	StateManager();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL じゃない場合

			// スイッチの更新処理
			m_apSwitch[nCnt]->Update();
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0キーを押した場合

		// 状態を設定する
		m_state = (STATE)((m_state + 1) % STATE_MAX);
	}
}

//=====================================
// カーテンの描画処理
//=====================================
void CCurtain::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL じゃない場合

			// スイッチの描画処理
			m_apSwitch[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CCurtain::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 拡大率を初期化する
	SetScale(D3DXVECTOR3(1.0f, 1.0f, CLOSE_SCALE));

	// 全ての値を設定する
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // モデルが NULL じゃない場合

			// スイッチの生成処理
			m_apSwitch[nCnt] = CSwitch::Create(SWITCH_POS[nCnt], SWITCH_ROT[nCnt]);
		}
	}
	m_state = STATE_CLOSE;			// 状態
	m_fVtxMinZ = GetFileData().vtxMin.z * GetScale().z;		// Z軸の最小値
}

//=====================================
// 当たり判定処理
//=====================================
bool CCurtain::Collision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	D3DXVECTOR3 objMin = GetFileData().vtxMin;							// カーテンの最小値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);	// 最小値
	D3DXVECTOR3 vtxMax = collSize;										// 最大値

	// カーテンの最小値(Z軸)を設定する
	objMin.z = GetFileData().vtxMin.z * GetScale().z;

	// 六面体の当たり判定
	if (collision::HexahedronCollision
	(
		pos,
		GetPos(),
		posOld,
		GetPosOld(),
		vtxMin,
		objMin,
		vtxMax,
		GetFileData().vtxMax
		) == true)
	{ // 当たった場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// 円のヒット処理
//=====================================
bool CCurtain::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CCurtain::Action(void)
{

}

//=====================================
// 状態マネージャー
//=====================================
void CCurtain::StateManager(void)
{
	// 拡大率を取得する
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CCurtain::STATE_CLOSE:		// 閉じる状態

		// 均等な補正処理
		useful::FrameCorrect(CLOSE_SCALE, &scale.z, SCALE_CORRECT);

		break;

	case CCurtain::STATE_OPEN:		// 開いた状態

		// 均等な補正処理
		useful::FrameCorrect(OPEN_SCALE, &scale.z, SCALE_CORRECT);

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 拡大率を適用する
	SetScale(scale);
}