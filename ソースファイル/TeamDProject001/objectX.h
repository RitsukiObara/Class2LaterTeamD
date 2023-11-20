//============================================================
//
// Xファイルヘッダー [xfile.h]
// Author：小原立暉
//
//============================================================
#ifndef _XFILE_H_	// このマクロ定義がされていない場合
#define _XFILE_H_	// 二重インクルード防止のマクロを定義する

//------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------
#define INIT_VTX_MIN	(D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))		// モデルの最小の頂点座標の初期値
#define INIT_VTX_MAX	(D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))		// モデルの最大の頂点座標の初期値
#define INIT_SIZE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))					// モデルサイズの初期値
#define INIT_RAT		(CXFile::TYPE_RAT_BODY)							// ネズミモデルの開始位置
#define INIT_CAT		(CXFile::TYPE_CAT_BODY)							// 猫モデルの開始位置
#define INIT_BLOCK		(CXFile::TYPE_CARDBOARD)						// ブロックモデルの開始位置
#define INIT_OBSTACLE	(CXFile::TYPE_HONEYBOTTLE)						// 障害物モデルの開始位置

//------------------------------------------------------------
// クラス定義(Xファイル)
//------------------------------------------------------------
class CXFile
{
public:			// 誰でもアクセスできる

	//************************************************************
	//	列挙型定義 (TYPE)
	//************************************************************
	enum TYPE
	{
		// 通常モデル
		TYPE_RIPPLE = 0,		// 波紋
		TYPE_KARIPLAYER,		// 仮プレイヤー
		TYPE_WOODBLOCK,			// 木箱
		TYPE_WEAPONCAGE,		// 武器小屋
		TYPE_FLOWERFRAC,		// 花瓶の破片
		TYPE_PLASTICFRAC,		// プラスチックケース破片
		TYPE_HONEY,				// 蜂蜜
		TYPE_TOYCARSCREW,		// おもちゃの車(ネジ)
		TYPE_TITLEWALL,			// タイトルの壁
		TYPE_ROOMBA_SUB,		// ルンバのプロペラ
		TYPE_TARAI,				// たらい

		// ブロックモデル
		TYPE_CARDBOARD,			// 段ボール
		TYPE_TISSUEBOX,			// ティッシュ箱
		TYPE_PENHOLDER,			// ペン立て
		TYPE_REMOCON,			// リモコン
		TYPE_BEAR,				// ブロック
		TYPE_CLOCK,				// 時計
		TYPE_RUBBISH,			// チリ紙
		TYPE_MILKPACK,			// 牛乳パック
		TYPE_CUP,				// コップ
		TYPE_OBAPHONE,			// オバフォン
		TYPE_WII,				// Wii
		TYPE_DS,				// DS
		TYPE_HEADPHONE,			// ヘッドフォン
		TYPE_PEN,				// ペン
		TYPE_ACADAPTER,			// ACアダプター
		TYPE_BUILDINGBLOCK,		// 積み木
		TYPE_GLASSES,			// 眼鏡ケース
		TYPE_PENCIL,			// 鉛筆
		TYPE_PICTUREFRAME,		// 写真立て

		// 障害物モデル
		TYPE_HONEYBOTTLE,		// 蜂蜜のボトル
		TYPE_SLIME,				// スライム
		TYPE_HAIRBALL,			// 毬
		TYPE_FLOWERVASE,		// 花瓶
		TYPE_PLASTICCASE,		// プラスチックケース
		TYPE_PETBOTTLE,			// ペットボトル
		TYPE_TOYCARBODY,		// おもちゃの車(本体)
		TYPE_ROOMBA_MAIN,		// ルンバの本体
		TYPE_HIMO,				// ひも

		//マップモデル
		TYPE_KITCHEN,			//キッチン
		TYPE_REIZOUKO,			//冷蔵庫
		TYPE_TABLE,				//テーブル

		//ネズミモデル
		TYPE_RAT_BODY,			// 体
		TYPE_RAT_HEAD,			// 頭
		TYPE_RAT_LHAND,			// 左手
		TYPE_RAT_RHAND,			// 右手
		TYPE_RAT_LLEG,			// 左足
		TYPE_RAT_RLEG,			// 右足

		//猫モデル
		TYPE_CAT_BODY,			//体
		TYPE_CAT_HEAD,			//頭
		TYPE_CAT_LARM,			//左腕
		TYPE_CAT_LHAND,			//左手
		TYPE_CAT_RAEM,			//右腕
		TYPE_CAT_RHAND,			//右手
		TYPE_CAT_LFOOT,			//左腿
		TYPE_CAT_LLEG,			//左足
		TYPE_CAT_RFOOT,			//右腿
		TYPE_CAT_RLEG,			//右足

		// ネズミモデル
		TYPE_RAT_GHOST,			// 幽霊モデル

		// エディットモデル
		TYPE_MAX,				// 全モデルの総数
	};

	//************************************************************
	//	構造体定義 (SXFile)
	//************************************************************
	struct SXFile
	{
		LPD3DXMESH	 pMesh;						// メッシュ (頂点情報) へのポインタ
		LPD3DXBUFFER pBuffMat;					// マテリアルへのポインタ
		DWORD		 dwNumMat;					// マテリアルの数
		D3DXVECTOR3	 vtxMin;					// 最小の頂点座標
		D3DXVECTOR3	 vtxMax;					// 最大の頂点座標
		D3DXVECTOR3	 collsize;					// 当たり判定のサイズ
		float		 fRadius;					// 半径
		int			 m_nTexIdx[MAX_MATERIAL];	// テクスチャのインデックス
	};

	CXFile();			// コンストラクタ
	~CXFile();			// デストラクタ

	// メンバ関数
	static HRESULT Init(void);		// Xファイルの初期化処理
	static void Uninit(void);		// Xファイルの終了処理

	// セット・ゲット関数
	static SXFile GetXFile(TYPE type);	// Xファイルの取得処理

private:

	// メンバ関数
	static HRESULT LoadXFile(void);		// xファイルの読み込み
	static void SetCollision(void);		// 当たり判定の作成
	static HRESULT LoadTexture(void);	// テクスチャの読み込み

	// 静的メンバ変数
	static const char *c_apModelData[CXFile::TYPE_MAX];			// モデルの名前
	static SXFile m_apModel[CXFile::TYPE_MAX];					// モデルの情報
};

#endif