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

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth);		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Cycle(void);			// ��]����
	void Gravity(void);			// �d�͏���
	void Elevation(void);		// �N���n�ʂ̓����蔻��

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	STATE m_state;				// ���
};
#endif