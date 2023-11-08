//===========================================
//
// ��Q���̃��C������[obstacle.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "obstacle.h"
#include "obstacle_manager.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CObstacle::CObstacle() : CModel(CObject::TYPE_WOODBLOCK, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE_WOODBLOCK;	// ���
	m_pPrev = nullptr;			// �O�̂ւ̃|�C���^
	m_pNext = nullptr;			// ���̂ւ̃|�C���^

	if (CObstacleManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CObstacleManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CObstacle::~CObstacle()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CObstacle::SetPrev(CObstacle* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CObstacle::SetNext(CObstacle* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CObstacle* CObstacle::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CObstacle* CObstacle::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CObstacle::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_type = TYPE_WOODBLOCK;	// ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CObstacle::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CObstacleManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CObstacleManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CObstacle::Update(void)
{
	
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CObstacle::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CObstacle::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_WOODBLOCK);	// ���f���̏��ݒ�

	// �S�Ă̒l������������
	m_type = TYPE_WOODBLOCK;	// ���
}

//=======================================
// ��������
//=======================================
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CObstacle* pFrac = nullptr;	// �C���X�^���X�𐶐�

	if (pFrac == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pFrac = new CObstacle;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFrac != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pFrac->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pFrac->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �j�Ђ̃|�C���^��Ԃ�
	return pFrac;
}

//=======================================
// ��ނ̐ݒ菈��
//=======================================
void CObstacle::SetType(const TYPE type)
{
	// ��ނ�ݒ肷��
	m_type = type;
}

//=======================================
// ��ނ̎擾����
//=======================================
CObstacle::TYPE CObstacle::GetType(void)
{
	// ��ނ�Ԃ�
	return m_type;
}