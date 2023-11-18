//============================================
//
// �^�C�g�����S����[title_logo.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "title_logo.h"
#include "object2D.h"
#include "title.h"
#include "locus2D.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define RAT_TEXTURE			"data/TEXTURE/KariChuChu.png"			// �^�C�g�����S(�l�Y�~)�̃e�N�X�`��
#define CAT_TEXTURE			"data/TEXTURE/KariNyanko.png"			// �^�C�g�����S(�l�R)�̃e�N�X�`��
#define AND_TEXTURE			"data/TEXTURE/KariAnd.png"				// �^�C�g�����S(��)�̃e�N�X�`��
#define RAT_POS				(D3DXVECTOR3(-360.0f, 330.0f, 0.0f))		// �l�Y�~�̈ʒu
#define CAT_POS				(D3DXVECTOR3(-240.0f, 270.0f, 0.0f))		// �l�R�̈ʒu
#define AND_POS				(D3DXVECTOR3(530.0f, 300.0f, 0.0f))			// ���̈ʒu
#define RAT_SIZE			(D3DXVECTOR3(360.0f, 60.0f, 0.0f))		// �l�Y�~�̃T�C�Y
#define CAT_SIZE			(D3DXVECTOR3(240.0f, 60.0f, 0.0f))		// �l�R�̃T�C�Y
#define AND_SIZE			(NONE_D3DXVECTOR3)						// ���̃T�C�Y
#define MOVE_SPEED			(60.0f)			// �ړ��ʂ̑��x
#define CAT_APPEAR_RAT_POS	(780.0f)		// �l�R���ړ��������l�Y�~�̈ʒu
#define RAT_STOP_POS		(930.0f)		// �l�Y�~�̎~�܂�ʒu
#define CAT_STOP_POS		(250.0f)		// �l�R�̎~�܂�ʒu
#define AND_DEST_SIZE		(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// �A���h�̖ړI�̃T�C�Y
#define AND_ADD_SIZE		(5.0f)			// �A���h�̃T�C�Y�̒ǉ���

//============================
// �R���X�g���N�^
//============================
CTitleLogo::CTitleLogo() : CObject(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;	// �ړ���
		m_aTitle[nCnt].pLogo = nullptr;			// �^�C�g���̃|���S��
		m_aTitle[nCnt].bDisp = false;			// �\����
		m_aTitle[nCnt].bMove = false;			// �ړ���
	}

	m_state = STATE_ESCAPE;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
}

//============================
// �f�X�g���N�^
//============================
CTitleLogo::~CTitleLogo()
{

}

//============================
// ����������
//============================
HRESULT CTitleLogo::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo == nullptr)
		{ // �^�C�g���� NULL �̏ꍇ

			// �^�C�g���̃��S�𐶐�����
			m_aTitle[nCnt].pLogo = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}

		// �S�Ă̒l������������
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// �ړ���
		m_aTitle[nCnt].bDisp = false;				// �\����
		m_aTitle[nCnt].bMove = false;				// �ړ���
	}

	m_state = STATE_ESCAPE;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CTitleLogo::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // �^�C�g���̃|���S���� NULL ����Ȃ��ꍇ

			// �I������
			m_aTitle[nCnt].pLogo->Uninit();
			m_aTitle[nCnt].pLogo = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//============================
// �X�V����
//============================
void CTitleLogo::Update(void)
{
	switch (CTitle::GetState())
	{
	case CTitle::STATE_TITLE_APPEAR:		// �o�����

		switch (m_state)
		{
		case STATE_ESCAPE:

			// ������Ԃ̏���
			EscapeProcess();

			break;

		case STATE_AND:

			// ���o����Ԃ̏���
			AndProcess();

			break;

		default:

			// ��~
			assert(false);

			break;
		}

		break;

	case CTitle::STATE_WAIT:				// �ҋ@���

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �����ƒ�����ݒ肷��
		m_aTitle[nCnt].pLogo->SetAngle();
		m_aTitle[nCnt].pLogo->SetLength();

		// ���_���W�̐ݒ菈��
		m_aTitle[nCnt].pLogo->SetVertexRot();
	}
}

