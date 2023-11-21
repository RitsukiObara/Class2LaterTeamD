//===================================
//
// �l�Y�~�̏�ԃw�b�_�[[rat_state.h]
// Author ��������
//
//===================================
#ifndef _RAT_STATE_H_
#define _RAT_STATE_H_

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CRat;			// �l�Y�~

//--------------------------------------------
// �N���X(�l�Y�~�̏�ԃN���X)
//--------------------------------------------
class CRatState
{
public:			// �N�ł��A�N�Z�X�ł���

	CRatState();	// �R���X�g���N�^
	~CRatState();	// �f�X�g���N�^

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_WAIT = 0,			// �ҋ@���
		STATE_RUN,				// ���s���
		STATE_ATTACK,			// �U�����
		STATE_INVINCIBLE,		// ���G���
		STATE_DAMAGE,			// �_���[�W���
		STATE_SMASH,			// ������я��
		STATE_STUN,				// �C����
		STATE_DEATH,			// ���S���
		STATE_MAX				// ���̗񋓌^�̑���
	};

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(CRat& pRat);	// �X�V����

	// �Z�b�g�E�Q�b�g�֌W
	void SetState(const STATE state);		// ��Ԃ̐ݒ菈��
	STATE GetState(void);					// ��Ԃ̎擾����

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	STATE m_State;				// �l�Y�~�̏��
	int m_nStateCount;			// ��ԃJ�E���g
};

#endif