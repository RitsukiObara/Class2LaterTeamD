//=============================================================================
//
// �T�E���h���� [sound.h]
// Author ��������
//
//=============================================================================
#ifndef _SOUND_H_					//���̃}�N����`������Ă��Ȃ�������
#define _SOUND_H_					//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

// �N���X��`(CSound)
class CSound
{
public:			// �N�ł��A�N�Z�X�o����

	//-------------------------------------------------------------------------
	// �T�E���h�ꗗ
	//-------------------------------------------------------------------------
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,		// �^�C�g��BGM
		SOUND_LABEL_BGM_ENTRY,			// �G���g���[BGM
		SOUND_LABEL_BGM_GAME,			// �Q�[��BGM
		SOUND_LABEL_BGM_RESULT,			// ���U���gBGM
		SOUND_LABEL_BGM_RANKING,		// �����L���OBGM
		SOUND_LABEL_SE_SELECT,			// �I����
		SOUND_LABEL_SE_DECIDE,			// ���艹
		SOUND_LABEL_SE_VICTORY,			//������
		SOUND_LABEL_SE_CATATTACK,		//�l�R���U���������̉�
		SOUND_LABEL_SE_CATATTACK_HIT,	//�l�R�̍U�����l�Y�~�Ƀq�b�g������
		SOUND_LABEL_SE_CATWALK,			//�l�R��������
		SOUND_LABEL_SE_MOUSEWALK,		//�l�Y�~��������
		SOUND_LABEL_SE_MOUSETRAP_ADDICTED,	//�l�Y�~�߂�Ƀn�}�鉹
		SOUND_LABEL_SE_THE_CUP_FALLS,	//�R�b�v����������
		SOUND_LABEL_SE_TV_SANDSTORM,	//�e���r�̍���
		SOUND_LEBEL_SE_PUSH_SWITCH,		//�X�C�b�`�����������̉�
		SOUND_LABEL_SE_SETITEM,			//�ݒu��
		SOUND_LABEL_SE_CLEANING,		//�|���@(�����o)
		SOUND_LABEL_SE_FAN,				//��@
		SOUND_LABEL_SE_THUMBTACK,		//��e
		SOUND_LABEL_SE_TUB,				//�^���C
		SOUND_LABEL_SE_PETBOTTLES_ROLL,	//�y�b�g�{�g�����]���鉹
		SOUND_LABEL_SE_PETBOTTLES_FALL_DOWN, //�y�b�g�{�g�����|��鉹
		SOUND_LABEL_SE_PICKED_UP,		//�E������
		SOUND_LABEL_SE_CHECK,			// �`���[�g���A���̃`�F�b�N��
		SOUND_LABEL_SE_HIMO,			// �Ђ��̉�
		SOUND_LABEL_SE_HAIRBALL,		// �܂�̉�
		SOUND_LABEL_SE_HONEYBREAK,		// �I���̕r������鉹
		SOUND_LABEL_SE_HONEYLEAK,		// �I�����L���鉹
		SOUND_LABEL_SE_HONEYWALK,		// �I���̏������
		SOUND_LABEL_SE_BOOLDOWN,		// �{�������鉹

		SOUND_LABEL_MAX					// ���̗񋓌^�̑���
	};

	//-----------------------------------------------------------------------------
	// �T�E���h���̍\���̒�`
	//-----------------------------------------------------------------------------
	struct SOUNDINFO
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	};

	CSound();			// �R���X�g���N�^
	~CSound();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �����o�ϐ�
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDINFO m_aSoundInfo[CSound::SOUND_LABEL_MAX];	// �T�E���h�̏��
};

#endif
