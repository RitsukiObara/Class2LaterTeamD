//===========================================
//
// �n�`�u���b�N�̃��C������[block.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "block.h"
#include "block_manager.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CBlock::CBlock() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_collision = COLLISION_SQUARE;	// �����蔻��̎��
	m_rotType = ROTTYPE_FRONT;		// �����̎��
	m_type = TYPE_CARDBOARD;		// ���
	m_vtxMax = NONE_D3DXVECTOR3;	// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;	// �ŏ��l
	m_pPrev = nullptr;				// �O�̂ւ̃|�C���^
	m_pNext = nullptr;				// ���̂ւ̃|�C���^

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CBlockManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CBlock::~CBlock()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetPrev(CBlock* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetNext(CBlock* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
// ����������
//==============================
HRESULT CBlock::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_collision = COLLISION_SQUARE;	// �����蔻��̎��
	m_rotType = ROTTYPE_FRONT;		// �����̎��
	m_type = TYPE_CARDBOARD;		// ���
	m_vtxMax = NONE_D3DXVECTOR3;	// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;	// �ŏ��l

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �I������
//========================================
void CBlock::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CBlockManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
// �I������
//========================================
void CBlock::UninitAll(void)
{
	// ���[�J���ϐ��錾
	CBlock* pObj = nullptr;		// ���݂̃I�u�W�F�N�g�̃|�C���^

	for (int nCnt = 0; nCnt < CObject::PRIORITY_MAX; nCnt++)
	{
		 pObj->GetTop(((CObject::PRIORITY)nCnt));
	}
	Uninit();
}

//=====================================
// �X�V����
//=====================================
void CBlock::Update(void)
{

}

//=====================================
// �`�揈��
//=====================================
void CBlock::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBlock::SetData(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetScale(NONE_SCALE);					// �g�嗦

	// �S�Ă̒l������������
	m_type = type;			// ���
	m_rotType = rotType;	// �����̎��

	switch (m_rotType)
	{
	case CBlock::ROTTYPE_FRONT:		// �O����

		// ������ݒ肷��
		SetRot(NONE_D3DXVECTOR3);

		break;

	case CBlock::ROTTYPE_RIGHT:		// �E����

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

		break;

	case CBlock::ROTTYPE_BACK:		// ������

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

		break;

	case CBlock::ROTTYPE_LEFT:		// ������

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (m_type >= TYPE_MAX)
	{ // �^�C�v�ɂ���ꍇ

		// ��~
		assert(false);
	}
	else
	{ // ��L�ȊO

		// �u���b�N�̎�ނ�ݒ肷��
		SetFileData((CXFile::TYPE)(INIT_BLOCK + m_type));
	}

	if (m_type == TYPE_PENHOLDER ||
		m_type == TYPE_RUBBISH ||
		m_type == TYPE_HEADPHONE)
	{ // ���̐��l�̏ꍇ

		// �~�̓����蔻���ݒ肷��
		m_collision = COLLISION_CIRCLE;
	}
	else
	{ // ��L�ȊO

		// �l�p�̓����蔻���ݒ肷��
		m_collision = COLLISION_SQUARE;

		// �����ɂ��ő�l�E�ŏ��l�̐ݒ菈��
		CollisionSetting();
	}
}

//=====================================
// ��������
//=====================================
CBlock* CBlock::Create(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBlock* pBlock = nullptr;	// �C���X�^���X�𐶐�

	if (pBlock == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �{�𐶐�����
		pBlock = new CBlock;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBlock != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBlock->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBlock->SetData(pos, rotType, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �u���b�N�̃|�C���^��Ԃ�
	return pBlock;
}

//=====================================
// �����蔻��̎�ނ̐ݒ菈��
//=====================================
void CBlock::SetCollision(const COLLISION collsion)
{
	// �����蔻���ݒ肷��
	m_collision = collsion;
}

//=====================================
// �����蔻��̎�ނ̎擾����
//=====================================
CBlock::COLLISION CBlock::GetCollision(void) const
{
	// �����蔻���Ԃ�
	return m_collision;
}

//=====================================
// �����̎�ނ̎擾����
//=====================================
CBlock::ROTTYPE CBlock::GetRotType(void) const
{
	// �����̎�ނ�ݒ肷��
	return m_rotType;
}

//=====================================
// ��ނ̎擾����
//=====================================
CBlock::TYPE CBlock::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=====================================
// �ő�l�̎擾����
//=====================================
D3DXVECTOR3 CBlock::GetVtxMax(void) const
{
	// �ő�l��Ԃ�
	return m_vtxMax;
}

//=====================================
// �ŏ��l�̎擾����
//=====================================
D3DXVECTOR3 CBlock::GetVtxMin(void) const
{
	// �ŏ��l��Ԃ�
	return m_vtxMin;
}

//=====================================
// �����ɂ��ő�l�E�ŏ��l�̐ݒ菈��
//=====================================
void CBlock::CollisionSetting(void)
{
	// �ŏ��l�ƍő�l���擾����
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	switch (m_rotType)
	{
	case CBlock::ROTTYPE_FRONT:		// ����

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = vtxMax;			// �ő�l
		m_vtxMin = vtxMin;			// �ŏ��l

		break;

	case CBlock::ROTTYPE_RIGHT:		// �E

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, vtxMax.x);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.x);

		break;

	case CBlock::ROTTYPE_BACK:		// ���

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);

		break;

	case CBlock::ROTTYPE_LEFT:		// ��

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, -vtxMin.x);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, -vtxMax.x);

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}