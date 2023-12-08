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
#define SHIFT_HEIGHT			(27.5f)			// ���炷����
#define COLLAPSE_RANGE			(80.0f)			// �q�b�g����͈̔�
#define COLLAPSE_MOVE			(5.0f)			// �|���Ԃ̈ړ���
#define COLLAPSE_ROT_MOVE		(8)				// �|���Ԃ̌����̈ړ���
#define COLLAPSE_MIN_ROT_MOVE	(3)				// �|���Ԃ̌����̈ړ��ʂ̍Œ�l
#define COLLAPSE_GRAVITY		(8)				// �|���Ԃ̏d��
#define COLLAPSE_MIN_GRAVITY	(3)				// �|���Ԃ̏d�͂̍Œ�l
#define DEATH_POS_Y				(0.0f)			// �����Ȃ��Ȃ���W(Y��)

//==============================
// �R���X�g���N�^
//==============================
CBook::CBook() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		m_aBook[nCnt].pBook = nullptr;			// �{�̏��
		m_aBook[nCnt].move = NONE_D3DXVECTOR3;	// �ړ���
		m_aBook[nCnt].fGravity = 0.0f;			// �d��
		m_aBook[nCnt].fRotMove = 0.0f;			// �����̈ړ���
		m_aBook[nCnt].bDisp = true;				// �`���
	}
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
	m_fGravity = 0.0f;				// �d��
	m_fRotMove = 0.0f;				// �����̈ړ���
	m_bDisp = true;					// �`���
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
		if (m_aBook[nCnt].pBook == nullptr)
		{ // �{�̏�� NULL �̏ꍇ

			// �{�𐶐�����
			m_aBook[nCnt].pBook = new CModel(TYPE_NONE, PRIORITY_BLOCK);
		}
		m_aBook[nCnt].move = NONE_D3DXVECTOR3;		// �ړ���
		m_aBook[nCnt].fGravity = 0.0f;				// �d��
		m_aBook[nCnt].fRotMove = 0.0f;				// �����̈ړ���
		m_aBook[nCnt].bDisp = true;				// �`���
	}

	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
	m_fGravity = 0.0f;				// �d��
	m_fRotMove = 0.0f;				// �����̈ړ���
	m_bDisp = true;					// �`���

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
		if (m_aBook[nCnt].pBook != nullptr)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// �{�̏I������
			m_aBook[nCnt].pBook->Uninit();
			m_aBook[nCnt].pBook = nullptr;
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

	if (KillZ() == true)
	{ // �S�Ă����̍����܂ŗ������ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}
}

//=====================================
// �{�̕`�揈��
//=====================================
void CBook::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_aBook[nCnt].pBook != nullptr &&
			m_aBook[nCnt].bDisp == true)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// �{�̕`�揈��
			m_aBook[nCnt].pBook->Draw();
		}
	}

	if (m_bDisp == true)
	{ // �`��󋵂� true �̏ꍇ

		// �`�揈��
		CObstacle::Draw();
	}
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
		if (m_aBook[nCnt].pBook != nullptr)
		{ // �{�̏�� NULL ����Ȃ��ꍇ

			// �����������_���ŎZ�o
			fRot = (rand() % 81 - 40) * 0.01f;

			// ����ݒ肷��
			m_aBook[nCnt].pBook->SetPos(D3DXVECTOR3(pos.x, pos.y + ((nCnt + 1) * SHIFT_HEIGHT), pos.z));
			m_aBook[nCnt].pBook->SetPosOld(m_aBook[nCnt].pBook->GetPos());
			m_aBook[nCnt].pBook->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
			m_aBook[nCnt].pBook->SetScale(NONE_SCALE);
			m_aBook[nCnt].pBook->SetFileData((CXFile::TYPE)(CXFile::TYPE_BOOKBLUE + nCnt));
		}
	}
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
	m_fGravity = 0.0f;				// �d��
	m_fRotMove = 0.0f;				// �����̈ړ���
	m_bDisp = true;					// �`���
}

