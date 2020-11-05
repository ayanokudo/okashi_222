////////////////////////////////////////////////////
//
//    enemy�N���X�̏���[enemy.cpp]
//    Author:����@�r�H
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "boss.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "bullet.h"

//*****************************
// �}�N����`
//*****************************
#define BOSS_CARRIER_MODEL_PATH	"./data/Models/cube.x"	//�^�уl�Y�~�̃��f�����
#define ENEMY_SPEED 5
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  100
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_DIRECTION_RATE 0.1f              // ������ς���Ƃ��̌W��

#define ATTACK_BASE 200             // �U������^�C�~���O�̃x�[�X�l

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CBoss::m_pMeshModel = {};   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CBoss::m_pBuffMatModel = {};	//�}�e���A�����ւ̃|�C���^
DWORD        CBoss::m_nNumMatModel = {};	//�}�e���A�����̐�

//******************************
// �R���X�g���N�^
//******************************
CBoss::CBoss() :CModel(OBJTYPE_ENEMY)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pCollision = NULL;
	m_pRadiusColision = NULL;
	m_fRotYDist = 0.0f;
	m_nCount = 0;
	m_nCountMotion = 0;
	m_bRd = false;
	m_nLife = 0;
}

//******************************
// �f�X�g���N�^
//******************************
CBoss::~CBoss()
{

}

//******************************
// �N���G�C�g
//******************************
CBoss * CBoss::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CBoss *pEnemy;
	pEnemy = new CBoss;

	if (pEnemy != NULL)
	{
		// ������
		pEnemy->Init();

		// �e�l�̑���E�Z�b�g
		pEnemy->SetPos(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY); // �I�u�W�F�N�g�^�C�v
	}

	return pEnemy;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CBoss::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	//�^�уl�Y�~
	D3DXLoadMeshFromX(BOSS_CARRIER_MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CBoss::Unload(void)
{
	//���b�V���̔j��
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}


//******************************
// ����������
//******************************
HRESULT CBoss::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);

	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);

	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);
	return S_OK;
}

//******************************
// �I������
//******************************
void CBoss::Uninit(void)
{
	// �R���W�����̏I������
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}
	if (m_pRadiusColision != NULL)
	{
		m_pRadiusColision->Uninit();
	}

	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CBoss::Update(void)
{
	// �ڕW�l�̏�����
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���W
	D3DXVECTOR3 pos = GetPos();

	// ����
	D3DXVECTOR3 rot = GetRot();

	// �����̐ݒ�
	SetRot(rot);

	// �����̊Ǘ�
	Direction();

	// �R���W�����̈ʒu�X�V
	m_pCollision->SetPos(GetPos());
	m_pRadiusColision->SetPos(GetPos());

	// ����
	m_move += (m_moveDest - m_move) * ENEMY_MOVE_RATE;

	// �ړ��ʂ𑫂�
	pos += m_move;

	// ���W�̃Z�b�g
	SetPos(pos);
}

//******************************
// �`�揈��
//******************************
void CBoss::Draw(void)
{
	CModel::Draw();
}

//******************************
// �q�b�g����
//******************************
void CBoss::Hit(int nDamage)
{

}

////******************************
//// �G�̈ړ�����
////******************************


//******************************
// �L�����N�^�[�̌����̐ݒ�
//******************************
void CBoss::Direction(void)
{
	// ���݂̃��b�g�̎擾
	D3DXVECTOR3 rot = GetRot();

	// �O����Ɖ�]���Ȃ��悤����
	while (m_fRotYDist - rot.y > D3DXToRadian(180))
	{
		m_fRotYDist -= D3DXToRadian(360);
	}
	while (m_fRotYDist - rot.y < D3DXToRadian(-180))
	{
		m_fRotYDist += D3DXToRadian(360);
	}

	// �����̍X�V
	rot.y += (m_fRotYDist - rot.y)*ENEMY_DIRECTION_RATE;
	// �����̐ݒ�
	SetRot(rot);
}

//=============================================================================
// �U������
// Author : AYANO KUDO
//=============================================================================
void CBoss::Attack(void)
{
    // �����_���ȃ^�C�~���O�ōU������
    if (rand() % ATTACK_BASE == 0)
    {
        // �v���C���[�Ƃ̋��������m�F

    }

}
