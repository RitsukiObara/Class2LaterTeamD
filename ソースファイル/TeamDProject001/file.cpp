//============================================
//
// �t�@�C���̃��C������[file.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "scene.h"
#include "file.h"
#include "object.h"

#include "obstacle_manager.h"
#include "block_manager.h"
#include "game.h"
#include "edit.h"
#include "collision_edit.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define OBSTACLE_TXT		"data\\TXT\\Obstacle.txt"		// ��Q���̃e�L�X�g
#define CARROUTE_TXT		"data\\TXT\\CarRoute.txt"		// �Ԃ̌o�H�̃e�L�X�g
#define BLOCK_TXT			"data\\TXT\\Block.txt"			// �u���b�N�̃e�L�X�g
#define COLLISION_TXT		"data\\TXT\\Collision.txt"		// �����蔻��̃e�L�X�g
#define COLLISIONSAVE_TXT	"data\\TXT\\CollSave.txt"		// �����蔻��Z�[�u�̃e�L�X�g

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
const char* CFile::c_apBooleanDisp[2] =					// bool�^�̕\��
{
	"FALSE",							// TRUE
	"TRUE",								// FALSE
};

//===========================================
// �R���X�g���N�^
//===========================================
CFile::CFile()
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;				// �ʒu
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;			// ���

		for (int nCntCar = 0; nCntCar < MAX_CAR_ROUTE; nCntCar++)
		{
			m_CarRouteInfo.pos[nCntInfo][nCntCar];						// �Ԃ̃��[�g�̏��
		}
		m_CarRouteInfo.nNumPos[nCntInfo] = 0;							// �ʒu�̐�

		m_BlockInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;			// �ʒu
		m_BlockInfo.rotType[nCntInfo] = CBlock::ROTTYPE_FRONT;	// �����̎��
		m_BlockInfo.type[nCntInfo] = CBlock::TYPE_CARDBOARD;	// ���
	}

	for (int nCntBlock = 0; nCntBlock < CBlock::TYPE_MAX; nCntBlock++)
	{
		for (int nCntColl = 0; nCntColl < MAX_NUMCOLL; nCntColl++)
		{
			m_CollInfo.aData[nCntBlock].vtxMax[nCntColl] = NONE_D3DXVECTOR3;	// �ő�l
			m_CollInfo.aData[nCntBlock].vtxMin[nCntColl] = NONE_D3DXVECTOR3;	// �ŏ��l
			m_CollInfo.aData[nCntBlock].fAngle[nCntColl] = 0.0f;				// ����
			m_CollInfo.aData[nCntBlock].fLength[nCntColl] = 0.0f;				// ����
			m_CollInfo.aData[nCntBlock].fHeight[nCntColl] = 0.0f;				// ����
		}
		m_CollInfo.aData[nCntBlock].nNum = 0;			// ����
		m_CollInfo.aData[nCntBlock].bSuccess = false;	// ������
	}


	// �������N���A����
	m_ObstacleInfo.nNum = 0;			// ��Q��
	m_CarRouteInfo.nNum = 0;			// �Ԃ̌o�H
	m_BlockInfo.nNum = 0;				// �u���b�N

	// �����󋵂��N���A����
	m_ObstacleInfo.bSuccess = false;	// ��Q��
	m_CarRouteInfo.bSuccess = false;	// �Ԃ̌o�H
	m_BlockInfo.bSuccess = false;		// �u���b�N
	m_CollInfo.bSuccess = false;		// �����蔻��
}

//===========================================
// �f�X�g���N�^
//===========================================
CFile::~CFile()
{

}

