//===========================================
//
// �l�Y�~�߂�̓S�����̃��C������[mousetrap_iron.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "switch.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CSwitch::CSwitch() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// �f�X�g���N�^
//==============================
CSwitch::~CSwitch()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CSwitch::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CSwitch::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CSwitch::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CSwitch::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSwitch::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(rot);								// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CXFile::TYPE_TRAPIRON);			// ���f�����
}

//=======================================
// ��������
//=======================================
CSwitch* CSwitch::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �X�C�b�`�𐶐�
		pSwitch = new CSwitch;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSwitch != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pSwitch->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSwitch->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �X�C�b�`�̃|�C���^��Ԃ�
	return pSwitch;
}