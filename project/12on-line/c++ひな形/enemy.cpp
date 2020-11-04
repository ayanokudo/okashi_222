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
#include "scratch.h"
#include "motion.h"

//*****************************
// �}�N����`
//*****************************
#define ENEMY_CARRIER_MODEL_PATH	"./data/Texts/MouseData.txt"	//�^�уl�Y�~�̃��f�����
#define ENEMY_ESCORT_MODEL_PATH		"./data/Texts/MouseData.txt"	//���l�Y�~�̃��f�����

#define WALK_ANIM_PATH  "data/Texts/nezumi_walk.txt"      // �����A�j���[�V�����̃p�X

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
CModel::Model CEnemy::m_model[MAX_PLAYER][MAX_PARTS_NUM] = {};
int CEnemy::m_nNumModel = 0;
char CEnemy::m_achAnimPath[MOTION_MAX][64]
{
	{ WALK_ANIM_PATH },	   // �����A�j���[�V����
};

//******************************
// �R���X�g���N�^
//******************************
CEnemy::CEnemy() :CModelHierarchy(OBJTYPE_ENEMY)
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
		pEnemy->m_type = type;

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
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		// �t�@�C���I�[�v��
		FILE*pFile = NULL;

		if (nCntEnemy == ENEMY_CARRIER)
		{// �v���C���[�P
			pFile = fopen(ENEMY_CARRIER_MODEL_PATH, "r");

		}
		else
		{// �v���C���[�Q
			pFile = fopen(ENEMY_ESCORT_MODEL_PATH, "r");
		}

		if (pFile != NULL)
		{
			// �e�L�X�g�t�@�C���̉��

			char chChar[256] = {};
			fscanf(pFile, "%s", chChar);

			// "NUM_MODEL"�ǂݍ��ނ܂Ń��[�v
			while (strcmp(chChar, "NUM_MODEL") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}

			// �ǂݍ��ރ��f���̐�
			fscanf(pFile, "%*s %d # %*s", &m_nNumModel);

			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				// �ǂݍ��񂾕����i�[�p
				char chPath[64] = {};
				// "MODEL_FILENAME"��ǂݍ��ނ܂Ń��[�v
				while (strcmp(chChar, "MODEL_FILENAME") != 0)
				{
					fscanf(pFile, "%s", chChar);
				}
				// �t�@�C���p�X�̓ǂݍ���
				fscanf(pFile, "%*s %s", chPath);

				// X�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX(chPath,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_model[nCntEnemy][nCnt].pBuffMat,
					NULL,
					&m_model[nCntEnemy][nCnt].nNumMat,
					&m_model[nCntEnemy][nCnt].pMesh);

				// ���̕�����ǂݍ���
				fscanf(pFile, "%s", chChar);
			}
		}
	}

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CEnemy::Unload(void)
{
	for (int nCntType = 0; nCntType < ENEMY_MAX; nCntType++)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			//���b�V���̔j��
			if (m_model[nCntType][nCnt].pMesh != NULL)
			{
				m_model[nCntType][nCnt].pMesh->Release();
				m_model[nCntType][nCnt].pMesh = NULL;
			}
			//�}�e���A���̔j��
			if (m_model[nCntType][nCnt].pBuffMat != NULL)
			{
				m_model[nCntType][nCnt].pBuffMat->Release();
				m_model[nCntType][nCnt].pBuffMat = NULL;
			}
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CEnemy::Init(void)
{
	if (m_type == ENEMY_CARRIER)
	{// �^�уl�Y�~
		if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[m_type][0], ENEMY_CARRIER_MODEL_PATH)))
		{
			return E_FAIL;
		}
	}
	else
	{// ���l�Y�~
		if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[m_type][0], ENEMY_ESCORT_MODEL_PATH)))
		{
			return E_FAIL;
		}
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

	// �A�j���[�V�����̐���
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_pMotion[nCntAnim] = CMotion::Create(GetPartsNum(), m_achAnimPath[nCntAnim], GetModelData());
	}
	m_pMotion[WALK]->SetActiveAnimation(true);
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

	CModelHierarchy::Uninit();
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
	CModelHierarchy::Draw();
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
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

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
				//�����̐ݒ�
				m_fRotYDist = atan2((playerPos.x - enemyPos.x), (playerPos.z - enemyPos.z));

				// �ړ���
				D3DXVECTOR3 Move;
				Move.x = sinf(m_fRotYDist)*10.0f;
				Move.y = 0.0f;
				Move.z = cosf(m_fRotYDist)*10.0f;

				m_moveDest -= Move;
				break;
			}
			else
			{
				m_bRd = false;
			}
		}
	}
}

//******************************
// ���l�Y�~�͈͔̔���̍X�V����
//******************************
void CEnemy::RangeDecisionEscort(void)
{
	//�v���C���[�̏����擾
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			//�v���C���[�̈ʒu�����擾
			D3DXVECTOR3 playerPos = pPlayer->GetPos();
			//�G�l�~�[�̈ʒu�����擾
			D3DXVECTOR3 enemyPos = GetPos();


			//�v���C���[�ƓG�͈̔͂̓����蔻��
			if (CCollision::CollisionSphere(m_pRadiusColision, pPlayer->GetCollision()))
			{
				m_bRd = true;
				m_nCount++;
				m_nCntAttack++;
				//�����̐ݒ�
				m_fRotYDist = atan2((playerPos.x - enemyPos.x), (playerPos.z - enemyPos.z));

				// �ړ���
				D3DXVECTOR3 Move;
				Move.x = sinf(m_fRotYDist)*10.0f;
				Move.y = 0.0f;
				Move.z = cosf(m_fRotYDist)*10.0f;

				m_moveDest = Move;
				//���Ԋu�őł�
				if (m_nCount == 50)
				{
					// �e�̐���
					CScratch::Create(enemyPos, m_fRotYDist, CScratch::SCRATCHUSER_ENEMY, -1);
					m_nCount = 0;
				}
				//�e�̌����̐ݒ�
				m_fRotYDist = atan2(-(playerPos.x - enemyPos.x), -(playerPos.z - enemyPos.z));
				break;
			}
			else
			{
				//�G�l�~�[���ēx������
				m_bRd = false;
			}
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
