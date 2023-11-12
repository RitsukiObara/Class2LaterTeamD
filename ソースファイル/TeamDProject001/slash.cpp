//============================================
//
// �a�����o�̃��C������[slash.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "slash.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define TURN_TEXTURE		"data/TEXTURE/SlashStaging001.png"	// �a�����o�̃e�N�X�`��
#define TURN_COUNT			(2)									// �a�����o�̃J�E���g
#define TURN_PATTERN		(8)									// �a�����o�̃p�^�[����

//===========================================
// �R���X�g���N�^
//===========================================
CSlash::CSlash() : CBillboardAnim(CObject::TYPE_SLASH,CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
	m_nLife = 0;				// ����
}

//===========================================
// �f�X�g���N�^
//===========================================
CSlash::~CSlash()
{

}

//===========================================
// ����������
//===========================================
HRESULT CSlash::Init(void)
{
	if (FAILED(CBillboardAnim::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nLife = 0;				// ����

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CSlash::Uninit(void)
{
	// �I��
	CBillboardAnim::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CSlash::Update(void)
{
	// ���������炷
	m_nLife--;

	// �X�V����
	CBillboardAnim::Update();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxAnim(GetTexPattern(), GetPattern());

	if (m_nLife <= 0)
	{ // �p�^�[�������ő吔�𒴂����ꍇ

		// �I������
		Uninit();
	}
}

//===========================================
// �`�揈��
//===========================================
void CSlash::Draw(void)
{
	// �`�揈��
	CBillboardAnim::DrawLightOff();
}

//===========================================
// �ݒ菈��
//===========================================
void CSlash::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetSize(D3DXVECTOR3(1000.0f, 1000.0f, 0.0f));			// �T�C�Y�ݒ�

	// �A�j���[�V�����̐ݒ菈��
	SetAnim(TURN_COUNT, TURN_PATTERN);

	// �S�Ă̒l������������
	m_nLife = TURN_COUNT * TURN_PATTERN;	// ����

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxAnim(GetTexPattern(), GetPattern());

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TURN_TEXTURE));
}

//===========================================
// ��������
//===========================================
CSlash* CSlash::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSlash* pSlash = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pSlash == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pSlash = new CSlash;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSlash != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pSlash->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSlash->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �a�����o�̃|�C���^��Ԃ�
	return pSlash;
}