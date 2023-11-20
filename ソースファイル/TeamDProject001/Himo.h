//===================================
//
// �Ђ��w�b�_�[[Himo.h]
// Author ��{�ėB
//
//===================================
#ifndef _HIMO_H_
#define _HIMO_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

#define MAX_TARAI		(5)	// ���炢�̗����ő吔

class CModel;

//-----------------------------------
// �N���X��`(�Ђ�)
//-----------------------------------
class CHimo : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CHimo();				// �R���X�g���N�^
	~CHimo();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���
	void ActionDown(void);

	CModel *m_apSub[MAX_TARAI];
	bool m_bAction;
};

#endif