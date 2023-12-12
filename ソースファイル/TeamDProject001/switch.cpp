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
#include "model.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CSwitch::CSwitch() : CObject(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// ���f���̏��
	}
	m_bMove = false;					// �ړ���
	m_bBoot = false;					// �N����
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
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // ���f���̏�� NULL �̏ꍇ

			// ���f���̐�������
			m_apModel[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);
		}
	}
	m_bMove = false;					// �ړ���
	m_bBoot = false;					// �N����

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CSwitch::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL ����Ȃ��ꍇ

			// ���f���̏I������
			m_apModel[nCnt]->Uninit();
			m_apModel[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
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
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			// ���f���̕`�揈��
			m_apModel[nCnt]->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSwitch::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// �S�Ă̒l��ݒ肷��
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			// ���̐ݒ菈��
			m_apModel[nCnt]->SetPos(pos);							// �ʒu
			m_apModel[nCnt]->SetPosOld(pos);						// �O��̈ʒu
			m_apModel[nCnt]->SetRot(rot);							// ����
			m_apModel[nCnt]->SetScale(NONE_SCALE);					// �g�嗦
			m_apModel[nCnt]->SetFileData(CXFile::TYPE_TRAPIRON);	// ���f�����
		}
	}
	m_bMove = false;					// �ړ���
	m_bBoot = false;					// �N����
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

//=======================================
// ���f���̎擾����
//=======================================
CModel* CSwitch::GetModel(const TYPE type)
{
	// ���f���̏���Ԃ�
	return m_apModel[type];
}

//=======================================
// �N���󋵂̐ݒ菈��
//=======================================
void CSwitch::SetBoot(const bool bBoot)
{
	// �N���󋵂�ݒ肷��
	m_bBoot = bBoot;
}

//=======================================
// �N���󋵂̎擾����
//=======================================
bool CSwitch::GetBoot(void) const
{
	// �N���󋵂�Ԃ�
	return m_bBoot;
}