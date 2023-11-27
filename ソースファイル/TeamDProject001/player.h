//===================================
//
// �v���C���[�w�b�_�[[player.h]
// Author ��������
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "character.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����
class CPlayerID;			// �v���C���[��ID
class CStun;				// �C��

//--------------------------------------------
// �N���X(�v���C���[�N���X)
//--------------------------------------------
class CPlayer : public CCharacter
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_CAT = 0,		// �l�R
		TYPE_RAT,			// �l�Y�~
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CPlayer();				// �R���X�g���N�^
	CPlayer(CObject::TYPE type, PRIORITY priority = PRIORITY_PLAYER);				// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CPlayer();		// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	virtual void Hit(void) = 0;					// �q�b�g����
	virtual void Smash(const float fAngle);		// ������я��
	virtual void Stun(void) = 0;				// �C����
	virtual void MotionManager(void) = 0;		// ���[�V�����}�l�[�W���[

	virtual void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetMotion(CMotion* pMotion);			// ���[�V�����̐ݒ菈��
	CMotion* GetMotion(void) const;				// ���[�V�����̎擾����

	CPlayerID* GetPlayerID(void) const;			// �v���C���[ID�̏��̎擾����

	void SetStun(const D3DXVECTOR3& pos);		// �C�≉�o�̐ݒ菈��
	CStun* GetStun(void) const;					// �C�≉�o�̎擾����
	void DeleteStun(void);						// �C�≉�o�̏�������

	void SetMove(const D3DXVECTOR3& move);		// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʂ̎擾����

	void SetSizeColl(const D3DXVECTOR3& size);	// �����蔻��T�C�Y�̐ݒ菈��

	void SetType(const TYPE type);				// ��ނ̐ݒ菈��
	TYPE GetType(void) const;					// ��ނ̎擾����

	void SetLife(const int nLife);				// �����̐ݒ菈��
	int GetLife(void) const;					// �����̎擾����

	int GetPlayerIdx(void) const;				// �v���C���[��ID�̎擾����

	void SetSpeed(const float fSpeed);			// ���x�̐ݒ菈��
	float GetSpeed(void) const;					// ���x�̎擾����

	void SetEnableAttack(const bool bAttack);	// �U������̐ݒ菈��
	bool IsAttack(void) const;					// �U������̎擾����

	void SetEnableMove(const bool bMove);		// �ړ��󋵂̐ݒ菈��
	bool IsMove(void) const;					// �ړ��󋵂̎擾����

	// �ÓI�����o�֐�
	static CPlayer* Create(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// ��������

protected:		// �����Ɣh���N���X�������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);		// �ړ�����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void ObstacleCollision(void);	// ��Q���Ƃ̓����蔻��

	// �����o�ϐ�
	CMotion* m_pMotion;			// ���[�V�����̏��
	CPlayerID* m_pPlayerID;		// �v���C���[��ID
	CStun* m_pStun;				// �C��̏��
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_sizeColl;		// �����蔻��̃T�C�Y
	TYPE m_type;				// ���
	int m_nLife;				// ����
	int m_nPlayerIdx;			// �v���C���[�̃C���f�b�N�X
	float m_fSpeed;				// ���x
	bool m_bAttack;				// �U��������
	bool m_bMove;				// �ړ����Ă��邩
};

#endif