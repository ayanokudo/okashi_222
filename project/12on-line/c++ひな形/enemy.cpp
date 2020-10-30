////////////////////////////////////////////////////
//
//    enemy�N���X�̏���[enemy.cpp]
//    Author:����@�r�H
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "enemy.h"
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
#define ENEMY_CARRIER_MODEL_PATH	"./data/Models/cube.x"	//�^�уl�Y�~�̃��f�����
#define ENEMY_ESCORT_MODEL_PATH		"./data/Models/cat_sakamoto.x"	//���l�Y�~�̃��f�����
#define ENEMY_SPEED 5
#define ENEMY_RAND rand() % 8 + 1
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  50
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_MOVE_RATE 0.05f 
#define ENEMY_DIRECTION_RATE 0.1f              // ������ς���Ƃ��̌W��
#define ENEMY_ESCORT_LIFE 100
#define ENEMY_CARRIER_LIFE 100

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CEnemy::m_pMeshModel[ENEMY_MAX] = {};   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CEnemy::m_pBuffMatModel[ENEMY_MAX] = {};	//�}�e���A�����ւ̃|�C���^
DWORD        CEnemy::m_nNumMatModel[ENEMY_MAX] = {};	    //�}�e���A�����̐�

//******************************
// �R���X�g���N�^
//******************************
CEnemy::CEnemy() :CModel(OBJTYPE_ENEMY)
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
CEnemy::~CEnemy()
{

}

//******************************
// �N���G�C�g
//******************************
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, ENEMY type)
{
	// �������̊m��
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		// ������
		pEnemy->Init();

		// �e�l�̑���E�Z�b�g
		pEnemy->SetPos(pos);
		pEnemy->m_type = type;
		pEnemy->SetObjType(OBJTYPE_ENEMY); // �I�u�W�F�N�g�^�C�v
	}

	return pEnemy;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	//�^�уl�Y�~
	D3DXLoadMeshFromX(ENEMY_CARRIER_MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[ENEMY_CARRIER],
		NULL,
		&m_nNumMatModel[ENEMY_CARRIER],
		&m_pMeshModel[ENEMY_CARRIER]);

	//���l�Y�~
	D3DXLoadMeshFromX(ENEMY_ESCORT_MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[ENEMY_ESCORT],
		NULL,
		&m_nNumMatModel[ENEMY_ESCORT],
		&m_pMeshModel[ENEMY_ESCORT]);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CEnemy::Unload(void)
{
	for (int nCount = ENEMY_CARRIER; nCount < ENEMY_MAX; nCount++)
	{
		//���b�V���̔j��
		if (m_pMeshModel[nCount] != NULL)
		{
			m_pMeshModel[nCount]->Release();
			m_pMeshModel[nCount] = NULL;
		}
		//�}�e���A���̔j��
		if (m_pBuffMatModel[nCount] != NULL)
		{
			m_pBuffMatModel[nCount]->Release();
			m_pBuffMatModel[nCount] = NULL;
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CEnemy::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}
	for (int nCount = ENEMY_CARRIER; nCount < ENEMY_MAX; nCount++)
	{
		// �e�N�X�`�����蓖��
		BindModel(m_pMeshModel[nCount], m_pBuffMatModel[nCount], m_nNumMatModel[nCount]);
	}
	//���C�t�ݒ�
	switch (m_type)
	{
	case ENEMY_CARRIER:
		m_nLife = ENEMY_CARRIER_LIFE;
		break;

	case ENEMY_ESCORT:
		m_nLife = ENEMY_ESCORT_LIFE;
		break;
	}
	
	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);
	
	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);
	return S_OK;
}

//******************************
// �I������
//******************************
void CEnemy::Uninit(void)
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
void CEnemy::Update(void)
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

	//�G���Ƃ̓����̏�������
	switch (m_type)
	{
		//�^�уl�Y�~
	case ENEMY_CARRIER:
		RangeDecisionCarrier();
		MotionCarrier();
		break;
		//���l�Y�~
	case ENEMY_ESCORT:
		RangeDecisionEscort();
		MotionEscort();
		break;
	}
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
void CEnemy::Draw(void)
{
	CModel::Draw();
}

//******************************
// �q�b�g����
//******************************
void CEnemy::Hit(int nDamage)
{

}

