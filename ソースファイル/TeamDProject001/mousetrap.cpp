//===========================================
//
// �l�Y�~�߂�̃��C������[mousetrap.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "mousetrap.h"
#include "obstacle.h"
#include "mousetrap_iron.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CMouseTrap::CMouseTrap() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pIron = nullptr;		// �S����
}

//==============================
// �f�X�g���N�^
//==============================
CMouseTrap::~CMouseTrap()
{

}

//==============================
// �l�Y�~�߂�̏���������
//==============================
HRESULT CMouseTrap::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	m_pIron = nullptr;		// �S����

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~�߂�̏I������
//========================================
void CMouseTrap::Uninit(void)
{
	if (m_pIron != nullptr)
	{ // �S������ NULL ����Ȃ��ꍇ

		// �S�����̏I������
		m_pIron->Uninit();
		m_pIron = nullptr;
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �l�Y�~�߂�̍X�V����
//=====================================
void CMouseTrap::Update(void)
{
	if (m_pIron != nullptr)
	{ // �S������ NULL ����Ȃ��ꍇ

		// �S�����̍X�V����
		m_pIron->Update();
	}
}

//=====================================
// �l�Y�~�߂�̕`�揈��
//=====================================
void CMouseTrap::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	if (m_pIron != nullptr)
	{ // �S������ NULL ����Ȃ��ꍇ

		// �S�����̕`�揈��
		m_pIron->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CMouseTrap::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, type);

	// �S�Ă̒l���N���A����
	if (m_pIron == nullptr)
	{ // �S������ NULL �̏ꍇ

		// �S�����𐶐�
		m_pIron = CTrapIron::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z));
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CMouseTrap::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CMouseTrap::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CObstacle::COLLTYPE type)
{
	// false ��Ԃ�
	return false;
}