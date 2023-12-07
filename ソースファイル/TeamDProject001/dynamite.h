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
// �O���錾
//-----------------------------------


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

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��
	bool Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;		// �q�b�g����
	void ChageScale(void);	// ���f���T�C�Y�ύX����
	void Explosion(void);	// ��������
private:		// ���������A�N�Z�X�ł���
	
	// �����o�ϐ�
	STATE m_state;				// ���
	D3DXVECTOR3 m_Scale;		// �g�嗦
	D3DXVECTOR3 m_pos;			// �ʒu
	bool m_bCatch;				// �����Ă��邩�ǂ���
	int m_nExplosion;			// �����^�C�~���O
	int m_nDelTyming;			// �����̔��莞��
};

#endif