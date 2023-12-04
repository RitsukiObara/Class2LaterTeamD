//===========================================
//
// 当たり判定エディットのメイン処理[collision_edit.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "collision_edit.h"
#include "model.h"
#include "file.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define NORMAL_MOVE			(10.0f)		// 通常の移動量
#define ADJUST_MOVE			(1.0f)		// 微調整時の移動量
#define SCALE_MOVE			(0.01f)		// 拡大率の移動量

//==============================
// コンストラクタ
//==============================
CCollisionEdit::CCollisionEdit() : CObject(CObject::TYPE_EDIT, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_NUMCOLL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// 当たり判定の情報
	}
	m_posInit = NONE_D3DXVECTOR3;		// 初期位置
	m_nNumColl = MIN_NUMCOLL;			// 当たり判定の総数
	m_nIdx = m_nNumColl - 1;			// インデックス
}

//==============================
// デストラクタ
//==============================
CCollisionEdit::~CCollisionEdit()
{

}

//==============================
// 当たり判定エディットの初期化処理
//==============================
HRESULT CCollisionEdit::Init(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_NUMCOLL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// 当たり判定の情報
	}
	m_posInit = NONE_D3DXVECTOR3;		// 初期位置
	m_nNumColl = MIN_NUMCOLL;			// 当たり判定の総数
	m_nIdx = m_nNumColl - 1;			// インデックス

	// 値を返す
	return S_OK;
}

//========================================
// 当たり判定エディットの終了処理
//========================================
void CCollisionEdit::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_NUMCOLL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// 当たり判定の情報の終了処理
			m_apModel[nCnt]->Uninit();
			m_apModel[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//=====================================
// 当たり判定エディットの更新処理
//=====================================
void CCollisionEdit::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) != true)
	{ // 左CTRLキーを押していない場合

		// 移動処理
		Move();

		// 微調整処理
		Adjust();

		// インデックス切り替え処理
		IdxChange();

		// 位置のリセット処理
		PosReset();

		// 総数の設定処理
		NumSet();

		// 拡縮処理
		Scaling();

		// 拡縮微調整処理
		ScalingAdjust();

		// セーブ処理
		Save();
	}

	// デバッグメッセージ
	CManager::Get()->GetDebugProc()->Print("当たり判定の総数：%d\n現在の当たり判定：%d\n位置：%f %f %f\n拡大率：%f %f %f\n左SHIFTキー：微調整\nW/Sキー：Z軸移動\nA/Dキー：X軸移動\n↑/↓キー：Y軸移動\n"
		"SPACEキー：インデックスの切り替え\n1キー：原点へと戻す\n9キー：総数の加算\n8キー：総数の減算\n"
		"X軸の拡縮：T/B\nY軸の拡縮：Y/N\nZ軸の拡縮：U/M\n"
		, m_nNumColl, m_nIdx, m_apModel[m_nIdx]->GetPos().x, m_apModel[m_nIdx]->GetPos().y, m_apModel[m_nIdx]->GetPos().z,
		m_apModel[m_nIdx]->GetScale().x, m_apModel[m_nIdx]->GetScale().y, m_apModel[m_nIdx]->GetScale().z);
}

//=====================================
// 当たり判定エディットの描画処理
//=====================================
void CCollisionEdit::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nNumColl; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルが NULL じゃない場合

			if (nCnt == m_nIdx)
			{ // 現在選択中の当たり判定の場合

				// 通常描画処理
				m_apModel[nCnt]->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f));
			}
			else
			{ // 上記以外

				// 通常描画処理
				m_apModel[nCnt]->Draw(0.5f);
			}
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CCollisionEdit::SetData(const D3DXVECTOR3& pos)
{
	// 全ての値を設定する
	m_posInit = pos;				// 初期位置
	m_nNumColl = MIN_NUMCOLL;		// 当たり判定の総数
	m_nIdx = m_nNumColl - 1;			// インデックス

	if (m_apModel[m_nIdx] == nullptr)
	{ // 1つ目のモデルが NULL の場合

		// 当たり判定モデルを生成する
		m_apModel[m_nIdx] = new CModel(TYPE_NONE, PRIORITY_UI);

		// 情報の設定処理
		m_apModel[m_nIdx]->SetPos(pos);							// 位置
		m_apModel[m_nIdx]->SetPosOld(pos);						// 前回の位置
		m_apModel[m_nIdx]->SetRot(NONE_D3DXVECTOR3);			// 向き
		m_apModel[m_nIdx]->SetScale(NONE_SCALE);				// 拡大率
		m_apModel[m_nIdx]->SetFileData(CXFile::TYPE_COLLISION);	// モデルの情報設定
	}
}

