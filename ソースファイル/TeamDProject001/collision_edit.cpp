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
#include "file.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define NORMAL_MOVE			(10.0f)		// �ʏ�̈ړ���
#define ADJUST_MOVE			(1.0f)		// ���������̈ړ���
#define SCALE_MOVE			(0.01f)		// �g�嗦�̈ړ���

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
// �����蔻��G�f�B�b�g�̏���������
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
// �����蔻��G�f�B�b�g�̏I������
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
// �����蔻��G�f�B�b�g�̍X�V����
//=====================================
void CCollisionEdit::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) != true)
	{ // ��CTRL�L�[�������Ă��Ȃ��ꍇ

		// �ړ�����
		Move();

		// ����������
		Adjust();

		// �C���f�b�N�X�؂�ւ�����
		IdxChange();

		// �ʒu�̃��Z�b�g����
		PosReset();

		// �����̐ݒ菈��
		NumSet();

		// �g�k����
		Scaling();

		// �g�k����������
		ScalingAdjust();

		// �Z�[�u����
		Save();
	}

	// �f�o�b�O���b�Z�[�W
	CManager::Get()->GetDebugProc()->Print("�����蔻��̑����F%d\n���݂̓����蔻��F%d\n�ʒu�F%f %f %f\n�g�嗦�F%f %f %f\n��SHIFT�L�[�F������\nW/S�L�[�FZ���ړ�\nA/D�L�[�FX���ړ�\n��/���L�[�FY���ړ�\n"
		"SPACE�L�[�F�C���f�b�N�X�̐؂�ւ�\n1�L�[�F���_�ւƖ߂�\n9�L�[�F�����̉��Z\n8�L�[�F�����̌��Z\n"
		"X���̊g�k�FT/B\nY���̊g�k�FY/N\nZ���̊g�k�FU/M\n"
		, m_nNumColl, m_nIdx, m_apModel[m_nIdx]->GetPos().x, m_apModel[m_nIdx]->GetPos().y, m_apModel[m_nIdx]->GetPos().z,
		m_apModel[m_nIdx]->GetScale().x, m_apModel[m_nIdx]->GetScale().y, m_apModel[m_nIdx]->GetScale().z);
}

//=====================================
// �����蔻��G�f�B�b�g�̕`�揈��
//=====================================
void CCollisionEdit::Draw(void)
{
	for (int nCnt = 0; nCnt < m_nNumColl; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			if (nCnt == m_nIdx)
			{ // ���ݑI�𒆂̓����蔻��̏ꍇ

				// �ʏ�`�揈��
				m_apModel[nCnt]->Draw(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f));
			}
			else
			{ // ��L�ȊO

				// �ʏ�`�揈��
				m_apModel[nCnt]->Draw(0.5f);
			}
		}
	}
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
		m_apModel[m_nIdx] = new CModel(TYPE_NONE, PRIORITY_UI);

		// ���̐ݒ菈��
		m_apModel[m_nIdx]->SetPos(pos);							// �ʒu
		m_apModel[m_nIdx]->SetPosOld(pos);						// �O��̈ʒu
		m_apModel[m_nIdx]->SetRot(NONE_D3DXVECTOR3);			// ����
		m_apModel[m_nIdx]->SetScale(NONE_SCALE);				// �g�嗦
		m_apModel[m_nIdx]->SetFileData(CXFile::TYPE_COLLISION);	// ���f���̏��ݒ�
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

	// �����蔻��G�f�B�b�g�̃|�C���^��Ԃ�
	return pEdit;
}

//=======================================
// ���f���̏��̎擾����
//=======================================
CModel* CCollisionEdit::GetModel(const int nNum) const
{
	// ���f���̏���Ԃ�
	return m_apModel[nNum];
}

//=======================================
// �����ʒu�̎擾����
//=======================================
D3DXVECTOR3 CCollisionEdit::GetPosInit(void) const
{
	// �����ʒu��Ԃ�
	return m_posInit;
}

