//===========================================
//
// �J�[�e���̏���[curtain.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "curtain.h"
#include "useful.h"
#include "input.h"
#include "collision.h"

#include "switch.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	static const D3DXVECTOR3 SWITCH_POS[MAX_SWITCH] =		// �X�C�b�`�̈ʒu
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
	};
	static const D3DXVECTOR3 SWITCH_ROT[MAX_SWITCH] =		// �X�C�b�`�̌���
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
	};
	static const float CLOSE_SCALE = 0.03f;					// ������Ԃ̊g�嗦
	static const float SCALE_CORRECT = 0.01f;				// �g�嗦�̕␳��
	static const float OPEN_SCALE = 1.0f;					// �J������Ԃ̊g�嗦
}

//==============================
// �R���X�g���N�^
//==============================
CCurtain::CCurtain() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// �X�C�b�`�̏��
	}
	m_state = STATE_CLOSE;				// ���
	m_fVtxMinZ = 0.0f;					// Z���̍ŏ��l
	SetCatUse(false);					// �l�R�̎g�p����
	SetRatUse(true);					// �l�Y�~�̎g�p����
}

//==============================
// �f�X�g���N�^
//==============================
CCurtain::~CCurtain()
{

}

//==============================
// �J�[�e���̏���������
//==============================
HRESULT CCurtain::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// ���f���̏��
	}
	m_state = STATE_CLOSE;				// ���
	m_fVtxMinZ = 0.0f;					// Z���̍ŏ��l

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �J�[�e���̏I������
//========================================
void CCurtain::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̏I������
			m_apSwitch[nCnt]->Uninit();
			m_apSwitch[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �J�[�e���̍X�V����
//=====================================
void CCurtain::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// ��ԃ}�l�[�W���[
	StateManager();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̍X�V����
			m_apSwitch[nCnt]->Update();
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�L�[���������ꍇ

		// ��Ԃ�ݒ肷��
		m_state = (STATE)((m_state + 1) % STATE_MAX);
	}
}

//=====================================
// �J�[�e���̕`�揈��
//=====================================
void CCurtain::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̕`�揈��
			m_apSwitch[nCnt]->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCurtain::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �g�嗦������������
	SetScale(D3DXVECTOR3(1.0f, 1.0f, CLOSE_SCALE));

	// �S�Ă̒l��ݒ肷��
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̐�������
			m_apSwitch[nCnt] = CSwitch::Create(SWITCH_POS[nCnt], SWITCH_ROT[nCnt]);
		}
	}
	m_state = STATE_CLOSE;			// ���
	m_fVtxMinZ = GetFileData().vtxMin.z * GetScale().z;		// Z���̍ŏ��l
}

//=====================================
// �����蔻�菈��
//=====================================
bool CCurtain::Collision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	D3DXVECTOR3 objMin = GetFileData().vtxMin;							// �J�[�e���̍ŏ��l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);	// �ŏ��l
	D3DXVECTOR3 vtxMax = collSize;										// �ő�l

	// �J�[�e���̍ŏ��l(Z��)��ݒ肷��
	objMin.z = GetFileData().vtxMin.z * GetScale().z;

	// �Z�ʑ̂̓����蔻��
	if (collision::HexahedronCollision
	(
		pos,
		GetPos(),
		posOld,
		GetPosOld(),
		vtxMin,
		objMin,
		vtxMax,
		GetFileData().vtxMax
		) == true)
	{ // ���������ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �~�̃q�b�g����
//=====================================
bool CCurtain::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CCurtain::Action(void)
{

}

//=====================================
// ��ԃ}�l�[�W���[
//=====================================
void CCurtain::StateManager(void)
{
	// �g�嗦���擾����
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CCurtain::STATE_CLOSE:		// ������

		// �ϓ��ȕ␳����
		useful::FrameCorrect(CLOSE_SCALE, &scale.z, SCALE_CORRECT);

		break;

	case CCurtain::STATE_OPEN:		// �J�������

		// �ϓ��ȕ␳����
		useful::FrameCorrect(OPEN_SCALE, &scale.z, SCALE_CORRECT);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �g�嗦��K�p����
	SetScale(scale);
}