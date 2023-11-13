#ifndef _MAP_H_	//���̃}�N������`����Ă��Ȃ����
#define _MAP_H_	//��d�C���N���[�h�h�~�}�N��

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
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPlayer;	//���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;
	int m_partsNum;

	CModel* m_Model[4];
};
#endif // !_MAP_H_