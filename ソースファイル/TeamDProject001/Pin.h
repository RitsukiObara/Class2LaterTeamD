//===================================
//
// �s���w�b�_�[[Pin.h]
// Author ��{�ėB
//
//===================================
#ifndef _PIN_H_
#define _PIN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(���[�h)
//-----------------------------------
class CPin : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CPin();				// �R���X�g���N�^
	~CPin();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����
	void Action(void) override;

private:		// ���������A�N�Z�X�ł���
	D3DXVECTOR3 m_move;			//�ړ���
	bool m_bAction;				//�N�����Ă��邩�ǂ���
};

#endif