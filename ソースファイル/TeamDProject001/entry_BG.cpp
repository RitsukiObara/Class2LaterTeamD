//=======================================
//
// �G���g���[�̔w�i����[entry_BG.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_BG.h"

#include "model.h"

//=========================
// �R���X�g���N�^
//=========================
CEntryBG::CEntryBG() : CObject(CObject::TYPE_ENTRYBG, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;			// ���f���̏��
	}
}

//=========================
// �f�X�g���N�^
//=========================
CEntryBG::~CEntryBG()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryBG::Init(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // ���f���̏�� NULL �̏ꍇ

			// ���f���𐶐�����
			m_apModel[nCnt] = new CModel(TYPE_NONE, PRIORITY_BLOCK);
		}
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEntryBG::Uninit(void)
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

//=========================
// �X�V����
//=========================
void CEntryBG::Update(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL ����Ȃ��ꍇ

			// ���f���̍X�V����
			m_apModel[nCnt]->Update();
		}
	}
}

//=========================
// �`�揈��
//=========================
void CEntryBG::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL ����Ȃ��ꍇ

			// ���f���̕`�揈��
			m_apModel[nCnt]->Draw();
		}
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryBG::SetData(void)
{

}

//=========================
// ��������
//=========================
CEntryBG* CEntryBG::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryBG* pEntry = nullptr;		// �G���g���[�̔w�i�̃C���X�^���X�𐶐�

	if (pEntry == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntry = new CEntryBG;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntry != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntry->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntry->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�̔w�i�̃|�C���^��Ԃ�
	return pEntry;
}