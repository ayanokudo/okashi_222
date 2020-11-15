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
#include "particle.h"
#include "item.h"
#include "score.h"
#include "scene.h"
#include "particle.h"
#include "lostpoint.h"
#include "wall.h"
#include "sound.h"
#include "file.h"
#include "collect.h"
#include "billboard.h"
#include "boss.h"

//*****************************
// �}�N����`
//*****************************
#define ENEMY_CARRIER_MODEL_PATH	"./data/Texts/MouseData_Bule.txt"	//�^�уl�Y�~�̃��f�����
#define ENEMY_ESCORT_MODEL_PATH		"./data/Texts/MouseData_Red.txt"	//���l�Y�~�̃��f�����

#define WALK_ANIM_PATH  "data/Texts/nezumi_walk.txt"      // �����A�j���[�V�����̃p�X

#define SWEAT_PATH "data/Textures/Sweat.png"              // ���̃e�N�X�`��
#define SWEAT_SIZE D3DXVECTOR3(40.0f,80.0f,0.0f)          // ���̃T�C�Y
#define ANIM_SPEED 7          // �A�j���[�V�������x
#define MAX_ANIMATION_X 5      // �A�j���[�V������ ��
#define MAX_ANIMATION_Y 1     // �A�j���[�V������ �c


#define ENEMY_SPEED 10
#define ENEMY_RAND rand() % 8 + 1
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  80
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_MOVE_RATE 0.05f 
#define ENEMY_DIRECTION_RATE 0.1f              // ������ς���Ƃ��̌W��
#define ENEMY_ESCORT_LIFE 100
#define ENEMY_CARRIER_LIFE 200
#define ENEMY_UP_SCORE 1000

#define STATE_COUNT_DAMAGE 10                               // �_���[�W��Ԃ̃J�E���g
#define DAMAGE_STATE_COLOR D3DXCOLOR(0.7f,0.0f,0.0f,1.0f)   // �_���[�W��Ԃ̃J���[