//=====================================
// ��ԃ}�l�[�W���[
//=====================================
void CBook::StateManager(void)
{
	// �ʒu�ƌ������擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 objpos = NONE_D3DXVECTOR3;
	D3DXVECTOR3 objrot = NONE_D3DXVECTOR3;

	switch (m_state)
	{
	case CBook::STATE_STOP:			// ��~���

		// ���ɂȂ�

		break;

	case CBook::STATE_COLLAPSE:		// �|����

		// �����̐ݒ菈��
		rot.z += m_fRotMove;

		// �d�͏���
		useful::Gravity(&m_move.y, pos, m_fGravity);

		// �ړ��ʂ����Z����
		pos += m_move;

		for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
		{
			// �ʒu�ƌ������擾����
			objpos = m_aBook[nCnt].pBook->GetPos();
			objrot = m_aBook[nCnt].pBook->GetRot();

			// �����̐ݒ菈��
			objrot.z += m_aBook[nCnt].fRotMove;

			// �d�͏���
			useful::Gravity(&m_move.y, objpos, m_aBook[nCnt].fGravity);

			// �ړ��ʂ����Z����
			objpos += m_move;

			// �ʒu�ƌ�����ݒ肷��
			m_aBook[nCnt].pBook->SetPos(objpos);
			m_aBook[nCnt].pBook->SetRot(objrot);
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �ʒu�ƌ�����K�p����
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// Z���ɂ���������
//=====================================
bool CBook::KillZ(void)
{
	// ������
	bool bHeight = true;

	if (GetPos().y <= DEATH_POS_Y)
	{ // �ʒu�����̈ʒu�ȉ��ɂȂ����ꍇ

		// �`��󋵂� false �ɂ���
		m_bDisp = false;
	}
	else
	{ // ��L�ȊO

		// �����󋵂� false �ɂ���
		bHeight = false;
	}

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_aBook[nCnt].pBook->GetPos().y <= DEATH_POS_Y)
		{ // �ʒu�����̈ʒu�ȉ��ɂȂ����ꍇ

			// �`��󋵂� false �ɂ���
			m_aBook[nCnt].bDisp = false;
		}
		else
		{ // ��L�ȊO

			// �����󋵂� false �ɂ���
			bHeight = false;
		}
	}

	// �����󋵂�Ԃ�
	return bHeight;
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
	if (m_state == STATE_STOP &&
		collision::HexahedronCollision
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
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	CModel* pBook = nullptr;

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		// �{�̏���ݒ肷��
		pBook = m_aBook[nCnt].pBook;

		if (m_state == STATE_COLLAPSE &&
			useful::RectangleCollisionXY(pos, pBook->GetPos(), vtxMax, pBook->GetFileData().vtxMax, vtxMin, pBook->GetFileData().vtxMin) == true && 
			useful::RectangleCollisionXZ(pos, pBook->GetPos(), vtxMax, pBook->GetFileData().vtxMax, vtxMin, pBook->GetFileData().vtxMin) == true && 
			useful::RectangleCollisionYZ(pos, pBook->GetPos(), vtxMax, pBook->GetFileData().vtxMax, vtxMin, pBook->GetFileData().vtxMin) == true)
		{ // �|���ԂŖ{�ɓ��������ꍇ

			// true ��Ԃ�
			return true;
		}
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
		m_move.x = sinf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;
		m_move.z = cosf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;

		// �d�͂�ݒ肷��
		m_fGravity = (float)((rand() % COLLAPSE_GRAVITY + COLLAPSE_MIN_GRAVITY) * 0.01f);

		// �����̈ړ��ʂ�ݒ肷��
		m_fRotMove = (float)((rand() % COLLAPSE_ROT_MOVE + COLLAPSE_MIN_ROT_MOVE) * 0.01f);

		for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
		{
			// �ړ��ʂ�ݒ肷��
			m_aBook[nCnt].move.x = sinf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;
			m_aBook[nCnt].move.z = cosf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;

			// �d�͂�ݒ肷��
			m_aBook[nCnt].fGravity = (float)((rand() % COLLAPSE_GRAVITY + COLLAPSE_MIN_GRAVITY) * 0.01f);

			// �����̈ړ��ʂ�ݒ肷��
			m_aBook[nCnt].fRotMove = (float)((rand() % COLLAPSE_ROT_MOVE + COLLAPSE_MIN_ROT_MOVE) * 0.01f);
		}
	}
}