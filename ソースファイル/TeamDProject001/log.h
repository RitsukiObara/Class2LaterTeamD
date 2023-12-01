//===================================
//
// ���O�w�b�_�[[log.h]
// Author ��{�ėB
//
//===================================
#ifndef _LOG_H_
#define _LOG_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

class CObject2D;

//-----------------------------------
// �N���X��`(�T���v��)
//-----------------------------------
class CLog : public CObject/*�e�N���X*/
{
public:			// �N�ł��A�N�Z�X�ł���

	CLog();			// �R���X�g���N�^
	~CLog();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(int nIdex, int nCreateNumber);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CLog* Create(int nIdex, int nCreateNumber);		// ��������

private:		// ���������A�N�Z�X�ł���

	D3DXVECTOR3 LogPos;
	int m_nPlayerNumber;
	int m_CreateNumber;
	CObject2D *m_pLogBG;
	CObject2D *m_pLogPlayerID;
	CObject2D *m_pLogMessage;
};
#endif