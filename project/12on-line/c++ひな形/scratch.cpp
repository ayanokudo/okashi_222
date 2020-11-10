////////////////////////////////////////////////////
//
//    scratch�N���X�̏���[scratch.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "scratch.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "enemy.h"
#include "boss.h"

//*****************************
// �}�N����`
//*****************************
#define SCRATCH_TEXTURE_PATH_PLAYER "./data/Textures/scratch.png" //�e�N�X�`���̃p�X
#define SCRATCH_TEXTURE_PATH_ENEMY  "./data/Textures/Enemy_Attack.png" //�e�N�X�`���̃p�X
#define SCRATCH_COLOR D3DXCOLOR(1.0f,1.0f,0.3f,1.0f)       // �A�j���[�V�������x
#define SCRATCH_ANIM_SPEED 2                               // �A�j���[�V�������x
#define SCRATCH_MAX_ANIMATION_X 5                          // �A�j���[�V������ ��
#define SCRATCH_MAX_ANIMATION_Y 2                          // �A�j���[�V������ �c
#define SCRATCH_ANIM_PATTERN 10                            // �A�j���[�V�����̃p�^�[����
#define SCRATCH_ATTACK_PLAYER 50							//�v���C���[�U����
#define SCRATCH_ATTACK_ENEMY 1								//�G�l�~�[�U����

//******************************
// �ÓI�����o�ϐ��錾
//******************************
LPDIRECT3DTEXTURE9  CScratch::m_apTexture[SCRATCHUSER_MAX] = {}; // �e�N�X�`���|�C���^

//******************************
// �R���X�g���N�^
//******************************
CScratch::CScratch() :CScene3d(OBJTYPE_ATTACK)
{
	// �ϐ��̃N���A
	m_user = SCRATCHUSER_PLAYER;
	m_pCollision = NULL;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
	m_bAttackPlayer = true;
	m_bAttackEnemy = true;
}

//******************************
// �f�X�g���N�^
//******************************
CScratch::~CScratch()
{
}

