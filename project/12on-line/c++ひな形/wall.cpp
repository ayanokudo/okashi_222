//===================================================
//
//    �ǂ̏���[wall.cpp]
//    Author:����@�r�H
//
//====================================================
//**********************************
//�C���N���[�h
//**********************************
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "boss.h"

//*****************************
// �}�N����`
//*****************************
#define WALL_1_TEXTURE_PATH		"./data/Textures/w.png"		 // �t���[�����O�̃e�N�X�`���̃p�X
#define WALL_2_TEXTURE_PATH		"./data/Textures/wall_right.png"	 // �܂��Ƃ̃e�N�X�`���̃p�X
#define WALL_3_TEXTURE_PATH		"./data/Textures/wall_left.png"    // �L�b�`���̏��̃e�N�X�`���̃p�X

//==================================
// �R���X�g���N�^
//==================================
LPDIRECT3DTEXTURE9 CWall::m_apTexture[WALL_MAX] = {};

//==================================
// �R���X�g���N�^
//==================================
CWall::CWall():CScene3d(OBJTYPE_WALL)
{
	m_type   =   WALL_NORMAL;			// ���̎�ނ̏�����
	m_pos    =	{ 0.0f,0.0f,0.0f };	// pos�̏�����
	m_posold =	{ 0.0f,0.0f,0.0f };	// �O�̈ʒu�̏�����
	m_size   =	{ 0.0f,0.0f,0.0f };	// size�̏�����
}

//==================================
// �f�X�g���N�^
//==================================
CWall::~CWall()
{
}

//==================================
// ��������
//==================================
CWall * CWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, WALL type)
{
	//�C���X�^���X�𐶐�
	CWall *pWall = new CWall;
	//NULL�`�F�b�N
	if (pWall != NULL)
	{
		//���ꂼ��̏���������
		pWall->m_pos = pos;
        pWall->m_rot = rot;
		pWall->m_size = size;
		pWall->m_type = type;
		pWall->Init();
		pWall->SetPos(pos);
        pWall->SetRot(rot);
		pWall->SetSize(size);
		pWall->SetObjType(OBJTYPE_WALL);
	}
	//�|�C���^��Ԃ�
	return pWall;
}

//==================================
// �e�N�X�`�����[�h����
//==================================
HRESULT CWall::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, WALL_1_TEXTURE_PATH, &m_apTexture[WALL_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, WALL_2_TEXTURE_PATH, &m_apTexture[WALL_RIGHT]);
	D3DXCreateTextureFromFile(pDevice, WALL_3_TEXTURE_PATH, &m_apTexture[WALL_LEFT]);

	return S_OK;
}

//==================================
// �e�N�X�`���j��
//==================================
void CWall::Unload(void)
{
	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		// �e�N�X�`���̉������
		if (m_apTexture[nCntWall] != NULL)
		{
			m_apTexture[nCntWall]->Release();
			m_apTexture[nCntWall] = NULL;
		}
	}
}

//==================================
// ����������
//==================================
HRESULT CWall::Init(void)
{
    if (m_type == 2)
    {
        int a = 0;
    }
	CScene3d::Init();
	CScene3d::BindTexture(m_apTexture[m_type]);
	// �ǂ�肿����Ƒ傫�߂ɓ����蔻����Ƃ�
	D3DXVECTOR3 collisionSize = m_size + D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	if (m_rot.y == 0|| m_rot.y == D3DXToRadian(180))
	{
		// �����蔻��̐���
		m_pCollision = CCollision::CreateBox(m_pos, collisionSize * 2);
	}
	else
	{
		float fSize = collisionSize.x;
		collisionSize.x = collisionSize.z;
		collisionSize.z = fSize;
		// �����蔻��̐���
		m_pCollision = CCollision::CreateBox(m_pos, collisionSize * 2);
	}
	return S_OK;
}

//==================================
// �I������
//==================================
void CWall::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}

	CScene3d::Uninit();
}

//==================================
// �X�V����
//==================================
void CWall::Update(void)
{
	// �����蔻��
	CollisionPlayer(); // �v���C���[
	CollisionEnemy();  // �G�l�~�[
	CollisionBoss();   // �{�X
	CollisionBullet(); // �e
}

//==================================
// �`�揈��
//==================================
void CWall::Draw(void)
{
	CScene3d::Draw();
}

//==================================
// �v���C���[�ƕǂ̓����蔻��
//==================================
void CWall::CollisionPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCntPlayer);
		if (pPlayer != NULL)
		{
			if (!CPlayer::GetDeath(nCntPlayer))
			{
				if (CCollision::CollisionSphereToBox(pPlayer->GetCollision(), m_pCollision))
				{
					// �v���C���[���W�̎擾
					D3DXVECTOR3 playerPos = pPlayer->GetPos();
					// �����蔻��̃T�C�Y�̎擾
					D3DXVECTOR3 collsionSize = m_pCollision->GetCollisionSize();

					// �{�b�N�X���̍ŒZ�n�_�̌���
					D3DXVECTOR3 shortrectPos;
					shortrectPos.x = CCollision::OnRange(playerPos.x, GetPos().x - collsionSize.x / 2, GetPos().x + collsionSize.x / 2);
					shortrectPos.y = CCollision::OnRange(playerPos.y, GetPos().y - collsionSize.y / 2, GetPos().y + collsionSize.y / 2);
					shortrectPos.z = CCollision::OnRange(playerPos.z, GetPos().z - collsionSize.z / 2, GetPos().z + collsionSize.z / 2);
					// �{�b�N�X����v���C���[�̕����x�N�g��
					playerPos = playerPos - shortrectPos;
					// ���K��
					D3DXVec3Normalize(&playerPos, &playerPos);
					// �ŒZ�n�_���瓖���蔻��̔��a������
					playerPos = shortrectPos + playerPos * pPlayer->GetCollision()->GetCollisionRadius();
					// �v���C���[���W�̃Z�b�g
					pPlayer->SetPos(playerPos);
					// �v���C���[�̃R���W�����̍��W�̃Z�b�g
					pPlayer->GetCollision()->SetPos(playerPos);
				}
			}
		}
	}
}

