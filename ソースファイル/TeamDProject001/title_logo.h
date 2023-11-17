//===================================
//
// �^�C�g�����S�w�b�_�[[title_logo.h]
// Author ��������
//
//===================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CObject2D;		// 2D�|���S��

//-----------------------------------
// �N���X��`(�^�C�g�����S)
//-----------------------------------
class CTitleLogo : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_RAT = 0,// �ɂ��
		TYPE_AND,	 // ��
		TYPE_CAT,	 // ����[����[
		TYPE_MAX	 // ���̗񋓌^�̑���
	};

	CTitleLogo();			// �R���X�g���N�^
	~CTitleLogo();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTitleLogo* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CObject2D* m_apTitle[TYPE_MAX];		// �^�C�g���̃|���S��
};

#endif