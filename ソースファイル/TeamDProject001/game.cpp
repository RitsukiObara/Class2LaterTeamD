//============================================
//
// �Q�[���̃��C������[game.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "map.h"
#include "skybox.h"
#include "rat.h"
#include "Cat.h"
#include "game_timer.h"
#include "edit.h"
#include "weapon_selectUI.h"
#include "block.h"
#include "countdown.h"
#include "item.h"
#include "resurrection_fan.h"
#include "player.h"
#include "entry.h"

#include "obstacle_manager.h"
#include "chara_infoUI.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define TRANS_COUNT		(80)	// �J�ڃJ�E���g

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// �|�[�Y�̏��
CPlayer* CGame::m_apPlayer[MAX_PLAY] = {};				// �v���C���[�̏��
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// �Q�[���̐i�s���
int CGame::m_nFinishCount = 0;								// �I���J�E���g

// �f�o�b�O��
#ifdef _DEBUG
CEdit* CGame::m_pEdit = nullptr;							// �G�f�B�b�g�̏��
bool CGame::m_bEdit = false;								// �G�f�B�b�g��
#endif

//=========================================
// �R���X�g���N�^
//=========================================
CGame::CGame() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pPause = nullptr;			// �|�[�Y
	m_nFinishCount = 0;			// �I���J�E���g
	m_GameState = STATE_START;	// ���

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// �l�Y�~�̏��
	}

// �f�o�b�O��
#ifdef _DEBUG
	m_pEdit = nullptr;			// �G�f�B�b�g
	m_bEdit = false;			// �G�f�B�b�g��
#endif
}

//=========================================
// �f�X�g���N�^
//=========================================
CGame::~CGame()
{

}

//=========================================
//����������
//=========================================
HRESULT CGame::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// ���b�V���̓ǂݍ��ݏ���
	//CMesh::TxtSet();

	// �}�b�v�̏������[�h����
	CManager::Get()->GetFile()->Load(CFile::TYPE_OBSTACLE);
	CManager::Get()->GetFile()->Load(CFile::TYPE_CARROUTE);
	CManager::Get()->GetFile()->Load(CFile::TYPE_BLOCK);

	// �}�b�v�̐ݒ菈��
	CManager::Get()->GetFile()->SetMap();

	// �J�E���g�_�E���̐�������
	CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(200.0f, 250.0f, 0.0f));

	// ���b�V���̃e�L�X�g�ǂݍ���
	//CMesh::TxtSet();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	//�}�b�v�̐���
	CMap::Create();

#ifdef _DEBUG	//��Q���e�X�g�p

	// �����o�̐�������
	CObstacle::Create(D3DXVECTOR3(-600.0f, 0.0f, -400.0f), CObstacle::TYPE_ROOMBA);

	// �Ђ��̐�������
	CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), CObstacle::TYPE_HIMO);

	// �X�s�[�J�[�̐�������
	CObstacle::Create(D3DXVECTOR3(-250.0f, 200.0f, 900.0f), CObstacle::TYPE_SPEAKER);

	// ���[�h�̐�������
	CObstacle *pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), CObstacle::TYPE_LEASH);
	pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	// ��e�̐�������
	CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, -120.0f), CObstacle::TYPE_PIN);

	// ��@�̐�������
	CObstacle::Create(D3DXVECTOR3(0.0f, 200.0f, 900.0f), CObstacle::TYPE::TYPE_FAN);

	// �R�b�v�̐�������
	CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, 100.0f), CObstacle::TYPE::TYPE_CUP);

