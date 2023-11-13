//=======================================
//
// �v���C���[��ID�\���̃��C������[player_idUI.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "player_idUI.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define PLAYER_ID_PATTERN	((float)(1.0f / 3.0f))					// �v���C���[��ID��1�ʂ��Ƃ̃T�C�Y
#define PLAYER_ID_SIZE		(D3DXVECTOR3(100.0f, 50.0f, 0.0f))		// �v���C���[��ID�\���̃T�C�Y
#define PLAYER_ID_TEXTURE	"data\\TEXTURE\\Rank.png"				// �v���C���[��ID�\���̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CPlayerID::CPlayerID() : CBillboard(CObject::TYPE_PLAYERID, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
}

//=========================
// �f�X�g���N�^
//=========================
CPlayerID::~CPlayerID()
{

}

//=========================
// ����������
//=========================
HRESULT CPlayerID::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CPlayerID::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CPlayerID::Update(void)
{
	// ���_���̏�����
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CPlayerID::Draw(void)
{
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

//=========================
// ���̐ݒ菈��
//=========================
void CPlayerID::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetPosOld(pos);				// �O��̈ʒu�ݒ�
	SetSize(PLAYER_ID_SIZE);	// �T�C�Y�ݒ�

	// �S�Ă̒l��ݒ肷��

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxAnim(PLAYER_ID_PATTERN, nID);

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(PLAYER_ID_TEXTURE));
}

//=========================
// ��������
//=========================
CPlayerID* CPlayerID::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPlayerID* pPlayerID = nullptr;	// �v���C���[��ID�\���̃C���X�^���X�𐶐�

	if (pPlayerID == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pPlayerID = new CPlayerID;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPlayerID != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPlayerID->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPlayerID->SetData(pos, nID);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[��ID�\���̃|�C���^��Ԃ�
	return pPlayerID;
}