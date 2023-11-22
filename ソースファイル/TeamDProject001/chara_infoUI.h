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
#include "chara_icon.h"

//--------------------------------------------
// �N���X��`(�L�����N�^�[�̏��UI)
//--------------------------------------------
class CCharaInfoUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CCharaInfoUI();					// �R���X�g���N�^
	~CCharaInfoUI();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaIcon::TYPE type);						// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCharaInfoUI* Create(const D3DXVECTOR3& pos, const int nPlayerID, const CCharaIcon::TYPE type);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CCharaIcon* m_pIcon;	// �A�C�R���̏��
};

#endif