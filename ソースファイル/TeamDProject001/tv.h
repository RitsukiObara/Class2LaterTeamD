//===================================
//
// �e���r�w�b�_�[[cup.h]
// Author �x�씋��
//
//===================================
#ifndef _TV_H_
#define _TV_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

class CConsent;
class CObject3D;
class CBlock;
//-----------------------------------
// �N���X��`(�R�b�v)
//-----------------------------------
class CTv : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CTv();				// �R���X�g���N�^
	~CTv();				// �f�X�g���N�^

							// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,	// �A�C�e���擾�\���
		STATE_COOLDOWN,	// �N�[���^�C�����
		STATE_TRAP,		// �l�Y�~�߂��ʂ������ꍇ
		STATE_BOMB,		// ���e��ʂ������ꍇ
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);		// �q�b�g����
	bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type);
	bool HitRemocon(void);
	void Action(void) override;		// �A�N�V����
	void PowerAction(void);			// �d������
	void VisionChange(void);		// �e���r��ʐ؂�ւ�
private:		// ���������A�N�Z�X�ł���
	void StateManager(void);		// ��ԊǗ��}�l�[�W���[

	bool m_bPower;
	int m_nCoolTime;			// �N�[���^�C��
	int m_nChangeVision;		// ��ʕω�����
	STATE m_State;				// �e���r�̏��
	CObject3D *m_pVision;		// �|���S�����
	D3DXVECTOR3 m_VisionSize;	// �|���S���T�C�Y
	CBlock* m_pRemocn;			// �����R���̃��f�����
};

#endif