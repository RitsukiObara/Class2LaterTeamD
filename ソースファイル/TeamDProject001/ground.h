#ifndef _GROUND_H_	//���̃}�N������`����Ă��Ȃ����
#define _GROUND_H_	//��d�C���N���[�h�h�~�}�N��

#include "main.h"
#include "Object3D.h"

class CGround :public CObject3D
{
public:
	CGround();
	~CGround();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGround* Create(void);
private:

	static LPDIRECT3DTEXTURE9 m_pTexturePlayer;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPlayer;	//���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;

};
#endif // !_GROUND_H_