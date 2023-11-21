//===========================================
//
// �A�C�e���̃��C������[item.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "item.h"
#include "item_manager.h"

//==============================
// �R���X�g���N�^
//==============================
CItem::CItem() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;				// �O�̂ւ̃|�C���^
	m_pNext = nullptr;				// ���̂ւ̃|�C���^

	if (CItemManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CItemManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CItem::~CItem()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CItem::SetPrev(CItem* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CItem::SetNext(CItem* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CItem* CItem::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CItem* CItem::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
// ����������
//==============================
HRESULT CItem::Init(void)
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
// �I������
//========================================
void CItem::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CItemManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CItemManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// �X�V����
//=====================================
void CItem::Update(void)
{

}

//=====================================
// �`�揈��
//=====================================
void CItem::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CItem::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_TRAPITEM);		// ���f���̏��
}

//=====================================
// ��������
//=====================================
CItem* CItem::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CItem* pItem = nullptr;	// �C���X�^���X�𐶐�

	if (pItem == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �{�𐶐�����
		pItem = new CItem;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pItem != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pItem->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pItem->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �A�C�e���̃|�C���^��Ԃ�
	return pItem;
}