//===================================
//
// �J�[�e���w�b�_�[[curtain.h]
// Author ��������
//
//===================================
#ifndef _CURTAIN_H_
#define _CURTAIN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_SWITCH		(3)		// �X�C�b�`�̍ő吔

//-----------------------------------
// �O���錾
//-----------------------------------
class CSwitch;			// �X�C�b�`

//-----------------------------------
// �N���X��`(�J�[�e��)
//-----------------------------------
class CCurtain : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_CLOSE = 0,	// ������
		STATE_OPEN,			// �J���Ă���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CCurtain();				// �R���X�g���N�^
	~CCurtain();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	//bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;	// �����蔻�菈��
	//bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type) override;			// �~�̃q�b�g����
	//void Action(void) override;										// �M�~�b�N�N������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void StateManager(void);	// ��ԃ}�l�[�W���[

	// �����o�ϐ�
	CSwitch* m_apSwitch[MAX_SWITCH];	// �X�C�b�`�̏��
	STATE m_state;						// ���
};

#endif