#ifndef _GROUND_H_	//このマクロが定義されていなければ
#define _GROUND_H_	//二重インクルード防止マクロ

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

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;

};
#endif // !_GROUND_H_