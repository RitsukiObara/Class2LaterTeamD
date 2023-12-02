//===========================================
//
// �����蔻��G�f�B�b�g�̃��C������[collision_edit.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "collision_edit.h"
#include "model.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define NORMAL_MOVE			(10.0f)		// �ʏ�̈ړ���
#define ADJUST_MOVE			(1.0f)		// ���������̈ړ���

//==============================
// �R���X�g���N�^
//==============================
CCollisionEdit::CCollisionEdit() : CObject(CObject::TYPE_EDIT, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_NUMCOLL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// �����蔻��̏��
	}
	m_posInit = NONE_D3DXVECTOR3;		// �����ʒu
	m_nNumColl = MIN_NUMCOLL;			// �����蔻��̑���
	m_nIdx = m_nNumColl - 1;			// �C���f�b�N�X
}

//==============================
// �f�X�g���N�^
//==============================
CCollisionEdit::~CCollisionEdit()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CCollisionEdit::Init(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_NUMCOLL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// �����蔻��̏��
	}
	m_posInit = NONE_D3DXVECTOR3;		// �����ʒu
	m_nNumColl = MIN_NUMCOLL;			// �����蔻��̑���
	m_nIdx = m_nNumColl - 1;			// �C���f�b�N�X

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CCollisionEdit::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_NUMCOLL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL ����Ȃ��ꍇ

			// �����蔻��̏��̏I������
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
void CCollisionEdit::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) != true)
	{ // ��CTRL�L�[�������Ă��Ȃ��ꍇ

		// �ړ�����
		Move();

		// ����������
		Adjust();

		// �ʒu�̃��Z�b�g����
		PosReset();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CCollisionEdit::Draw(void)
{

}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCollisionEdit::SetData(const D3DXVECTOR3& pos)
{
	// �S�Ă̒l��ݒ肷��
	m_posInit = pos;				// �����ʒu
	m_nNumColl = MIN_NUMCOLL;		// �����蔻��̑���
	m_nIdx = m_nNumColl - 1;			// �C���f�b�N�X

	if (m_apModel[m_nIdx] == nullptr)
	{ // 1�ڂ̃��f���� NULL �̏ꍇ

		// �����蔻�胂�f���𐶐�����
		m_apModel[m_nIdx] = CModel::Create();

		// ���̐ݒ菈��
		m_apModel[m_nIdx]->SetPos(pos);							// �ʒu
		m_apModel[m_nIdx]->SetPosOld(pos);						// �O��̈ʒu
		m_apModel[m_nIdx]->SetRot(NONE_D3DXVECTOR3);			// ����
		m_apModel[m_nIdx]->SetScale(NONE_SCALE);				// �g�嗦
		m_apModel[m_nIdx]->SetFileData(CXFile::TYPE_HONEY);		// ���f���̏��ݒ�
	}
}

//=======================================
// ��������
//=======================================
CCollisionEdit* CCollisionEdit::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCollisionEdit* pEdit = nullptr;	// �C���X�^���X�𐶐�

	if (pEdit == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pEdit = new CCollisionEdit;
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
		pEdit->SetData(pos);
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
void CCollisionEdit::Move(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�܂��́A��CTRL�L�[�������Ă����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = m_apModel[m_nIdx]->GetPos();		// �ʒu���擾����

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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_UP) == true)
	{ // ��L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.y += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_DOWN) == true)
	{ // ���L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.y -= NORMAL_MOVE;
	}

	// �ʒu��ݒ肷��
	m_apModel[m_nIdx]->SetPos(pos);
}

//=======================================
// ����������
//=======================================
void CCollisionEdit::Adjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�L�[�������Ă����ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 pos = m_apModel[m_nIdx]->GetPos();		// �ʒu���擾����

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

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_UP) == true)
		{ // ��L�[���������ꍇ

			// �ʒu�����Z����
			pos.y += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_DOWN) == true)
		{ // ���L�[���������ꍇ

			// �ʒu�����Z����
			pos.y -= ADJUST_MOVE;
		}

		// �ʒu��ݒ肷��
		m_apModel[m_nIdx]->SetPos(pos);
	}
}

//=======================================
// �ʒu�̃��Z�b�g����
//=======================================
void CCollisionEdit::PosReset(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1�L�[���������ꍇ

		// �ʒu���擾����
		D3DXVECTOR3 pos = m_apModel[m_nIdx]->GetPos();

		// �ʒu�������ʒu�ɖ߂�
		pos = m_posInit;

		// �ʒu��K�p����
		m_apModel[m_nIdx]->SetPos(pos);
	}
}