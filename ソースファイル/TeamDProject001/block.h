//===================================
//
// �u���b�N�w�b�_�[[block.h]
// Author ��������
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�n�`�p�u���b�N)
//-----------------------------------
class CBlock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(�����蔻��̎��)
	enum COLLISION
	{
		COLLISION_SQUARE = 0,		// �l�p
		COLLISION_CIRCLE,			// �~
		COLLISION_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_CARDBOARD = 0,		// �i�{�[��
		TYPE_TISSUE,			// �e�B�b�V����
		TYPE_PENHOLDER,			// �y������
		TYPE_REMOCON,			// �����R��
		TYPE_BEAR,				// �e�f�B�x�A
		TYPE_CLOCK,				// ���v
		TYPE_RUBBISH,			// �`����
		TYPE_MILKPACK,			// �����p�b�N
		TYPE_CUP,				// �R�b�v
		TYPE_OBAPHONE,			// �I�o�t�H��
		TYPE_WII,				// Wii
		TYPE_DS,				// DS
		TYPE_HEADPHONE,			// �w�b�h�t�H��
		TYPE_PEN,				// �y��
		TYPE_ACADAPTER,			// AC�A�_�v�^�[
		TYPE_BUILDINGBLOCK,		// �ςݖ�
		TYPE_GLASSES,			// �ዾ�P�[�X
		TYPE_PENCIL,			// ���M
		TYPE_PICTUREFRAME,		// �ʐ^����
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CBlock();			// �R���X�g���N�^
	~CBlock();			// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CBlock* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CBlock* pNext);		// ��̃|�C���^�̐ݒ菈��
	CBlock* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CBlock* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetCollision(const COLLISION collsion);	// �����蔻��̎�ނ̐ݒ菈��
	COLLISION GetCollision(void) const;				// �����蔻��̎�ނ̎擾����

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	COLLISION m_collision;	// �����蔻��̎��
	TYPE m_type;			// ���

	// ���X�g�\���֌W
	CBlock* m_pPrev;	// �O�ւ̃|�C���^
	CBlock* m_pNext;	// ���ւ̃|�C���^
};

#endif