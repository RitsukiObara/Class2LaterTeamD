//===================================
//
// �X�s�[�J�[�w�b�_�[[Himo.h]
// Author ��{�ėB
//
//===================================
#ifndef _SPEAKER_H_
#define _SPEAKER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

#define MAX_NOTE (32)

class CNote;
//-----------------------------------
// �N���X��`(�X�s�[�J�[)
//-----------------------------------
class CSpeaker : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CSpeaker();				// �R���X�g���N�^
	~CSpeaker();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	bool Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);	// �����蔻�菈��
	bool Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type);		// �q�b�g����

	static void NULLNote(int Idx) { m_apNote[Idx] = NULL; }

private:		// ���������A�N�Z�X�ł���
	void Action(void);
	void SetNote(void);

	static CNote *m_apNote[MAX_NOTE];
	bool m_bAction;
	int m_nNoateCount;
};

#endif