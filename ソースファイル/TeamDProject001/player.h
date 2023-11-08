//===================================
//
// �v���C���[�w�b�_�[[player.h]
// Author ��������
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�v���C���[)
//-----------------------------------
class CPlayer : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CPlayer* Get(void);							// �擾����
	static CPlayer* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	CPlayer();			// �R���X�g���N�^
	~CPlayer();			// �f�X�g���N�^

	// �����o�֐�
	void Move(void);			// �ړ�����
	void Jump(void);			// �W�����v����
	void Elevation(void);		// �N���n�ʂ̓����蔻��

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���

	bool m_bJump;				// �W�����v������
	bool m_bLand;				// ���n������

	// �ÓI�����o�ϐ�
	static CPlayer* m_pPlayer;	// �v���C���[�̏��
};

#endif