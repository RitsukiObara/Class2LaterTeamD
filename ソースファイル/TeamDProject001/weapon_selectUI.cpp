////=======================================
////
//// ����I��UI�̃��C������[weapon_selectUI.cpp]
//// Author ��������
////
////=======================================
//#include "main.h"
//#include "manager.h"
//#include "weapon_selectUI.h"
//#include "object2D.h"
//#include "texture.h"
//
////---------------------------------------
//// �}�N����`
////---------------------------------------
//
//// �ʒu�֌W
//#define WEAPON_POS		(D3DXVECTOR3(540.0f, 300.0f, 0.0f))
//#define WEAPON_SIZE		(D3DXVECTOR3(40.0f))
//#define WEAPON_SHIFT	(D3DXVECTOR3(100.0f ,100.0f, 0.0f))
//
////==========================================
//// �R���X�g���N�^
////==========================================
//CWeaponSelectUI::CWeaponSelectUI() : CObject(TYPE_WEAPONSELECTUI, PRIORITY_PAUSE)
//{
//	// �S�Ă̒l���N���A����
//	m_pScreen = nullptr;		// �X�N���[���̏��
//
//	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
//	{
//		m_apWeapon[nCnt] = nullptr;		// ����̏��
//	}
//}
//
////==========================================
//// �f�X�g���N�^
////==========================================
//CWeaponSelectUI::~CWeaponSelectUI()
//{
//
//}
//
////==========================================
//// �|�[�Y�̏���������
////==========================================
//HRESULT CWeaponSelectUI::Init(void)
//{
//	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
//	{
//		if (m_apWeapon[nCnt] == nullptr)
//		{ // �I�u�W�F�N�g�� NULL �̏ꍇ
//
//			// �|���S���̐�������
//			m_apWeapon[nCnt] = m_apWeapon[nCnt]->Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, PRIORITY_PAUSE);
//
//			// ����ݒ肷��
//			m_apWeapon[nCnt]->SetPos(c_aPauseInfo[nCnt].pos);			// �ʒu
//			m_apWeapon[nCnt]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����
//			m_apWeapon[nCnt]->SetSize(c_aPauseInfo[nCnt].size);			// �T�C�Y
//			m_apWeapon[nCnt]->SetLength();								// ����
//			m_apWeapon[nCnt]->SetAngle();								// ����
//
//			// ���_��ݒ肷��
//			m_apWeapon[nCnt]->SetVertex();
//
//			if (nCnt == POLYGON_BACK)
//			{ // �w�i�|���S���̏ꍇ
//
//				// ���_�J���[��ݒ肷��
//				m_apWeapon[nCnt]->SetVtxColor(PAUSE_BACK_COL);
//			}
//
//			// �e�N�X�`���̊��蓖�ď���
//			m_apWeapon[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(c_apFilename[nCnt]));
//		}
//	}
//
//	// �S�Ă̒l������������
//	m_PauseMenu = MENU_CONTINUE;						// ���j���[
//	m_PauseColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �I�����̐F
//	sizeDest = D3DXVECTOR3(c_aPauseInfo[m_PauseMenu].size.x * SIZEDEST_MAGNI, c_aPauseInfo[m_PauseMenu].size.y * SIZEDEST_MAGNI, 0.0f);			// �ڕW�̃T�C�Y
//	m_nPauseCounter = 0;								// �J�E���^�[
//	m_fPauseAlpha = PAUSE_ALPHA;						// �����x�̕ω���
//	m_bPause = false;									// �|�[�Y��
//	m_bDisp = true;										// �`���
//
//	// ������Ԃ�
//	return S_OK;
//}
//
////========================================
//// �|�[�Y�̏I������
////========================================
//void CWeaponSelectUI::Uninit(void)
//{
//	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
//	{
//		// �I������
//		m_apWeapon[nCnt]->Uninit();
//	}
//
//	// �j������
//	Release();
//
//	// �|�[�Y��NULL������
//	CGame::DeletePause();
//}
//
////========================================
//// �|�[�Y�̍X�V����
////========================================
//void CWeaponSelectUI::Update(void)
//{
//	// �J�E���^�[�����Z����
//	m_nPauseCounter++;
//
//	// �|�[�Y�̑I������
//	PauseSelect();
//
//	// �|�[�Y�̌��菈��
//	if (PauseDecide() == true)
//	{ // �ʂ̃��[�h�ɂȂ����ꍇ
//
//		// ���̐�̏������s��Ȃ�
//		return;
//	}
//
//	if (CManager::Get()->GetFade()->GetFade() != CFade::FADE_NONE &&
//		CManager::Get()->GetFade()->GetFade() != CFade::FADE_IN)
//	{ // �t�F�[�h�A�E�g���Ă���ꍇ
//
//		// �����x�̕ω���ݒ肷��
//		m_fPauseAlpha = DECIDE_ALPHA;
//	}
//
//	// �����x�␳����
//	PauseAlphaCorrect();
//
//	// �I�𒆂̑I�����̓����x��ω�������
//	m_PauseColor.a -= m_fPauseAlpha;
//
//	// ���_�ݒ菈��
//	PauseVertex();
//}
//
////=====================================
//// �|�[�Y�̕`�揈��
////=====================================
//void CWeaponSelectUI::Draw(void)
//{
//// �f�o�b�O�p
//#ifdef _DEBUG
//
//	if (m_bDisp == true)
//	{ // �`��󋵂� true �������ꍇ
//
//		for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
//		{
//			// �`�揈��
//			m_apWeapon[nCnt]->Draw();
//		}
//	}
//
//#else
//
//	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
//	{
//		// �`�揈��
//		m_apWeapon[nCnt]->Draw();
//	}
//
//#endif
//}
//
////=====================================
//// �T�C�Y�␳����
////=====================================
//void CWeaponSelectUI::SizeCorrect(int nIdx)
//{
//	// ���[�J���ϐ��錾
//	D3DXVECTOR3 size = m_apWeapon[nIdx]->GetSize();		// �T�C�Y���擾����
//
//	// �T�C�Y�̕␳
//	useful::Correct(sizeDest.x, &size.x, SIZEDEST_CORRECT_VALUE);
//	useful::Correct(sizeDest.y, &size.y, SIZEDEST_CORRECT_VALUE);
//
//	//�T�C�Y���X�V����
//	m_apWeapon[nIdx]->SetSize(size);
//}
//
////=====================================
//// �|�[�Y�󋵂̐ݒ菈��
////=====================================
//void CWeaponSelectUI::SetPause(const bool bPause)
//{
//	// �|�[�Y�̏󋵂�ݒ肷��
//	m_bPause = bPause;
//
//	if (m_bPause == false)
//	{ // �|�[�Y�� false �̏ꍇ
//
//		// �I�����Ă�����̂��R���e�B�j���[�ɂ���
//		m_PauseMenu = MENU::MENU_CONTINUE;
//	}
//}
//
////=====================================
//// �|�[�Y�󋵂̎擾����
////=====================================
//bool CWeaponSelectUI::GetPause(void)
//{
//	// �|�[�Y�̏󋵂�Ԃ�
//	return m_bPause;
//}
//
////=====================================
//// �`��󋵂̐؂�ւ�����
////=====================================
//void CWeaponSelectUI::ChangeDisp(void)
//{
//	// �`��󋵂�؂�ւ���
//	m_bDisp = m_bDisp ? false : true;
//}
//
////=====================================
//// �|�[�Y�̑I������
////=====================================
//void CWeaponSelectUI::PauseSelect(void)
//{
//	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true ||
//		CManager::Get()->GetInputKeyboard()->GetRepeat(DIK_W, SELECT_REPEAT_COUNT) == true ||
//		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_UP, 0) == true)
//	{ // W�L�[���������ꍇ
//
//		// �|�[�Y�̐ݒ�
//		m_PauseMenu = (MENU)((m_PauseMenu + (MENU_MAX - 1)) % MENU_MAX);
//
//		// �����x�̕ω���ݒ肷��
//		m_fPauseAlpha = PAUSE_ALPHA;
//
//		// �I������炷
//		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
//	}
//
//	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true ||
//		CManager::Get()->GetInputKeyboard()->GetRepeat(DIK_S, SELECT_REPEAT_COUNT) == true ||
//		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_DOWN, 0) == true)
//	{ // S�L�[���������ꍇ
//
//		// �|�[�Y�̐ݒ�
//		m_PauseMenu = (MENU)((m_PauseMenu + 1) % MENU_MAX);
//
//		// �����x�̕ω���ݒ肷��
//		m_fPauseAlpha = PAUSE_ALPHA;
//
//		// �I������炷
//		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
//	}
//
//	// �ڕW�̃T�C�Y�̐ݒ菈��
//	sizeDest = D3DXVECTOR3(c_aPauseInfo[m_PauseMenu + POLYGON_CONTINUE].size.x * SIZEDEST_MAGNI, c_aPauseInfo[m_PauseMenu + POLYGON_CONTINUE].size.y * SIZEDEST_MAGNI, 0.0f);
//}
//
////=====================================
//// �|�[�Y�̌��菈��
////=====================================
//bool CWeaponSelectUI::PauseDecide(void)
//{
//	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
//		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
//		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
//	{ // ENTER�L�[���������ꍇ
//
//		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
//		{ // �t�F�[�h���s���Ă��Ȃ��Ƃ�
//
//			switch (m_PauseMenu)
//			{
//			case MENU_CONTINUE:		// �R���e�B�j���[���w���Ă����ꍇ
//
//				break;
//
//			case MENU_RESET:			// ���g���C���w���Ă����ꍇ
//
//				// �I������
//				Uninit();
//
//				// ���[�h�ݒ�(�Q�[���Ɉڍs)
//				CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);
//
//				break;
//
//			case MENU_TITLE:			// �^�C�g�����w���Ă����ꍇ
//
//				// �I������
//				Uninit();
//
//				// ���[�h�ݒ�(�^�C�g���Ɉڍs)
//				CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);
//
//				break;
//
//			default:
//
//				// ��~
//				assert(false);
//
//				break;
//			}
//
//			// �|�[�Y����������
//			m_bPause = false;
//		}
//
//		// ���艹��炷
//		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
//
//		// true ��Ԃ�
//		return true;
//	}
//
//	// false ��Ԃ�
//	return false;
//}
//
////=====================================
//// �|�[�Y�̓����x�␳����
////=====================================
//void CWeaponSelectUI::PauseAlphaCorrect(void)
//{
//	if (m_PauseColor.a > 1.0f)
//	{ // �A���t�@�l��1.0f���ゾ�����ꍇ
//
//		// �A���t�@�l��1.0f�ɐݒ肷��
//		m_PauseColor.a = 1.0f;
//
//		// �A���t�@�l�̕������t�ɕς���
//		m_fPauseAlpha *= -1;
//	}
//	else if (m_PauseColor.a < CHOICE_ALPHA_MIN)
//	{ // �A���t�@�l����萔�����������ꍇ
//
//		// �A���t�@�l���ŏ��l�ɐݒ肷��
//		m_PauseColor.a = CHOICE_ALPHA_MIN;
//
//		// �A���t�@�l�̕������t�ɕς���
//		m_fPauseAlpha *= -1;
//	}
//}
//
////=====================================
//// �|�[�Y�̒��_�ݒ菈��
////=====================================
//void CWeaponSelectUI::PauseVertex(void)
//{
//	for (int nPauseCnt = 0; nPauseCnt < MENU_MAX; nPauseCnt++)
//	{
//		if (m_PauseMenu == nPauseCnt)
//		{ // �I�𒆂̑I�����̏ꍇ
//
//			// �F��ݒ肷��
//			m_apWeapon[nPauseCnt + POLYGON_CONTINUE]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_PauseColor.a));
//
//			// �T�C�Y�̕␳����
//			SizeCorrect(nPauseCnt + POLYGON_CONTINUE);
//		}
//		else
//		{ // �I�����Ă��Ȃ��I�����̏ꍇ
//
//			// �F��ݒ肷��
//			m_apWeapon[nPauseCnt + POLYGON_CONTINUE]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, NOCHOICE_ALPHA));
//
//			// �T�C�Y�̐ݒ菈��
//			m_apWeapon[nPauseCnt + POLYGON_CONTINUE]->SetSize(c_aPauseInfo[nPauseCnt + POLYGON_CONTINUE].size);
//		}
//
//		// ���_���W�̐ݒ菈��
//		m_apWeapon[nPauseCnt + POLYGON_CONTINUE]->SetVertex();
//	}
//}
//
////=====================================
//// ��������
////=====================================
//CWeaponSelectUI* CWeaponSelectUI::Create(void)
//{
//	// ���[�J���I�u�W�F�N�g�𐶐�
//	CWeaponSelectUI* pPause = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�
//
//	if (pPause == nullptr)
//	{ // �I�u�W�F�N�g�� NULL �̏ꍇ
//
//		// �I�u�W�F�N�g�𐶐�
//		pPause = new CWeaponSelectUI;
//	}
//	else
//	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ
//
//		// ��~
//		assert(false);
//
//		// NULL ��Ԃ�
//		return nullptr;
//	}
//
//	if (pPause != nullptr)
//	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ
//
//		// ����������
//		if (FAILED(pPause->Init()))
//		{ // �������Ɏ��s�����ꍇ
//
//			// ��~
//			assert(false);
//
//			// NULL ��Ԃ�
//			return nullptr;
//		}
//	}
//	else
//	{ // �I�u�W�F�N�g�� NULL �̏ꍇ
//
//		// ��~
//		assert(false);
//
//		// NULL ��Ԃ�
//		return nullptr;
//	}
//
//	// �|�[�Y�̃|�C���^��Ԃ�
//	return pPause;
//}