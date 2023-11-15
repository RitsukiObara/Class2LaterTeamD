//============================================
//
// ファイルのメイン処理[file.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "scene.h"
#include "file.h"
#include "object.h"

#include "obstacle_manager.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define RANKING_BIN			"data\\BIN\\Ranking.bin"		// ランキングのテキスト
#define OBSTACLE_TXT		"data\\TXT\\Obstacle.txt"		// 障害物のテキスト
#define CARROUTE_TXT		"data\\TXT\\CarRoute.txt"		// 車の経路のテキスト

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
const char* CFile::c_apBooleanDisp[2] =					// bool型の表示
{
	"FALSE",							// TRUE
	"TRUE",								// FALSE
};

//===========================================
// コンストラクタ
//===========================================
CFile::CFile()
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;				// 位置
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;			// 種類

		for (int nCntCar = 0; nCntCar < MAX_CAR_ROUTE; nCntCar++)
		{
			m_CarRouteInfo.pos[nCntInfo][nCntCar];						// 車のルートの情報
		}
		m_CarRouteInfo.nNumPos[nCntInfo] = 0;							// 位置の数
	}

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		m_RankingInfo.aRank[nCntRank] = 0;				// ランキングの値
	}

	// 総数をクリアする
	m_ObstacleInfo.nNum = 0;			// 障害物
	m_CarRouteInfo.nNum = 0;			// 車の経路

	// 成功状況をクリアする
	m_RankingInfo.bSuccess = false;		// ランキング
	m_ObstacleInfo.bSuccess = false;	// 障害物
	m_CarRouteInfo.bSuccess = false;	// 車の経路
}

//===========================================
// デストラクタ
//===========================================
CFile::~CFile()
{

}

