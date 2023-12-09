//===================================
//
// �X�C�b�`�w�b�_�[[switch.h]
// Author ��������
//
//===================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CModel;		// ���f��

//-----------------------------------
// �N���X��`(�X�C�b�`)
//-----------------------------------
class CSwitch : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_BASE = 0,		// �y��
		TYPE_LEVER,			// ���o�[
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CSwitch();				// �R���X�g���N�^
	~CSwitch();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֐�
	void SetBoot(const bool bBoot);			// �N���󋵂̐ݒ菈��
	bool GetBoot(void) const;				// �N���󋵂̎擾����

	// �ÓI�����o�֐�
	static CSwitch* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CModel* m_apModel[TYPE_MAX];		// ���f���̏��
	bool m_bMove;						// �ړ���
	bool m_bBoot;						// �N����
};

#endif