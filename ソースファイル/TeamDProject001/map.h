#ifndef _MAP_H_	//このマクロが定義されていなければ
#define _MAP_H_	//二重インクルード防止マクロ

#include "main.h"
#include "model.h"

class CMap :public CObject
{
public:
	CMap();
	~CMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMap* Create(void);
private:

	static LPDIRECT3DTEXTURE9 m_pTexturePlayer;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPlayer;	//頂点バッファへのポインタ

	D3DXVECTOR3 m_pos;
	int m_partsNum;

	CModel* m_Model[4];
};
#endif // !_MAP_H_