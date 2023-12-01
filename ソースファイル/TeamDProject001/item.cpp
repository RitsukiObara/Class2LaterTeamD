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
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define ROT_MOVE		(0.01f)		// �����̈ړ���
#define EXTEND_SCALE	(1.05f)		// �g�厞�̊g�嗦
#define SHRINK_SCALE	(0.95f)		// �g�k���̊g�嗦

//==============================
// �R���X�g���N�^
//==============================
CItem::CItem() : CModel(CObject::TYPE_ITEM, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE_MOUSETRAP;		// ���
	m_fScaleDest = 0.0f;			// �ړI�̊g�嗦
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

	// �S�Ă̒l������������
	m_type = TYPE_MOUSETRAP;	// ���
	m_fScaleDest = 0.0f;		// �ړI�̊g�嗦

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
	// ��]����
	Cycle();

	// �g�k����
	Scaling();
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
void CItem::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_TRAPITEM);		// ���f���̏��

	// �S�Ă̒l��ݒ肷��
	m_type = type;					// ���
	m_fScaleDest = EXTEND_SCALE;	// �ړI�̊g�嗦
}

//=====================================
// ��������
//=====================================
CItem* CItem::Create(const D3DXVECTOR3& pos, const TYPE type)
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
		pItem->SetData(pos, type);
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

//=====================================
// ��ނ̐ݒ菈��
//=====================================
void CItem::SetType(const TYPE type)
{
	// ��ނ�ݒ肷��
	m_type = type;
}

//=====================================
// ��ނ̎擾����
//=====================================
CItem::TYPE CItem::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=====================================
// ��]����
//=====================================
void CItem::Cycle(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();		// �������擾����

	// ���������Z����
	rot.y += ROT_MOVE;

	// ������K�p����
	SetRot(rot);
}

//=====================================
// �g�k����
//=====================================
void CItem::Scaling(void)
{
	// �g�嗦���擾����
	D3DXVECTOR3 scale = GetScale();

	// �g�嗦�̕␳����
	if (useful::FrameCorrect(m_fScaleDest, &scale.x, 0.002f) == true ||
		useful::FrameCorrect(m_fScaleDest, &scale.y, 0.002f) == true ||
		useful::FrameCorrect(m_fScaleDest, &scale.z, 0.002f) == true)
	{ // �ړI�̒l�ɂȂ����ꍇ

		// �ړI�̊g�嗦��ݒ肷��
		m_fScaleDest = (m_fScaleDest >= EXTEND_SCALE) ? SHRINK_SCALE : EXTEND_SCALE;
	}

	// �g�嗦��K�p����
	SetScale(scale);
}