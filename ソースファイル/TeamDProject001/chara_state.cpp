//=======================================
//
// �L�����N�^�[�̏�Ԃ̃��C������[chara_state.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "chara_state.h"
#include "texture.h"
#include "useful.h"

#include "game.h"
#include "rat.h"
#include "rat_state.h"

//=======================================
// �}�N����`
//=======================================
#define STUN_SIZE				(D3DXVECTOR3(90.0f, 45.0f, 0.0f))	// �C��A�C�R���̃T�C�Y
#define GHOST_SIZE				(D3DXVECTOR3(80.0f, 20.0f, 0.0f))	// ���S�A�C�R���̃T�C�Y
#define STUNICON_TEXTURE		"data\\TEXTURE\\StunIcon.png"		// �C��A�C�R���̃e�N�X�`��
#define GHOSTICON_TEXTURE		"data\\TEXTURE\\GhostIcon.png"		// ���S�A�C�R���̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CCharaState::CCharaState() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_state = STATE_STUN;	// ���
	m_bDisp = false;		// �`���
}

//=========================
// �f�X�g���N�^
//=========================
CCharaState::~CCharaState()
{

}

//=========================
// ����������
//=========================
HRESULT CCharaState::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_state = STATE_STUN;	// ���
	m_bDisp = false;		// �`���

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CCharaState::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CCharaState::Update(void)
{
	// ��ԏ���
	State();
}

//=========================
// �`�揈��
//=========================
void CCharaState::Draw(void)
{
	if (m_bDisp == true)
	{ // �`��󋵂� true �̏ꍇ

		// �`�揈��
		CObject2D::Draw();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CCharaState::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(STUN_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(STUNICON_TEXTURE));

	// ���_���̏�����
	SetVertex();

	// �S�Ă̒l��ݒ肷��
	m_state = STATE_NONE;	// ���
	m_bDisp = false;		// �`���
}

//=========================
// ��������
//=========================
CCharaState* CCharaState::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCharaState* pCharaImage = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCharaImage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCharaImage = new CCharaState;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCharaImage != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCharaImage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCharaImage->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �L�����N�^�[�摜�̃|�C���^��Ԃ�
	return pCharaImage;
}

//=========================
// ��ԏ���
//=========================
void CCharaState::State(void)
{
	//// �l�Y�~�̃|�C���^��錾����
	//CPlayer* pPlayer = nullptr;

	//for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	//{
	//	// �l�Y�~�̃|�C���^���擾����
	//	pPlayer = CGame::GetPlayer(nCnt);

	//	if (pPlayer != nullptr)
	//	{ // �l�Y�~�� NULL ����Ȃ��ꍇ

	//		if (pPlayer->GetState()->GetState() == CRatState::STATE_STUN &&
	//			m_state != STATE_STUN)
	//		{ // �C���Ԃ̏ꍇ

	//			// �`��󋵂� true �ɂ���
	//			m_bDisp = true;

	//			// �C���Ԃɂ���
	//			m_state = STATE_STUN;

	//			// �e�N�X�`���̊��蓖�ď���
	//			BindTexture(CManager::Get()->GetTexture()->Regist(STUNICON_TEXTURE));

	//			// �T�C�Y��ݒ肷��
	//			SetSize(STUN_SIZE);

	//			// ���_���̐ݒ菈��
	//			SetVertex();
	//		}
	//		else if (pPlayer->GetState()->GetState() == CRatState::STATE_DEATH &&
	//			m_state != STATE_GHOST)
	//		{ // ���S��Ԃ̏ꍇ

	//			// �`��󋵂� true �ɂ���
	//			m_bDisp = true;

	//			// �S�[�X�g��Ԃɂ���
	//			m_state = STATE_GHOST;

	//			// �e�N�X�`���̊��蓖�ď���
	//			BindTexture(CManager::Get()->GetTexture()->Regist(GHOSTICON_TEXTURE));

	//			// �T�C�Y��ݒ肷��
	//			SetSize(GHOST_SIZE);

	//			// ���_���̐ݒ菈��
	//			SetVertex();
	//		}
	//	}
	//}
}