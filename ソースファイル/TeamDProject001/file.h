//============================================
//
// ファイルヘッダー[file.h]
// Author：小原立暉
//
//============================================
#ifndef _FILE_H_			//このマクロ定義がされていなかったら
#define _FILE_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"
#include "ranking.h"
#include "obstacle.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAX_FILE_DATA		(512)		// ファイルのデータの最大数
#define MAX_CAR_ROUTE		(10)		// 車の経路の最大数

//--------------------------------------------
// クラス(ファイル読み込みクラス)
//--------------------------------------------
class CFile
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_RANKING = 0,	// ランキング
		TYPE_OBSTACLE,		// 障害物
		TYPE_CARROUTE,		// 車の経路
		TYPE_MAX			// この列挙型の総数
	};

	// ランキングの情報
	struct SRankingInfo
	{
		int aRank[MAX_RANKING];					// ランキングのデータ
		bool bSuccess;							// 成功状況
	};

	// 障害物の情報
	struct SObstacleInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];			// 位置
		CObstacle::TYPE type[MAX_FILE_DATA];	// 種類
		int nNum;								// 総数
		bool bSuccess;							// 成功状況
	};

	// 車の経路
	struct SCarRouteInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA][MAX_CAR_ROUTE];	// 車の位置
		int nNumPos[MAX_FILE_DATA];						// 位置の数
		int nNum;										// 総数
		bool bSuccess;									// 成功状況
	};

	CFile();					// コンストラクタ
	~CFile();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理

	HRESULT Save(const TYPE type);	// セーブ処理
	HRESULT Load(const TYPE type);	// ロード処理

	void SetRankingInfo(int* pRank);		// ランキングの設定処理
	SRankingInfo GetRankingInfo(void);		// ランキングの取得処理

	D3DXVECTOR3* GetCarRoute(const int nType);		// 車の経路の取得処理
	int GetCarRouteNum(void) const;					// 車の経路の総数取得処理
	int GetCarRouteNumPos(const int nType) const;	// 車の経路の位置の総数の取得処理

	void SetMap(void);				// マップの設定処理

private:		// 自分のみアクセスできる

	// メンバ関数(セーブ関係)
	HRESULT SaveRanking(void);		// ランキングのセーブ処理
	HRESULT SaveObstacle(void);		// 障害物のセーブ処理

	// メンバ関数(ロード関係)
	HRESULT LoadRanking(void);		// ランキングのロード処理
	HRESULT LoadObstacle(void);		// 障害物のロード処理
	HRESULT LoadCarRoute(void);		// 車の経路のロード処理

	// メンバ変数
	SRankingInfo m_RankingInfo;		// ランキングの情報
	SObstacleInfo m_ObstacleInfo;	// 障害物の情報
	SCarRouteInfo m_CarRouteInfo;	// 車のルートの情報

	// 静的メンバ変数
	static const char* c_apBooleanDisp[2];			// bool型の表示
};

#endif