//=======================================
// �����̎擾����
//=======================================
int CCollisionEdit::GetNumColl(void) const
{
	// ������Ԃ�
	return m_nNumColl;
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
// �C���f�b�N�X�̐؂�ւ�����
//=======================================
void CCollisionEdit::IdxChange(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // SPACE�L�[���������ꍇ

		// �C���f�b�N�X��؂�ւ���
		m_nIdx = (m_nIdx + 1) % m_nNumColl;
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

//=======================================
// �����̐ݒ菈��
//=======================================
void CCollisionEdit::NumSet(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
	{ // 9�L�[���������ꍇ

		if (m_nNumColl < MAX_NUMCOLL)
		{ // �����蔻��̐����ő�l�����̏ꍇ

			// ���������Z����
			m_nNumColl++;

			// �����蔻�胂�f���𐶐�����
			m_apModel[m_nNumColl - 1] = new CModel(TYPE_NONE, PRIORITY_UI);

			// ���̐ݒ菈��
			m_apModel[m_nNumColl - 1]->SetPos(m_posInit);					// �ʒu
			m_apModel[m_nNumColl - 1]->SetPosOld(m_posInit);				// �O��̈ʒu
			m_apModel[m_nNumColl - 1]->SetRot(NONE_D3DXVECTOR3);			// ����
			m_apModel[m_nNumColl - 1]->SetScale(NONE_SCALE);				// �g�嗦
			m_apModel[m_nNumColl - 1]->SetFileData(CXFile::TYPE_COLLISION);	// ���f���̏��ݒ�
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_8) == true)
	{ // 8�L�[���������ꍇ

		if (m_nNumColl > MIN_NUMCOLL)
		{ // �����蔻��̐����ő�l�����̏ꍇ

			// ���������Z����
			m_nNumColl--;

			// �I������
			m_apModel[m_nNumColl]->Uninit();
			m_apModel[m_nNumColl] = nullptr;

			// ���݂̃C���f�b�N�X��ݒ肷��
			m_nIdx = m_nNumColl - 1;
		}
	}
}

//=======================================
// �g�k����
//=======================================
void CCollisionEdit::Scaling(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�܂��́A��CTRL�L�[�������Ă����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	// �g�嗦���擾����
	D3DXVECTOR3 scale = m_apModel[m_nIdx]->GetScale();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_T) == true)
	{ // T�L�[���������ꍇ

		// X�����g�傷��
		scale.x += SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_B) == true)
	{ // B�L�[���������ꍇ

		// X�����k������
		scale.x -= SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_Y) == true)
	{ // Y�L�[���������ꍇ

		// Y�����g�傷��
		scale.y += SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_N) == true)
	{ // N�L�[���������ꍇ

		// Y�����k������
		scale.y -= SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_U) == true)
	{ // U�L�[���������ꍇ

		// Z�����g�傷��
		scale.z += SCALE_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_M) == true)
	{ // M�L�[���������ꍇ

		// Z�����k������
		scale.z -= SCALE_MOVE;
	}

	// �g�嗦��K�p����
	m_apModel[m_nIdx]->SetScale(scale);
}

//=======================================
// �g�k����������
//=======================================
void CCollisionEdit::ScalingAdjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�܂��́A��CTRL�L�[�������Ă����ꍇ

		// �g�嗦���擾����
		D3DXVECTOR3 scale = m_apModel[m_nIdx]->GetScale();

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_T) == true)
		{ // T�L�[���������ꍇ

			// X�����g�傷��
			scale.x += SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_B) == true)
		{ // B�L�[���������ꍇ

			// X�����k������
			scale.x -= SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_Y) == true)
		{ // Y�L�[���������ꍇ

			// Y�����g�傷��
			scale.y += SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_N) == true)
		{ // N�L�[���������ꍇ

			// Y�����k������
			scale.y -= SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_U) == true)
		{ // U�L�[���������ꍇ

			// Z�����g�傷��
			scale.z += SCALE_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_M) == true)
		{ // M�L�[���������ꍇ

			// Z�����k������
			scale.z -= SCALE_MOVE;
		}

		// �g�嗦��K�p����
		m_apModel[m_nIdx]->SetScale(scale);
	}
}

//=======================================
// �Z�[�u����
//=======================================
void CCollisionEdit::Save(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�L�[���������ꍇ

		// �����蔻��̃Z�[�u����
		CManager::Get()->GetFile()->Save(CFile::TYPE_COLLISION);
	}
}