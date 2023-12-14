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
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_fEdge = 0.0f;						// カーテンの端の座標
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
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_fEdge = 0.0f;						// カーテンの端の座標

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

	// 拡大率の設定処理
	ScaleVtxSet();
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

	// 頂点の設定処理
	VtxSetting();

	// 拡大率による頂点の設定処理
	ScaleVtxSet();
}

//=====================================
// 当たり判定処理
//=====================================
bool CCurtain::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);	// 最小値
	D3DXVECTOR3 vtxMax = collSize;										// 最大値

	// 六面体の当たり判定
	collision::HexahedronCollision
	(
		&pos,
		GetPos(),
		pPlayer->GetPosOld(),
		GetPosOld(),
		vtxMin,
		m_vtxMin,
		vtxMax,
		m_vtxMax
	);

	// 位置を適用する
	pPlayer->SetPos(pos);

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
// 頂点の設定処理
//=====================================
void CCurtain::VtxSetting(void)
{
	// 向きと最大値・最小値を設定する
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;

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
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.x);
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);
	}
}

//=====================================
// 拡大率による頂点の設定処理
//=====================================
void CCurtain::ScaleVtxSet(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// カーテンの端の座標を設定する
	m_fEdge = GetFileData().vtxMin.z * GetScale().z;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // 方向が手前からの場合

		// 頂点を設定する
		m_vtxMin.z = m_fEdge;
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // 方向が左からの場合

		// 頂点を設定する
		m_vtxMin.x = m_fEdge;
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // 方向が右からの場合

		// 頂点を設定する
		m_vtxMax.x = -m_fEdge;
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 頂点を設定する
		m_vtxMax.z = -m_fEdge;
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