//============================================
//
// �`���[�g���A���w�b�_�[[game.h]
// Author�F��������
//
//============================================
#ifndef _TUTORIAL_H_			//���̃}�N����`������Ă��Ȃ�������
#define _TUTORIAL_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

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
class CAnswer;			// �ԓ����A�N�V����
class CExplanation;		// ����

//--------------------------------------------
// �N���X(�`���[�g���A���N���X)
//--------------------------------------------
class CTutorial : public CScene
{
public:						// �N�ł��A�N�Z�X�ł���

	// �`���[�g���A���̐i�s���
	enum STATE
	{
		STATE_START = 0,	// �J�n���
		STATE_PLAY,			// �v���C���
		STATE_RAT_WIN,		// �l�Y�~�̏������
		STATE_CAT_WIN,		// �l�R�̏������
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �`���[�g���A���̐i�s���
	enum TUTORIAL
	{
		TUTORIAL_MOVE = 0,		// �ړ�
		TUTORIAL_ATTACK_JAMP,	// �A�^�b�N���W�����v
		TUTORIAL_CAT_KILL,		// �l�R�̃L��
		TUTORIAL_RAT_RESCUE,	// �l�Y�~�̋~��
		TUTORIAL_ACTION,		// �A�N�V����
		TUTORIAL_ITEM_MULTI,	// �A�C�e�����}���`�A�N�V����
		TUTORIAL_GIMMICK,		// �M�~�b�N����
		TUTORIAL_LETS_GO,		// ���������Ɖ�ʑJ��
		TUTORIAL_MAX			// ���̗񋓌^�̑���
	};

	CTutorial();				// �R���X�g���N�^
	~CTutorial();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const MODE mode);		// ���̐ݒ菈��

										// �ÓI�����o�֐�(�Z�b�g�E�Q�b�g)
	static CPause* GetPause(void);					// �|�[�Y�̎擾����

	static void SetState(const STATE state);		// �`���[�g���A���̐i�s��Ԃ̐ݒ菈��
	static STATE GetState(void);					// �`���[�g���A���̐i�s��Ԃ̎擾����

	static void SetPlay(const bool bPlay) { m_bPlay = bPlay; }		// �v���C�����ǂ����̐i�s��Ԃ̐ݒ菈��
	static bool GetPlay(void) { return m_bPlay; }					// �v���C�����ǂ����̐i�s��Ԃ̎擾����

	static void SetMultiAction(const bool bPlay) { m_MultiAction = bPlay; }		// �v���C�����ǂ����̐i�s��Ԃ̐ݒ菈��

	static CPlayer* GetPlayer(const int nID);		// �v���C���[�̎擾����

	// NULL������
	static void DeletePause(void);		// �|�[�Y��NULL������
	static void DeletePlayer(int nIdx);	// �v���C���[��NULL������

	static void PlayTrue(void);
	static void PlayFalse(void);

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
	static STATE m_GameState;				// �`���[�g���A���̐i�s���
	static int m_nFinishCount;				// �I���J�E���g
	static TUTORIAL m_Tutorial;				// �`���[�g���A���̍���
	static bool m_bPlay;					// �v���C�����ǂ���
	static CAnswer* m_pAnswer;				// �ԓ����A�N�V�����̏��
	static CExplanation* m_pExplanation;	// �����̏��
	static bool m_MultiAction;				// �A�g�N���̏��

	// �f�o�b�O��
#ifdef _DEBUG
	static CEdit* m_pEdit;				// �G�f�B�b�g�̏��
	static bool m_bEdit;				// �G�f�B�b�g��
#endif
};

#endif