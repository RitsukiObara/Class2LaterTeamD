//===========================================
//
// �G�f�B�b�g�̃��C������[edit.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "edit.h"
#include "manager.h"
#include "input.h"
#include "useful.h"

#include "obstacle.h"
#include "obstacle_manager.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define ADJUST_MOVE		(2.0f)		// ��������Ԃ̈ړ���
#define NORMAL_MOVE		(16.0f)		// �ʏ��Ԃ̈ړ���

//==============================
// �R���X�g���N�^
//==============================
CEdit::CEdit() : CModel(CObject::TYPE_EDIT, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE::TYPE_OBSTACLE;			// ���
	m_obstacleType = CObstacle::TYPE_HONEY;	// ��Q���̎��
}

//==============================
// �f�X�g���N�^
//==============================
CEdit::~CEdit()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CEdit::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_type = TYPE::TYPE_OBSTACLE;			// ���
	m_obstacleType = CObstacle::TYPE_HONEY;	// ��Q���̎��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CEdit::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CEdit::Update(void)
{
	switch (m_type)
	{
	case CEdit::TYPE_OBSTACLE:		// ��Q��


		break;

	default:						// ��L�ȊO

		// ��~
		assert(false);

		break;
	}

	// �ړ�����
	Move();

	// �������ړ�����
	Adjust();

	// ��������
	Delete();

	// �ݒu����
	Set();
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CEdit::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CEdit::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(NONE_D3DXVECTOR3);				// �ʒu
	SetPosOld(NONE_D3DXVECTOR3);			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_WOODBLOCK);	// ���f���̏��ݒ�

	// �S�Ă̒l���N���A����
	m_type = TYPE::TYPE_OBSTACLE;		// ���
}

//=======================================
// ��������
//=======================================
CEdit* CEdit::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEdit* pEdit = nullptr;	// �C���X�^���X�𐶐�

	if (pEdit == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pEdit = new CEdit;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEdit != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEdit->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEdit->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �j�Ђ̃|�C���^��Ԃ�
	return pEdit;
}

//=======================================
// �ړ�����
//=======================================
void CEdit::Move(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�L�[�������Ă����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // W�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.z += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // S�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.z -= NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // D�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.x += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.x -= NORMAL_MOVE;
	}

	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=======================================
// ����������
//=======================================
void CEdit::Adjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�L�[�������Ă����ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true)
		{ // W�L�[���������ꍇ

			// �ʒu�����Z����
			pos.z += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true)
		{ // S�L�[���������ꍇ

			// �ʒu�����Z����
			pos.z -= ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
		{ // D�L�[���������ꍇ

			// �ʒu�����Z����
			pos.x += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
		{ // A�L�[���������ꍇ

			// �ʒu�����Z����
			pos.x -= ADJUST_MOVE;
		}

		// �ʒu��ݒ肷��
		SetPos(pos);
	}
}

//=======================================
// �ݒu����
//=======================================
void CEdit::Set(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�L�[���������ꍇ

		switch (m_type)
		{
		case CEdit::TYPE_OBSTACLE:		// ��Q��

			// ��Q���̐�������
			CObstacle::Create(GetPos(), m_obstacleType);

			break;

		default:						// ���

			// ��~
			assert(false);

			break;
		}
	}
}

//=======================================
// ��������
//=======================================
void CEdit::Delete(void)
{
	switch (m_type)
	{
	case CEdit::TYPE_OBSTACLE:		// ��Q��

		// ��Q���̏�������
		DeleteObstacle();

		break;

	default:						// ���

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// ��Q���̏�������
//=======================================
void CEdit::DeleteObstacle(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	CObstacle* pObstacleNext = nullptr;								// ���̏�Q��

	while (pObstacle != nullptr)
	{ // ��Q���� NULL ����Ȃ��ꍇ

		// ���̏�Q����ݒ肷��
		pObstacleNext = pObstacle->GetNext();

		if (useful::RectangleCollisionXY(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
		{ // �I�u�W�F�N�g�̒��ɓ����Ă���ꍇ

			// �I������
			pObstacle->Uninit();
		}

		// ���̏�Q���̃|�C���^��������
		pObstacle = pObstacleNext;
	}
}