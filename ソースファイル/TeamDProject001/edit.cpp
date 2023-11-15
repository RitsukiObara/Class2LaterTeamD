//===========================================
//
// エディットのメイン処理[edit.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "edit.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "useful.h"

#include "obstacle_manager.h"
#include "block_manager.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define ADJUST_MOVE		(2.0f)		// 微調整状態の移動量
#define NORMAL_MOVE		(16.0f)		// 通常状態の移動量
#define ROTMOVE			(0.01f)		// 向きの移動量

//==============================
// コンストラクタ
//==============================
CEdit::CEdit() : CModel(CObject::TYPE_EDIT, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_type = TYPE::TYPE_OBSTACLE;				// 種類
	m_obstacleType = CObstacle::TYPE_HONEY;		// 障害物の種類
	m_blockType = CBlock::TYPE_CARDBOARD;		// ブロックの種類
}

//==============================
// デストラクタ
//==============================
CEdit::~CEdit()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CEdit::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_type = TYPE::TYPE_OBSTACLE;			// 種類
	m_obstacleType = CObstacle::TYPE_HONEY;	// 障害物の種類
	m_blockType = CBlock::TYPE_CARDBOARD;	// ブロックの種類

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CEdit::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CEdit::Update(void)
{
	// 種類ごとの処理
	TypeProcess();

	// 種類の設定処理 
	Type();

	// 移動処理
	Move();

	// 微調整移動処理
	Adjust();

	// 向きの移動処理
	RotMove();

	// 消去処理
	Delete();

	// 設置処理
	Set();

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n", GetPos().x, GetPos().y, GetPos().z);
}

//=====================================
// 破片の描画処理
//=====================================
void CEdit::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CEdit::SetData(void)
{
	// 情報の設定処理
	SetPos(NONE_D3DXVECTOR3);				// 位置
	SetPosOld(NONE_D3DXVECTOR3);			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_HONEY);		// モデルの情報設定

	// 全ての値をクリアする
	m_type = TYPE::TYPE_OBSTACLE;			// 種類
	m_obstacleType = CObstacle::TYPE_HONEY;	// 障害物の種類
	m_blockType = CBlock::TYPE_CARDBOARD;	// ブロックの種類
}

//=======================================
// 生成処理
//=======================================
CEdit* CEdit::Create(void)
{
	// ローカルオブジェクトを生成
	CEdit* pEdit = nullptr;	// インスタンスを生成

	if (pEdit == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pEdit = new CEdit;
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
		pEdit->SetData();
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
// 種類ごとの処理
//=======================================
void CEdit::TypeProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押している場合

		// この先の処理を行わない
		return;
	}

	switch (m_type)
	{
	case CEdit::TYPE_OBSTACLE:		// 障害物

		// 障害物の処理
		ObstacleProcess();

		break;

	case CEdit::TYPE_BLOCK:			// ブロック

		// ブロックの処理
		BlockProcess();

		break;

	default:						// 上記以外

		// 停止
		assert(false);

		break;
	}
}

//=======================================
// 移動処理
//=======================================
void CEdit::Move(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左SHIFTまたは、左CTRLキーを押していた場合

		// この先の処理を行わない
		return;
	}

	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

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

	// 位置を設定する
	SetPos(pos);
}

//=======================================
// 微調整処理
//=======================================
void CEdit::Adjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押している場合

		// この先の処理を行わない
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // 左SHIFTキーを押していた場合

		// ローカル変数宣言
		D3DXVECTOR3 pos = GetPos();		// 位置を取得する

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

		// 位置を設定する
		SetPos(pos);
	}
}

//=======================================
// 向きの移動処理
//=======================================
void CEdit::RotMove(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押している場合

		// この先の処理を行わない
		return;
	}

	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RIGHT) == true)
	{ // 右キーを押している場合

		// 向きを減算する
		rot.y -= ROTMOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LEFT) == true)
	{ // 左キーを押している場合

		// 向きを加算する
		rot.y += ROTMOVE;
	}

	// 向きの正規化
	useful::RotNormalize(&rot.y);

	// 向きを設定する
	SetRot(rot);
}

//=======================================
// 設置処理
//=======================================
void CEdit::Set(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押している場合

		// この先の処理を行わない
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0キーを押した場合

		switch (m_type)
		{
		case CEdit::TYPE_OBSTACLE:		// 障害物

			// 障害物の生成処理
			CObstacle::Create(GetPos(), m_obstacleType);

			break;

		case CEdit::TYPE_BLOCK:

			// ブロックの生成処理
			CBlock::Create(GetPos(), GetRot(), m_blockType);

			break;

		default:						// 種類

			// 停止
			assert(false);

			break;
		}
	}
}

