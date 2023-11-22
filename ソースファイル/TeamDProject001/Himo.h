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

#define MAX_TARAI (5)

class CTarai;
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

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����
	void Action(void) override;										// �M�~�b�N�N������

	static void NULLTarai(int Idx) { m_apTarai[Idx] = NULL; }

private:		// ���������A�N�Z�X�ł���
	void SetTarai(void);

	static CTarai *m_apTarai[MAX_TARAI];
	int m_nTaraiCount;
	bool m_bAction;
	float m_fDownPosY;
	float m_fUpPosY;
};

#endif