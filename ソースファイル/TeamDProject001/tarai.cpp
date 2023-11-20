//===========================================
//
// ���Ԃ̃��C������[tarai.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "tarai.h"
#include "useful.h"
#include "Himo.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GEAR_CYCLE_SPEED		(0.1f)		// ��鑬�x

//==============================
// �R���X�g���N�^
//==============================
CTarai::CTarai() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_move = NONE_D3DXVECTOR3;
	m_nIndex = -1;
}

//==============================
// �f�X�g���N�^
//==============================
CTarai::~CTarai()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CTarai::Init(void)
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
// �j�Ђ̏I������
//========================================
void CTarai::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CTarai::Update(void)
{
	// �������擾����
	D3DXVECTOR3 pos = GetPos();

	// ���������Z����
	m_move.y -= 0.98f;

	if (pos.y < 0.0f)
	{
		//m_move.y = 0.0f;
		//m_move.y = -m_move.y * 0.5f;

		CHimo::NULLTarai(m_nIndex);
		Uninit();
		return;
	}

	pos.y += m_move.y;

	// ������ݒ肷��
	SetPos(pos);
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CTarai::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTarai::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CXFile::TYPE_TARAI);		// ���f�����
}

//=======================================
// ��������
//=======================================
CTarai* CTarai::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTarai* pTarai = nullptr;	// �C���X�^���X�𐶐�

	if (pTarai == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pTarai = new CTarai;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTarai != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pTarai->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTarai->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���炢�̃M�A�̃|�C���^��Ԃ�
	return pTarai;
}