#endif // _DEBUG

	// �l�R�̃C���f�b�N�X���擾����
	int nCat = CEntry::GetCatIdx();

	// �l�Y�~�̐���
	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		if (nCntPlay == nCat)
		{ // �l�R�S���̃v���C���[�̏ꍇ

			// �v���C���[�̐���
			m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(500.0f * nCntPlay - 500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_CAT);
		}
		else
		{ // ��L�ȊO

			// �v���C���[�̐���
			m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(500.0f * nCntPlay - 500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_RAT);
		}
	}

	// ��������
	CGameTime::Create();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CCharaInfoUI::Create(D3DXVECTOR3(160.0f + (nCnt * 320.0f), 650.0f, 0.0f), nCnt, m_apPlayer[nCnt]->GetType());
	}

	//// ����I��UI�𐶐�
	//CWeaponSelectUI::Create();

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
	m_GameState = STATE_START;		// ���

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CGame::Uninit(void)
{
	// �|�C���^�� NULL �ɂ���
	m_pPause = nullptr;			// �|�[�Y

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// �l�Y�~�̏��
	}

	// �I���J�E���g������������
	m_nFinishCount = 0;

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CGame::Update(void)
{

// �f�o�b�O��
#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_8) == true)
	{ // 8�L�[���������Ƃ�
		m_GameState = STATE_CAT_WIN;		// �˂��̂���
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
	{ // 9�L�[���������Ƃ�
		m_GameState = STATE_RAT_WIN;		// �˂��݂̂���
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F7) == true)
	{ // F7�L�[���������ꍇ

		// �G�f�B�b�g�󋵂����ւ���
		m_bEdit = m_bEdit ? false : true;

		if (m_bEdit == true)
		{ // �G�f�B�b�g�󋵂� true �̏ꍇ

			if (m_pEdit == nullptr)
			{ // �G�f�B�b�g�󋵂� NULL �̏ꍇ

				// �G�f�B�b�g�̐�������
				m_pEdit = CEdit::Create();
			}
		}
		else
		{ // ��L�ȊO

			if (m_pEdit != nullptr)
			{ // �G�f�B�b�g�󋵂� NULL ����Ȃ��ꍇ

				// �I������
				m_pEdit->Uninit();
				m_pEdit = nullptr;
			}
			else
			{ // ��L�ȊO

				// ��~
				assert(false);
			}
		}
	}

#endif

	switch (m_GameState)
	{
	case CGame::STATE_START:

		// �|�[�Y����
		Pause();

		break;

	case CGame::STATE_PLAY:

		// �|�[�Y����
		Pause();

		break;

	case CGame::STATE_RAT_WIN:

		// �J�ڏ���
		Transition();

		break;

	case CGame::STATE_CAT_WIN:

		// �J�ڏ���
		Transition();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

#ifdef _DEBUG

	if (m_bEdit == true)
	{ // �G�f�B�b�g�󋵂� true �̏ꍇ

		if (m_pEdit != nullptr)
		{ // �G�f�B�b�g�� NULL ����Ȃ��ꍇ

			// �G�f�B�b�g�̍X�V����
			m_pEdit->Update();
		}

		for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
		{
			// ���S���ʏ���
			CObject::DeathDecision(nCnt);
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F9) == true)
		{ // F9�L�[���������ꍇ

			// �����Z�[�u����
			CManager::Get()->GetFile()->Save(CFile::TYPE_OBSTACLE);		// ��Q��
			CManager::Get()->GetFile()->Save(CFile::TYPE_BLOCK);		// �u���b�N
		}
	}
	else
	{ // ��L�ȊO

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // �����_���[�� NULL ����Ȃ��ꍇ

			// �����_���[�̍X�V
			CManager::Get()->GetRenderer()->Update();
		}
	}

#else

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �����_���[�̍X�V
		CManager::Get()->GetRenderer()->Update();
	}

#endif
		
	CManager::Get()->GetDebugProc()->Print("��ԁF%d", m_GameState);
}

//======================================
//�`�揈��
//======================================
void CGame::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CGame::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);

	if (m_pPause == nullptr)
	{ // �|�[�Y�ւ̃|�C���^�� NULL �̏ꍇ

		// �|�[�Y�̐�������
		m_pPause = CPause::Create();
	}

	// �X�^�[�g��Ԃɂ���
	m_GameState = STATE_START;

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
}

//======================================
// �|�[�Y����
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true)
	{ // P�L�[���������ꍇ

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // �t�F�[�h������Ԃ��A�I���ȊO�̏ꍇ

			if (m_pPause->GetPause() == false)
			{ // �|�[�Y�� false �������ꍇ

				// �|�[�Y�󋵂� true �ɂ���
				m_pPause->SetPause(true);
			}
			else
			{ // �|�[�Y�� true �������ꍇ

				// �|�[�Y�󋵂� false �ɂ���
				m_pPause->SetPause(false);
			}

			// ���艹��炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// �J�ڏ���
//======================================
void CGame::Transition(void)
{
	// �I���J�E���g�����Z����
	m_nFinishCount++;

	if (m_nFinishCount % TRANS_COUNT == 0)
	{ // �I���J�E���g����萔�𒴂����ꍇ

		// ���U���g�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// �|�[�Y�̎擾����
//======================================
CPause* CGame::GetPause(void)
{
	// �|�[�Y�̏���Ԃ�
	return m_pPause;
}

//======================================
// �Q�[���̐i�s��Ԃ̐ݒ菈��
//======================================
void CGame::SetState(const STATE state)
{
	// �Q�[���̐i�s��Ԃ�ݒ肷��
	m_GameState = state;
}

//======================================
// �Q�[���̐i�s��Ԃ̎擾����
//======================================
CGame::STATE CGame::GetState(void)
{
	// �Q�[���̐i�s��Ԃ�Ԃ�
	return m_GameState;
}

//======================================
// �v���C���[�̎擾����
//======================================
CPlayer* CGame::GetPlayer(const int nID)
{
	if (nID < MAX_PLAY)
	{ // �C���f�b�N�X����薢���̏ꍇ

		// �v���C���[�̏����擾����
		return m_apPlayer[nID];
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}
}

//======================================
// �|�[�Y��NULL������
//======================================
void CGame::DeletePause(void)
{
	// �|�[�Y�̃|�C���^�� NULL �ɂ���
	m_pPause = nullptr;
}

//======================================
// �l�Y�~��NULL������
//======================================
void CGame::DeletePlayer(int nIdx)
{
	if (nIdx < MAX_PLAY)
	{ // �ԍ����ő吔�����̏ꍇ

		// �v���C���[�̃|�C���^�� NULL �ɂ���
		m_apPlayer[nIdx] = nullptr;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}
}

// �f�o�b�O��
#ifdef _DEBUG
//======================================
// �G�f�B�b�g�̎擾����
//======================================
CEdit* CGame::GetEdit(void)
{
	// �G�f�B�b�g�̏���Ԃ�
	return m_pEdit;
}

//======================================
// �G�f�B�b�g�󋵂̎擾����
//======================================
bool CGame::IsEdit(void)
{
	// �G�f�B�b�g�󋵂�Ԃ�
	return m_bEdit;
}

#endif