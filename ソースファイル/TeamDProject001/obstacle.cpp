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

#include "honey.h"
#include "slime.h"
#include "hairball.h"
#include "flowervase.h"
#include "plastic_case.h"
#include "petbottle.h"
#include "toycar.h"
#include "roomba.h"

//==============================
// �R���X�g���N�^
//==============================
CObstacle::CObstacle() : CModel(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CObstacle::CObstacle(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �f�X�g���N�^
//==============================
CObstacle::~CObstacle()
{

}

//==============================
// �R���X�g���N�^�̔�
//==============================
void CObstacle::Box(void)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE_HONEY;	// ���
	m_pPrev = nullptr;		// �O�̂ւ̃|�C���^
	m_pNext = nullptr;		// ���̂ւ̃|�C���^

	if (CObstacleManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CObstacleManager::Get()->Regist(this);
	}
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
	m_type = TYPE_HONEY;	// ���

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
void CObstacle::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData((CXFile::TYPE)(INIT_OBSTACLE + type));	// ���f�����

	// �S�Ă̒l������������
	m_type = type;		// ���
}

//=======================================
// ��������
//=======================================
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CObstacle* pObstacle = nullptr;	// �C���X�^���X�𐶐�

	if (pObstacle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case CObstacle::TYPE_HONEY:

			// �I���𐶐�����
			pObstacle = new CHoney;

			break;

		case CObstacle::TYPE_SLIME:

			// �X���C���𐶐�����
			pObstacle = new CSlime;

			break;

		case CObstacle::TYPE_HAIRBALL:

			// �{�𐶐�����
			pObstacle = new CHairBall;

			break;

		case CObstacle::TYPE_FLOWERVASE:

			// �ԕr�𐶐�����
			pObstacle = new CFlowerVase;

			break;
			
		case CObstacle::TYPE_PLASTICCASE:

			// �v���X�`�b�N�P�[�X�𐶐�����
			pObstacle = new CPlasticCase;

			break;

		case CObstacle::TYPE::TYPE_PETBOTTLE:

			//�y�b�g�{�g���𐶐�����
			pObstacle = new CPetbottle;

			break;

		case CObstacle::TYPE_TOYCAR:

			// ��������̎Ԃ𐶐�����
			pObstacle = new CToyCar;

			break;

		case CObstacle::TYPE_ROOMBA:

			// �����o�𐶐�����
			pObstacle = new CRoomba;

			break;

		default:

			//��~
			assert(false);

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pObstacle != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pObstacle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pObstacle->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��Q���̃|�C���^��Ԃ�
	return pObstacle;
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