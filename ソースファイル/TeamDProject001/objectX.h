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
#define INIT_CAT		(CXFile::TYPE_CAT_BODY)							// 猫モデルの開始位置

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
		TYPE_HONEY,				// 蜂蜜
		TYPE_SLIME,				// スライム
		TYPE_HAIRBALL,			// 毬
		TYPE_HONEYBOTTLE,		// 蜂蜜のボトル
		TYPE_TISSUEBOX,			// ティッシュ箱
		TYPE_CARDBOARD,			// 段ボール
		TYPE_PENHOLDER,			// ペン立て
		TYPE_REMOCON,			// リモコン
		TYPE_FLOWERVASE,		// 花瓶
		TYPE_FLOWERFRAC,		// 花瓶の破片

		//マップモデル
		TYPE_KITCHEN,			//キッチン
		TYPE_TAP,				//蛇口部分
		TYPE_IH_OFF,			//IH（off）
		TYPE_IH_ON,				//IH（on）

		// 猫モデル
		TYPE_CAT_BODY,			// 体
		TYPE_CAT_HEAD,			// 頭
		TYPE_CAT_LHAND,			// 左手
		TYPE_CAT_RHAND,			// 右手
		TYPE_CAT_LLEG,			// 左足
		TYPE_CAT_RLEG,			// 右足

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