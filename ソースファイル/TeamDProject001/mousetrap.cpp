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
#include "danger_mark.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define IRON_SHIFT			(10.0f)		// �S�����̂��炷�ʒu
#define DANGER_SHIFT		(200.0f)	// �댯�}�[�N�̂��炷�ʒu

//==============================
// �R���X�g���N�^
//==============================
CMouseTrap::CMouseTrap() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pIron = nullptr;			// �S����
	m_pMark = nullptr;			// �댯�}�[�N�̏��
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
	m_pIron = nullptr;			// �S����
	m_pMark = nullptr;			// �댯�}�[�N�̏��

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

	if (m_pMark != nullptr)
	{ // �}�[�N�� NULL ����Ȃ��ꍇ

		// �}�[�N�̏I������
		m_pMark->Uninit();
		m_pMark = nullptr;
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

		// �S�����̈ʒu�ݒ菈��
		IronPosSet();

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

	// �S�Ă̒l��ݒ肷��
	if (m_pIron == nullptr)
	{ // �S������ NULL �̏ꍇ

		// �S�����𐶐�
		m_pIron = CTrapIron::Create(D3DXVECTOR3(pos.x, pos.y + IRON_SHIFT, pos.z));
	}

	if (m_pMark == nullptr)
	{ // �}�[�N�� NULL �̏ꍇ

		// �댯�}�[�N�̐���
		m_pMark = CDangerMark::Create(D3DXVECTOR3(pos.x, pos.y + DANGER_SHIFT, pos.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CMouseTrap::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CMouseTrap::Hit(const D3DXVECTOR3& pos, const float fWidth, const float fHeight, const float fDepth, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CMouseTrap::Action(void)
{

}

//=====================================
// �S�����̈ʒu�̐ݒ菈��
//=====================================
void CMouseTrap::IronPosSet(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();					// �ʒu���擾����
	D3DXVECTOR3 posIron = NONE_D3DXVECTOR3;		// �S�̕���

	// �S�̕����̈ʒu��ݒ肷��
	posIron.x = pos.x;
	posIron.y = pos.y + IRON_SHIFT;
	posIron.z = pos.z;

	// �ʒu��K�p����
	m_pIron->SetPos(posIron);
}