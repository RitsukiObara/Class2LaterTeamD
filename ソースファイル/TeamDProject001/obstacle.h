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
		TYPE_PLASTICCASE,	// �v���X�`�b�N�P�[�X
		TYPE_PETBOTTLE,		// �y�b�g�{�g��
		TYPE_TOYCAR,		// ��������̎�
		TYPE_ROOMBA,		// �����o
		TYPE_HIMO,			// �Ђ�
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(�����蔻��̎��)
	enum COLLTYPE
	{
		COLLTYPE_CAT = 0,
		COLLTYPE_RAT,
		COLLTYPE_MAX
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

	virtual void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	virtual bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type) = 0;	// �����蔻�菈��
	virtual bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type) = 0;								// �q�b�g����

	// �Z�b�g�E�Q�b�g�֌W
	void SetType(const TYPE type);		// ��ނ̐ݒ菈��
	TYPE GetType(void);					// ��ނ̎擾����

	// �ÓI�����o�֐�
	static CObstacle* Create(const D3DXVECTOR3& pos, const TYPE type);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	TYPE m_type;		// ���

	// ���X�g�\���֌W
	CObstacle* m_pPrev;	// �O�ւ̃|�C���^
	CObstacle* m_pNext;	// ���ւ̃|�C���^
};

#endif