//=======================================
// 生成処理
//=======================================
CCollisionEdit* CCollisionEdit::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CCollisionEdit* pEdit = nullptr;	// インスタンスを生成

	if (pEdit == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pEdit = new CCollisionEdit;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEdit != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEdit->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEdit->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 当たり判定エディットのポインタを返す
	return pEdit;
}

//=======================================
// モデルの情報の取得処理
//=======================================
CModel* CCollisionEdit::GetModel(const int nNum) const
{
	// モデルの情報を返す
	return m_apModel[nNum];
}

//=======================================
// 初期位置の取得処理
//=======================================
D3DXVECTOR3 CCollisionEdit::GetPosInit(void) const
{
	// 初期位置を返す
	return m_posInit;
}

//=======================================
// 総数の取得処理
//=======================================
int CCollisionEdit::GetNumColl(void) const
{
	// 総数を返す
	return m_nNumColl;
}

//=======================================
// 移動処理
//=======================================
void CCollisionEdit::Move(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // 左SHIFTまたは、左CTRLキーを押していた場合

		// この先の処理を行わない
		return;
	}

	// ローカル変数宣言
	D3DXVECTOR3 pos = m_apModel[m_nIdx]->GetPos();		// 位置を取得する

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // Wキーを押していた場合

		// 位置を加算する
		pos.z += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // Sキーを押していた場合

		// 位置を加算する
		pos.z -= NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // Dキーを押していた場合

		// 位置を加算する
		pos.x += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // Aキーを押していた場合

		// 位置を加算する
		pos.x -= NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_UP) == true)
	{ // 上キーを押していた場合

		// 位置を加算する
		pos.y += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_DOWN) == true)
	{ // 下キーを押していた場合

		// 位置を加算する
		pos.y -= NORMAL_MOVE;
	}

	// 位置を設定する
	m_apModel[m_nIdx]->SetPos(pos);
}

//=======================================
// 微調整処理
//=======================================
void CCollisionEdit::Adjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // 左SHIFTキーを押していた場合

		// ローカル変数宣言
		D3DXVECTOR3 pos = m_apModel[m_nIdx]->GetPos();		// 位置を取得する

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true)
		{ // Wキーを押した場合

			// 位置を加算する
			pos.z += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true)
		{ // Sキーを押した場合

			// 位置を加算する
			pos.z -= ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
		{ // Dキーを押した場合

			// 位置を加算する
			pos.x += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
		{ // Aキーを押した場合

			// 位置を加算する
			pos.x -= ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_UP) == true)
		{ // 上キーを押した場合

			// 位置を加算する
			pos.y += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_DOWN) == true)
		{ // 下キーを押した場合

			// 位置を加算する
			pos.y -= ADJUST_MOVE;
		}

		// 位置を設定する
		m_apModel[m_nIdx]->SetPos(pos);
	}
}

//=======================================
// インデックスの切り替え処理
//=======================================
void CCollisionEdit::IdxChange(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // SPACEキーを押した場合

		// インデックスを切り替える
		m_nIdx = (m_nIdx + 1) % m_nNumColl;
	}
}

//=======================================
// 位置のリセット処理
//=======================================
void CCollisionEdit::PosReset(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1キーを押した場合

		// 位置を取得する
		D3DXVECTOR3 pos = m_apModel[m_nIdx]->GetPos();

		// 位置を初期位置に戻す
		pos = m_posInit;

		// 位置を適用する
		m_apModel[m_nIdx]->SetPos(pos);
	}
}