#define ITEM_DROP_RANDOM_KOBAN rand() % 10 + 1 == 5
#define ITEM_DROP_RANDOM_LIFE rand() % 6 + 1 == 4

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CModel::Model CEnemy::m_model[ENEMY_MAX][MAX_PARTS_NUM] = {};
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
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
	// �ϐ��̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pCollision = NULL;
	m_pRadiusColision = NULL;
	m_fRotYDist = D3DXToRadian(180.0f);
	m_nCount = 0;
	m_nCountMotion = 0;
	m_bRd = false;
	m_bCarrier = false;
	m_nLife = 0;
	memset(&m_pMotion, 0, sizeof(m_pMotion));
	m_bRoute = false;
	m_state = STATE_NORMAL;
	m_nCntState = 0;
	m_pBilboard = NULL;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, ENEMY type)
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

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SWEAT_PATH, &m_pTexture);

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
		//�^�уl�Y�~
	case ENEMY_CARRIER:
		m_nLife = ENEMY_CARRIER_LIFE;
		CCollect::AddObj();
		break;
		//���l�Y�~
	case ENEMY_ESCORT:
		m_nLife = ENEMY_ESCORT_LIFE;
		break;
	}
	
	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);
	
	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);

	// ���[�V�����̐���
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_pMotion[nCntAnim] = CMotion::Create(GetPartsNum(), m_achAnimPath[nCntAnim], GetModelData());
	}

	m_pMotion[WALK]->SetActiveAnimation(true);
	// ��Ԃ̏�����
	m_state = STATE_NORMAL;
	// �J�E���g�̏�����
	m_nCntState = 0;
	m_pBilboard = NULL;
	m_fRotYDist = D3DXToRadian(180.0f);
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

	if (m_pBilboard != NULL)
	{
		m_pBilboard->Uninit();
		m_pBilboard = NULL;
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
void CEnemy::Update(void)
{
	// �ڕW�l�̏�����
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���W
	D3DXVECTOR3 pos = GetPos();

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

	CBoss*pBoss = (CBoss*)GetTop(OBJTYPE_BOSS);
	if (CGame::GetGameMode() == CGame::GAME_NORMAL)// != CBoss::SPAWN)
	{// �{�X��ȊO

		// ����
		m_move += (m_moveDest - m_move) * ENEMY_MOVE_RATE;

		// �ړ��ʂ𑫂�
		pos += m_move;

		// ���W�̃Z�b�g
		SetPos(pos);
	}
	else if (pBoss != NULL)
	{// �{�X���X�|�[�����[�V����������Ȃ��Ƃ�

		if (pBoss->GetMotion() != CBoss::SPAWN)
		{
			// ����
			m_move += (m_moveDest - m_move) * ENEMY_MOVE_RATE;

			// �ړ��ʂ𑫂�
			pos += m_move;

			// ���W�̃Z�b�g
			SetPos(pos);
		}
		else
		{
			m_fRotYDist = D3DXToRadian(180.0f);
		}
	}
	else
	{
		m_fRotYDist = D3DXToRadian(180.0f);
	}

	// �����̊Ǘ�
	Direction();
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
	// ���̊Ǘ�
	Sweat();

	// �v�C���C���[�Ƃ̓����蔻��
	CollisionPlayer();
}

//******************************
// �`�揈��
//******************************
void CEnemy::Draw(void)
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
void CEnemy::Hit(int nDamage)
{
	// ���W
	D3DXVECTOR3 pos = GetPos();

	m_nLife -= nDamage;

	if (m_state == STATE_NORMAL)
	{
		m_state = STATE_DAMAGE;
		m_nCntState = 0;
	}

	if (m_nLife <= 0)
	{
		switch (m_type)
		{
		case ENEMY_CARRIER:
			//�X�R�AUP
			CScore::AddScore(ENEMY_UP_SCORE);
			CItem::Create(pos, CItem::CANDY);
			break;
		case ENEMY_ESCORT:
			//�X�R�AUP
			CScore::AddScore(ENEMY_UP_SCORE);
			if (ITEM_DROP_RANDOM_KOBAN)
			{
				CItem::Create(pos, CItem::KOBAN);
			}
			else if (ITEM_DROP_RANDOM_LIFE)
			{
				CItem::Create(pos, CItem::LIFE);
			}
		default:
			break;
		}

		// �p�[�e�B�N������
		// ��鐔���[�v
		for (int nCntPart = 0; nCntPart < 5; nCntPart++)
		{
			int nRandSize = rand() % 10 + 20;
			// �X�s�[�h�̃����_��
			int nRandSpeed = rand() % 2 + 2;
			// ���ł��p�x�̃����_��
			float fRandAngle = D3DXToRadian(rand() % 360);
			D3DXVECTOR3 partMove;
			partMove.x = cosf(fRandAngle)*nRandSpeed;
			partMove.y = 0.0f;
			partMove.z = sinf(fRandAngle)*nRandSpeed;
			// �p�[�e�B�N������
			CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y+20, GetPos().z), partMove, D3DXVECTOR3(nRandSize, nRandSize, 0.0f), 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		Uninit();
		return;
	}
}

//******************************
// �^�уl�Y�~�͈͔̔���̍X�V����
//******************************
void CEnemy::RangeDecisionCarrier(void)
{

	// �v���C���[�Ƃ̋���*�����l�͓K���ɑ傫���l�����Ƃ�
	float fDistance = 99999.0f;

	//�v���C���[�̏����擾
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			if (!CPlayer::GetDeath(nCount))
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
					m_bCarrier = true;

					// �܂̐���
					if (m_pBilboard == NULL)
					{// �܂���������Ă��Ȃ��Ƃ�
						// �܂̍��W
						D3DXVECTOR3 SweatPos;
						SweatPos.x = GetPos().x + cosf(GetRot().y-D3DXToRadian(120)) * 100;
						SweatPos.y = GetPos().y+20;				 
						SweatPos.z = GetPos().z + sinf(GetRot().y-D3DXToRadian(120)) * 100;
						// �܂̐���
						m_pBilboard = CBillboard::Create(SweatPos, SWEAT_SIZE);
						// �e�N�X�`���̐ݒ�
						m_pBilboard->BindTexture(m_pTexture);
						// �p�x�̐ݒ�
						m_pBilboard->SetAngle(GetRot().y+ D3DXToRadian(180));

						// �e�N�X�`��UV���W�̏�����
						m_nAnimX = 0;
						m_nAnimY = 0;

						// UV���W�̐ݒ�
						D3DXVECTOR2 uv[NUM_VERTEX];
						float fu = 1.0f / MAX_ANIMATION_X;
						float fv = 1.0f / MAX_ANIMATION_Y;

						uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
						uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
						uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
						uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

						// UV���W�Z�b�g
						m_pBilboard->SetTextureUV(uv);
					}
				}
			}
		}
	}
}

