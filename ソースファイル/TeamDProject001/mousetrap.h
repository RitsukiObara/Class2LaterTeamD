//===================================
//
// �l�Y�~�߂�w�b�_�[[mousetrap.h]
// Author ��������
//
//===================================
#ifndef _MOUSETRAP_H_
#define _MOUSETRAP_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CTrapIron;		// �l�Y�~�߂�̓S����
class CDangerMark;		// �댯�}�[�N

//-----------------------------------
// �N���X��`(�l�Y�~�߂�)
//-----------------------------------
class CMouseTrap : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_MOVE,			// �ړ����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CMouseTrap();			// �R���X�g���N�^
	~CMouseTrap();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void IronPosSet(void);		// �S�����̈ʒu�̐ݒ菈��

	// �����o�ϐ�
	CTrapIron* m_pIron;			// �S����
	CDangerMark* m_pMark;		// �댯�}�[�N�̏��
	STATE m_state;				// ���
};

#endif