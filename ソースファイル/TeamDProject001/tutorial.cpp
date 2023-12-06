//============================================
//
// �`���[�g���A���̃��C������[game.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "tutorial.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"
#include "log.h"

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
#include "game_finish.h"

#include "obstacle_manager.h"
#include "chara_infoUI.h"

#include "answer.h"
#include "explanation.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	static const D3DXVECTOR3 PLAYERUI_POS[MAX_PLAY] =								// �v���C���[UI�̈ʒu
	{
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
	};
	static const int TRANS_COUNT = 80;				// �J�ڃJ�E���g
}

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPause* CTutorial::m_pPause = nullptr;								// �|�[�Y�̏��
CPlayer* CTutorial::m_apPlayer[MAX_PLAY] = {};						// �v���C���[�̏��
CTutorial::STATE CTutorial::m_GameState = CTutorial::STATE_START;	// �`���[�g���A���̐i�s���
int CTutorial::m_nFinishCount = 0;									// �I���J�E���g
CGameFinish* CTutorial::m_pFinish = nullptr;						// �t�B�j�b�V���̏��
CTutorial::TUTORIAL CTutorial::m_Tutorial = TUTORIAL_MOVE;			// �`���[�g���A���̍���
bool CTutorial::m_bPlay = false;									// �`���[�g���A���̃v���C�����ۂ�
CAnswer*  CTutorial::m_pAnswer = nullptr;							// �ԓ����A�N�V����
CExplanation*  CTutorial::m_pExplanation = nullptr;					// ����

// �f�o�b�O��
#ifdef _DEBUG
CEdit* CTutorial::m_pEdit = nullptr;							// �G�f�B�b�g�̏��
bool CTutorial::m_bEdit = false;								// �G�f�B�b�g��
bool CTutorial::m_MultiAction = false;							// �A�g�N���̏��
#endif

//=========================================
// �R���X�g���N�^
//=========================================
CTutorial::CTutorial() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pPause = nullptr;			// �|�[�Y
	m_pFinish = nullptr;		// �t�B�j�b�V��
	m_nFinishCount = 0;			// �I���J�E���g
	m_GameState = STATE_START;	// ���
	m_Tutorial = TUTORIAL_MOVE;
	m_bPlay = false;
	m_pAnswer = nullptr;
	m_pExplanation = nullptr;
	m_MultiAction = false;

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
CTutorial::~CTutorial()
{

}

//=========================================
//����������
//=========================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// ���b�V���̓ǂݍ��ݏ���
	//CMesh::TxtSet();

	// �}�b�v�̏������[�h����
	//CManager::Get()->GetFile()->Load(CFile::TYPE_OBSTACLE);
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

	CObstacle *pObstacle = NULL;

	// �����o�̐�������
	CObstacle::Create(D3DXVECTOR3(-600.0f, 0.0f, -400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);
	CObstacle::Create(D3DXVECTOR3(600.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);

	// �Ђ��̐�������
	CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_HIMO);

	// �X�s�[�J�[�̐�������
	pObstacle = CObstacle::Create(D3DXVECTOR3(900.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f));

	pObstacle = CObstacle::Create(D3DXVECTOR3(1000.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));

	// ���[�h�̐�������
	pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_LEASH);

	// ��e�̐�������
	CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, -120.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);

	// ��@�̐�������
	CObstacle::Create(D3DXVECTOR3(0.0f, 200.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_FAN);

	// �R�b�v�̐�������
	CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, 100.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_CUP);
	pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 200.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f), CObstacle::TYPE::TYPE_CUP);
	pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