//============================
// �`�揈��
//============================
void CTitleLogo::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr &&
			m_aTitle[nCnt].bDisp == true)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_aTitle[nCnt].pLogo->Draw();
		}
	}
}

//============================
// ���̐ݒ菈��
//============================
void CTitleLogo::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			switch (nCnt)
			{
			case TYPE_RAT:		// �l�Y�~

				m_aTitle[nCnt].pLogo->SetPos(RAT_POS);		// �ʒu
				m_aTitle[nCnt].pLogo->SetPosOld(RAT_POS);	// �O��̈ʒu
				m_aTitle[nCnt].pLogo->SetSize(RAT_SIZE);	// �T�C�Y

				// �e�N�X�`���̐ݒ菈��
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

				// ����ݒ肷��
				m_aTitle[nCnt].move.x = MOVE_SPEED;			// �ړ���
				m_aTitle[nCnt].bDisp = true;				// �\����
				m_aTitle[nCnt].bMove = true;				// �ړ���

				break;

			case TYPE_AND:		// �A���h

				m_aTitle[nCnt].pLogo->SetPos(AND_POS);		// �ʒu
				m_aTitle[nCnt].pLogo->SetPosOld(AND_POS);	// �O��̈ʒu
				m_aTitle[nCnt].pLogo->SetSize(AND_SIZE);	// �T�C�Y

				// �e�N�X�`���̐ݒ菈��
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(AND_TEXTURE));

				// ����ݒ肷��
				m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// �ړ���
				m_aTitle[nCnt].bDisp = false;				// �\����
				m_aTitle[nCnt].bMove = false;			// �ړ���

				break;

			case TYPE_CAT:		// �l�R

				m_aTitle[nCnt].pLogo->SetPos(CAT_POS);		// �ʒu
				m_aTitle[nCnt].pLogo->SetPosOld(CAT_POS);	// �O��̈ʒu
				m_aTitle[nCnt].pLogo->SetSize(CAT_SIZE);	// �T�C�Y

				// �e�N�X�`���̐ݒ菈��
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(CAT_TEXTURE));

				// ����ݒ肷��
				m_aTitle[nCnt].move.x = MOVE_SPEED;			// �ړ���
				m_aTitle[nCnt].bDisp = true;				// �\����
				m_aTitle[nCnt].bMove = false;			// �ړ���

				break;
			}

			m_aTitle[nCnt].pLogo->SetRot(NONE_D3DXVECTOR3);	// ����
			m_aTitle[nCnt].pLogo->SetAngle();				// ����
			m_aTitle[nCnt].pLogo->SetLength();				// ����

			// ���_���W�̐ݒ菈��
			m_aTitle[nCnt].pLogo->SetVertexRot();
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}
	}

	m_state = STATE_ESCAPE;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
}

//============================
//��������
//============================
CTitleLogo* CTitleLogo::Create(void)
{
	// �^�C�g�����S�̃|�C���^�𐶐�
	CTitleLogo* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTitle = new CTitleLogo;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTitle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTitle->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �^�C�g�����S�̃|�C���^��Ԃ�
	return pTitle;
}

//============================
// ������Ԃ̏���
//============================
void CTitleLogo::EscapeProcess(void)
{
	// �ړ�����
	Move(TYPE::TYPE_RAT);		// �l�Y�~
	Move(TYPE::TYPE_CAT);		// �l�R

	// �l�Y�~�̈ʒu�̐ݒ菈��
	EscapeRatPosSet();

	// �l�R�̈ʒu�̐ݒ菈��
	EscapeCatPosSet();

	if (m_nStateCount % 5 == 0)
	{ // ��莞�Ԃ��Ƃ�

		// �c���̔�������
		Locus(TYPE_RAT);
		Locus(TYPE_CAT);
	}

	// �c���̔����J�E���g�����Z����
	m_nStateCount++;
}

