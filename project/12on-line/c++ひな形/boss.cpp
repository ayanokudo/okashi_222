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
#include "motion.h"
#include "debug_log.h"

//*****************************
// �}�N����`
//*****************************
#define BOSS_PATH	"./data/Texts/BossData.txt"	//�^�уl�Y�~�̃��f�����

#define WALK_PATH    "data/Texts/BossMotion/Boss_taiki.txt"             // �������[�V�����̃p�X
#define BREATH_PATH  "data/Texts/BossMotion/Boss_Attack_breath.txt"     // �u���X���[�V�����̃p�X
#define SCRATH_PATH  "data/Texts/BossMotion/Boss_Attack_hikkaki.txt"    // �Ђ��������[�V�����̃p�X
#define TAIL_PATH    "data/Texts/BossMotion/Boss_Attack_kaiten.txt"     // �����ۃ��[�V�����̃p�X

#define ENEMY_SPEED 5
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  100
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_DIRECTION_RATE 0.1f  // ������ς���Ƃ��̌W��
#define TAIL_RADIUS 50             // �����ۂ̔��a

#define ATTACK_PATTARN 3            // �U���p�^�[��
#define ATTACK_BASE 200             // �U������^�C�~���O�̃x�[�X�l
#define BOSS_LIFE 1500              // �{�X�̃��C�t
#define BULLET_INTERVAL 20          // �e�̃C���^�[�o��

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
//LPD3DXMESH   CBoss::m_pMeshModel = {};   	//���b�V�����ւ̃|�C���^
//LPD3DXBUFFER CBoss::m_pBuffMatModel = {};	//�}�e���A�����ւ̃|�C���^
//DWORD        CBoss::m_nNumMatModel = {};	//�}�e���A�����̐�
CModel::Model CBoss::m_model[MAX_PARTS_NUM] = {};
int CBoss::m_nNumModel = 0;
char CBoss::m_achAnimPath[MOTION_MAX][64]
{
	{ WALK_PATH },	  // �������[�V����
	{ BREATH_PATH },  // �u���X���[�V����
	{ SCRATH_PATH },  // �Ђ��������[�V����
	{ TAIL_PATH },	  // �����ۃ��[�V����
};

//******************************
// �R���X�g���N�^
//******************************
CBoss::CBoss() :CModelHierarchy(OBJTYPE_BOSS)
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
	memset(&m_pMotion, 0, sizeof(m_pMotion));
	m_motionState = WALK;
	m_bMotion = false;
	m_nCntBullet = 0;
	m_pCollisionTail = NULL;
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
	CBoss *pBoss;
	pBoss = new CBoss;

	if (pBoss != NULL)
	{
		// ������
		pBoss->Init();

		// �e�l�̑���E�Z�b�g
		pBoss->SetPos(pos);               // ���W
		pBoss->SetObjType(OBJTYPE_BOSS); // �I�u�W�F�N�g�^�C�v
	}

	return pBoss;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CBoss::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �t�@�C���I�[�v��
	FILE*pFile = NULL;

	pFile = fopen(BOSS_PATH, "r");


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
				&m_model[nCnt].pBuffMat,
				NULL,
				&m_model[nCnt].nNumMat,
				&m_model[nCnt].pMesh);

			// ���̕�����ǂݍ���
			fscanf(pFile, "%s", chChar);
		}
	}

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CBoss::Unload(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		//���b�V���̔j��
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CBoss::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[0], BOSS_PATH)))
	{
		return E_FAIL;
	}

	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);

	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);

	m_pCollisionTail = CCollision::CreateSphere(GetPos(), TAIL_RADIUS);
	m_nLife = BOSS_LIFE;
	// ���[�V�����̐���
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

	CModelHierarchy::Uninit();
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


	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		SetMotion(BREARH);
		m_bMotion = true;
	}

	if (m_motionState == BREARH)
	{
		Brearh();
	}

	// ���[�V�����Ǘ�
	MotionManager();
}

//******************************
// �`�揈��
//******************************
void CBoss::Draw(void)
{
	CModelHierarchy::Draw();
}

//******************************
// �q�b�g����
//******************************
void CBoss::Hit(int nDamage)
{
	m_nLife -= nDamage;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
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

//=============================================================================
// �u���X
// Author : ���V ����
//=============================================================================
void CBoss::Brearh(void)
{

	if (m_pMotion[BREARH]->GetKey() >= 3)
	{
		// �J�E���g��i�߂�
		m_nCntBullet++;

		if (m_nCntBullet%BULLET_INTERVAL == 0)
		{//���̊Ԋu�ŋ����o��

			// �e���o������
			float fAngle = GetModelData()[0].rot.y + GetModelData()[1].rot.y + GetRot().y - D3DXToRadian(90);
			// �e�̈ړ���
			D3DXVECTOR3 bulletMove;
			bulletMove.x = cosf(fAngle) * -BULLET_SPEED_ENEMY;
			bulletMove.y = 0.0f;
			bulletMove.z = sinf(fAngle) * BULLET_SPEED_ENEMY;
			CBullet::Create(GetPos(), bulletMove, 100, CBullet::BULLETUSER_ENEMY);
		}
	}

}

void CBoss::Tail(void)
{
}

//=============================================================================
// ���[�V�����Ǘ�
// Author : ���V ����
//=============================================================================
void CBoss::MotionManager(void)
{
	if (m_bMotion)
	{// �U���t���O�������Ă�Ƃ�
		if (!m_pMotion[BREARH]->GetActiveAnimation() && !m_pMotion[SCRATCH]->GetActiveAnimation() && !m_pMotion[TAIL]->GetActiveAnimation())
		{// �U�����[�V������false�̎�
			SetMotion(WALK);
			m_bMotion = false;
		}
	}
}

//=============================================================================
// ���[�V���������ׂ�false�ɂ���
// Author : ���V ����
//=============================================================================
void CBoss::MotionFalse(void)
{
	// �A�j���[�V���������ׂ�false�ɂ���
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_pMotion[nCntAnim]->SetActiveAnimation(false);
	}
}

//=============================================================================
// ���[�V�����Z�b�g
// Author : ���V ����
//=============================================================================
void CBoss::SetMotion(MOTION motionState)
{
	m_motionState = motionState;

	if (!m_pMotion[m_motionState]->GetActiveAnimation())
	{// ���݂̃��[�V������false�̂Ƃ�
	 // ���[�V�����̏�����
		MotionFalse();
		// ���݂̃��[�V������true�ɂ���
		m_pMotion[m_motionState]->SetActiveAnimation(true);
	}
}
