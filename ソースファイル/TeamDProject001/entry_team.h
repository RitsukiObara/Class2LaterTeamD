//===================================
//
// �G���g���[�`�[���w�b�_�[[entry_team.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_TEAM_H_
#define _ENTRY_TEAM_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CEntryTeam)
//-----------------------------------
class CEntryTeam : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CEntryTeam();			// �R���X�g���N�^
	~CEntryTeam();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryTeam* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif