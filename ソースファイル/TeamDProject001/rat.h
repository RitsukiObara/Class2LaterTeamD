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
#include "player.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CRatState;			// �l�Y�~�̏��
class CRatGhost;			// �H��l�Y�~
class CRessrectionFan;		// �~�͈̔�

//--------------------------------------------
// �N���X(�l�Y�~�N���X)
//--------------------------------------------
class CRat : public CPlayer
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

	void Hit(void);					// �q�b�g����
	void Smash(const float fAngle);	// ������я��
	void Stun(void);				// �C����
	void MotionManager(void);		// ���[�V�����̊Ǘ�

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);	// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	int GetRatIdx(void) const;				// �l�Y�~�̔ԍ��̎擾����
	CRatState* GetState(void);				// �l�Y�~�̏�Ԃ̎擾����
	CRatGhost* GetRatGhost(void);			// �H��l�Y�~�̎擾����
	void DeleteRatGhost(void);				// �H��l�Y�~�̏�������
	CRessrectionFan* GetRessrectionFan(void);			// �~�͈̔͂̎擾����
	void DeleteRessrectionFan(void);					// �~�͈̔͂̏�������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Jump(void);				// �W�����v����
	void Attack(void);				// �U������
	void Elevation(void);			// �N���n�ʂ̓����蔻��
	void ResurrectionCollision(void);		// �����Ԃ�̓����蔻��

	// �����o�ϐ�
	CRatState* m_pRatState;		// �l�Y�~�̏�Ԃ̏��
	CRatGhost* m_pRatGhost;		// �H��l�Y�~�̏��
	CRessrectionFan* m_pRessrectionFan;		// �~�͈̔͂̏��
	int m_nRatIdx;				// �l�Y�~�̔ԍ�
	bool m_bJump;				// �W�����v��

	// �ÓI�����o�֐�
	static int m_nNumAll;		// �l�Y�~�̑���
	static int m_nResurrectionCounter;		// �����Ԃ�܂ł̃J�E���^�[

};

#endif