//=======================================
// 総数の設定処理
//=======================================
void CCollisionEdit::NumSet(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
	{ // 9キーを押した場合

		if (m_nNumColl < MAX_NUMCOLL)
		{ // 当たり判定の数が最大値未満の場合

			// 総数を加算する
			m_nNumColl++;

			// 当たり判定モデルを生成する
			m_apModel[m_nNumColl - 1] = new CModel(TYPE_NONE, PRIORITY_UI);

			// 情報の設定処理
			m_apModel[m_nNumColl - 1]->SetPos(m_posInit);					// 位置
			m_apModel[m_nNumColl - 1]->SetPosOld(m_posInit);				// 前回の位置
			m_apModel[m_nNumColl - 1]->SetRot(NONE_D3DXVECTOR3);			// 向き
			m_apModel[m_nNumColl - 1]->SetScale(NONE_SCALE);				// 拡大率
			m_apModel[m_nNumColl - 1]->SetFileData(CXFile::TYPE_COLLISION);	// モデルの情報設定
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_8) == true)
	{ // 8キーを押した場合

		if (m_nNumColl > MIN_NUMCOLL)
		{ // 当たり判定の数が最大値未満の場合

			// 総数を減算する
			m_nNumColl--;

			// 終了処理
			m_apModel[m_nNumColl]->Uninit();
			m_apModel[m_nNumColl] = nullptr;

			// 現在のインデックスを設定する
			m_nIdx = m_nNumColl - 1;
		}
	}
}

//=======================================
// 拡縮処理
//=======================================
void CCollisionEdit::Scaling(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // 左SHIFTまたは、左CTRLキーを押していた場合

		// この先の処理を行わない
		return;
	}

	// 拡大率を取得する
	D3DXVECTOR3 scale = m_apModel[m_nIdx]->GetScale();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_T) == true)
	{ // Tキーを押した場合

		// X軸を拡大する
		scale.x += SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_B) == true)
	{ // Bキーを押した場合

		// X軸を縮小する
		scale.x -= SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_Y) == true)
	{ // Yキーを押した場合

		// Y軸を拡大する
		scale.y += SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_N) == true)
	{ // Nキーを押した場合

		// Y軸を縮小する
		scale.y -= SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_U) == true)
	{ // Uキーを押した場合

		// Z軸を拡大する
		scale.z += SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_M) == true)
	{ // Mキーを押した場合

		// Z軸を縮小する
		scale.z -= SCALE_MOVE;
	}

	// 拡大率を適用する
	m_apModel[m_nIdx]->SetScale(scale);
}

//=======================================
// 拡縮微調整処理
//=======================================
void CCollisionEdit::ScalingAdjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // 左SHIFTまたは、左CTRLキーを押していた場合

		// 拡大率を取得する
		D3DXVECTOR3 scale = m_apModel[m_nIdx]->GetScale();

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_T) == true)
		{ // Tキーを押した場合

			// X軸を拡大する
			scale.x += SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_B) == true)
		{ // Bキーを押した場合

			// X軸を縮小する
			scale.x -= SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_Y) == true)
		{ // Yキーを押した場合

			// Y軸を拡大する
			scale.y += SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_N) == true)
		{ // Nキーを押した場合

			// Y軸を縮小する
			scale.y -= SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_U) == true)
		{ // Uキーを押した場合

			// Z軸を拡大する
			scale.z += SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_M) == true)
		{ // Mキーを押した場合

			// Z軸を縮小する
			scale.z -= SCALE_MOVE;
		}

		// 拡大率を適用する
		m_apModel[m_nIdx]->SetScale(scale);
	}
}

//=======================================
// セーブ処理
//=======================================
void CCollisionEdit::Save(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0キーを押した場合

		// 当たり判定のセーブ処理
		CManager::Get()->GetFile()->Save(CFile::TYPE_COLLISION);
	}
}