//******************************
// �^�уl�Y�~�͈͔̔���̍X�V����
//******************************
void CEnemy::RangeDecisionCarrier(void)
{
	//�v���C���[�̏����擾
	CPlayer*pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu�����擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		D3DXVECTOR3 enemyPos = GetPos();
		//�v���C���[�ƓG�͈̔͂̓����蔻��
		if (CCollision::CollisionSphere(m_pRadiusColision, pPlayer->GetCollision()))
		{

		}
	}
}

//******************************
// ���l�Y�~�͈͔̔���̍X�V����
//******************************
void CEnemy::RangeDecisionEscort(void)
{
	//�v���C���[�̏����擾
	CPlayer*pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		//�v���C���[�̈ʒu�����擾
		D3DXVECTOR3 playerPos = pPlayer->GetPos();
		//�G�l�~�[�̈ʒu�����擾
		D3DXVECTOR3 enemyPos = GetPos();
		

		//�v���C���[�ƓG�͈̔͂̓����蔻��
		if (CCollision::CollisionSphere(m_pRadiusColision, pPlayer->GetCollision()))
		{
			//�G�l�~�[�̈ړ������Ȃ�����
			m_bRd = true;
			m_nCount++;
			//�����̐ݒ�
			m_fRotYDist = atan2((playerPos.x - enemyPos.x),(playerPos.z - enemyPos.z));
			
			// �ړ���
			D3DXVECTOR3 Move;
			Move.x = sinf(m_fRotYDist)*10.0f;
			Move.y = 0.0f;
			Move.z = cosf(m_fRotYDist)*10.0f;

			//���Ԋu�őł�
			if (m_nCount == 30)
			{
				enemyPos.y += 30;
				CBullet::Create(enemyPos, Move, 300,
					CBullet::BULLETUSER_ENEMY)->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

				m_nCount = 0;
			}
			//�e�̌����̐ݒ�
			m_fRotYDist = atan2(-(playerPos.x - enemyPos.x), -(playerPos.z - enemyPos.z));
		}
		else
		{
			//�G�l�~�[���ēx������
			m_bRd = false;
		}
	}
}

//******************************
// �^�уl�Y�~�̓����X�V����
//******************************
void CEnemy::MotionCarrier(void)
{
	//false�̎�
	if (!m_bRd)
	{
		//�ړ�����
		Move();
	}
	else
	{

	}
}

//******************************
// ���l�Y�~�̓����X�V����
//******************************
void CEnemy::MotionEscort(void)
{
	//false�̎�
	if (!m_bRd)
	{
		//�ړ�����
		Move();
	}
}

//******************************
// �G�̈ړ�����
//******************************
void CEnemy::Move(void)
{
	//�J�E���g�v���X
	m_nCountMotion++;
	//50�J�E���g�������痐�������ɓ���
	if (m_nCountMotion == 50)
	{
		//����
		m_nCountRand = ENEMY_RAND;
		m_nCountMotion = 0;
	}
	switch (m_nCountRand)
	{
	case 1:
		// ���ړ�
		m_moveDest.z = ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(180);
		break;
	case 2:
		// ���ړ�
		m_moveDest.z = -ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(0);
		break;
	case 3:
		// ���ړ�
		m_moveDest.x = ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(-90);
		break;
	case 4:
		// ���ړ�
		m_moveDest.x = -ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(90);
		break;
	case 5:
		//�@�΂�
		m_moveDest.z = sinf(45) * -ENEMY_SPEED;
		m_moveDest.x = cosf(45) * ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(-45);
		break;
	case 6:
		//�@�΂�
		m_moveDest.z = sinf(45) * -ENEMY_SPEED;
		m_moveDest.x = cosf(45) * -ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(45);
		break;
	case 7:
		//�@�΂�
		m_moveDest.z = sinf(45) * ENEMY_SPEED;
		m_moveDest.x = cosf(45) * ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(225);
		break;
	case 8:
		//�@�΂�
		m_moveDest.z = sinf(45) * ENEMY_SPEED;
		m_moveDest.x = cosf(45) * -ENEMY_SPEED;

		// �����̐ݒ�
		m_fRotYDist = D3DXToRadian(135);
		break;
	}
}

//******************************
// �L�����N�^�[�̌����̐ݒ�
//******************************
void CEnemy::Direction(void)
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
