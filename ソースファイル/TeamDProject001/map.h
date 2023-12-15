#ifndef _MAP_H_	//���̃}�N������`����Ă��Ȃ����
#define _MAP_H_	//��d�C���N���[�h�h�~�}�N��

#include "main.h"
#include "ground.h"
#include "wall.h"

#define WALL_NUM (12)

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

	static CWall* GetWall(void);
private:

	D3DXVECTOR3 m_pos;
	int m_partsNum;

	CGround* m_Ground;
	static CWall* m_Wall[WALL_NUM];
	static CModel* m_Model[2];
};
#endif // !_MAP_H_