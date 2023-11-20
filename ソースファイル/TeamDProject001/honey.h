//===================================
//
// �I���w�b�_�[[honey.h]
// Author ��������
//
//===================================
#ifndef _HONEY_H_
#define _HONEY_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�I��)
//-----------------------------------
class CHoney : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum State
	{
		STATE_HONEYBOTTLE = 0,	// �{�g��
		STATE_HONEY,			// �t��
		STATE_MAX				// ���̗񋓌^�̑���
	};

	CHoney();				// �R���X�g���N�^
	~CHoney();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���
	void Break(void);
	void StateManager(void);

	State m_State;
};

#endif