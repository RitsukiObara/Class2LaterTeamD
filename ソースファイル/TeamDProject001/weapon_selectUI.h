////===========================================
////
//// ����̑I��UI�w�b�_�[[weapon_selectUI.h]
//// Author ��������
////
////===========================================
//#ifndef _WEAPON_SELECT_UI_H_
//#define _WEAPON_SELECT_UI_H_
//
////-------------------------------------------
//// �C���N���[�h�t�@�C��
////-------------------------------------------
//#include "object.h"
//
////-------------------------------------------
//// �O���錾
////-------------------------------------------
//class CObject2D;
//
////-------------------------------------------
//// �N���X��`(����I��UI)
////-------------------------------------------
//class CWeaponSelectUI : public CObject
//{
//public:		// �N�ł��A�N�Z�X�ł���
//
//	// �񋓌^��`(���)
//	enum TYPE
//	{
//		TYPE_ONE = 0,	// 1��
//		TYPE_TWO,		// 2��
//		TYPE_THREE,		// 3��
//		TYPE_MAX		// ���̗񋓌^�̑���
//	};
//
//	CWeaponSelectUI();			// �R���X�g���N�^
//	~CWeaponSelectUI();			// �f�X�g���N�^
//
//	// �����o�֐�
//	HRESULT Init(void);			// ����������
//	void Uninit(void);			// �I������
//	void Update(void);			// �X�V����
//	void Draw(void);			// �`�揈��
//
//	// �Z�b�g�E�Q�b�g�֌W
//
//	// �ÓI�����o�֐�
//	static CWeaponSelectUI* Create(void);	// ��������
//
//private:		// ���������A�N�Z�X�ł���
//
//	// �����o�ϐ�
//	CObject2D* m_pScreen;					// �X�N���[���̏��
//	CObject2D* m_apWeapon[TYPE_MAX];		// ����̏��
//};
//
//#endif