//******************************
// �N���G�C�g
//******************************
CScratch * CScratch::Create(const D3DXVECTOR3 pos, const float fAngle,  const  SCRATCHUSER user,const int nPlayerNum)
{
	// �������̊m��
	CScratch *pScratch;
	pScratch = new CScratch;

	// ���[�U�[�̐ݒ�
	pScratch->m_user = user;
	// ������
	pScratch->Init();

	// �e�l�̑���E�Z�b�g
	pScratch->SetPos(pos);                             // ���W
	pScratch->SetRot(D3DXVECTOR3(0.0f, fAngle, 0.0f)); // �p�x
	pScratch->SetObjType(OBJTYPE_ATTACK);              // �I�u�W�F�N�g�^�C�v
	
	pScratch->m_nPlayerNum = nPlayerNum;
	// �����蔻��̐���
	pScratch->m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(pos.x, pos.y-SCRATCH_HEIGHT, pos.z), SCRATCH_COLLISION_SIZE);

	return pScratch;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CScratch::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, SCRATCH_TEXTURE_PATH_PLAYER, &m_apTexture[SCRATCHUSER_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, SCRATCH_TEXTURE_PATH_ENEMY, &m_apTexture[SCRATCHUSER_ENEMY]);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CScratch::Unload(void)
{
	for (int nCnt = 0; nCnt < SCRATCHUSER_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}


//******************************
// ����������
//******************************
HRESULT CScratch::Init(void)
{
	if (FAILED(CScene3d::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindTexture(m_apTexture[m_user]);
	if (m_user == SCRATCHUSER_PLAYER)
	{
		// �T�C�Y�̐ݒ�
		SetSize(D3DXVECTOR3(-SCRATCH_SIZE_PLAYER, 0.0f, -SCRATCH_SIZE_PLAYER));
	}
	else
	{
		// �T�C�Y�̐ݒ�
		SetSize(D3DXVECTOR3(-SCRATCH_SIZE_ENEMY, 0.0f, -SCRATCH_SIZE_ENEMY));
	}

	// UV���W�̐ݒ�
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
	float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

	// UV���W�Z�b�g
	SetTextureUV(uv);

	// �J���[�̐ݒ�
	SetColor(SCRATCH_COLOR);
	return S_OK;
}

//******************************
// �I������
//******************************
void CScratch::Uninit(void)
{
	// �R���W�����̏I������
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}

	CScene3d::Uninit();
}

//******************************
// �X�V����
//******************************
void CScratch::Update(void)
{
	// �����蔻��
	CollisionScratch(m_user);
	switch (m_user)
	{
	case SCRATCHUSER_ENEMY:
	{
		// �v���C���[�̎擾
		CEnemy*pEnemy = (CEnemy*)GetTop(OBJTYPE_ENEMY);
		while (pEnemy != NULL)
		{
			if (m_nPlayerNum == pEnemy->GetID())
			{
				// ���W�̐ݒ�
				D3DXVECTOR3 pos;
				float fRotY = pEnemy->GetRot().y - D3DXToRadian(90);
				pos.x = pEnemy->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE_ENEMY;
				pos.y = pEnemy->GetPos().y + SCRATCH_HEIGHT;
				pos.z = pEnemy->GetPos().z + sinf(fRotY) * SCRATCH_SIZE_ENEMY;
				SetPos(pos);

				// �p�x
				SetRot(D3DXVECTOR3(0.0f, fRotY + D3DXToRadian(90), 0.0f));
				m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
			}
			pEnemy = (CEnemy*)pEnemy->GetNext();
		}
		
	}
		break;
	case SCRATCHUSER_PLAYER:
	{
		// �v���C���[�̎擾
		CPlayer*pPlayer = CGame::GetPlayer(m_nPlayerNum);
		if (pPlayer != NULL)
		{
			// ���W�̐ݒ�
			D3DXVECTOR3 pos;
			float fRotY = pPlayer->GetRot().y - D3DXToRadian(90);
			pos.x = pPlayer->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE_PLAYER;
			pos.y = pPlayer->GetPos().y + SCRATCH_HEIGHT;
			pos.z = pPlayer->GetPos().z + sinf(fRotY) * SCRATCH_SIZE_PLAYER;
			SetPos(pos);

			// �p�x
			SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
			m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
		}
	}
	default:
		break;
	}
	// �A�j���[�V����*�A�j���[�V�������I�������������
	Animation();
}

//******************************
// �`�揈��
//******************************
void CScratch::Draw(void)
{
	CScene3d::Draw();
}


//******************************
// �����蔻��
//******************************
void CScratch::CollisionScratch(SCRATCHUSER user)
{

	switch (user)
	{
	case SCRATCHUSER_ENEMY:
	{
		if (m_bAttackEnemy)
		{
			for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
			{
				CPlayer*pPlayer = CGame::GetPlayer(nCount);
				if (pPlayer != NULL)
				{
					if (!CPlayer::GetDeath(nCount))
					{
						if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
						{
							pPlayer->Hit(SCRATCH_ATTACK_ENEMY);
							m_bAttackEnemy = false;
							//Uninit();
							//break;
						}
					}
				}
			}
		}
		break;
	}
	case SCRATCHUSER_PLAYER:
	{
		if (m_bAttackPlayer)
		{
			CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
			CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);
			
			//�G�S��
			while (pEnemy != NULL)
			{

				if (CCollision::CollisionSphere(m_pCollision, pEnemy->GetCollision()))
				{
					pEnemy->Hit(SCRATCH_ATTACK_PLAYER);
					m_bAttackPlayer = false;
					//Uninit();
					//break;
				}
				pEnemy = (CEnemy*)pEnemy->GetNext();
			}

			//�{�X
			while (pBoss != NULL)
			{
				if (CCollision::CollisionSphere(m_pCollision, pBoss->GetCollision()))
				{
					pBoss->Hit(SCRATCH_ATTACK_PLAYER);
					m_bAttackPlayer = false;
					//Uninit();
					//
					break;
				}
				pBoss = (CBoss*)pBoss->GetNext();
			}

		}
	default:
		break;
	}
	}
}

//******************************
// �A�j���[�V����
//******************************
void CScratch::Animation(void)
{
	// �A�j���[�V�����J�E���g��i�߂�
	m_nCntAnim++;

	// �A�j���[�V�����������̃J�E���g
	if (m_nCntAnim % SCRATCH_ANIM_SPEED == 0)
	{

		if (m_nCntAnim >= SCRATCH_ANIM_PATTERN*SCRATCH_ANIM_SPEED)
		{
			m_bAttackPlayer = true;
			m_bAttackEnemy = true;
			Uninit();
			return;
		}

		// �A�j���[�V����X���̉��Z
		m_nAnimX++;

		if (m_nAnimX >= SCRATCH_MAX_ANIMATION_X)
		{
			// �A�j���[�V����X���̏�����
			m_nAnimX = 0;
			m_nAnimY++;
		}

		// UV���W�̐ݒ�
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
		float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

		// UV���W�Z�b�g
		SetTextureUV(uv);
	}
}
