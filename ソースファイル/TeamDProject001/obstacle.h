//===================================
//
// ��Q���w�b�_�[[obstacle.h]
// Author ��������
//
//===================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "player.h"

class CBillboard;

//-----------------------------------
// �N���X��`(��Q��)
//-----------------------------------
class CObstacle : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_HONEY = 0,		// �I��
		TYPE_SLIME,			// �X���C��
		TYPE_HAIRBALL,		// �{
		TYPE_FLOWERVASE,	// �ԕr
		TYPE_PETBOTTLE,		// �y�b�g�{�g��
		TYPE_TOYCAR,		// ��������̎�
		TYPE_ROOMBA,		// �����o
		TYPE_HIMO,			// �Ђ�
		TYPE_SPEAKER,		// �X�s�[�J�[
		TYPE_MOUSETRAP,		// �l�Y�~�߂�
		TYPE_LEASH,			// ���[�h
		TYPE_PIN,			// ��e
		TYPE_FAN,			// ��@
		TYPE_CUP,			// �R�b�v
		TYPE_GARBAGECAN,	//�S�~
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CObstacle();			// �R���X�g���N�^
	CObstacle(CObject::TYPE type, PRIORITY priority = PRIORITY_BLOCK);			// �R���X�g���N�^
	virtual ~CObstacle();	// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// ���X�g�\���֌W
	void SetPrev(CObstacle* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CObstacle* pNext);		// ��̃|�C���^�̐ݒ菈��
	CObstacle* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CObstacle* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	virtual void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	virtual bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type) = 0;	// �����蔻�菈��
	virtual bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type) = 0;								// �q�b�g����
	virtual bool HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type) { return false; }													// �q�b�g����
	virtual void Action(void) = 0;											// �M�~�b�N�N������
	virtual void MultiAction(void) {}										// �M�~�b�N�����N������
	void GimmickUI(bool Set, int Player_Idx);												// �M�~�b�N�N��UI�̕\��

	// �Z�b�g�E�Q�b�g�֌W
	void SetType(const TYPE type);		// ��ނ̐ݒ菈��
	TYPE GetType(void);					// ��ނ̎擾����

	void SetCatUse(const bool Set) { m_bCatUse = Set; }		// �N���\�̐ݒ菈��
	bool GetCatUse(void) { return m_bCatUse; }				// �N���\�̎擾����
	void SetRatUse(const bool Set) { m_bRatUse = Set; }		// �N���\�̐ݒ菈��
	bool GetRatUse(void) { return m_bRatUse; }				// �N���\�̎擾����

	// �ÓI�����o�֐�
	static CObstacle* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	TYPE m_type;		// ���
	CBillboard *m_pGimmickUI;
	bool m_pGimmickUIFalse[MAX_PLAY];	//�S��[False]�̎���UI���폜����
	bool m_bCatUse;						//�L���N���ł��邩�ǂ���
	bool m_bRatUse;						//�l�Y�~���N���ł��邩�ǂ���

	// ���X�g�\���֌W
	CObstacle* m_pPrev;	// �O�ւ̃|�C���^
	CObstacle* m_pNext;	// ���ւ̃|�C���^
};

#endif