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
#include "character.h"
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����

//--------------------------------------------
// �N���X(�v���C���[�N���X)
//--------------------------------------------
class CCat : public CCharacter
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

	void Hit(void);			// �q�b�g����
	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W

	CMotion* GetMotion(void) const;				// ���[�V�����̏��̎擾����

	// �ÓI�����o�֐�
	static CCat* Get(void);					// �擾����
	static CCat* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void MoveAttackPos();
	void Attack();
	void AttackStateManager();
	void CollisionMagicWall();
	void DebugMessage();

	// �����o�ϐ�
	CMotion* m_pMotion;				// ���[�V�����̏��

	D3DXVECTOR3 m_AttackPos;		// �U���̈ʒu
	D3DXVECTOR3 m_posDest;			// �ړI�̈ʒu
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
	int m_nShadowIdx;				// �e�̃C���f�b�N�X

	ATTACKSTATE m_AttackState;		// �U���̏��
	int m_nAtkStateCount;			// �U���̏�Ԃ̃J�E���g

	// �ÓI�����o�ϐ�
	static CCat* m_pPlayer;		// �v���C���[�̃|�C���^
};

#endif