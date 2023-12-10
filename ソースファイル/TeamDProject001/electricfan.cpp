//===========================================
//
// ��@�̏���[electricfan.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "electricfan.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"

#include "fan_blade.h"
#include "Effect.h"
#include "collision.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define FAN_SHIFT		(175.0f)		// ��@�̉H���̂��炷����
#define WIND_RANGE		(1600.0f)		// ��@�̕��͈̔�
#define WIND_MOVE		(11)			// ���G�t�F�N�g�̈ړ��ʂ̕�
#define WIND_LIFE		(50)			// ���G�t�F�N�g�̎���
#define WIND_RADIUS		(40.0f)			// ���G�t�F�N�g�̔��a
#define FAN_MOVE_OFF	(0.0f)			// �X�C�b�`OFF�̉H���̈ړ���
#define FAN_MOVE_ON		(0.5f)			// �X�C�b�`ON�̉H���̈ړ���

//==============================
// �R���X�g���N�^
//==============================
CElecFan::CElecFan() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pFan = nullptr;			// ��@�̃t�@��
	m_bPower = false;			// �d����
	SetCatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CElecFan::~CElecFan()
{

}

//==============================
// ��@�̏���������
//==============================
HRESULT CElecFan::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pFan = nullptr;			// ��@�̃t�@��
	m_bPower = false;			// �d����

	// �l��Ԃ�
	return S_OK;
}

//========================================
// ��@�̏I������
//========================================
void CElecFan::Uninit(void)
{
	if (m_pFan != nullptr)
	{ // �t�@���� NULL ����Ȃ��ꍇ

		// �t�@���̏I������
		m_pFan->Uninit();
		m_pFan = nullptr;
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// ��@�̍X�V����
//=====================================
void CElecFan::Update(void)
{
	if (m_bPower == true)
	{ // �d�������Ă���ꍇ

		//D3DXVECTOR3 pos;		// �ʒu
		//D3DXVECTOR3 move;		// �ړ���

		//// �ʒu��ݒ肷��
		//pos.x = GetPos().x + sinf(GetRot().y + (D3DX_PI * 0.5f)) * (rand() % (int)(GetFileData().vtxMax.x) - (int)(GetFileData().vtxMax.x * 0.5f));
		//pos.y = GetPos().y + rand() % (int)(GetFileData().vtxMax.y) + (int)(GetFileData().vtxMin.y);
		//pos.z = GetPos().z + cosf(GetRot().y + (D3DX_PI * 0.5f)) * (rand() % (int)(GetFileData().vtxMax.z) - (int)(GetFileData().vtxMax.z * 0.5f));

		//// �ړ��ʂ�ݒ肷��
		//move.x = sinf(GetRot().y + D3DX_PI) * (rand() % WIND_MOVE + (WIND_MOVE * 0.5f));
		//move.y = 0.0f;
		//move.z = cosf(GetRot().y + D3DX_PI) * (rand() % WIND_MOVE + (WIND_MOVE * 0.5f));

		//// �G�t�F�N�g���o��
		//CEffect::Create(pos, move, WIND_LIFE, WIND_RADIUS, CEffect::TYPE_WIND, NONE_D3DXCOLOR, true);
	}

	if (m_pFan != nullptr)
	{ // �t�@���� NULL ����Ȃ��ꍇ

		// �t�@���̍X�V����
		m_pFan->Update();
	}
}

//=====================================
// ��@�̕`�揈��
//=====================================
void CElecFan::Draw(void)
{	
	// �`�揈��
	CObstacle::Draw();

	if (m_pFan != nullptr)
	{ // �t�@���� NULL ����Ȃ��ꍇ

		// �t�@���̕`�揈��
		m_pFan->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CElecFan::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �S�Ă̒l��ݒ肷��
	if (m_pFan == nullptr)
	{ // �t�@���� NULL �������ꍇ

		// �H���̈ʒu
		D3DXVECTOR3 posFan;

		// �H���̈ʒu��ݒ肷��
		posFan.x = pos.x;
		posFan.y = pos.y + FAN_SHIFT;
		posFan.z = pos.z;

		// �t�@���𐶐�����
		m_pFan = CFanBlade::Create(posFan);
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CElecFan::Collision(D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(GetFileData().fRadius, GetFileData().vtxMax.y, GetFileData().fRadius);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-GetFileData().fRadius, GetFileData().vtxMin.y, -GetFileData().fRadius);
	D3DXVECTOR3 playMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 playMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	// �Z�ʑ̂̓����蔻��
	if (collision::HexahedronCollision(pos, GetPos(), posOld, GetPosOld(), playMin, vtxMin, playMax, vtxMax) == true)
	{ // �����蔻�肪 true �̏ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CElecFan::Hit(const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, const CPlayer::TYPE type)
{
	if (m_bPower == true)
	{ // �d���󋵂� true �̏ꍇ

		// �e�ő�l�E�ŏ��l��錾
		D3DXVECTOR3 vtxMin = D3DXVECTOR3(sinf(GetRot().y) * -WIND_RANGE, 0.0f, cosf(GetRot().y) * -WIND_RANGE);
		D3DXVECTOR3 vtxMax = D3DXVECTOR3(0.0f, GetFileData().vtxMax.y, 0.0f);
		D3DXVECTOR3 playerMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
		D3DXVECTOR3 playerMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);

		if (useful::RectangleCollisionXY(pos, GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true &&
			useful::RectangleCollisionXZ(pos, GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true &&
			useful::RectangleCollisionYZ(pos, GetPos(), playerMax, vtxMax, playerMin, vtxMin) == true)
		{ // �����蔻��̒��ɓ������ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CElecFan::HitCircle(const D3DXVECTOR3& pos, const float Radius, const CPlayer::TYPE type)
{
	if (useful::CircleCollisionXZ(pos, GetPos(), Radius, GetFileData().fRadius) == true)
	{//�~�͈͓̔��̏ꍇtrue��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CElecFan::Action(void)
{
	// �d����ݒ肷��
	m_bPower = !m_bPower;

	if (m_bPower == true)
	{ // �d��ON�̏ꍇ

		// �ړI�̌����̈ړ��ʂ�ݒ肷��
		m_pFan->SetRotMoveDest(FAN_MOVE_ON);
		SetCatUse(false);
		SetRatUse(true);
	}
	else
	{ // ��L�ȊO

		// �ړI�̌����̈ړ��ʂ�ݒ肷��
		m_pFan->SetRotMoveDest(FAN_MOVE_OFF);
		SetCatUse(true);
		SetRatUse(false);
	}
}