#endif // _DEBUG

	{ // �L�����̐�������

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
	}

	// ��������
	CGameTime::Create();
	m_pFinish = CGameFinish::Create();

	// �L�����N�^�[UI�̐�������
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		CCharaInfoUI::Create(PLAYERUI_POS[nCnt], nCnt, m_apPlayer[nCnt]->GetType());
	}

	// �l�Y�~�߂�̐���
	CItem::Create(D3DXVECTOR3(0.0f, 0.0f, -700.0f), CItem::TYPE::TYPE_MOUSETRAP);
	CItem::Create(D3DXVECTOR3(400.0f, 0.0f, -700.0f), CItem::TYPE::TYPE_MOUSETRAP);

	//// ����I��UI�𐶐�
	//CWeaponSelectUI::Create();

	// �T�E���h�̍Đ�
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
	m_GameState = STATE_START;		// ���

									// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTutorial::Uninit(void)
{
	// �|�C���^�� NULL �ɂ���
	m_pPause = nullptr;			// �|�[�Y
	m_pFinish = nullptr;		// �t�B�j�b�V��

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// �l�Y�~�̏��
	}

	// �I���J�E���g������������
	m_nFinishCount = 0;

	// �Đ����̃T�E���h�̒�~
	CManager::Get()->GetSound()->Stop();

	if (m_pExplanation != NULL)
	{
		m_pExplanation->Uninit();
		m_pExplanation = NULL;
	}

	if (m_pAnswer != NULL)
	{
		m_pAnswer->Uninit();
		m_pAnswer = NULL;
	}

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CTutorial::Update(void)
{

	// �f�o�b�O��
#ifdef _DEBUG
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

	if (m_bPlay == false)
	{
		//���݂��Ȃ��ꍇ����--------------------------------------------------------------------------
		if (m_pExplanation == NULL)
		{
			m_pExplanation = CExplanation::Create(m_Tutorial);

			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(true);
			}
		}

		if (m_pAnswer == NULL)
		{
			m_pAnswer = CAnswer::Create();
		}

		//�X�V
		if (m_pExplanation != NULL)
		{
			m_pExplanation->Update();
		}

		if (m_pAnswer != NULL)
		{
			m_pAnswer->Update();
		}
	}
	else
	{
		if (m_pAnswer == NULL)
		{
			m_pAnswer = CAnswer::Create();
		}

		if (m_pAnswer != NULL)
		{
			m_pAnswer->Update();
		}

		//�v���C��Ԃւ̈ڍs
		PlayFalse();
	}

	switch (m_GameState)
	{
	case CTutorial::STATE_START:

		// �|�[�Y����
		Pause();

		break;

	case CTutorial::STATE_PLAY:

		// �|�[�Y����
		Pause();

		break;

	case CTutorial::STATE_RAT_WIN:

		// �J�ڏ���
		Transition();

		break;

	case CTutorial::STATE_CAT_WIN:

		// �J�ڏ���
		if (m_pFinish != nullptr)
		{
			m_pFinish->SetFinish(true);
		}
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
void CTutorial::Draw(void)
{
	if (m_pExplanation != NULL)
	{
		m_pExplanation->Draw();
	}

	if (m_pAnswer != NULL)
	{
		m_pAnswer->Draw();
	}
}

//======================================
// �v���C��Ԃւ̈ڍs
//======================================
void CTutorial::PlayTrue(void)
{
	m_bPlay = true;
	
	if (m_pExplanation != NULL)
	{
		m_pExplanation->Uninit();
		m_pExplanation = NULL;
	}
	if (m_pAnswer != NULL)
	{
		m_pAnswer->Uninit();
		m_pAnswer = NULL;
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bPlay = true;

		if (m_Tutorial == CTutorial::TUTORIAL_CAT_KILL)
		{
			if (CTutorial::GetPlayer(nCnt)->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(false);
				CTutorial::GetPlayer(nCnt)->SetRatKill(false);
			}
		}
		else if (m_Tutorial == CTutorial::TUTORIAL_RAT_RESCUE)
		{
			if (CTutorial::GetPlayer(nCnt)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(false);
				CTutorial::GetPlayer(nCnt)->SetRatRescue(false);
			}
		}
		else if (m_Tutorial == CTutorial::TUTORIAL_ACTION)
		{
			CTutorial::GetPlayer(nCnt)->SetTutorial(false);
			CTutorial::GetPlayer(nCnt)->SetUseAction(false);
		}
		else
		{
			CTutorial::GetPlayer(nCnt)->SetTutorial(false);
		}
	}
}

//======================================
// ������Ԃւ̈ڍs
//======================================
void CTutorial::PlayFalse(void)
{
	switch (m_Tutorial)
	{
	case CTutorial::TUTORIAL_MOVE:

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayer[nCnt]->GetBMove() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ATTACK_JAMP:

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayer[nCnt]->GetAttack_Jump() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_CAT_KILL:

		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatKill() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);
						}
					}
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_RAT_RESCUE:

		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatRescue() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);
						}
					}
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ACTION:

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (CTutorial::GetPlayer(nCnt)->GetUseAction() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ITEM_MULTI:

		if (m_MultiAction == true)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					if (m_pAnswer != NULL)
					{
						m_pAnswer->SetAnswer(true, nCnt);
					}
				}
			}
		}

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (CTutorial::GetPlayer(nCnt)->GetItem_MultiAction() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_GIMMICK:
		break;
	case CTutorial::TUTORIAL_LETS_GO:
		break;
	case CTutorial::TUTORIAL_MAX:
		break;
	default:
		break;
	}

	if (m_pAnswer != NULL)
	{
		if (m_pAnswer->GetAnswer(0) == true &&
			m_pAnswer->GetAnswer(1) == true &&
			m_pAnswer->GetAnswer(2) == true &&
			m_pAnswer->GetAnswer(3) == true)
		{
			m_bPlay = false;

			int mTutorialNumber = (int)m_Tutorial;
			mTutorialNumber++;
			m_Tutorial = (TUTORIAL)mTutorialNumber;

			if (m_pAnswer != NULL)
			{
				m_pAnswer->Uninit();
				m_pAnswer = NULL;
			}
		}
	}
}

//======================================
// ���̐ݒ菈��
//======================================
void CTutorial::SetData(const MODE mode)
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
void CTutorial::Pause(void)
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
void CTutorial::Transition(void)
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
CPause* CTutorial::GetPause(void)
{
	// �|�[�Y�̏���Ԃ�
	return m_pPause;
}

//======================================
// �`���[�g���A���̐i�s��Ԃ̐ݒ菈��
//======================================
void CTutorial::SetState(const STATE state)
{
	// �`���[�g���A���̐i�s��Ԃ�ݒ肷��
	m_GameState = state;
}

//======================================
// �`���[�g���A���̐i�s��Ԃ̎擾����
//======================================
CTutorial::STATE CTutorial::GetState(void)
{
	// �`���[�g���A���̐i�s��Ԃ�Ԃ�
	return m_GameState;
}

//======================================
// �v���C���[�̎擾����
//======================================
CPlayer* CTutorial::GetPlayer(const int nID)
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
void CTutorial::DeletePause(void)
{
	// �|�[�Y�̃|�C���^�� NULL �ɂ���
	m_pPause = nullptr;
}

//======================================
// �l�Y�~��NULL������
//======================================
void CTutorial::DeletePlayer(int nIdx)
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
CEdit* CTutorial::GetEdit(void)
{
	// �G�f�B�b�g�̏���Ԃ�
	return m_pEdit;
}

//======================================
// �G�f�B�b�g�󋵂̎擾����
//======================================
bool CTutorial::IsEdit(void)
{
	// �G�f�B�b�g�󋵂�Ԃ�
	return m_bEdit;
}

#endif