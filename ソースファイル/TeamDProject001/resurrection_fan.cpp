//===========================================
//
// �����Ԃ�̉~�͈̔͂̏���[resurrection_fan.h]
// Author ����������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "resurrection_fan.h"
#include "object3Dfan.h"
#include "model.h"
#include "texture.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CRessrectionFan::CRessrectionFan()
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CRessrectionFan::~CRessrectionFan()
{

}

//==============================
// �����Ԃ�̉~�̏���������
//==============================
HRESULT CRessrectionFan::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �����Ԃ�̉~�̏I������
//========================================
void CRessrectionFan::Uninit(void)
{
	// �I������
	CObject3DFan::Uninit();
}

//=====================================
// �����Ԃ�̉~�̍X�V����
//=====================================
void CRessrectionFan::Update(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=====================================
// �����Ԃ�̉~�̕`�揈��
//=====================================
void CRessrectionFan::Draw(void)
{
	// �`�揈��
	CObject3DFan::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRessrectionFan::SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	//NONE_SCALE						// �g�嗦��ύX���Ȃ��Ƃ��Ƃ��Ɏg��
	// ���̐ݒ菈��

	//==========================================================================
	// 3D�|���S��
	//==========================================================================
	SetPos(pos);					// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetSize(NONE_SCALE);			// �T�C�Y
	SetNumAngle(16);				// �p�x�̑���
	SetRadius(100.0f);				// ���a
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\cheese.jpg"));		// �e�N�X�`���̊��蓖�ď���

	//==========================================================================
	// �A�j���[�V�����n
	//==========================================================================
	//SetPos(�ʒu������);			// �ʒu
	//SetPosOld(�ʒu������);		// �O��̈ʒu
	//SetRot(����������);			// ����
	//SetSize(�T�C�Y������);		// �T�C�Y
	//SetLength(��������);			// ����
	//SetAngle(��������);			// ����
	//BindTexture(CManager::Get()->GetTexture()->Regist(�e�N�X�`���̖��O));		// �e�N�X�`���̊��蓖�ď���

	// �A�j���[�V�����̐ݒ菈��
	//SetAnim(�J�E���g������, �p�^�[����������);

	//// ���_���W�̐ݒ菈��
	//SetVertex();

	// �e�N�X�`���̐ݒ�(�A�j���[�V�����o�[�W����)
	//SetVtxTextureAnim(�A�j���[�V�����̑��p�^�[����������, 0);
}

//=======================================
// ��������
//=======================================
CRessrectionFan* CRessrectionFan::Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRessrectionFan* pRessrectionFan = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pRessrectionFan == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pRessrectionFan = new CRessrectionFan;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRessrectionFan != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ
		
		// ���̐ݒ菈��
		pRessrectionFan->SetData(pos, col);

		// ����������
		if (FAILED(pRessrectionFan->Init()))
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

	// �T���v���̃|�C���^��Ԃ�
	return pRessrectionFan;
}