//============================================
//
// ��ʂ̘g����[screen_frame.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "screen_frame.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	static const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// �ʒu
	static const D3DXVECTOR3 FRAME_SIZE = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// �T�C�Y
}

//============================
// �R���X�g���N�^
//============================
CScreenFrame::CScreenFrame() : CObject2D(CObject::TYPE_SCREENFRAME, CObject::PRIORITY_BG)
{

}

//============================
// �f�X�g���N�^
//============================
CScreenFrame::~CScreenFrame()
{

}

//============================
// ����������
//============================
HRESULT CScreenFrame::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CScreenFrame::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//============================
// �X�V����
//============================
void CScreenFrame::Update(void)
{
	// ���_���̐ݒ菈��
	SetVertex();
}

//============================
// �`�揈��
//============================
void CScreenFrame::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//============================
// ���̐ݒ菈��
//============================
void CScreenFrame::SetData(void)
{
	// �X�N���[���̐ݒ菈��
	SetPos(FRAME_POS);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
	SetSize(FRAME_SIZE);			// �T�C�Y�ݒ�
	SetLength();					// �����ݒ�
	SetAngle();						// �����ݒ�

	// ���_���̏�����
	SetVertex();
}

//============================
//��������
//============================
CScreenFrame* CScreenFrame::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CScreenFrame* pScreen = nullptr;	// ��ʂ̘g�̃C���X�^���X�𐶐�

	if (pScreen == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pScreen = new CScreenFrame;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScreen != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScreen->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��ʂ̘g�̃|�C���^��Ԃ�
	return pScreen;
}