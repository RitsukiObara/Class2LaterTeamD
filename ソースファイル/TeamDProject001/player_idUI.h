//===================================
//
// �v���C���[��ID�\���w�b�_�[[player_idUI.h]
// Author ��������
//
//===================================
#ifndef _PLAYER_IDUI_H_
#define _PLAYER_IDUI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(CPlayerID)
//-----------------------------------
class CPlayerID : public CBillboard
{
public:

	CPlayerID();			// �R���X�g���N�^
	~CPlayerID();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nID);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CPlayerID* Create(const D3DXVECTOR3& pos, const int nID);	// ��������

private:

	// �����o�ϐ�

};

#endif