//=======================================
// 障害物の設定処理
//=======================================
void CEdit::ObstacleProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1キーを押した場合

		// 障害物の種類を設定する
		m_obstacleType = (CObstacle::TYPE)((m_obstacleType + 1) % CObstacle::TYPE_MAX);
	}

	switch (m_obstacleType)
	{
	case CObstacle::TYPE_HONEY:

		// 蜂蜜を設定する
		SetFileData(CXFile::TYPE_HONEY);

		break;

	case CObstacle::TYPE_SLIME:

		// スライムを設定する
		SetFileData(CXFile::TYPE_SLIME);

		break;

	case CObstacle::TYPE_HAIRBALL:

		// 毬を設定する
		SetFileData(CXFile::TYPE_HAIRBALL);

		break;

	case CObstacle::TYPE_FLOWERVASE:

		// 花瓶を設定する
		SetFileData(CXFile::TYPE_FLOWERVASE);

		break;

	case CObstacle::TYPE_PLASTICCASE:

		// プラスチックケースを設定する
		SetFileData(CXFile::TYPE_PLASTICCASE);

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=======================================
// ブロックの処理
//=======================================
void CEdit::BlockProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1キーを押した場合

		// ブロックの種類を設定する
		m_blockType = (CBlock::TYPE)((m_blockType + 1) % CBlock::TYPE_MAX);
	}

	if (m_blockType >= TYPE_MAX)
	{ // タイプにある場合

		// 停止
		assert(false);
	}
	else
	{ // 上記以外

		// ブロックの種類を設定する
		SetFileData((CXFile::TYPE)(INIT_BLOCK + m_blockType));
	}
}

//=======================================
// 種類の変更処理
//=======================================
void CEdit::Type(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押している場合

		// この先の処理を行わない
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // SPACEキーを押した場合

		// 種類を変更する
		m_type = (CEdit::TYPE)((m_type + 1) % CEdit::TYPE_MAX);
	}
}

//=======================================
// 消去処理
//=======================================
void CEdit::Delete(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押している場合

		// この先の処理を行わない
		return;
	}

	switch (m_type)
	{
	case CEdit::TYPE_OBSTACLE:		// 障害物

		// 障害物の消去処理
		DeleteObstacle();

		break;

	case CEdit::TYPE_BLOCK:			// ブロック

		// ブロックの消去処理
		DeleteBlock();

		break;

	default:						// 種類

		// 停止
		assert(false);

		break;
	}
}

//=======================================
// 障害物の消去処理
//=======================================
void CEdit::DeleteObstacle(void)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	CObstacle* pObstacleNext = nullptr;								// 次の障害物

	while (pObstacle != nullptr)
	{ // 障害物が NULL じゃない場合

		// 次の障害物を設定する
		pObstacleNext = pObstacle->GetNext();

		if (useful::RectangleCollisionXY(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
		{ // オブジェクトの中に入っている場合

			// 終了処理
			pObstacle->Uninit();
		}

		// 次の障害物のポインタを代入する
		pObstacle = pObstacleNext;
	}
}

//=======================================
// ブロックの消去処理
//=======================================
void CEdit::DeleteBlock(void)
{
	// ローカル変数宣言
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// 先頭のブロックを取得する
	CBlock* pBlockNext = nullptr;							// 次のブロック

	while (pBlock != nullptr)
	{ // ブロックが NULL じゃない場合

		// 次のブロックを設定する
		pBlockNext = pBlock->GetNext();

		if (useful::RectangleCollisionXY(GetPos(), pBlock->GetPos(), GetFileData().vtxMax, pBlock->GetFileData().vtxMax, GetFileData().vtxMin, pBlock->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pBlock->GetPos(), GetFileData().vtxMax, pBlock->GetFileData().vtxMax, GetFileData().vtxMin, pBlock->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pBlock->GetPos(), GetFileData().vtxMax, pBlock->GetFileData().vtxMax, GetFileData().vtxMin, pBlock->GetFileData().vtxMin) == true &&
			CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
		{ // オブジェクトの中に入っている場合

			// 終了処理
			pBlock->Uninit();
		}

		// 次のブロックのポインタを代入する
		pBlock = pBlockNext;
	}
}