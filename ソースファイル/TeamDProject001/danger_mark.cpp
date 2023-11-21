//=======================================
//
// �댯�}�[�N�̃��C������[danger_mark.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "danger_mark.h"
#include "renderer.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================

//=========================
// �R���X�g���N�^
//=========================
CDangerMark::CDangerMark() : CBillboard(CObject::TYPE_DANGERMARK, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_col = NONE_D3DXCOLOR;			// �F
	m_bDisp = true;					// �`���
}

//=========================
// �f�X�g���N�^
//=========================
CDangerMark::~CDangerMark()
{

}

//=========================
// ����������
//=========================
HRESULT CDangerMark::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_col = NONE_D3DXCOLOR;			// �F
	m_bDisp = true;					// �`���

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CDangerMark::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CDangerMark::Update(void)
{
	
}

//=========================
// �`�揈��
//=========================
void CDangerMark::Draw(void)
{
	if (m_bDisp == true)
	{ // �`��󋵂� true �̏ꍇ

		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �`�揈��
		CBillboard::DrawLightOff();

		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CDangerMark::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);	// �ʒu
	SetPosOld(pos);	// �O��̈ʒu
	SetSize(size);	// �T�C�Y

	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_col = col;					// �F
	m_bDisp = true;					// �`���

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\danger001.png"));

	// ���_���̏�����
	SetVertex();

	// �F�̐ݒ菈��
	SetVtxColor(m_col);
}

//=========================
// ��������
//=========================
CDangerMark* CDangerMark::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CDangerMark* pDanger = nullptr;		// �댯�}�[�N�̃C���X�^���X�𐶐�

	if (pDanger == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pDanger = new CDangerMark;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pDanger != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pDanger->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pDanger->SetData(pos, size, col);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �댯�}�[�N�̃|�C���^��Ԃ�
	return pDanger;
}