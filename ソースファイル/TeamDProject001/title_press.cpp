//============================================
//
// �v���X�G���^�[����[title_press.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "title_press.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"

#include "title.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define PRESS_TEXTURE		"data\\TEXTURE\\PRESS.png"				// �v���X�̃e�N�X�`��
#define BUTTON_TEXTURE		"data\\TEXTURE\\ENTER.png"				// �{�^���̃e�N�X�`��
#define PRESS_SIZE			(D3DXVECTOR3(200.0f, 50.0f, 0.0f))		// �uPRESS�v�̃T�C�Y
#define BUTTON_SIZE			(D3DXVECTOR3(200.0f, 50.0f, 0.0f))		// �uENTER�v�̃T�C�Y
#define INIT_PRESS_POS		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - PRESS_SIZE.x, 500.0f, 0.0f))		// �uPRESS�v�̏����ʒu
#define INIT_BUTTON_POS		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + BUTTON_SIZE.x, 500.0f, 0.0f))	// �uENTER�v�̏����ʒu
#define DEEP_DEST_ALPHA		(1.0f)									// �Z�F�̖ړI�̓����x
#define LIGHT_DEST_ALPHA	(0.3f)									// ���F�̖ړI�̓����x
#define ADD_ALPHA			(0.02f)									// �ǉ��̓����x

//============================
// �R���X�g���N�^
//============================
CTitlePress::CTitlePress() : CObject(CObject::TYPE_PRESSENTER, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aPress[nCnt].pPress = nullptr;			// �v���X�̏��
		m_aPress[nCnt].posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
		m_aPress[nCnt].move = NONE_D3DXVECTOR3;		// �ړ���
		m_aPress[nCnt].fAlpha = 0.0f;				// �����x
		m_aPress[nCnt].fAlphaDest = 0.0f;			// �ړI�̓����x
	}
}

//============================
// �f�X�g���N�^
//============================
CTitlePress::~CTitlePress()
{

}

//============================
// ����������
//============================
HRESULT CTitlePress::Init(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress == nullptr)
		{ // �v���X�̏�� NULL �̏ꍇ

			// �v���X�𐶐�����
			m_aPress[nCnt].pPress = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, PRIORITY_UI);

			if (m_aPress[nCnt].pPress != nullptr)
			{ // ��񂪓����Ă���ꍇ

				if (FAILED(m_aPress[nCnt].pPress->Init()))
				{ // �������Ɏ��s�����ꍇ

					// ��~
					assert(false);

					// ���s��Ԃ�
					return E_FAIL;
				}
			}
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		m_aPress[nCnt].posDest = NONE_D3DXVECTOR3;	// �ړI�̈ʒu
		m_aPress[nCnt].move = NONE_D3DXVECTOR3;		// �ړ���
		m_aPress[nCnt].fAlpha = 0.0f;				// �����x
		m_aPress[nCnt].fAlphaDest = 0.0f;			// �ړI�̓����x
	}

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CTitlePress::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress != nullptr)
		{ // �^�C�g���̃|���S���� NULL ����Ȃ��ꍇ

			// �|���S���̏I������
			m_aPress[nCnt].pPress->Uninit();
			m_aPress[nCnt].pPress = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//============================
// �X�V����
//============================
void CTitlePress::Update(void)
{
	switch (CTitle::GetState())
	{
	case CTitle::STATE_TITLE_APPEAR:	// �o�����

		break;

	case CTitle::STATE_WAIT:			// �ҋ@���

		// �����x����
		Alpha();

		break;

	case CTitle::STATE_TRANS:			// �J�ڏ��



		break;

	case CTitle::STATE_HOLEIN:			// ���̒��ɓ����Ă�������

		break;

	default:				// ��L�ȊO

		// ��~
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// ���_���W�̐ݒ菈��
		m_aPress[nCnt].pPress->SetVertex();

		// ���_�J���[�̐ݒ菈��
		m_aPress[nCnt].pPress->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_aPress[nCnt].fAlpha));
	}
}

//============================
// �`�揈��
//============================
void CTitlePress::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress != nullptr)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_aPress[nCnt].pPress->Draw();
		}
	}
}

//============================
// ���̐ݒ菈��
//============================
void CTitlePress::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress != nullptr)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			switch (nCnt)
			{
			case CTitlePress::TYPE_PRESS:

				m_aPress[nCnt].pPress->SetPos(INIT_PRESS_POS);		// �ʒu
				m_aPress[nCnt].pPress->SetSize(PRESS_SIZE);			// �T�C�Y

				// �e�N�X�`���̊��蓖�ď���
				m_aPress[nCnt].pPress->BindTexture(CManager::Get()->GetTexture()->Regist(PRESS_TEXTURE));

				break;

			case CTitlePress::TYPE_BUTTON:

				m_aPress[nCnt].pPress->SetPos(INIT_BUTTON_POS);		// �ʒu
				m_aPress[nCnt].pPress->SetSize(BUTTON_SIZE);		// �T�C�Y

				// �e�N�X�`���̊��蓖�ď���
				m_aPress[nCnt].pPress->BindTexture(CManager::Get()->GetTexture()->Regist(BUTTON_TEXTURE));

				break;

			default:

				// ��~
				assert(false);

				break;
			}

			m_aPress[nCnt].pPress->SetRot(NONE_D3DXVECTOR3);	// ����
			m_aPress[nCnt].pPress->SetAngle();					// ����
			m_aPress[nCnt].pPress->SetLength();					// ����

			// ���_���W�̐ݒ菈��
			m_aPress[nCnt].pPress->SetVertex();

			// ���_�J���[�̐ݒ菈��
			m_aPress[nCnt].pPress->SetVtxColor(NONE_D3DXCOLOR);
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}

		m_aPress[nCnt].posDest = NONE_D3DXVECTOR3;		// �ړI�̈ʒu
		m_aPress[nCnt].move = NONE_D3DXVECTOR3;			// �ړ���
		m_aPress[nCnt].fAlpha = 1.0f;					// �����x
		m_aPress[nCnt].fAlphaDest = LIGHT_DEST_ALPHA;	// �ړI�̓����x
	}
}

//============================
//��������
//============================
CTitlePress* CTitlePress::Create(void)
{
	// �v���X�G���^�[�̃|�C���^�𐶐�
	CTitlePress* pPress = nullptr;

	if (pPress == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pPress = new CTitlePress;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPress != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPress->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPress->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���X�G���^�[�̃|�C���^��Ԃ�
	return pPress;
}

//============================
// �����x�̏���
//============================
void CTitlePress::Alpha(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (useful::FrameCorrect(m_aPress[nCnt].fAlphaDest, &m_aPress[nCnt].fAlpha, ADD_ALPHA) == true)
		{ // �ړI�̓����x�ɋ߂Â����ꍇ

			// �ړI�̓����x��ݒ肷��
			m_aPress[nCnt].fAlphaDest = (m_aPress[nCnt].fAlphaDest >= DEEP_DEST_ALPHA) ? LIGHT_DEST_ALPHA : DEEP_DEST_ALPHA;
		}
	}
}