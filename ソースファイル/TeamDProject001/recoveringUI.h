//===================================
//
// �񕜒�UI�w�b�_�[[recoveringUI.h]
// Author ����������
//
//===================================
#ifndef _RECOVERINGUI_H_
#define _RECOVERINGUI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(�T���v��)
//-----------------------------------
class CRecoveringUI : public CBillboard
{
public:			// �N�ł��A�N�Z�X�ł���

	CRecoveringUI();			// �R���X�g���N�^
	~CRecoveringUI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(D3DXVECTOR3& pos, D3DXVECTOR3& posOld);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CRecoveringUI* Create(D3DXVECTOR3& pos, D3DXVECTOR3& posOld);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif