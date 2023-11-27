//===================================
//
// ��������̎ԃw�b�_�[[toycar.h]
// Author ��������
//
//===================================
#ifndef _TOYCAR_H_
#define _TOYCAR_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CCarGear;			// �Ԃ̎���

//-----------------------------------
// �N���X��`(��������̎�)
//-----------------------------------
class CToyCar : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_DRIVE = 0,	// �h���C�u���
		STATE_CURVE,		// �J�[�u���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CToyCar();				// �R���X�g���N�^
	~CToyCar();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type);		// �q�b�g����
	void Action(void) override;										// �M�~�b�N�N������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Drive(void);			// ���s����
	void Curve(void);			// �J�[�r���O����
	void Check(void);			// �ʒu�̊m�F����
	void RotCalc(void);			// �����̐ݒ菈��

	// �����o�ϐ�
	D3DXVECTOR3 m_pPosInit;		// �����ʒu
	CCarGear* m_pGear;			// ���Ԃ̏��
	D3DXVECTOR3* m_pPosDest;	// �ړI�̈ʒu
	STATE m_state;				// ���
	int m_nPosDestNum;			// �ړI�̈ʒu�̑���
	int m_nPosDestIdx;			// �ړI�̈ʒu�̔ԍ�
	float m_fRotDest;			// �ړI�̌���
	bool m_bRight;				// �E������
};

#endif