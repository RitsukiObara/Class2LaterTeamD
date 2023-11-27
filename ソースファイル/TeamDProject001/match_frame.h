//===================================
//
// �}�b�`���O�̘g�w�b�_�[[match_frame.h]
// Author ��������
//
//===================================
#ifndef _MATCH_FRAME_H_
#define _MATCH_FRAME_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CMatchFrame)
//-----------------------------------
class CMatchFrame : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CMatchFrame();			// �R���X�g���N�^
	~CMatchFrame();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CMatchFrame* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif