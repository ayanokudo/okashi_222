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
#include "score.h"
#include "debug_log.h"
#include "scratch.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "file.h"
#include "ui.h"

//*****************************
// �}�N����`
//*****************************
#define BOSS_PATH	"./data/Texts/BossData.txt"	//�^�уl�Y�~�̃��f�����

#define SPAWN_PATH   "data/Texts/BossMotion/Boss_Enshutsu.txt"             // �������[�V�����̃p�X
#define WALK_PATH    "data/Texts/BossMotion/Boss_taiki.txt"             // �������[�V�����̃p�X
#define BREATH_PATH  "data/Texts/BossMotion/Boss_Attack_breath.txt"     // �u���X���[�V�����̃p�X
#define SCRATH_PATH  "data/Texts/BossMotion/Boss_Attack_hikkaki.txt"    // �Ђ��������[�V�����̃p�X
#define TAIL_PATH    "data/Texts/BossMotion/Boss_Attack_kaiten.txt"     // �����ۃ��[�V�����̃p�X

#define BOSS_SPEED 8
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  130
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_DIRECTION_RATE 0.1f   // ������ς���Ƃ��̌W��
#define TAIL_RADIUS 100             // �����ۂ̔��a

#define ATTACK_PATTARN 3            // �U���p�^�[��
#define ATTACK_BASE 200             // �U������^�C�~���O�̃x�[�X�l
#define BOSS_LIFE 4000              // �{�X�̃��C�t
#define BULLET_INTERVAL 15          // �e�̃C���^�[�o��
#define BOSS_SCORE_UP 15000

#define MOVE_COUNT 100             // �ړ����̃J�E���g

#define STATE_COUNT_DAMAGE 10                               // �_���[�W��Ԃ̃J�E���g
#define DAMAGE_STATE_COLOR D3DXCOLOR(0.7f,0.0f,0.0f,1.0f)   // �_���[�W��Ԃ̃J���[

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
	{ SPAWN_PATH },   // �N���Ƃ��̃��[�V����
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
	memset(m_bHitTail, 0, sizeof(m_bHitTail));
	m_nCntMove = 0;
	m_nTargetNum = 0;
	m_state = STATE_NORMAL;
	m_nCntState = 0;
	m_pUi = NULL;
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
	
	// �������[�V�����������
	SetMotion(SPAWN);
	m_bMotion = true;

	// �^�[�Q�b�g�̏�����
	ChangeTarget(1);

	// �����ۂ̃q�b�g�m�F�̏�����
	memset(m_bHitTail, 0, sizeof(m_bHitTail));

	// �����̌����̐ݒ�
	SetRot(D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f));
	m_fRotYDist = D3DXToRadian(180.0f);
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
		m_pCollision = NULL;
	}
	if (m_pRadiusColision != NULL)
	{
		m_pRadiusColision->Uninit();
		m_pRadiusColision = NULL;
	}
	if (m_pCollisionTail != NULL)
	{
		m_pCollisionTail->Uninit();
		m_pCollisionTail = NULL;
	}

	// ���[�V�����̍폜
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		if (m_pMotion[nCntAnim] != NULL)
		{
			m_pMotion[nCntAnim]->Uninit();
			m_pMotion[nCntAnim] = NULL;
		}
	}

	CModelHierarchy::Uninit();
}

//******************************
// �X�V����
//******************************
void CBoss::Update(void)
{
	// �R���W�����̈ʒu�X�V
	m_pCollision->SetPos(GetPos());
	m_pRadiusColision->SetPos(GetPos());


	if (!m_bMotion)
	{
		// �^�[�Q�b�g�Ǘ�
		ChangeTarget();
		// �ړ�����
		Move();
	}
	// �����̊Ǘ�
	Direction();

	// �X�N���b�`
	Scratch();

	// �u���X
	Brearh();

	// ������
	Tail();
	
	// ���[�V�����Ǘ�
	MotionManager();

	if (CCollision::CollisionSphereToBox(m_pCollision, CFile::BossRoomCollision()))
	{
		// �v���C���[���W�̎擾
		D3DXVECTOR3 pos = GetPos();
		// �����蔻��̃T�C�Y�̎擾
		D3DXVECTOR3 collsionSize = CFile::BossRoomCollision()->GetCollisionSize();

		// �{�b�N�X���̍ŒZ�n�_�̌���
		D3DXVECTOR3 shortrectPos;
		shortrectPos.x = CCollision::OnRange(pos.x, CFile::BossRoomCollision()->GetPos().x - collsionSize.x / 2, CFile::BossRoomCollision()->GetPos().x + collsionSize.x / 2);
		shortrectPos.y = CCollision::OnRange(pos.y, CFile::BossRoomCollision()->GetPos().y - collsionSize.y / 2, CFile::BossRoomCollision()->GetPos().y + collsionSize.y / 2);
		shortrectPos.z = CCollision::OnRange(pos.z, CFile::BossRoomCollision()->GetPos().z - collsionSize.z / 2, CFile::BossRoomCollision()->GetPos().z + collsionSize.z / 2);
		// �{�b�N�X����v���C���[�̕����x�N�g��
		pos = pos - shortrectPos;
		// ���K��
		D3DXVec3Normalize(&pos, &pos);
		// �ŒZ�n�_���瓖���蔻��̔��a������
		pos = shortrectPos + pos * m_pCollision->GetCollisionRadius();
		// �v���C���[���W�̃Z�b�g
		SetPos(pos);
		// �v���C���[�̃R���W�����̍��W�̃Z�b�g
		GetCollision()->SetPos(pos);
	}

	// ��Ԃ̊Ǘ�

	if (m_state == STATE_DAMAGE)
	{// �_���[�W��Ԃ̎�

	 // �J�E���g��i�߂�
		m_nCntState++;
		if (m_nCntState > STATE_COUNT_DAMAGE)
		{// �J�E���g���K��l�𒴂�����

		 // �J�E���g�̏�����
			m_nCntState = 0;
			// ��Ԃ��m�[�}���ɖ߂�
			m_state = STATE_NORMAL;
		}
	}
}

//******************************
// �`�揈��
//******************************
void CBoss::Draw(void)
{
	if (m_state == STATE_DAMAGE)
	{// �_���[�W��Ԃ̎�

	 // ���ׂẴp�[�c��ԐF�ɂ���
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			D3DXMATERIAL*pMat = (D3DXMATERIAL*)GetModelData()[nCnt].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < GetModelData()[nCnt].nNumMat; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse = DAMAGE_STATE_COLOR;
			}
		}
	}

	CModelHierarchy::Draw();
}

//******************************
// �q�b�g����
//******************************
void CBoss::Hit(int nDamage)
{
	m_nLife -= nDamage;

	if (m_state == STATE_NORMAL)
	{
		m_state = STATE_DAMAGE;
		m_nCntState = 0;
	}

	if (m_nLife <= 0)
	{
		CScore::AddScore(BOSS_SCORE_UP);
		Uninit();
		CManager::GetFade()->SetFade(CManager::MODE_WIN);
		return;
	}
}

//******************************
// �ړ�����
// Author : ���V ����
//******************************
void CBoss::Move(void)
{

	if (!CPlayer::GetDeath(0) || !CPlayer::GetDeath(1))
	{// �ǂ������̃v���C���[�������Ă���Ƃ�

		// ���W
		D3DXVECTOR3 pos = GetPos();

		// �ڕW�l�̏�����
		m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �^�[�Q�b�g�̃v���C���[���W�̐ݒ�
		D3DXVECTOR3 playerPos = CGame::GetPlayer(m_nTargetNum)->GetPos();

		// �ړ��ʂ̌v�Z
		m_moveDest = playerPos - pos;
		D3DXVec3Normalize(&m_moveDest, &m_moveDest);
		m_moveDest *= BOSS_SPEED;
		m_moveDest.y = 0.0f;

		// ����
		m_move += (m_moveDest - m_move) * ENEMY_MOVE_RATE;

		// �ړ��ʂ𑫂�
		pos += m_move;

		m_fRotYDist = atan2f(m_move.x, m_move.z) + D3DXToRadian(180);
		// ���W�̃Z�b�g
		SetPos(pos);
	}

}

//******************************
// �^�[�Q�b�g��ς���
// Author : ���V ����
//******************************
void CBoss::ChangeTarget(int nNum)
{

	if (!CPlayer::GetDeath(0) && CPlayer::GetDeath(1))
	{// �v���C���[0�����������Ă���Ƃ�
		m_nTargetNum = 0;

		// �J�E���g��i�߂�
		m_nCntMove++;

		if (m_nCntMove%MOVE_COUNT == 0)
		{// ���J�E���g��

			// �U������
			Attack();
		}
	}
	else if (!CPlayer::GetDeath(1) && CPlayer::GetDeath(0))
	{// �v���C���[1�����������Ă���Ƃ�
		m_nTargetNum = 1;


		// �J�E���g��i�߂�
		m_nCntMove++;

		if (m_nCntMove%MOVE_COUNT == 0)
		{// ���J�E���g��

		 // �U������
			Attack();
		}
	}
	else
	{// ���������Ă���Ƃ�

		if (nNum == 1)
		{// ��������̎�
		
			// �^�[�Q�b�g�������_���ɕύX
			m_nTargetNum = rand() % MAX_PLAYER;
			// �J�E���g�̏�����
			m_nCntMove = 0;
		}
		else
		{// �������ꂶ��Ȃ��Ƃ�

			// �J�E���g��i�߂�
			m_nCntMove++;
		
			if (m_nCntMove%MOVE_COUNT == 0)
			{// ���J�E���g��

				// �^�[�Q�b�g�������_���ɕύX
				m_nTargetNum = rand() % MAX_PLAYER;

				// �U������
				Attack();
			}
		}
	}
}

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
// Author : ���V ����
//=============================================================================
void CBoss::Attack(void)
{
	//�T�E���h�̃|�C���^�ϐ��錾
	CSound*pSound = CManager::GetSound();
    // �����_���ȃ^�C�~���O�ōU������
	int nRandAttack = rand() % ATTACK_PATTARN;

	switch (nRandAttack)
	{
	case ATTACK_BREARH:
		// �u���X
		SetMotion(BREARH);
		m_bMotion = true;
		break;
	case ATTACK_SCRATCH:
		// �Ђ�����
		SetMotion(SCRATCH);
		m_bMotion = true;
		break;
	case ATTACK_TAIL:
		// ������
		SetMotion(TAIL);
		m_bMotion = true;
		break;
	default:
		break;
	}

}

//=============================================================================
// �u���X
// Author : ���V ����
//=============================================================================
void CBoss::Brearh(void)
{
	if (m_motionState == BREARH)
	{
		if (m_pMotion[BREARH]->GetKey() >= 3)
		{
			// �J�E���g��i�߂�
			m_nCntBullet++;

			if (m_nCntBullet%BULLET_INTERVAL == 0)
			{//���̊Ԋu�ŋ����o��

				// �e���o������
				float fAngle = GetModelData()[0].rot.y + GetModelData()[1].rot.y + GetRot().y - D3DXToRadian(90);
				
				// �e���o���ʒu
				D3DXVECTOR3 bulletPos;
				bulletPos.x = GetPos().x + cosf(GetModelData()[0].rot.y) * -50;
				bulletPos.y = GetPos().y;
				bulletPos.z = GetPos().z + sinf(GetModelData()[0].rot.y) * 50;

				// �e�̈ړ���
				D3DXVECTOR3 bulletMove;
				bulletMove.x = cosf(fAngle) * -BULLET_SPEED_ENEMY;
				bulletMove.y = 0.0f;
				bulletMove.z = sinf(fAngle) * BULLET_SPEED_ENEMY;

				CBullet::Create(bulletPos, bulletMove, 200, CBullet::BULLETUSER_ENEMY)->SetRot(GetRot());
			}
		}
	}

}

//=============================================================================
// �Ђ�����
// Author : ���V ����
//=============================================================================]
void CBoss::Scratch(void)
{
	if (m_pMotion[SCRATCH]->GetKey() == 1 && m_pMotion[SCRATCH]->GetFrame() == 0)
	{
		CScratch::Create(GetPos(), 0.0f, CScratch::SCRATCHUSER_BOSS, GetID());
	}
}

//=============================================================================
// �����ۍU��
// Author : ���V ����
//=============================================================================
void CBoss::Tail(void)
{
	// �����ۂ̈ʒu�ɓ����蔻���u��
	// �p�x�̎Z�o
	float fAngleTail = (GetModelData()[6].rot.y + GetModelData()[0].rot.y + GetRot().y) + D3DXToRadian(90);
	// ���W�̎Z�o
	D3DXVECTOR3 tailPos;
	tailPos.x = GetPos().x + cosf(fAngleTail)*-TAIL_RADIUS * 2;
	tailPos.y = GetPos().y;
	tailPos.z = GetPos().z + sinf(fAngleTail)*TAIL_RADIUS * 2;
	// ���W�̐ݒ�
	m_pCollisionTail->SetPos(tailPos);

	// �U���̔���

	if (m_motionState == TAIL)
	{
		// �ŏ��̐��t���[���͓�����Ȃ��悤�ɂ���
		if (m_pMotion[TAIL]->GetKey() >= 2)
		{
			// �v���C���[�������[�v
			for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
			{
				// �v���C���[�̐�����Ԃ̊m�F
				if (!CPlayer::GetDeath(nCnt))
				{
					// �v���C���[���̎擾
					CPlayer*pPlayer = CGame::GetPlayer(nCnt);
					if (pPlayer != NULL)
					{
						if (CCollision::CollisionSphere(m_pCollisionTail, pPlayer->GetCollision()))
						{
							// ���i�q�b�g���Ȃ��悤�t���O�����܂�
							if (!m_bHitTail[nCnt])
							{
								// �_���[�W����
								pPlayer->Hit(1);
								// �����ۂ𓖂�������Ԃ�
								m_bHitTail[nCnt] = true;
							}
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// ���[�V�����Ǘ�
// Author : ���V ����
//=============================================================================
void CBoss::MotionManager(void)
{
	if (m_bMotion)
	{// �U���t���O�������Ă�Ƃ�
		if (!m_pMotion[SPAWN]->GetActiveAnimation() && !m_pMotion[BREARH]->GetActiveAnimation() && !m_pMotion[SCRATCH]->GetActiveAnimation() && !m_pMotion[TAIL]->GetActiveAnimation())
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

		if (motionState == TAIL)
		{
			// �����ۂ̃q�b�g�m�F�̏�����
			memset(m_bHitTail, 0, sizeof(m_bHitTail));
		}
	}
}
