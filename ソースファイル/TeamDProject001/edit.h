//===================================
//
// �G�f�B�b�g�w�b�_�[[edit.h]
// Author ��������
//
//===================================
#ifndef _EDIT_H_
#define _EDIT_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�G�f�B�b�g)
//-----------------------------------
class CEdit : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_OBSTACLE = 0,		// ��Q��
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CEdit();			// �R���X�g���N�^
	~CEdit();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEdit* Create(void);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);		// �ړ�����
	void Adjust(void);		// ����������
	void Set(void);			// �ݒu����
	void Delete(void);		// ��������

	// ���ꂼ��̏�������
	void DeleteObstacle(void);	// ��Q���̏�������

	// �����o�ϐ��錾
	TYPE m_type;					// ���
	CObstacle::TYPE m_obstacleType;	// ��Q���̎��
};

#endif