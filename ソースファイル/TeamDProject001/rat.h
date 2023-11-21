//===================================
//
// ���b�g�w�b�_�[[rat.h]
// Author ��������
//
//===================================
#ifndef _RAT_H_
#define _RAT_H_

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "character.h"
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����
class CPlayerID;			// �v���C���[��ID

//--------------------------------------------
// �N���X(�l�Y�~�N���X)
//--------------------------------------------
class CRat : public CCharacter
{
public:			// �N�ł��A�N�Z�X�ł���

	CRat();			// �R���X�g���N�^
	~CRat();			// �f�X�g���N�^

	//************************************************************
	//	�񋓌^��`(���[�V�����̎��)
	//************************************************************
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@
		MOTIONTYPE_MOVE,			// �ړ�
		MOTIONTYPE_ATTACK,			// �U��
		MOTIONTYPE_JUMP,			// �W�����v
		MOTIONTYPE_DEATH,			// ���S
		MOTIONTYPE_RESURRECTION,	// �h��
		MOTIONTYPE_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// ���ł��Ȃ����
		STATE_WAIT,			// �ҋ@���
		STATE_RUN,			// ���s���
		STATE_ATTACK,		// �U�����
		STATE_INVINCIBLE,	// ���G���
		STATE_DAMAGE,		// �_���[�W���
		STATE_SMASH,		// ������я��
		STATE_DEATH,		// ���S���
		STATE_MAX
	};

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	bool Hit(void);					// �q�b�g����
	void Smash(const float fAngle);	// ������я��

	void SetData(const D3DXVECTOR3& pos, const int nID);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetMove(const D3DXVECTOR3& move);	// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;		// �ړ��ʂ̎擾����
	void SetSpeed(const float fSpeed);		// ���x�̐ݒ菈��
	float GetSpeed(void) const;				// ���x�̎擾����
	int GetRatIdx(void) const;				// �l�Y�~�̔ԍ��̎擾����
	void SetState(STATE state);				// �l�Y�~�̏�Ԃ̐ݒ菈��
	STATE GetState(void);					// �l�Y�~�̏�Ԃ̎擾����
	bool IsMove(void);					

	// �ÓI�����o�֐�
	static CRat* Create(const D3DXVECTOR3& pos, const int nID);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);				// �ړ�����
	void Jump(void);				// �W�����v����
	void Attack(void);				// �U������
	void UpdateState(void);			// ��ԍX�V����
	void MotionManager(void);		// ���[�V�����̊Ǘ�
	void Elevation(void);			// �N���n�ʂ̓����蔻��
	void ObstacleCollision(void);	// ��Q���Ƃ̓����蔻��

	// �����o�ϐ�
	CMotion* m_pMotion;			// ���[�V�����̏��
	CPlayerID* m_pPlayerID;		// �v���C���[��ID
	D3DXVECTOR3 m_move;			// �ړ���
	STATE m_State;				// �l�Y�~�̏��
	int m_nRatIdx;				// �l�Y�~�̔ԍ�
	int m_nLife;				// ����
	int m_nStateCount;			// ��ԃJ�E���g
	float m_fSpeed;				// ���x
	bool m_bJump;				// �W�����v������
	bool m_bAttack;				// �U��������
	bool m_bMove;				// �ړ����Ă��邩
	MOTIONTYPE MotionType;		// ���[�V�����̏��

	// �ÓI�����o�֐�
	static int m_nNumAll;		// �l�Y�~�̑���

};

#endif