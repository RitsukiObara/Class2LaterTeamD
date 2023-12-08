//===================================
//
// �{�w�b�_�[[book.h]
// Author ��������
//
//===================================
#ifndef _BOOK_H_
#define _BOOK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_BOOK	(3)		// �{�̍ő吔

//-----------------------------------
// �O���錾
//-----------------------------------
class CModel;			// ���f��

//-----------------------------------
// �N���X��`(���[�h)
//-----------------------------------
class CBook : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_STOP = 0,		// ��~���
		STATE_COLLAPSE,		// �|����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CBook();				// �R���X�g���N�^
	~CBook();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type) override;		// �q�b�g����
	bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type) override;
	void Action(void) override;

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void StateManager(void);		// ��ԃ}�l�[�W���[

	// �����o�ϐ�
	CModel* m_apBook[MAX_BOOK];		// ��ɍڂ��Ă���{�̏��
	D3DXVECTOR3 m_move;				// �ړ���
	STATE m_state;					// ���
};

#endif