//===================================
//
// �G���g���[�}�b�`���OUI�w�b�_�[[entry_match.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_MATCH_H_
#define _ENTRY_MATCH_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MATCH_ID_MAX		(4)		// �I�����̍ő吔

//-----------------------------------
// �O���錾
//-----------------------------------
class CMatchFrame;		// �G���g���[�̘g
class CMatchChara;		// �L�����N�^�[
class CMatchVS;			// VS�}�[�N
class CMatchSelect;		// �I����

//-----------------------------------
// �N���X��`(CEntryMatch)
//-----------------------------------
class CEntryMatch : public CObject
{
public:

	CEntryMatch();			// �R���X�g���N�^
	~CEntryMatch();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nID);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryMatch* Create(const D3DXVECTOR3& pos, const int nID);	// ��������

private:

	// �����o�ϐ�
	CMatchFrame* m_pFrame;					// �g�̏��
	CMatchChara* m_pChara;					// �L�����N�^�[
	CMatchVS* m_pVS;						// VS�}�[�N
	CMatchSelect* m_apSelect[MATCH_ID_MAX];	// �I����
};

#endif