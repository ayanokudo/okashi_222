////////////////////////////////////////////////////
//
//    bullet�N���X�̏���[bullet.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "bullet.h"
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
#define BULLET_TEXTURE_PATH_PLAYER "./data/Textures/Catvoice_Barrett.png" //�e�N�X�`���̃p�X
#define BULLET_TEXTURE_PATH_ENEMY  "./data/Textures/MouseBoss_Voice.png" //�e�N�X�`���̃p�X
#define PLAYER_BULLET_DAMAGE 100				//�v���C���[�̍U����
#define ENEMY_BULLET_DAMAGE 1
#define BULLET_SIZE_PLAYER 100                  // �T�C�Y
#define BULLET_SIZE_ENEMY 70                    // �T�C�Y
//******************************
// �ÓI�����o�ϐ��錾
//******************************
LPDIRECT3DTEXTURE9  CBullet::m_apTexture[BULLETUSER_MAX] = {}; // �e�N�X�`���|�C���^

//******************************
// �R���X�g���N�^
//******************************
CBullet::CBullet():CScene3d(OBJTYPE_BULLET)
{
	// �ϐ��̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_user = BULLETUSER_PLAYER;
	m_pCollision = NULL;
}

//******************************
// �f�X�g���N�^
//******************************
CBullet::~CBullet()
{
}

//******************************
// �N���G�C�g
//******************************
CBullet * CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const  BULLETUSER user)
{
	// �������̊m��
	CBullet *pBullet;
	pBullet = new CBullet;

	// �o���b�g���[�U�[�̐ݒ�
	pBullet->m_user = user;

	// ������
	pBullet->Init();

	// �e�l�̑���E�Z�b�g
	pBullet->SetPos(pos);                // ���W
	pBullet->SetObjType(OBJTYPE_BULLET); // �I�u�W�F�N�g�^�C�v
	pBullet->m_move = move;              // �ړ���
	pBullet->m_nLife = nLife;            // ����

	// �����蔻��̐���
	pBullet->m_pCollision = CCollision::CreateSphere(pos, BULLET_SIZE_PLAYER);
	return pBullet;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CBullet::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_PATH_PLAYER, &m_apTexture[BULLETUSER_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_PATH_ENEMY, &m_apTexture[BULLETUSER_ENEMY]);
	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CBullet::Unload(void)
{
	for (int nCnt = 0; nCnt < BULLETUSER_MAX; nCnt++)
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
HRESULT CBullet::Init(void)
{
	if (FAILED(CScene3d::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindTexture(m_apTexture[m_user]);

	switch (m_user)
	{
	case BULLETUSER_PLAYER:
		// �T�C�Y�̐ݒ�
		SetSize(D3DXVECTOR3(BULLET_SIZE_PLAYER, 0.0f, BULLET_SIZE_PLAYER));
		break;
	case BULLETUSER_ENEMY:
		// �T�C�Y�̐ݒ�
		SetSize(D3DXVECTOR3(BULLET_SIZE_ENEMY, 0.0f, BULLET_SIZE_ENEMY));
		break;
	default:
		break;
	}
	

	return S_OK;
}

//******************************
// �I������
//******************************
void CBullet::Uninit(void)
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
void CBullet::Update(void)
{
	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();
	// �ړ��ʂ̃v���X
	pos += m_move;
	// ���W�̃Z�b�g
	SetPos(pos);

	// �����蔻��̈ʒu�X�V
	m_pCollision->SetPos(GetPos());
	// �����蔻��
	CollisionBullet(m_user);

	// ���������炷
	m_nLife--;
	if (m_nLife <= 0)
	{// ������0�ȉ��ɂȂ����Ƃ�
	 // ����
		Uninit();
		return;
	}
	
}

//******************************
// �`�揈��
//******************************
void CBullet::Draw(void)
{
	CScene3d::Draw();
}


//******************************
// �����蔻��
//******************************
void CBullet::CollisionBullet(BULLETUSER user)
{
	switch (user)
	{
	case BULLETUSER_ENEMY:
	{
		CPlayer*pPlayer = (CPlayer*)CScene::GetTop(OBJTYPE_PLAYER);

		while (pPlayer != NULL)
		{

			if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
			{
				pPlayer->Hit(ENEMY_BULLET_DAMAGE);
				Uninit();
				break;
			}

			pPlayer = (CPlayer*)pPlayer->GetNext();
		}
	}
		break;
	case BULLETUSER_PLAYER:
	{
		CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
		CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);

		//�G�S��
		while (pEnemy != NULL)
		{

			if (CCollision::CollisionSphere(m_pCollision, pEnemy->GetCollision()))
			{
				pEnemy->Hit(PLAYER_BULLET_DAMAGE);
				Uninit();
				break;
			}
			pEnemy = (CEnemy*)pEnemy->GetNext();
		}

		//�{�X
		while (pBoss != NULL)
		{
			if (CCollision::CollisionSphere(m_pCollision, pBoss->GetCollision()))
			{
				pBoss->Hit(PLAYER_BULLET_DAMAGE);
				Uninit();
				break;
			}
			pBoss = (CBoss*)pBoss->GetNext();
		}
	}
		break;
	default:
		break;
	}
}