//******************************
// ���l�Y�~�͈͔̔���̍X�V����
//******************************
void CEnemy::RangeDecisionEscort(void)
{
	//�T�E���h�̃|�C���^�ϐ��錾
	CSound*pSound = CManager::GetSound();
	// �v���C���[�Ƃ̋���*�����l�͓K���ɑ傫���l�����Ƃ�
	float fDistance = 99999.0f;
	//�v���C���[�̏����擾
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			if (!CPlayer::GetDeath(nCount))
			{
				//�v���C���[�̈ʒu�����擾
				D3DXVECTOR3 playerPos = pPlayer->GetPos();
				//�G�l�~�[�̈ʒu�����擾
				D3DXVECTOR3 enemyPos = GetPos();

				//�v���C���[�ƓG�͈̔͂̓����蔻��
				if (CCollision::CollisionSphere(m_pRadiusColision, pPlayer->GetCollision()))
				{
					// �������ׂ�
					if (sqrtf(powf(enemyPos.x - playerPos.x, 2) + powf(enemyPos.y - playerPos.y, 2) + powf(enemyPos.z - playerPos.z, 2)) <= fDistance)
					{// �������߂�������
						fDistance = sqrtf(powf(enemyPos.x - playerPos.x, 2) + powf(enemyPos.y - playerPos.y, 2) + powf(enemyPos.z - playerPos.z, 2));
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
							//pSound->Play(CSound::SOUND_SE_EN_ATTACK_NAIL);
							// �U���̐���
							CScratch::Create(enemyPos, m_fRotYDist + D3DXToRadian(90), CScratch::SCRATCHUSER_ENEMY,GetID());
							m_nCount = 0;
						}
						//�e�̌����̐ݒ�
						m_fRotYDist = atan2(-(playerPos.x - enemyPos.x), -(playerPos.z - enemyPos.z));
					}
					//break;
				}	
			}

			if (!CPlayer::GetDeath(0) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(0)->GetCollision()) &&
				!CPlayer::GetDeath(1) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(1)->GetCollision()) ||
				!CPlayer::GetDeath(0) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(0)->GetCollision()) && CPlayer::GetDeath(1) ||
				!CPlayer::GetDeath(1) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(1)->GetCollision()) && CPlayer::GetDeath(0))
			{// �ǂ����̃v���C���[�ɂ��������ĂȂ��Ƃ�
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
	// �v���C���[�Ƃ̋���*�����l�͓K���ɑ傫���l�����Ƃ�
	float fDistance = 99999.0f;
	//false�̎�
	if (!m_bRd)
	{
		//�ړ�����
		Move();
	}
	if (m_bCarrier)
	{
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			CPlayer*pPlayer = CGame::GetPlayer(nCount);
			if (pPlayer != NULL)
			{
			}
		}
		// ���p�̎擾
		D3DXVECTOR3 pos = GetPos();
		CGame::GetLostPoint()->sort(pos);

		if (!m_bRoute)
		{
			// ���Ԗڂɋ߂��ڕW�n�_�ɍs����
			int nNumPoint = 0;
			// �ڕW���W�̎擾
			D3DXVECTOR3 distPos = CGame::GetLostPoint()->GetLostPos(nNumPoint);
			
			// ���񃋁[�v������
			int nLoop = 0;
			
			// �v���C���[�ő吔�����[�v
			for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
			{
				// ���S�m�F
				if (!CPlayer::GetDeath(nCnt))
				{
					if (GetDistance(pos, distPos) > GetDistance(CGame::GetPlayer(nCnt)->GetPos(), distPos))
					{//���g���v���C���[�̂ق����߂������ꍇ

						// �J�E���g�̏�����
						nCnt = 0;
						// �߂���������₷
						nNumPoint++;

						if (nNumPoint >= CGame::GetLostPoint()->GetNumLostPoint())
						{
							nNumPoint = 0;
						}

						// ���[�v���̃J�E���g
						nLoop++;
						if (nLoop >= CGame::GetLostPoint()->GetNumLostPoint())
						{// �S���̃|�C���g���v���C���[��艓��
							nNumPoint = 0;
							// �ڕW�n�_�̍X�V
							distPos = CGame::GetLostPoint()->GetLostPos(nNumPoint);
							break;
						}

						// �ڕW�n�_�̍X�V
						distPos = CGame::GetLostPoint()->GetLostPos(nNumPoint);

					}
					else
					{
						// �J�E���g��i�߂�
						nCnt++;
					}
				}
			}

			if (GetDistance(pos, distPos) >= 1000)
			{// �ڕW�ƈ�苗���ȏ�̎�
				// �ǂƂ̓����蔻��
				CWall*pWall = (CWall*)GetTop(OBJTYPE_WALL);
				while (pWall != NULL)
				{
					if (CCollision::CollisionSphereToBox(m_pCollision, pWall->GetCollision()))
					{// �������Ă���
					 
						// ��񓹂̐^�񒆂��o�R���ĖڕW�n�_�ɍs��
						m_bRoute = true;
					}

					pWall = (CWall*)pWall->GetNext();
				}
			}

			// �ڕW�Ɍ������Ĉړ��ʂ̐ݒ�
			m_moveDest = distPos - pos;
			D3DXVec3Normalize(&m_moveDest, &m_moveDest);
			m_moveDest *= ENEMY_SPEED;
			
		}
		else
		{// ��񓹂̐^�񒆂��o�R���ĖڕW�n�_�ɍs��
			// �ڕW���W�̎擾
			D3DXVECTOR3 distPos = CGame::GetLostPoint()->GetRoutePos(0);

			// �ڕW�Ɍ������Ĉړ��ʂ̐ݒ�
			m_moveDest = distPos - pos;
			D3DXVec3Normalize(&m_moveDest, &m_moveDest);
			m_moveDest *= ENEMY_SPEED;

			// �����蔻����̓񕪂̈�ɂ���
			m_pCollision->SetCollisionRadius(m_pCollision->GetCollisionRadius() / 2);

			if (CCollision::CollisionSphere(m_pCollision, CGame::GetLostPoint()->GetRouteCollision(0)))
			{
				m_bRoute = false;
			}

			// �����蔻���߂�
			m_pCollision->SetCollisionRadius(m_pCollision->GetCollisionRadius() * 2);
		}

		// �����̖ڕW�l
		m_fRotYDist = atan2f(-m_moveDest.z, m_moveDest.x) - D3DXToRadian(90);

		if (CCollision::CollisionSphere(m_pCollision, CGame::GetLostPoint()->GetLostCollision(0)))
		{// ���X�g�|�C���g�ɐG�ꂽ�Ƃ��ɏ���

			// �p�[�e�B�N������
			for (int nCntPart= 0; nCntPart < 5; nCntPart++)
			{
				int nRandSize = rand() % 10 + 40;
				int nRandSpeed = rand() % 2 + 2;
				float fRandAngle = D3DXToRadian(rand() % 360);
				D3DXVECTOR3 partMove;
				partMove.x = cosf(fRandAngle)*nRandSpeed;
				partMove.y = 0.0f;
				partMove.z = sinf(fRandAngle)*nRandSpeed;
				CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 20, GetPos().z),
					partMove,
					D3DXVECTOR3(nRandSize, nRandSize, 0.0f),
					50,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CParticle::PARTICLE_SMOKE);
			}
			// ����
			Uninit();
		}
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

