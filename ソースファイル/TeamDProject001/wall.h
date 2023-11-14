#ifndef _WALL_H_	//このマクロが定義されていなければ
#define _WALL_H_	//二重インクルード防止マクロ

#include "main.h"
#include "Object3D.h"

class CWall :public CObject3D
{
public:
	CWall();
	~CWall();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
private:

	static LPDIRECT3DTEXTURE9 m_pTexturePlayer;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPlayer;	//頂点バッファへのポインタ

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;

};
#endif // !_WALL_H_