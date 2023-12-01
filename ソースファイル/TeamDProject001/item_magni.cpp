//============================================
//
// �A�C�e���̎����Ă��鐔����[item_magni.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "item_magni.h"
#include "texture.h"
#include "useful.h"

#include "object2D.h"
#include "number.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAGNI_TEXTURE		"data\\TEXTURE\\Magni.png"			// �~�}�[�N�̃e�N�X�`��
#define NUMBER_TEXTURE		"data\\TEXTURE\\Number.png"			// �����̃e�N�X�`��
#define MAGNI_SIZE			(D3DXVECTOR3(10.0f, 10.0f, 0.0f))	// �~�}�[�N�̃T�C�Y
#define NUMBER_SIZE			(D3DXVECTOR3(10.0f, 20.0f, 0.0f))	// �����̃T�C�Y

//========================
// �R���X�g���N�^
//========================
CItemMagni::CItemMagni() : CObject(TYPE_CHARAINFO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pMagni = nullptr;
	m_pNumber = nullptr;
}

//========================
// �f�X�g���N�^
//========================
CItemMagni::~CItemMagni()
{

}

//========================
// ����������
//========================
HRESULT CItemMagni::Init(void)
{
	if (m_pMagni == nullptr)
	{ // �~�}�[�N�� NULL ����Ȃ��ꍇ

		// �~�}�[�N�𐶐�����
		m_pMagni = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pNumber == nullptr)
	{ // ������ NULL ����Ȃ��ꍇ

		// �����𐶐�����
		m_pNumber = new CNumber(TYPE_NONE, PRIORITY_UI);

		if (m_pNumber != nullptr)
		{ // ������ NULL ����Ȃ��ꍇ
			
			if (FAILED(m_pNumber->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CItemMagni::Uninit(void)
{
	if (m_pMagni != nullptr)
	{ // �~�}�[�N�� NULL ����Ȃ��ꍇ

		// �~�}�[�N�̏I������
		m_pMagni->Uninit();
		m_pMagni = nullptr;
	}

	if (m_pNumber != nullptr)
	{ // ������ NULL ����Ȃ��ꍇ

		// �����̏I������
		m_pNumber->Uninit();
		m_pNumber = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//========================
// �X�V����
//========================
void CItemMagni::Update(void)
{

}

//========================
// �`�揈��
//========================
void CItemMagni::Draw(void)
{
	if (m_pMagni != nullptr)
	{ // �~�}�[�N�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pMagni->Draw();
	}

	if (m_pNumber != nullptr)
	{ // ������ NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pNumber->Draw();
	}
}

//========================
// ���̐ݒ菈��
//========================
void CItemMagni::SetData(const D3DXVECTOR3& pos, const int nNum)
{
	if (m_pMagni != nullptr)
	{ // �~�}�[�N�� NULL ����Ȃ��ꍇ

		// ����ݒ肷��
		m_pMagni->SetPos(pos);					// �ʒu
		m_pMagni->SetPosOld(pos);				// �O��̈ʒu
		m_pMagni->SetRot(NONE_D3DXVECTOR3);		// ����
		m_pMagni->SetSize(MAGNI_SIZE);			// �T�C�Y
		m_pMagni->SetAngle();					// ����
		m_pMagni->SetLength();					// ����

		// �e�N�X�`���̊��蓖�ď���
		m_pMagni->BindTexture(CManager::Get()->GetTexture()->Regist(MAGNI_TEXTURE));

		// ���_���W�̐ݒ菈��
		m_pMagni->SetVertex();
	}

	if (m_pNumber != nullptr)
	{ // ������ NULL ����Ȃ��ꍇ

		// ����ݒ肷��
		m_pNumber->SetPos(pos);						// �ʒu
		m_pNumber->SetPosOld(pos);					// �O��̈ʒu
		m_pNumber->SetRot(NONE_D3DXVECTOR3);		// ����
		m_pNumber->SetSize(NUMBER_SIZE);			// �T�C�Y
		m_pNumber->SetAngle();						// ����
		m_pNumber->SetLength();						// ����

		m_pNumber->SetNumber(nNum);					// ����
		m_pNumber->SetType(CNumber::TYPE_DECIMAL);	// ���

		// �e�N�X�`���̊��蓖�ď���
		m_pNumber->BindTexture(CManager::Get()->GetTexture()->Regist(NUMBER_TEXTURE));

		// ���_���W�̐ݒ菈��
		m_pNumber->SetVertex();

		// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
		m_pNumber->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, nNum);
	}
}

//========================
// ��������
//========================
CItemMagni* CItemMagni::Create(const D3DXVECTOR3& pos, const int nNum)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CItemMagni* pInfoUI = nullptr;		// �L�����N�^�[���UI�̃C���X�^���X�𐶐�

	if (pInfoUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pInfoUI = new CItemMagni;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pInfoUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pInfoUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pInfoUI->SetData(pos, nNum);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �L�����N�^�[�̏��UI�̃|�C���^��Ԃ�
	return pInfoUI;
}