//===================================
//
// �}�b�`���O�̃L�����w�b�_�[[match_chara.h]
// Author ��������
//
//===================================
#ifndef _MATCH_CHARA_H_
#define _MATCH_CHARA_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CMatchChara)
//-----------------------------------
class CMatchChara : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CMatchChara();			// �R���X�g���N�^
	~CMatchChara();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CMatchChara* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif