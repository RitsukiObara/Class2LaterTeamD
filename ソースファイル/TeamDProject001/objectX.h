//============================================================
//
// X�t�@�C���w�b�_�[ [xfile.h]
// Author�F��������
//
//============================================================
#ifndef _XFILE_H_	// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _XFILE_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------
#define INIT_VTX_MIN	(D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))		// ���f���̍ŏ��̒��_���W�̏����l
#define INIT_VTX_MAX	(D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))		// ���f���̍ő�̒��_���W�̏����l
#define INIT_SIZE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))					// ���f���T�C�Y�̏����l
#define INIT_RAT		(CXFile::TYPE_RAT_BODY)							// �l�Y�~���f���̊J�n�ʒu
#define INIT_CAT		(CXFile::TYPE_CAT_BODY)							// �L���f���̊J�n�ʒu
#define INIT_BLOCK		(CXFile::TYPE_CARDBOARD)						// �u���b�N���f���̊J�n�ʒu
#define INIT_OBSTACLE	(CXFile::TYPE_HONEYBOTTLE)						// ��Q�����f���̊J�n�ʒu

//------------------------------------------------------------
// �N���X��`(X�t�@�C��)
//------------------------------------------------------------
class CXFile
{
public:			// �N�ł��A�N�Z�X�ł���

	//************************************************************
	//	�񋓌^��` (TYPE)
	//************************************************************
	enum TYPE
	{
		// �ʏ탂�f��
		TYPE_RIPPLE = 0,		// �g��
		TYPE_KARIPLAYER,		// ���v���C���[
		TYPE_WOODBLOCK,			// �ؔ�
		TYPE_WEAPONCAGE,		// ���포��
		TYPE_FLOWERFRAC,		// �ԕr�̔j��
		TYPE_PLASTICFRAC,		// �v���X�`�b�N�P�[�X�j��
		TYPE_HONEY,				// �I��
		TYPE_TOYCARSCREW,		// ��������̎�(�l�W)
		TYPE_TITLEWALL,			// �^�C�g���̕�
		TYPE_ROOMBA_SUB,		// �����o�̃v���y��
		TYPE_TARAI,				// ���炢

		// �u���b�N���f��
		TYPE_CARDBOARD,			// �i�{�[��
		TYPE_TISSUEBOX,			// �e�B�b�V����
		TYPE_PENHOLDER,			// �y������
		TYPE_REMOCON,			// �����R��
		TYPE_BEAR,				// �u���b�N
		TYPE_CLOCK,				// ���v
		TYPE_RUBBISH,			// �`����
		TYPE_MILKPACK,			// �����p�b�N
		TYPE_CUP,				// �R�b�v
		TYPE_OBAPHONE,			// �I�o�t�H��
		TYPE_WII,				// Wii
		TYPE_DS,				// DS
		TYPE_HEADPHONE,			// �w�b�h�t�H��
		TYPE_PEN,				// �y��
		TYPE_ACADAPTER,			// AC�A�_�v�^�[
		TYPE_BUILDINGBLOCK,		// �ςݖ�
		TYPE_GLASSES,			// �ዾ�P�[�X
		TYPE_PENCIL,			// ���M
		TYPE_PICTUREFRAME,		// �ʐ^����

		// ��Q�����f��
		TYPE_HONEYBOTTLE,		// �I���̃{�g��
		TYPE_SLIME,				// �X���C��
		TYPE_HAIRBALL,			// �{
		TYPE_FLOWERVASE,		// �ԕr
		TYPE_PLASTICCASE,		// �v���X�`�b�N�P�[�X
		TYPE_PETBOTTLE,			// �y�b�g�{�g��
		TYPE_TOYCARBODY,		// ��������̎�(�{��)
		TYPE_ROOMBA_MAIN,		// �����o�̖{��
		TYPE_HIMO,				// �Ђ�

		//�}�b�v���f��
		TYPE_KITCHEN,			//�L�b�`��
		TYPE_REIZOUKO,			//�①��
		TYPE_TABLE,				//�e�[�u��

		//�l�Y�~���f��
		TYPE_RAT_BODY,			// ��
		TYPE_RAT_HEAD,			// ��
		TYPE_RAT_LHAND,			// ����
		TYPE_RAT_RHAND,			// �E��
		TYPE_RAT_LLEG,			// ����
		TYPE_RAT_RLEG,			// �E��

		//�L���f��
		TYPE_CAT_BODY,			//��
		TYPE_CAT_HEAD,			//��
		TYPE_CAT_LARM,			//���r
		TYPE_CAT_LHAND,			//����
		TYPE_CAT_RAEM,			//�E�r
		TYPE_CAT_RHAND,			//�E��
		TYPE_CAT_LFOOT,			//����
		TYPE_CAT_LLEG,			//����
		TYPE_CAT_RFOOT,			//�E��
		TYPE_CAT_RLEG,			//�E��

		// �l�Y�~���f��
		TYPE_RAT_GHOST,			// �H�샂�f��

		// �G�f�B�b�g���f��
		TYPE_MAX,				// �S���f���̑���
	};

	//************************************************************
	//	�\���̒�` (SXFile)
	//************************************************************
	struct SXFile
	{
		LPD3DXMESH	 pMesh;						// ���b�V�� (���_���) �ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;					// �}�e���A���ւ̃|�C���^
		DWORD		 dwNumMat;					// �}�e���A���̐�
		D3DXVECTOR3	 vtxMin;					// �ŏ��̒��_���W
		D3DXVECTOR3	 vtxMax;					// �ő�̒��_���W
		D3DXVECTOR3	 collsize;					// �����蔻��̃T�C�Y
		float		 fRadius;					// ���a
		int			 m_nTexIdx[MAX_MATERIAL];	// �e�N�X�`���̃C���f�b�N�X
	};

	CXFile();			// �R���X�g���N�^
	~CXFile();			// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Init(void);		// X�t�@�C���̏���������
	static void Uninit(void);		// X�t�@�C���̏I������

	// �Z�b�g�E�Q�b�g�֐�
	static SXFile GetXFile(TYPE type);	// X�t�@�C���̎擾����

private:

	// �����o�֐�
	static HRESULT LoadXFile(void);		// x�t�@�C���̓ǂݍ���
	static void SetCollision(void);		// �����蔻��̍쐬
	static HRESULT LoadTexture(void);	// �e�N�X�`���̓ǂݍ���

	// �ÓI�����o�ϐ�
	static const char *c_apModelData[CXFile::TYPE_MAX];			// ���f���̖��O
	static SXFile m_apModel[CXFile::TYPE_MAX];					// ���f���̏��
};

#endif