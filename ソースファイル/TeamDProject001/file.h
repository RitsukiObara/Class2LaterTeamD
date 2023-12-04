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
#include "obstacle.h"
#include "block.h"
#include "collision_edit.h"

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
		TYPE_OBSTACLE = 0,	// ��Q��
		TYPE_CARROUTE,		// �Ԃ̌o�H
		TYPE_BLOCK,			// �u���b�N
		TYPE_COLLISION,		// �����蔻��
		TYPE_MAX			// ���̗񋓌^�̑���
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

	// �u���b�N�̏��
	struct SBlockInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];			// �ʒu
		CBlock::ROTTYPE rotType[MAX_FILE_DATA];	// �����̎��
		CBlock::TYPE type[MAX_FILE_DATA];		// ���
		int nNum;								// ����
		bool bSuccess;							// ������
	};

	// �����蔻��̃f�[�^
	struct SCollData
	{
		D3DXVECTOR3 vtxMax[MAX_NUMCOLL];		// �ő�l
		D3DXVECTOR3 vtxMin[MAX_NUMCOLL];		// �ŏ��l
		float fAngle[MAX_NUMCOLL];				// ����
		float fLength[MAX_NUMCOLL];				// ����
		float fHeight[MAX_NUMCOLL];				// ����
		int nNum;								// ����
		bool bSuccess;							// ������
	};

	// �����蔻��̏��
	struct SCollisionInfo
	{
		SCollData aData[CBlock::TYPE_MAX];		// �f�[�^
		bool bSuccess;							// ������
	};

	CFile();					// �R���X�g���N�^
	~CFile();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������

	HRESULT Save(const TYPE type);	// �Z�[�u����
	HRESULT Load(const TYPE type);	// ���[�h����

	D3DXVECTOR3* GetCarRoute(const int nType);		// �Ԃ̌o�H�̎擾����
	int GetCarRouteNum(void) const;					// �Ԃ̌o�H�̑����擾����
	int GetCarRouteNumPos(const int nType) const;	// �Ԃ̌o�H�̈ʒu�̑����̎擾����

	void SetMap(void);				// �}�b�v�̐ݒ菈��

private:		// �����̂݃A�N�Z�X�ł���

	// �����o�֐�(�Z�[�u�֌W)
	HRESULT SaveObstacle(void);		// ��Q���̃Z�[�u����
	HRESULT SaveBlock(void);		// �u���b�N�̃Z�[�u����
	HRESULT SaveCollision(void);	// �����蔻��̃Z�[�u����

	// �����o�֐�(���[�h�֌W)
	HRESULT LoadObstacle(void);		// ��Q���̃��[�h����
	HRESULT LoadCarRoute(void);		// �Ԃ̌o�H�̃��[�h����
	HRESULT LoadBlock(void);		// �u���b�N�̃��[�h����
	HRESULT LoadCollision(void);	// �����蔻��̃��[�h����

	// �����o�ϐ�
	SObstacleInfo m_ObstacleInfo;	// ��Q���̏��
	SCarRouteInfo m_CarRouteInfo;	// �Ԃ̃��[�g�̏��
	SBlockInfo m_BlockInfo;			// �u���b�N�̏��
	SCollisionInfo m_CollInfo;		// �����蔻��̏��

	// �ÓI�����o�ϐ�
	static const char* c_apBooleanDisp[2];			// bool�^�̕\��
};

#endif