//===========================================
// セーブ処理
//===========================================
HRESULT CFile::Save(const TYPE type)
{
	switch (type)
	{
	case TYPE_RANKING:

		// ランキングのセーブ処理
		if (FAILED(SaveRanking()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_OBSTACLE:

		// 障害物のセーブ処理
		if (FAILED(SaveObstacle()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// ロード処理
//===========================================
HRESULT CFile::Load(const TYPE type)
{
	switch (type)
	{
	case TYPE_RANKING:

		// ランキングのロード処理
		if (FAILED(LoadRanking()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_OBSTACLE:

		// 障害物のロード処理
		if (FAILED(LoadObstacle()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_CARROUTE:

		// 車のロード処理
		if (FAILED(LoadCarRoute()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 結果を返す
	return S_OK;
}

//===========================================
// ランキングの設定処理
//===========================================
void CFile::SetRankingInfo(int* pRank)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++, pRank++)
	{
		// ランキングの情報を設定する
		m_RankingInfo.aRank[nCnt] = *pRank;
	}
}

//===========================================
// ランキングの取得処理
//===========================================
CFile::SRankingInfo CFile::GetRankingInfo(void)
{
	// ランキングの情報を返す
	return m_RankingInfo;
}

//===========================================
// 車の経路の取得処理
//===========================================
D3DXVECTOR3* CFile::GetCarRoute(const int nType)
{
	// 車の経路を返す
	return m_CarRouteInfo.pos[nType];
}

//===========================================
// 車の経路の総数取得処理
//===========================================
int CFile::GetCarRouteNum(void) const
{
	// 車の経路の数を返す
	return m_CarRouteInfo.nNum;
}

//===========================================
// 車の経路の位置の総数の取得処理
//===========================================
int CFile::GetCarRouteNumPos(const int nType) const
{
	// 車の経路の位置の総数を返す
	return m_CarRouteInfo.nNumPos[nType];
}

//===========================================
// マップの設定処理
//===========================================
void CFile::SetMap(void)
{
	if (m_ObstacleInfo.bSuccess == true)
	{ // 成功状況が true の場合

		for (int nCntObst = 0; nCntObst < m_ObstacleInfo.nNum; nCntObst++)
		{
			// 障害物の生成処理
			CObstacle::Create(m_ObstacleInfo.pos[nCntObst], m_ObstacleInfo.type[nCntObst]);
		}
	}
}

//===========================================
// 初期化処理
//===========================================
HRESULT CFile::Init(void)
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;				// 位置
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;			// 種類

		for (int nCntCar = 0; nCntCar < MAX_CAR_ROUTE; nCntCar++)
		{
			m_CarRouteInfo.pos[nCntInfo][nCntCar];						// 車のルートの情報
		}
		m_CarRouteInfo.nNumPos[nCntInfo] = 0;							// 位置の数
	}

	for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
	{
		m_RankingInfo.aRank[nCntRank] = 0;				// ランキングの値
	}

	// 総数をクリアする
	m_ObstacleInfo.nNum = 0;			// 障害物
	m_CarRouteInfo.nNum = 0;			// 車の経路

	// 成功状況をクリアする
	m_RankingInfo.bSuccess = false;		// ランキング
	m_ObstacleInfo.bSuccess = false;	// 障害物
	m_CarRouteInfo.bSuccess = false;	// 車の経路

	// 成功を返す
	return S_OK;
}

//===========================================
// 終了処理
//===========================================
void CFile::Uninit(void)
{
	
}

//===========================================
// ランキングのセーブ処理
//===========================================
HRESULT CFile::SaveRanking(void)
{
	FILE *pFile;												// ファイルポインタを宣言
	m_RankingInfo.bSuccess = false;								// 成功状況

	// ファイルを開く
	pFile = fopen(RANKING_BIN, "wb");			// バイナリファイルに書き込むために開く

	// ファイルを比較する
	if (pFile != NULL)
	{ // ファイルが開けた場合

		// ファイルから数値を書き出す
		fwrite(&m_RankingInfo.aRank[0], sizeof(int), MAX_RANKING, pFile);

		// ファイルを閉じる
		fclose(pFile);

		// 成功状況を true にする
		m_RankingInfo.bSuccess = true;

		// 成功を返す
		return S_OK;
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}
}

//===========================================
// 障害物のセーブ処理
//===========================================
HRESULT CFile::SaveObstacle(void)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(OBSTACLE_TXT, "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pObstacle != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_OBSTACLE\n");		// 障害物の設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pObstacle->GetPos().x, pObstacle->GetPos().y, pObstacle->GetPos().z);			// 位置を書き込む

			fprintf(pFile, "\tTYPE = ");		// 種類の設定を書き込む
			fprintf(pFile, "%d\n", pObstacle->GetType());			// 種類を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_OBSTACLE\n\n");	// 障害物の設定の終了を書き込む

			// 次のオブジェクトを代入する
			pObstacle = pObstacle->GetNext();
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// ランキングのロード処理
//===========================================
HRESULT CFile::LoadRanking(void)
{
	FILE *pFile;						// ファイルポインタを宣言
	m_RankingInfo.bSuccess = false;		// 成功状況

	// ファイルを開く
	pFile = fopen(RANKING_BIN, "rb");			// バイナリファイルから読み込むために開く

	// ファイルを比較する
	if (pFile != NULL)
	{ // ファイルが開けた場合

		// ファイルから数値を読み込む
		fread(&m_RankingInfo.aRank[0], sizeof(int), MAX_RANKING, pFile);

		// ファイルを閉じる
		fclose(pFile);

		// 成功状況を true にする
		m_RankingInfo.bSuccess = true;

		// 成功を返す
		return S_OK;
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			// 数値を設定する
			m_RankingInfo.aRank[0] = 0;
		}

		// 失敗を返す
		return E_FAIL;
	}
}

//===========================================
// 障害物のロード処理
//===========================================
HRESULT CFile::LoadObstacle(void)
{
	// 変数を宣言
	int nEnd;							// テキスト読み込み終了の確認用
	char aString[MAX_STRING];			// テキストの文字列の代入用
	m_ObstacleInfo.nNum = 0;			// 総数
	m_ObstacleInfo.bSuccess = false;	// 成功状況

	// ポインタを宣言
	FILE *pFile;						// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(OBSTACLE_TXT, "r");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		do
		{ // 読み込んだ文字列が EOF ではない場合ループ

			// ファイルから文字列を読み込む
			nEnd = fscanf(pFile, "%s", &aString[0]);	// テキストを読み込みきったら EOF を返す

			if (strcmp(&aString[0], "SET_OBSTACLE") == 0)
			{ // 読み込んだ文字列が SET_OBSTACLE の場合

				do
				{ // 読み込んだ文字列が END_SET_OBSTACLE ではない場合ループ

				  // ファイルから文字列を読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // 読み込んだ文字列が POS の場合

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%f%f%f",
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].x,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].y,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].z);		// 位置を読み込む
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // 読み込んだ文字列が TYPE の場合

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%d",
							&m_ObstacleInfo.type[m_ObstacleInfo.nNum]);		// 位置を読み込む
					}

				} while (strcmp(&aString[0], "END_SET_OBSTACLE") != 0);		// 読み込んだ文字列が END_SET_OBSTACLE ではない場合ループ

				// データの総数を増やす
				m_ObstacleInfo.nNum++;
			}
		} while (nEnd != EOF);				// 読み込んだ文字列が EOF ではない場合ループ

		// ファイルを閉じる
		fclose(pFile);

		// 成功状況を true にする
		m_ObstacleInfo.bSuccess = true;
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// 車の経路のロード処理
//===========================================
HRESULT CFile::LoadCarRoute(void)
{
	// 変数を宣言
	int nEnd;							// テキスト読み込み終了の確認用
	char aString[MAX_STRING];			// テキストの文字列の代入用
	m_CarRouteInfo.nNum = 0;			// 総数
	m_CarRouteInfo.bSuccess = false;	// 成功状況

	// ポインタを宣言
	FILE *pFile;						// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(CARROUTE_TXT, "r");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		do
		{ // 読み込んだ文字列が EOF ではない場合ループ

			// ファイルから文字列を読み込む
			nEnd = fscanf(pFile, "%s", &aString[0]);	// テキストを読み込みきったら EOF を返す

			if (strcmp(&aString[0], "SET_CARROUTE") == 0)
			{ // 読み込んだ文字列が SET_CARROUTE の場合

				do
				{ // 読み込んだ文字列が END_SET_CARROUTE ではない場合ループ

					// ファイルから文字列を読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUMROUTE") == 0)
					{ // 読み込んだ文字列が NUMROUTE の場合

						fscanf(pFile, "%s", &aString[0]);										// = を読み込む (不要)
						fscanf(pFile, "%d", &m_CarRouteInfo.nNumPos[m_CarRouteInfo.nNum]);		// 位置を読み込む

						if (m_CarRouteInfo.nNumPos[m_CarRouteInfo.nNum] > MAX_CAR_ROUTE)
						{ // 最大数を超えていた場合

							// 停止
							assert(false);
						}
					}
					else if (strcmp(&aString[0], "POS") == 0)
					{ // 読み込んだ文字列が POS の場合

						for (int nCnt = 0; nCnt < m_CarRouteInfo.nNumPos[m_CarRouteInfo.nNum]; nCnt++)
						{
							fscanf(pFile, "%s", &aString[0]);					// 位置の番号 を読み込む (不要)
							fscanf(pFile, "%s", &aString[0]);					// = を読み込む (不要)
							fscanf(pFile, "%f%f%f", 
								&m_CarRouteInfo.pos[m_CarRouteInfo.nNum][nCnt].x,
								&m_CarRouteInfo.pos[m_CarRouteInfo.nNum][nCnt].y,
								&m_CarRouteInfo.pos[m_CarRouteInfo.nNum][nCnt].z);	// 位置を読み込む
						}
					}

				} while (strcmp(&aString[0], "END_SET_CARROUTE") != 0);		// 読み込んだ文字列が END_SET_CARROUTE ではない場合ループ

				// データの総数を増やす
				m_CarRouteInfo.nNum++;
			}
		} while (nEnd != EOF);				// 読み込んだ文字列が EOF ではない場合ループ

		// ファイルを閉じる
		fclose(pFile);

		// 成功状況を true にする
		m_CarRouteInfo.bSuccess = true;
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}