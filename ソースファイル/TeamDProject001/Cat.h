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
class CCatAct;			// �v���C���[�̍s��
class CAbility;				// �\��
class CScrewUI;				// �l�WUI
class CCombo;				// �R���{
class CBlock;				// �u���b�N
class CLifeUI;				// �̗�UI
class CPushTiming;			// �����^�C�~���O

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
	void SetMove(const D3DXVECTOR3& move);		// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʂ̎擾����
	void SetRotDest(const D3DXVECTOR3& rot);	// �ڕW�̌����̐ݒ菈��
	D3DXVECTOR3 GetRotDest(void) const;			// �ڕW�̌����̎擾����
	void SetSpeed(float fSpeed);				// ���x�̐ݒ菈��
	float GetSpeed(void) const;					// ���x�̎擾����
	void SetAlpha(const float fAlpha);			// �����x�̐ݒ菈��
	void SwapAlpha(void);						// �����x�̓���ւ�����
	float GetAlpha(void) const;					// �����x�̎擾����
	void SetEnableMove(bool bMove);				// �ړ��󋵂̐ݒ菈��
	bool IsMove(void) const;					// �ړ��󋵂̎擾����

	CMotion* GetMotion(void) const;				// ���[�V�����̏��̎擾����
	CCatAct* GetAction(void) const;			// �A�N�V�����̏��̎擾����

	// �ÓI�����o�֐�
	static CCat* Get(void);					// �擾����
	static CCat* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void CollisionMagicWall(void);	// �ړ���������

	void StartProcess(void);		// �X�^�[�g��Ԃ̏���
	void GoalProcess(void);			// �S�[����Ԃ̏���
	void LeaveProcess(void);		// �ޏ��Ԃ̏���
	void FinishProcess(void);		// �I����Ԃ̏���

	// �����o�ϐ�
	CMotion* m_pMotion;				// ���[�V�����̏��
	CCatAct* m_pAction;			// �v���C���[�̍s���̏��

	D3DXVECTOR3 m_posDest;			// �ړI�̈ʒu
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
	int m_nShadowIdx;				// �e�̃C���f�b�N�X
	int m_nStartCount;				// �X�^�[�g�J�E���g
	int m_nGoalCount;				// �S�[�����̃J�E���g
	float m_fSpeed;					// ���x
	float m_fAlpha;					// �����x
	bool m_bMove;					// �ړ���

	// �ÓI�����o�ϐ�
	static CCat* m_pPlayer;		// �v���C���[�̃|�C���^
};

#endif