//============================================
//
// �Q�[���w�b�_�[[game.h]
// Author�F��������
//
//============================================
#ifndef _GAME_H_			//���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CPause;			// �|�[�Y
class CEdit;			// �G�f�B�b�g
class CPlayer;			// �v���C���[
class CGameFinish;		// �t�B�j�b�V��

//--------------------------------------------
// �N���X(�Q�[���N���X)
//--------------------------------------------
class CGame : public CScene
{
public:						// �N�ł��A�N�Z�X�ł���

	// �Q�[���̐i�s���
	enum STATE
	{
		STATE_START = 0,	// �J�n���
		STATE_PLAY,			// �v���C���
		STATE_RAT_WIN,		// �l�Y�~�̏������
		STATE_CAT_WIN,		// �l�R�̏������
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CGame();				// �R���X�g���N�^
	~CGame();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const MODE mode);		// ���̐ݒ菈��

	// �ÓI�����o�֐�(�Z�b�g�E�Q�b�g)
	static CPause* GetPause(void);					// �|�[�Y�̎擾����

	static void SetState(const STATE state);		// �Q�[���̐i�s��Ԃ̐ݒ菈��
	static STATE GetState(void);					// �Q�[���̐i�s��Ԃ̎擾����

	static CPlayer* GetPlayer(const int nID);		// �v���C���[�̎擾����

	static void SetCountDown(const bool Set) { m_bCountDown = Set; }		// �Q�[���̐i�s��Ԃ̐ݒ菈��
	static bool GetCountDown(void) { return m_bCountDown; }					// �Q�[���̐i�s��Ԃ̎擾����

	// NULL������
	static void DeletePause(void);		// �|�[�Y��NULL������
	static void DeletePlayer(int nIdx);	// �v���C���[��NULL������

// �f�o�b�O��
#ifdef _DEBUG
	static CEdit* GetEdit(void);		// �G�f�B�b�g�̎擾����
	static bool IsEdit(void);			// �G�f�B�b�g�󋵂̎擾����
#endif

private:					// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Pause(void);			// �|�[�Y����
	void Transition(void);		// �J�ڏ���

	// �ÓI�����o�ϐ�(�ŏ�����K�v�ȕ���z�u���Ă���)
	static CPause* m_pPause;				// �|�[�Y�̏��
	static CPlayer* m_apPlayer[MAX_PLAY];	// �v���C���[�̏��
	static CGameFinish* m_pFinish;			// �t�B�j�b�V���̏��
	static STATE m_GameState;				// �Q�[���̐i�s���
	static int m_nFinishCount;				// �I���J�E���g

// �f�o�b�O��
#ifdef _DEBUG
	static CEdit* m_pEdit;				// �G�f�B�b�g�̏��
	static bool m_bEdit;				// �G�f�B�b�g��
	static bool m_bCountDown;			// �J�E���g�_�E�����g�p����Ă��邩�ǂ���
#endif
};

#endif