//==================================
// �G�l�~�[�ƕǂ̓����蔻��
//==================================
void CWall::CollisionEnemy(void)
{

	CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
	while (pEnemy != NULL)
	{
		if (CCollision::CollisionSphereToBox(pEnemy->GetCollision(), m_pCollision))
		{
			// �v���C���[���W�̎擾
			D3DXVECTOR3 playerPos = pEnemy->GetPos();
			// �����蔻��̃T�C�Y�̎擾
			D3DXVECTOR3 collsionSize = m_pCollision->GetCollisionSize();

			// �{�b�N�X���̍ŒZ�n�_�̌���
			D3DXVECTOR3 shortrectPos;
			shortrectPos.x = CCollision::OnRange(playerPos.x, GetPos().x - collsionSize.x / 2, GetPos().x + collsionSize.x / 2);
			shortrectPos.y = CCollision::OnRange(playerPos.y, GetPos().y - collsionSize.y / 2, GetPos().y + collsionSize.y / 2);
			shortrectPos.z = CCollision::OnRange(playerPos.z, GetPos().z - collsionSize.z / 2, GetPos().z + collsionSize.z / 2);
			// �{�b�N�X����v���C���[�̕����x�N�g��
			playerPos = playerPos - shortrectPos;
			// ���K��
			D3DXVec3Normalize(&playerPos, &playerPos);
			// �ŒZ�n�_���瓖���蔻��̔��a������
			playerPos = shortrectPos + playerPos * pEnemy->GetCollision()->GetCollisionRadius();
			// �v���C���[���W�̃Z�b�g
			pEnemy->SetPos(playerPos);
			// �v���C���[�̃R���W�����̍��W�̃Z�b�g
			pEnemy->GetCollision()->SetPos(playerPos);
		}
		pEnemy = (CEnemy*)pEnemy->GetNext();
	}

}

//==================================
// �{�X�ƕǂ̓����蔻��
//==================================
void CWall::CollisionBoss(void)
{

	CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);
	while (pBoss != NULL)
	{
		if (CCollision::CollisionSphereToBox(pBoss->GetCollision(), m_pCollision))
		{
			// �v���C���[���W�̎擾
			D3DXVECTOR3 bossPos = pBoss->GetPos();
			// �����蔻��̃T�C�Y�̎擾
			D3DXVECTOR3 collsionSize = m_pCollision->GetCollisionSize();

			// �{�b�N�X���̍ŒZ�n�_�̌���
			D3DXVECTOR3 shortrectPos;
			shortrectPos.x = CCollision::OnRange(bossPos.x, GetPos().x - collsionSize.x / 2, GetPos().x + collsionSize.x / 2);
			shortrectPos.y = CCollision::OnRange(bossPos.y, GetPos().y - collsionSize.y / 2, GetPos().y + collsionSize.y / 2);
			shortrectPos.z = CCollision::OnRange(bossPos.z, GetPos().z - collsionSize.z / 2, GetPos().z + collsionSize.z / 2);
			// �{�b�N�X����v���C���[�̕����x�N�g��
			bossPos = bossPos - shortrectPos;
			// ���K��
			D3DXVec3Normalize(&bossPos, &bossPos);
			// �ŒZ�n�_���瓖���蔻��̔��a������
			bossPos = shortrectPos + bossPos * pBoss->GetCollision()->GetCollisionRadius();
			// �v���C���[���W�̃Z�b�g
			pBoss->SetPos(bossPos);
			// �v���C���[�̃R���W�����̍��W�̃Z�b�g
			pBoss->GetCollision()->SetPos(bossPos);
		}
		pBoss = (CBoss*)pBoss->GetNext();
	}

}

//==================================
// �e�ƕǂ̓����蔻��
//==================================
void CWall::CollisionBullet(void)
{
	CBullet*pBullet = (CBullet*)CScene::GetTop(OBJTYPE_BULLET);
	while (pBullet != NULL)
	{
		if (!pBullet->GetReleaseFlag())
		{
			// ���̔��a��ێ�
			float fRadius = pBullet->GetCollision()->GetCollisionRadius();
			// ���a�𔼕��ɂ���
			pBullet->GetCollision()->SetCollisionRadius(fRadius / 2);
			if (CCollision::CollisionSphereToBox(pBullet->GetCollision(), m_pCollision))
			{
				// �v���C���[�̃R���W�����̍��W�̃Z�b�g
				pBullet->Uninit();
			}
			else
			{
				// ���̔��a�ɖ߂�
				pBullet->GetCollision()->SetCollisionRadius(fRadius);
			}
		}
		pBullet = (CBullet*)pBullet->GetNext();
	}

}
