//===================================
//
// �X�s�[�J�[�w�b�_�[[Himo.h]
// Author ��{�ėB
//
//===================================
#ifndef _SPEAKER_H_
#define _SPEAKER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_NOTE	 (64)		//��������ʂ̒��ɑ��݂ł���ő吔

//-----------------------------------
// �O���錾
//-----------------------------------
class CNote;		// ����

//-----------------------------------
// �N���X��`(�X�s�[�J�[)
//-----------------------------------
class CSpeaker : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_STOP = 0,		// ��~���
		STATE_SHRINK,		// �k�ݏ��
		STATE_EXTEND,		// �L�я��
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CSpeaker();				// �R���X�g���N�^
	~CSpeaker();			// �f�X�g���N�^

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
	void MySetIdx(int Idx){ m_bmySet[Idx] = false; }
	static void NULLNote(int Idx) { m_apNote[Idx] = NULL; }

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void State(void);		// ��Ԃɂ�鏈��
	void SetNote(void);

	// �����o�ϐ�
	STATE m_state;				// ���
	bool m_bmySet[MAX_NOTE];
	bool m_bAction;
	int m_nNoteCount;

	// �ÓI�����o�ϐ�
	static CNote *m_apNote[MAX_NOTE];
};

#endif