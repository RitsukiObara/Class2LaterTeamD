//===================================
//
// �R�b�v�w�b�_�[[cup.h]
// Author ��{�ėB
//
//===================================
#ifndef _CUP_H_
#define _CUP_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

class CConsent;
class CObject3D;
//-----------------------------------
// �N���X��`(�R�b�v)
//-----------------------------------
class CCup : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CCup();				// �R���X�g���N�^
	~CCup();				// �f�X�g���N�^

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_FALSE = 0,	// ��~���
		STATE_FALLWAIT,		// �N���܂ŗ������ɏ�������
		STATE_TRUE,			// �N�����
		STATE_MAX			// ���̗񋓌^�̑���
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
	void Action(void) override;

	void NULLConsent(void) { m_pConsent = NULL; }

private:		// ���������A�N�Z�X�ł���
	void StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);

	int m_ThunderCounter;
	D3DXVECTOR3 m_move;
	STATE m_State;
	CObject3D *m_pWater;
	D3DXVECTOR3 m_WaterSize;
	CConsent *m_pConsent;
};

#endif