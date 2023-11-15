//============================================
//
// �t�@�C���w�b�_�[[file.h]
// Author�F��������
//
//============================================
#ifndef _FILE_H_			//���̃}�N����`������Ă��Ȃ�������
#define _FILE_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "ranking.h"
#include "obstacle.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_FILE_DATA		(512)		// �t�@�C���̃f�[�^�̍ő吔
#define MAX_CAR_ROUTE		(10)		// �Ԃ̌o�H�̍ő吔

//--------------------------------------------
// �N���X(�t�@�C���ǂݍ��݃N���X)
//--------------------------------------------
class CFile
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_RANKING = 0,	// �����L���O
		TYPE_OBSTACLE,		// ��Q��
		TYPE_CARROUTE,		// �Ԃ̌o�H
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �����L���O�̏��
	struct SRankingInfo
	{
		int aRank[MAX_RANKING];					// �����L���O�̃f�[�^
		bool bSuccess;							// ������
	};

	// ��Q���̏��
	struct SObstacleInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];			// �ʒu
		CObstacle::TYPE type[MAX_FILE_DATA];	// ���
		int nNum;								// ����
		bool bSuccess;							// ������
	};

	// �Ԃ̌o�H
	struct SCarRouteInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA][MAX_CAR_ROUTE];	// �Ԃ̈ʒu
		int nNumPos[MAX_FILE_DATA];						// �ʒu�̐�
		int nNum;										// ����
		bool bSuccess;									// ������
	};

	CFile();					// �R���X�g���N�^
	~CFile();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������

	HRESULT Save(const TYPE type);	// �Z�[�u����
	HRESULT Load(const TYPE type);	// ���[�h����

	void SetRankingInfo(int* pRank);		// �����L���O�̐ݒ菈��
	SRankingInfo GetRankingInfo(void);		// �����L���O�̎擾����

	D3DXVECTOR3* GetCarRoute(const int nType);		// �Ԃ̌o�H�̎擾����
	int GetCarRouteNum(void) const;					// �Ԃ̌o�H�̑����擾����
	int GetCarRouteNumPos(const int nType) const;	// �Ԃ̌o�H�̈ʒu�̑����̎擾����

	void SetMap(void);				// �}�b�v�̐ݒ菈��

private:		// �����̂݃A�N�Z�X�ł���

	// �����o�֐�(�Z�[�u�֌W)
	HRESULT SaveRanking(void);		// �����L���O�̃Z�[�u����
	HRESULT SaveObstacle(void);		// ��Q���̃Z�[�u����

	// �����o�֐�(���[�h�֌W)
	HRESULT LoadRanking(void);		// �����L���O�̃��[�h����
	HRESULT LoadObstacle(void);		// ��Q���̃��[�h����
	HRESULT LoadCarRoute(void);		// �Ԃ̌o�H�̃��[�h����

	// �����o�ϐ�
	SRankingInfo m_RankingInfo;		// �����L���O�̏��
	SObstacleInfo m_ObstacleInfo;	// ��Q���̏��
	SCarRouteInfo m_CarRouteInfo;	// �Ԃ̃��[�g�̏��

	// �ÓI�����o�ϐ�
	static const char* c_apBooleanDisp[2];			// bool�^�̕\��
};

#endif