//============================
// ���o����Ԃ̏���
//============================
void CTitleLogo::AndProcess(void)
{
	// ��ԃJ�E���g�����Z����
	m_nStateCount++;

	// �T�C�Y���擾����
	D3DXVECTOR3 rot = m_aTitle[TYPE_AND].pLogo->GetRot();
	D3DXVECTOR3 size = m_aTitle[TYPE_AND].pLogo->GetSize();

	// �T�C�Y�����Z����
	size.x = AND_ADD_SIZE * m_nStateCount;
	size.y = AND_ADD_SIZE * m_nStateCount;

	// ���������Z����
	rot.z -= (D3DX_PI * 2) / 10;

	// �����̐��K��
	useful::RotNormalize(&rot.z);

	if (size.x >= AND_DEST_SIZE.x ||
		size.y >= AND_DEST_SIZE.y)
	{ // �T�C�Y�����ȏ�ɂȂ����ꍇ

		// �T�C�Y��␳����
		size = AND_DEST_SIZE;

		// �������܂������ɕ␳����
		rot.z = 0.0f;

		// �ҋ@��Ԃɂ���
		m_state = STATE_WAIT;

		// �^�C�g����ҋ@��Ԃɂ���
		CTitle::SetState(CTitle::STATE_WAIT);
	}

	// �����ƃT�C�Y��K�p����
	m_aTitle[TYPE_AND].pLogo->SetRot(rot);
	m_aTitle[TYPE_AND].pLogo->SetSize(size);
}

//============================
// �ړ�����
//============================
void CTitleLogo::Move(const TYPE type)
{
	if (m_aTitle[type].bMove == true)
	{ // �ړ��󋵂� true �̏ꍇ

		// �ʒu���擾����
		D3DXVECTOR3 pos = m_aTitle[type].pLogo->GetPos();

		// �ʒu�����Z����
		pos.x += m_aTitle[type].move.x;

		// �ʒu��K�p����
		m_aTitle[type].pLogo->SetPos(pos);
	}
}

//============================
// �c����������
//============================
void CTitleLogo::Locus(const TYPE type)
{
	if (m_aTitle[type].bMove == true)
	{ // �ړ��󋵂� true �̏ꍇ

		// �c���̐�������
		CLocus2D::Create
		(
			m_aTitle[type].pLogo->GetPos(),		// �ʒu
			NONE_D3DXVECTOR3,					// ����
			m_aTitle[type].pLogo->GetSize(),	// �T�C�Y
			0.2f,								// �����x
			40,									// ����
			m_aTitle[type].pLogo->GetTexIdx()	// �e�N�X�`���̃C���f�b�N�X
		);
	}
}

//============================
// ������Ԃ̃l�Y�~�̈ʒu�֌W����
//============================
void CTitleLogo::EscapeRatPosSet(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x >= CAT_APPEAR_RAT_POS)
	{ // �l�Y�~�̈ʒu�����ʒu�𒴂����ꍇ

		// �ړ��󋵂� true �ɂ���
		m_aTitle[TYPE_CAT].bMove = true;
	}

	if (pos.x >= RAT_STOP_POS)
	{ // �l�Y�~�̈ʒu�����̈ʒu�ɒB�����ꍇ

		// �l�Y�~�̈ʒu��␳����
		pos.x = RAT_STOP_POS;

		// �ړ��󋵂� false �ɂ���
		m_aTitle[TYPE_RAT].bMove = false;
	}

	// �ʒu��K�p����
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// ������Ԃ̃l�R�̈ʒu�֌W����
//============================
void CTitleLogo::EscapeCatPosSet(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_CAT].pLogo->GetPos();

	if (pos.x >= CAT_STOP_POS)
	{ // �l�R�̈ʒu�����̈ʒu�ɒB�����ꍇ

		// �l�R�̈ʒu��␳����
		pos.x = CAT_STOP_POS;

		// �ړ��󋵂� false �ɂ���
		m_aTitle[TYPE_CAT].bMove = false;

		// �A���h�̕\���󋵂� true �ɂ���
		m_aTitle[TYPE_AND].bDisp = true;

		// �ҋ@��Ԃɂ���
		m_state = STATE_AND;

		// ��ԃJ�E���g������������
		m_nStateCount = 0;
	}

	// �ʒu��K�p����
	m_aTitle[TYPE_CAT].pLogo->SetPos(pos);
}