//===========================================
// �Z�[�u����
//===========================================
HRESULT CFile::Save(const TYPE type)
{
	switch (type)
	{
	case TYPE_OBSTACLE:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveObstacle()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_BLOCK:

		// �u���b�N�̃Z�[�u����
		if (FAILED(SaveBlock()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_COLLISION:

		// �����蔻��̃Z�[�u����
		if (FAILED(SaveCollision()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// ���[�h����
//===========================================
HRESULT CFile::Load(const TYPE type)
{
	switch (type)
	{
	case TYPE_OBSTACLE:

		// ��Q���̃��[�h����
		if (FAILED(LoadObstacle()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_CARROUTE:

		// �Ԃ̃��[�h����
		if (FAILED(LoadCarRoute()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_BLOCK:

		// �u���b�N�̃��[�h����
		if (FAILED(LoadBlock()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_COLLISION:

		// �����蔻��̃��[�h����
		if (FAILED(LoadCollision()))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���ʂ�Ԃ�
	return S_OK;
}

//===========================================
// �Ԃ̌o�H�̎擾����
//===========================================
D3DXVECTOR3* CFile::GetCarRoute(const int nType)
{
	// �Ԃ̌o�H��Ԃ�
	return m_CarRouteInfo.pos[nType];
}

//===========================================
// �Ԃ̌o�H�̑����擾����
//===========================================
int CFile::GetCarRouteNum(void) const
{
	// �Ԃ̌o�H�̐���Ԃ�
	return m_CarRouteInfo.nNum;
}

//===========================================
// �Ԃ̌o�H�̈ʒu�̑����̎擾����
//===========================================
int CFile::GetCarRouteNumPos(const int nType) const
{
	// �Ԃ̌o�H�̈ʒu�̑�����Ԃ�
	return m_CarRouteInfo.nNumPos[nType];
}

//===========================================
// �}�b�v�̐ݒ菈��
//===========================================
void CFile::SetMap(void)
{
	if (m_ObstacleInfo.bSuccess == true)
	{ // �����󋵂� true �̏ꍇ

		for (int nCntObst = 0; nCntObst < m_ObstacleInfo.nNum; nCntObst++)
		{
			// ��Q���̐�������
			CObstacle::Create(m_ObstacleInfo.pos[nCntObst], NONE_D3DXVECTOR3, m_ObstacleInfo.type[nCntObst]);
		}
	}

	if (m_BlockInfo.bSuccess == true)
	{ // �����󋵂� true �̏ꍇ

		for (int nCntBlock = 0; nCntBlock < m_BlockInfo.nNum; nCntBlock++)
		{
			// �u���b�N�̐�������
			CBlock::Create(m_BlockInfo.pos[nCntBlock], m_BlockInfo.rotType[nCntBlock], m_BlockInfo.type[nCntBlock]);
		}
	}
}

//===========================================
// ����������
//===========================================
HRESULT CFile::Init(void)
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;				// �ʒu
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;			// ���

		for (int nCntCar = 0; nCntCar < MAX_CAR_ROUTE; nCntCar++)
		{
			m_CarRouteInfo.pos[nCntInfo][nCntCar];						// �Ԃ̃��[�g�̏��
		}
		m_CarRouteInfo.nNumPos[nCntInfo] = 0;							// �ʒu�̐�

		m_BlockInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;			// �ʒu
		m_BlockInfo.rotType[nCntInfo] = CBlock::ROTTYPE_FRONT;	// �����̎��
		m_BlockInfo.type[nCntInfo] = CBlock::TYPE_CARDBOARD;	// ���
	}

	for (int nCntBlock = 0; nCntBlock < CBlock::TYPE_MAX; nCntBlock++)
	{
		for (int nCntColl = 0; nCntColl < MAX_NUMCOLL; nCntColl++)
		{
			m_CollInfo.aData[nCntBlock].vtxMax[nCntColl] = NONE_D3DXVECTOR3;	// �ő�l
			m_CollInfo.aData[nCntBlock].vtxMin[nCntColl] = NONE_D3DXVECTOR3;	// �ŏ��l
			m_CollInfo.aData[nCntBlock].fAngle[nCntColl] = 0.0f;				// ����
			m_CollInfo.aData[nCntBlock].fLength[nCntColl] = 0.0f;				// ����
			m_CollInfo.aData[nCntBlock].fHeight[nCntColl] = 0.0f;				// ����
		}
		m_CollInfo.aData[nCntBlock].nNum = 0;			// ����
		m_CollInfo.aData[nCntBlock].bSuccess = false;	// ������
	}


	// �������N���A����
	m_ObstacleInfo.nNum = 0;			// ��Q��
	m_CarRouteInfo.nNum = 0;			// �Ԃ̌o�H
	m_BlockInfo.nNum = 0;				// �u���b�N

	// �����󋵂��N���A����
	m_ObstacleInfo.bSuccess = false;	// ��Q��
	m_CarRouteInfo.bSuccess = false;	// �Ԃ̌o�H
	m_BlockInfo.bSuccess = false;		// �u���b�N
	m_CollInfo.bSuccess = false;		// �����蔻��

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CFile::Uninit(void)
{

}

//===========================================
// ��Q���̃Z�[�u����
//===========================================
HRESULT CFile::SaveObstacle(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q����������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(OBSTACLE_TXT, "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pObstacle != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_OBSTACLE\n");		// ��Q���̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pObstacle->GetPos().x, pObstacle->GetPos().y, pObstacle->GetPos().z);			// �ʒu����������

			fprintf(pFile, "\tTYPE = ");		// ��ނ̐ݒ����������
			fprintf(pFile, "%d\n", pObstacle->GetType());			// ��ނ���������

			// ���������������
			fprintf(pFile, "END_SET_OBSTACLE\n\n");	// ��Q���̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pObstacle = pObstacle->GetNext();
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �u���b�N�̃Z�[�u����
//===========================================
HRESULT CFile::SaveBlock(void)
{
	// ���[�J���ϐ��錾
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// �擪�̃u���b�N��������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(BLOCK_TXT, "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pBlock != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_BLOCK\n");		// �u���b�N�̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pBlock->GetPos().x, pBlock->GetPos().y, pBlock->GetPos().z);			// �ʒu����������

			fprintf(pFile, "\tROT = ");			// �����̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pBlock->GetRot().x, pBlock->GetRot().y, pBlock->GetRot().z);			// ��������������

			fprintf(pFile, "\tTYPE = ");		// ��ނ̐ݒ����������
			fprintf(pFile, "%d\n", pBlock->GetType());			// ��ނ���������

			// ���������������
			fprintf(pFile, "END_SET_BLOCK\n\n");	// �u���b�N�̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pBlock = pBlock->GetNext();
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �����蔻��̃Z�[�u����
//===========================================
HRESULT CFile::SaveCollision(void)
{
// �f�o�b�O�ł̂�
#ifdef _DEBUG

	// ���[�J���ϐ��錾
	CCollisionEdit* pEdit = CGame::GetEdit()->GetCollEdit();	// �����蔻��G�f�B�b�g��������
	D3DXVECTOR3 vtxMax;		// �ő�l
	D3DXVECTOR3 vtxMin;		// �ŏ��l
	float fAngle;			// ����
	float fLength;			// ����

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(COLLISIONSAVE_TXT, "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		if (pEdit != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_COLLISION\n");		// �����蔻��̐ݒ����������

			// ���������������
			fprintf(pFile, "BLOCK_TYPE = ");							// �u���b�N�̎�ނ���������
			fprintf(pFile, "%d\n", CGame::GetEdit()->GetBlockType());	// ��ނ���������

			// ���������������
			fprintf(pFile, "COLL_NUM = ");								// �����蔻��̑�������������
			fprintf(pFile, "%d\n\n", pEdit->GetNumColl());				// ��������������

			for (int nCnt = 0; nCnt < pEdit->GetNumColl(); nCnt++)
			{
				// �������Z�o����
				fAngle = atan2f(pEdit->GetModel(nCnt)->GetPos().x - pEdit->GetPosInit().x, pEdit->GetModel(nCnt)->GetPos().z - pEdit->GetPosInit().z);

				// �������Z�o����
				fLength = sqrtf((pEdit->GetModel(nCnt)->GetPos().x - pEdit->GetPosInit().x) * (pEdit->GetModel(nCnt)->GetPos().x - pEdit->GetPosInit().x) + (pEdit->GetModel(nCnt)->GetPos().z - pEdit->GetPosInit().z) * (pEdit->GetModel(nCnt)->GetPos().z - pEdit->GetPosInit().z));

				// �ő�l��ݒ�
				vtxMax.x = pEdit->GetModel(nCnt)->GetFileData().vtxMax.x * pEdit->GetModel(nCnt)->GetScale().x;
				vtxMax.y = pEdit->GetModel(nCnt)->GetFileData().vtxMax.y * pEdit->GetModel(nCnt)->GetScale().y;
				vtxMax.z = pEdit->GetModel(nCnt)->GetFileData().vtxMax.z * pEdit->GetModel(nCnt)->GetScale().z;

				// �ŏ��l��ݒ�
				vtxMin.x = pEdit->GetModel(nCnt)->GetFileData().vtxMin.x * pEdit->GetModel(nCnt)->GetScale().x;
				vtxMin.y = pEdit->GetModel(nCnt)->GetFileData().vtxMin.y * pEdit->GetModel(nCnt)->GetScale().y;
				vtxMin.z = pEdit->GetModel(nCnt)->GetFileData().vtxMin.z * pEdit->GetModel(nCnt)->GetScale().z;

				// �ő�l����������
				fprintf(pFile, "\tMAX = ");
				fprintf(pFile, "%.1f %.1f %.1f\n", vtxMax.x, vtxMax.y, vtxMax.z);

				// �ŏ��l����������
				fprintf(pFile, "\tMIN = ");
				fprintf(pFile, "%.1f %.1f %.1f\n", vtxMin.x, vtxMin.y, vtxMin.z);

				// ��������������
				fprintf(pFile, "\tANGLE = ");
				fprintf(pFile, "%.1f\n", fAngle);

				// ��������������
				fprintf(pFile, "\tLENGTH = ");
				fprintf(pFile, "%.1f\n", fLength);

				// ��������������
				fprintf(pFile, "\tHEIGHT = ");
				fprintf(pFile, "%.1f\n\n", pEdit->GetModel(nCnt)->GetPos().y - pEdit->GetPosInit().y);
			}

			// ���������������
			fprintf(pFile, "END_SET_COLLISION\n\n");	// �����蔻��̐ݒ�̏I������������
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

#endif

	// ������Ԃ�
	return S_OK;
}

//===========================================
// ��Q���̃��[�h����
//===========================================
HRESULT CFile::LoadObstacle(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_ObstacleInfo.nNum = 0;			// ����
	m_ObstacleInfo.bSuccess = false;	// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(OBSTACLE_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_OBSTACLE") == 0)
			{ // �ǂݍ��񂾕����� SET_OBSTACLE �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_OBSTACLE �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].x,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].y,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // �ǂݍ��񂾕����� TYPE �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d",
							&m_ObstacleInfo.type[m_ObstacleInfo.nNum]);		// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_OBSTACLE") != 0);		// �ǂݍ��񂾕����� END_SET_OBSTACLE �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_ObstacleInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_ObstacleInfo.bSuccess = true;
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �Ԃ̌o�H�̃��[�h����
//===========================================
HRESULT CFile::LoadCarRoute(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_CarRouteInfo.nNum = 0;			// ����
	m_CarRouteInfo.bSuccess = false;	// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(CARROUTE_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_CARROUTE") == 0)
			{ // �ǂݍ��񂾕����� SET_CARROUTE �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_CARROUTE �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "NUMROUTE") == 0)
					{ // �ǂݍ��񂾕����� NUMROUTE �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);										// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &m_CarRouteInfo.nNumPos[m_CarRouteInfo.nNum]);		// �ʒu��ǂݍ���

						if (m_CarRouteInfo.nNumPos[m_CarRouteInfo.nNum] > MAX_CAR_ROUTE)
						{ // �ő吔�𒴂��Ă����ꍇ

							// ��~
							assert(false);
						}
					}
					else if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						for (int nCnt = 0; nCnt < m_CarRouteInfo.nNumPos[m_CarRouteInfo.nNum]; nCnt++)
						{
							fscanf(pFile, "%s", &aString[0]);					// �ʒu�̔ԍ� ��ǂݍ��� (�s�v)
							fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
							fscanf(pFile, "%f%f%f", 
								&m_CarRouteInfo.pos[m_CarRouteInfo.nNum][nCnt].x,
								&m_CarRouteInfo.pos[m_CarRouteInfo.nNum][nCnt].y,
								&m_CarRouteInfo.pos[m_CarRouteInfo.nNum][nCnt].z);	// �ʒu��ǂݍ���
						}
					}

				} while (strcmp(&aString[0], "END_SET_CARROUTE") != 0);		// �ǂݍ��񂾕����� END_SET_CARROUTE �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_CarRouteInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_CarRouteInfo.bSuccess = true;
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �u���b�N�̃��[�h����
//===========================================
HRESULT CFile::LoadBlock(void)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_BlockInfo.nNum = 0;				// ����
	m_BlockInfo.bSuccess = false;		// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(BLOCK_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_BLOCK") == 0)
			{ // �ǂݍ��񂾕����� SET_BLOCK �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_BLOCK �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_BlockInfo.pos[m_BlockInfo.nNum].x,
							&m_BlockInfo.pos[m_BlockInfo.nNum].y,
							&m_BlockInfo.pos[m_BlockInfo.nNum].z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� ROT �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d",
							&m_BlockInfo.rotType[m_BlockInfo.nNum]);	// ������ǂݍ���
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // �ǂݍ��񂾕����� TYPE �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d",
							&m_BlockInfo.type[m_BlockInfo.nNum]);		// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_BLOCK") != 0);		// �ǂݍ��񂾕����� END_SET_BLOCK �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_BlockInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_BlockInfo.bSuccess = true;
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �����蔻��̃��[�h����
//===========================================
HRESULT CFile::LoadCollision(void)
{
	// ���s��Ԃ�
	return E_FAIL;
}