//===================================
//
// �y�b�g�{�g���w�b�_�[[petbottle.h]
// Author ���˕�
//
//===================================
#ifndef _PETBOTTLE_H_
#define _PETBOTTLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�y�b�g�{�g��)
//-----------------------------------
class CPetbottle : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_STAND = 0,	// �ʏ���
		STATE_COLLAPSE,		// �|����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CPetbottle();			// �R���X�g���N�^
	~CPetbottle();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;	// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Cycle(void);								// ��]����
	void Gravity(void);								// �d�͏���
	void Elevation(void);							// �N���n�ʂ̓����蔻��
	void Collapse(const D3DXVECTOR3& posPlayer);	// �|��鏈��
	bool MagicWall(void);							// ���@�̕Ǐ���

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	STATE m_state;				// ���
};
#endif