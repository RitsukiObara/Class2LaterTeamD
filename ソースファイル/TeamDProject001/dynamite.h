//===================================
//
// ���e�w�b�_�[[dynamite.h]
// Author �x�씋��
//
//===================================
#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(���e)
//-----------------------------------
class CDynamite : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

				// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_MINI,			// �k�����
		STATE_BIG,			// �g����
		STATE_EXPLOSION,	// �������
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CDynamite();			// �R���X�g���N�^
	~CDynamite();			// �f�X�g���N�^

							// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ���̐ݒ菈��
	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;				// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;					// �q�b�g����

private:		// ���������A�N�Z�X�ł���
	
	// �����o�֐�
	void ChageScale(void);	// ���f���T�C�Y�ύX����
	void Explosion(void);	// ��������

	// �����o�ϐ�
	STATE m_state;				// ���
	int m_nExplosion;			// �����^�C�~���O
	int m_nDelTyming;			// �����̔��莞��
};

#endif