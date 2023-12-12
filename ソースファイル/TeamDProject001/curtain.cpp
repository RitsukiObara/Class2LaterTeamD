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
		D3DXVECTOR3(-500.0f,100.0f,0.0f),
		D3DXVECTOR3(0.0f,100.0f,0.0f),
		D3DXVECTOR3(500.0f,100.0f,0.0f),
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
	SetCatUse(true);					// ネコの使用条件
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

	if (m_apSwitch[0]->GetBoot() == true &&
		m_apSwitch[1]->GetBoot() == true &&
		m_apSwitch[2]->GetBoot() == true)
	{ // 全てスイッチが入っていた場合

		// 開ける
		m_state = STATE_OPEN;
	}
	else
	{ // 上記以外

		// 閉じる
		m_state = STATE_CLOSE;
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
		if (m_apSwitch[nCnt] == nullptr)
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
bool CCurtain::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 objMin = GetFileData().vtxMin;							// カーテンの最小値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);	// 最小値
	D3DXVECTOR3 vtxMax = collSize;										// 最大値

	// カーテンの最小値(Z軸)を設定する
	objMin.z = GetFileData().vtxMin.z * GetScale().z;

	// 六面体の当たり判定
	if (collision::HexahedronCollision
	(
		&pos,
		GetPos(),
		pPlayer->GetPosOld(),
		GetPosOld(),
		vtxMin,
		objMin,
		vtxMax,
		GetFileData().vtxMax
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
bool CCurtain::HitCircle(CPlayer* pPlayer, const float Radius)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL の場合

			if (useful::CircleCollisionXZ
			(
				pPlayer->GetPos(),
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetPos(),
				Radius,
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetFileData().fRadius
			) == true)
			{ // 円の当たり判定内に入った場合

				switch (pPlayer->GetType())
				{
				case CPlayer::TYPE_CAT:		// ネコ

					if (m_apSwitch[nCnt]->GetBoot() == true)
					{ // 起動状況が false の場合

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(true, pPlayer->GetPlayerIdx());
					}
					else
					{ // 上記以外

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
					}

					break;

				case CPlayer::TYPE_RAT:		// ネズミ

					if (m_apSwitch[nCnt]->GetBoot() == false)
					{ // 起動状況が true の場合

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(true, pPlayer->GetPlayerIdx());
					}
					else
					{ // 上記以外

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
					}

					break;

				default:

					// 停止
					assert(false);

					break;
				}
			}
			else
			{ // 上記以外

				// ギミックUIの設定処理
				m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
void CCurtain::HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL の場合

			if (useful::CircleCollisionXZ
			(
				pPlayer->GetPos(),
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetPos(),
				Radius,
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetFileData().fRadius
			) == true)
			{ // 円の当たり判定内に入った場合

				if (bInput == true)
				{ // 入力状況が true の場合

					switch (pPlayer->GetType())
					{
					case CPlayer::TYPE_CAT:		// ネコ

						if (m_apSwitch[nCnt]->GetBoot() == true)
						{ // 起動状況が false の場合

							// 起動状況の入れ替え処理
							m_apSwitch[nCnt]->ChangeBoot();
						}

						break;

					case CPlayer::TYPE_RAT:		// ネズミ

						if (m_apSwitch[nCnt]->GetBoot() == false)
						{ // 起動状況が true の場合

							// 起動状況の入れ替え処理
							m_apSwitch[nCnt]->ChangeBoot();
						}

						break;

					default:

						// 停止
						assert(false);

						break;
					}
				}
			}
		}
	}
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