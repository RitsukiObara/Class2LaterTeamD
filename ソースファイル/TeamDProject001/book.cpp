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
#include "collision.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define BOOK_SHIFT_HEIGHT		(27.5f)			// �{�̂��炷����
#define BOOK_COLLAPSE_RANGE		(80.0f)			// �{�̃q�b�g����͈̔�

//==============================
// �R���X�g���N�^
//==============================
CBook::CBook() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		m_apBook[nCnt] = nullptr;	// �{�̏��
	}
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
	SetCatUse(true);				// �l�R�̎g�p����
	SetRatUse(true);				// �l�Y�~�̎g�p����
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
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���

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
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// ��ԃ}�l�[�W���[
	StateManager();
}

//=====================================
// �{�̕`�揈��
//=====================================
void CBook::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// �{�̕`�揈��
			m_apBook[nCnt]->Draw();
		}
	}

	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBook::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �����̕ϐ���錾����
	float fRot;

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_apBook[nCnt] != nullptr)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// �����������_���ŎZ�o
			fRot = (rand() % 81 - 40) * 0.01f;

			// ����ݒ肷��
			m_apBook[nCnt]->SetPos(D3DXVECTOR3(pos.x, pos.y + ((nCnt + 1) * BOOK_SHIFT_HEIGHT), pos.z));
			m_apBook[nCnt]->SetPosOld(m_apBook[nCnt]->GetPos());
			m_apBook[nCnt]->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
			m_apBook[nCnt]->SetScale(NONE_SCALE);
			m_apBook[nCnt]->SetFileData((CXFile::TYPE)(CXFile::TYPE_BOOKBLUE + nCnt));
		}
	}
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
}

//=====================================
// ��ԃ}�l�[�W���[
//=====================================
void CBook::StateManager(void)
{
	switch (m_state)
	{
	case CBook::STATE_STOP:			// ��~���

		// ���ɂȂ�

		break;

	case CBook::STATE_COLLAPSE:		// �|����



		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CBook::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	D3DXVECTOR3 objMax = D3DXVECTOR3(GetFileData().vtxMax.x, GetFileData().vtxMax.y + (GetFileData().collsize.y * MAX_BOOK), GetFileData().vtxMax.z);

	// �Z�ʑ̂̓����蔻��
	if (collision::HexahedronCollision
	(
		&pos,					// �ʒu
		GetPos(),				// �{�̈ʒu
		posOld,					// �O��̈ʒu
		GetPosOld(),			// �{�̑O��̈ʒu
		vtxMin,					// �ŏ��l
		GetFileData().vtxMin,	// �{�̍ŏ��l
		vtxMax,					// �ő�l
		objMax					// �{�̍ŏ��l
	) == true)
	{ // �����蔻��ɓ��������ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CBook::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	if (m_state == STATE_COLLAPSE &&
		useful::CircleCollisionXZ(pos, GetPos(), collSize.x, GetFileData().fRadius) == true)
	{ // �|���Ԃň��͈͓��ɂ����ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CBook::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (m_state == STATE_STOP &&
		useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{ // ��~��Ԃ��A�~�͈͓̔��̏ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �N�����̏���
//=====================================
void CBook::Action(void)
{
	if (m_state == STATE_STOP)
	{ // ��~��Ԃ̏ꍇ

		// �������擾����
		D3DXVECTOR3 rot = GetRot();

		// �|���Ԃɂ���
		m_state = STATE_COLLAPSE;

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(rot.y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot.y + (D3DX_PI * -0.5f)) * 4.0f;
	}
}