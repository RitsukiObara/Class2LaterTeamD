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
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define NORMAL_MOVE			(10.0f)		// 通常の移動量
#define ADJUST_MOVE			(1.0f)		// 微調整時の移動量

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
// 破片の初期化処理
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
// 破片の終了処理
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
// 破片の更新処理
//=====================================
void CCollisionEdit::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) != true)
	{ // 左CTRLキーを押していない場合

		// 移動処理
		Move();

		// 微調整処理
		Adjust();

		// 位置のリセット処理
		PosReset();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CCollisionEdit::Draw(void)
{

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
		m_apModel[m_nIdx] = CModel::Create();

		// 情報の設定処理
		m_apModel[m_nIdx]->SetPos(pos);							// 位置
		m_apModel[m_nIdx]->SetPosOld(pos);						// 前回の位置
		m_apModel[m_nIdx]->SetRot(NONE_D3DXVECTOR3);			// 向き
		m_apModel[m_nIdx]->SetScale(NONE_SCALE);				// 拡大率
		m_apModel[m_nIdx]->SetFileData(CXFile::TYPE_HONEY);		// モデルの情報設定
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

	// 破片のポインタを返す
	return pEdit;
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