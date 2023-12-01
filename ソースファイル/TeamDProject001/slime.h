//===================================
//
// �X���C���w�b�_�[[slime.h]
// Author ��������
//
//===================================
#ifndef _SLIME_H_
#define _SLIME_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�X���C��)
//-----------------------------------
class CSlime : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CSlime();				// �R���X�g���N�^
	~CSlime();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);		// �q�b�g����
	void Action(void) override;										// �M�~�b�N�N������

private:		// ���������A�N�Z�X�ł���
};

#endif