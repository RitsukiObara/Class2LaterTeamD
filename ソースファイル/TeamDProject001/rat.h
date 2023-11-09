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
class CRat : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CRat();			// �R���X�g���N�^
	~CRat();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetRatIdx(const int nIdx);			// �l�Y�~�̔ԍ��̐ݒ菈��
	int GetRatIdx(void) const;				// �l�Y�~�̔ԍ��̎擾����

	// �ÓI�����o�֐�
	static CRat* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);			// �ړ�����
	void Jump(void);			// �W�����v����
	void Attack(void);			// �U������
	void Elevation(void);		// �N���n�ʂ̓����蔻��
	void Hit(void);				// �q�b�g����

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	int m_nRatIdx;				// �l�Y�~�̔ԍ�
	int m_nLife;				// ����
	int m_nDamageCounter;		// �_���[�W�H�炤�܂ł̃J�E���^�[

	bool m_bJump;				// �W�����v������
	bool m_bLand;				// ���n������
	bool m_bAttack;				// �U��������
};

#endif