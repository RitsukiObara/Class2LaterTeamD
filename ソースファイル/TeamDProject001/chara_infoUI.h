//============================================
//
// �L�����N�^�[�̏��UI�w�b�_�[[chara_infoUI.h]
// Author�F��������
//
//============================================
#ifndef _CHARA_INFOUI_H_			// ���̃}�N����`������Ă��Ȃ�������
#define _CHARA_INFOUI_H_			// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �N���X��`(�L�����N�^�[�̏��UI)
//--------------------------------------------
class CCharaInfoUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_CAT = 0,		// �l�R
		TYPE_RAT,			// �l�Y�~
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CCharaInfoUI();					// �R���X�g���N�^
	~CCharaInfoUI();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nPlayerID, const TYPE type);						// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCharaInfoUI* Create(const D3DXVECTOR3& pos, const int nPlayerID, const TYPE type);		// ��������

private:			// ���������A�N�Z�X�ł���

};

#endif