//******************************
// ���̊Ǘ�
//******************************
void CEnemy::Sweat(void)
{
	// �܂̍X�V
	if (m_pBilboard != NULL)
	{
		// �܂̍��W
		D3DXVECTOR3 SweatPos;
		SweatPos.x = GetPos().x + cosf(GetRot().y - D3DXToRadian(120)) * 110;
		SweatPos.y = GetPos().y + 100;
		SweatPos.z = GetPos().z - sinf(GetRot().y - D3DXToRadian(120)) * 110;
		// �ʒu�̍X�V
		m_pBilboard->SetPos(SweatPos);
		// �p�x�̍X�V
		m_pBilboard->SetAngle(D3DXToDegree(atan2f(m_moveDest.z, m_moveDest.x)) + 40);

		// �e�N�X�`���A�j���[�V����

		// �J�E���g��i�߂�
		m_nCntAnim++;
		if (m_nCntAnim % ANIM_SPEED == 0)
		{// ���̊Ԋu��
			// �A�j���[�V����X���̉��Z
			m_nAnimX++;
			if (m_nAnimX >= MAX_ANIMATION_X)
			{// X�̍ő�l
			 // �A�j���[�V����X���̏�����
				m_nAnimX = 0;
				// �A�j���[�V����Y���̉��Z
				m_nAnimY++;
				if (m_nAnimY >= MAX_ANIMATION_X)
				{// Y�̍ő�l
				 // �A�j���[�V����Y���̏�����
					m_nAnimY = 0;
				}
			}

			// UV���W�̐ݒ�
			D3DXVECTOR2 uv[NUM_VERTEX];

			float fu = 1.0f / MAX_ANIMATION_X;
			float fv = 1.0f / MAX_ANIMATION_Y;

			uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY);
			uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
			uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY + fv);
			uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

			// UV���W�Z�b�g
			m_pBilboard->SetTextureUV(uv);
		}

	}
}


//******************************
// �v���C���[�Ƃ̓����蔻��
//******************************
void CEnemy::CollisionPlayer(void)
{
	// �v���C���[�������[�v
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// �v���C���[�̎��S�m�F
		if (!CPlayer::GetDeath(nCnt))
		{// �����Ă���
			
			// �v���C���[�̎擾
			CPlayer*pPlayer = CGame::GetPlayer(nCnt);
			if(pPlayer!=NULL)
			{
				// �����蔻��
				if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
				{// �������Ă���
					
					// �v���C���[�̊O�ɉ����o��
					D3DXVECTOR3 vec = (GetPos() - pPlayer->GetPos());
					D3DXVec3Normalize(&vec, &vec);
					vec *= (m_pCollision->GetCollisionRadius() + pPlayer->GetCollision()->GetCollisionRadius());

					D3DXVECTOR3 pos = GetPos();
					SetPos(pPlayer->GetPos() + vec);
					pPlayer->SetPos(pos - vec);

					// �_���[�W����
					pPlayer->Hit(1);
				}
			}

		}
	}
}
