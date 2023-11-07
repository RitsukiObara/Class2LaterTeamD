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

	CFile();					// �R���X�g���N�^
	~CFile();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������

	HRESULT Save(const TYPE type);	// �Z�[�u����
	HRESULT Load(const TYPE type);	// ���[�h����

	void SetRankingInfo(int* pRank);		// �����L���O�̐ݒ菈��
	SRankingInfo GetRankingInfo(void);		// �����L���O�̎擾����

private:		// �����̂݃A�N�Z�X�ł���

	// �����o�֐�(�Z�[�u�֌W)
	HRESULT SaveRanking(void);		// �����L���O�̃Z�[�u����
	HRESULT SaveObstacle(void);		// ��Q���̃Z�[�u����

	// �����o�֐�(���[�h�֌W)
	HRESULT LoadRanking(void);		// �����L���O�̃��[�h����
	HRESULT LoadObstacle(void);		// ��Q���̃��[�h����

	// �����o�ϐ�
	SRankingInfo m_RankingInfo;		// �����L���O�̏��
	SObstacleInfo m_ObstacleInfo;	// ��Q���̏��

	// �ÓI�����o�ϐ�
	static const char* c_apBooleanDisp[2];			// bool�^�̕\��
};

#endif