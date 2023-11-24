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

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����
class CPlayerID;			// �v���C���[��ID
class CRatState;			// �l�Y�~�̏��
class CStun;				// �C��
class CRatGhost;			// �H��l�Y�~
class CRessrectionFan;		// �~�͈̔�

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

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	bool Hit(void);					// �q�b�g����
	void Smash(const float fAngle);	// ������я��
	void Stun(void);				// �C����

	void SetData(const D3DXVECTOR3& pos, const int nID);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetMove(const D3DXVECTOR3& move);	// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;		// �ړ��ʂ̎擾����
	void SetSpeed(const float fSpeed);		// ���x�̐ݒ菈��
	float GetSpeed(void) const;				// ���x�̎擾����
	int GetRatIdx(void) const;				// �l�Y�~�̔ԍ��̎擾����
	bool IsMove(void);						// �ړ��󋵂̎擾����
	CRatState* GetState(void);				// �l�Y�~�̏�Ԃ̎擾����
	CStun* GetStun(void);					// �C�≉�o�̎擾����
	void DeleteStun(void);					// �C�≉�o�̏�������
	CRatGhost* GetRatGhost(void);			// �H��l�Y�~�̎擾����
	void DeleteRatGhost(void);				// �H��l�Y�~�̏�������
	CRessrectionFan* GetRessrectionFan(void);			// �~�͈̔͂̎擾����
	void DeleteRessrectionFan(void);					// �~�͈̔͂̏�������

	// �ÓI�����o�֐�
	static CRat* Create(const D3DXVECTOR3& pos, const int nID);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);				// �ړ�����
	void Jump(void);				// �W�����v����
	void Attack(void);				// �U������
	void MotionManager(void);		// ���[�V�����̊Ǘ�
	void Elevation(void);			// �N���n�ʂ̓����蔻��
	void ObstacleCollision(void);	// ��Q���Ƃ̓����蔻��
	void ResurrectionCollision(void);		// �����Ԃ�̓����蔻��

	// �����o�ϐ�
	CMotion* m_pMotion;			// ���[�V�����̏��
	CPlayerID* m_pPlayerID;		// �v���C���[��ID
	CRatState* m_pRatState;		// �l�Y�~�̏�Ԃ̏��
	CStun* m_pStun;				// �C��̏��
	CRatGhost* m_pRatGhost;		// �H��l�Y�~�̏��
	CRessrectionFan* m_pRessrectionFan;		// �~�͈̔͂̏��
	D3DXVECTOR3 m_move;			// �ړ���
	int m_nRatIdx;				// �l�Y�~�̔ԍ�
	int m_nLife;				// ����
	float m_fSpeed;				// ���x
	bool m_bJump;				// �W�����v������
	bool m_bAttack;				// �U��������
	bool m_bMove;				// �ړ����Ă��邩
	MOTIONTYPE MotionType;		// ���[�V�����̏��

	// �ÓI�����o�֐�
	static int m_nNumAll;		// �l�Y�~�̑���
	static int m_nResurrectionCounter;		// �����Ԃ�܂ł̃J�E���^�[

};

#endif