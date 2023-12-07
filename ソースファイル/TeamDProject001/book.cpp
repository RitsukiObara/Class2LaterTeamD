//===========================================
//
// �{�̏���[book.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "book.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CBook::CBook() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		m_apBook[nCnt] = nullptr;
	}
	SetCatUse(true);		// �l�R�̎g�p����
	SetRatUse(true);		// �l�Y�~�̎g�p����
}

//==============================
// �f�X�g���N�^
//==============================
CBook::~CBook()
{

}

//==============================
// �{�̏���������
//==============================
HRESULT CBook::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] == nullptr)
		{ // �{�̏�� NULL �̏ꍇ

			// �{�𐶐�����
			m_apBook[nCnt] = new CModel(TYPE_NONE, PRIORITY_BLOCK);
		}
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �{�̏I������
//========================================
void CBook::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// �{�̏I������
			m_apBook[nCnt]->Uninit();
			m_apBook[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �{�̍X�V����
//=====================================
void CBook::Update(void)
{

}

//=====================================
// �{�̕`�揈��
//=====================================
void CBook::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// �{�̕`�揈��
			m_apBook[nCnt]->Draw();
		}
	}
}

//=====================================
// ���[�N�����̏���
//=====================================
void CBook::Action(void)
{

}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBook::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			m_apBook[nCnt]->SetPos(D3DXVECTOR3(pos.x, pos.y + (nCnt * 50.0f), pos.z));
			m_apBook[nCnt]->SetPosOld(m_apBook[nCnt]->GetPos());
			m_apBook[nCnt]->SetRot(NONE_D3DXVECTOR3);
			m_apBook[nCnt]->SetScale(NONE_SCALE);
			m_apBook[nCnt]->SetFileData(CXFile::TYPE_ACADAPTER);
		}
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CBook::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CBook::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CBook::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{ // �~�͈͓̔��̏ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}