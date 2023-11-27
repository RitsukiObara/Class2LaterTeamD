//============================================
//
// �L�w�b�_�[[Cat.h]
// Author�F��{�ėB
//
//============================================
#ifndef _CAT_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _CAT_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "player.h"

//--------------------------------------------
// �N���X(�v���C���[�N���X)
//--------------------------------------------
class CCat : public CPlayer
{
public:			// �N�ł��A�N�Z�X�ł���

	//************************************************************
	//	�񋓌^��`(���[�V�����̎��)
	//************************************************************
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@
		MOTIONTYPE_MOVE,			// �ړ�
		MOTIONTYPE_JUMP,			// �W�����v
		MOTIONTYPE_MAX				// ���̗񋓌^�̑���
	};

	enum ATTACKSTATE
	{
		ATTACKSTATE_MOVE = 0,		// �ړ�
		ATTACKSTATE_STANDBY,		// �X�^���o�C
		ATTACKSTATE_ATTACK,			// �U����
		ATTACKSTATE_MAX				// ���̗񋓌^�̑���
	};

	CCat();				// �R���X�g���N�^
	~CCat();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);						// �q�b�g����
	void Smash(const float fAngle);		// ������я��
	void Stun(void);					// �C����
	void MotionManager(void);			// ���[�V�����}�l�[�W���[

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCat* Get(void);					// �擾����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Attack();
	void AttackStateManager();
	void DebugMessage();

	// �����o�ϐ�
	D3DXVECTOR3 m_AttackPos;		// �U���̈ʒu
	D3DXVECTOR3 m_posDest;			// �ړI�̈ʒu
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
	int m_nShadowIdx;				// �e�̃C���f�b�N�X

	ATTACKSTATE m_AttackState;		// �U���̏��
	int m_nAtkStateCount;			// �U���̏�Ԃ̃J�E���g

	// �ÓI�����o�ϐ�
	static CCat* m_pPlayer;		// �v���C���[�̃|�C���^
};

#endif