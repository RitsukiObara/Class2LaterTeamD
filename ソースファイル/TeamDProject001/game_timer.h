//============================================
//
// �Q�[���̎��ԃw�b�_�[[game_time.h]
// Author�F��������
//
//============================================
#ifndef _GAME_TIME_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _GAME_TIME_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "time.h"

//--------------------------------------------
// �N���X��`(�Q�[���^�C��)
//--------------------------------------------
class CGameTime : public CTime
{
public:				// �N�ł��A�N�Z�X�ł���

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void TimeStart(void);	// �^�C���̊J�n����

	// �ÓI�����o�ϐ�
	static CGameTime* Get(void);			// �擾����
	static CGameTime* Create(void);			// ��������

private:			// ���������A�N�Z�X�ł���

	CGameTime();			// �R���X�g���N�^
	~CGameTime();			// �f�X�g���N�^

	// �����o�֐�
	void Basic(void);			// �ʏ�̍X�V����
	void PauseProcess(void);	// �|�[�Y���̏���
	void Calculate(void);		// �v�Z����

	// �����o�ϐ�
	DWORD m_StartTime;		// �J�n����
	DWORD m_PauseTime;		// �|�[�Y���̎���
	bool m_bGoal;			// �S�[����

	// �ÓI�����o�ϐ�
	static CGameTime* m_pGameTimer;		// �Q�[���^�C�}�[�̏��
};

#endif