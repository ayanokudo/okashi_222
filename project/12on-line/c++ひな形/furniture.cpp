//===================================================
//
//    �ǂ̏���[wall.cpp]
//    Author:����@�r�H
//
//====================================================
//**********************************
//�C���N���[�h
//**********************************
#include "furniture.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "boss.h"

//==================================
// �R���X�g���N�^
//==================================
LPDIRECT3DTEXTURE9 CFurniture::m_apTexture[FURNITURE_MAX] = {};
CModel::Model CFurniture::m_model[FURNITURE_MAX] = {};
char *CFurniture::m_apTextureName[FURNITURE_MAX] = 
{
    "./data/Models/furniture/ueki.x",
    "./data/Models/furniture/ueki.x",
    "./data/Models/furniture/ueki.x"
};

//==================================
// �R���X�g���N�^
//==================================
CFurniture::CFurniture() :CModel(OBJTYPE_FURNITURE)
{
	m_type = FURNITURE_CHAIR;		// ���̎�ނ̏�����
	m_pos = { 0.0f,0.0f,0.0f };		// pos�̏�����
	m_posold = { 0.0f,0.0f,0.0f };	// �O�̈ʒu�̏�����
	m_size = { 0.0f,0.0f,0.0f };	// size�̏�����
}

//==================================
// �f�X�g���N�^
//==================================
CFurniture::~CFurniture()
{
}

//==================================
// ��������
//==================================
CFurniture * CFurniture::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, FURNITURE type)
{
	//�C���X�^���X�𐶐�
	CFurniture *pWall = new CFurniture;
	//NULL�`�F�b�N
	if (pWall != NULL)
	{
		//���ꂼ��̏���������
		pWall->m_pos = pos;
		pWall->m_rot = rot;
		pWall->m_size = size;
		pWall->Init();
		pWall->m_type = type;
		pWall->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		pWall->SetRot(rot);
		//pWall->SetSize(size);
		pWall->SetObjType(OBJTYPE_FURNITURE);
	}
	//�|�C���^��Ԃ�
	return pWall;
}

//==================================
// �e�N�X�`�����[�h����
//==================================
HRESULT CFurniture::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    for (int nCount = 0; nCount < FURNITURE_MAX; nCount++)
    {
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_apTextureName[nCount],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_model[nCount].pBuffMat,
		NULL,
		&m_model[nCount].nNumMat,
		&m_model[nCount].pMesh);
    }

	
	return S_OK;
}

//==================================
// �e�N�X�`���j��
//==================================
void CFurniture::Unload(void)
{
    for (int nCntType = 0; nCntType < FURNITURE_MAX; nCntType++)
    {
        //���b�V���̔j��
        if (m_model[nCntType].pMesh != NULL)
        {
            m_model[nCntType].pMesh->Release();
            m_model[nCntType].pMesh = NULL;
        }
        //�}�e���A���̔j��
        if (m_model[nCntType].pBuffMat != NULL)
        {
            m_model[nCntType].pBuffMat->Release();
            m_model[nCntType].pBuffMat = NULL;
        }
    }
}

//==================================
// ����������
//==================================
HRESULT CFurniture::Init(void)
{
	CModel::Init();
	CModel::BindModel(m_model[m_type].pMesh,m_model[m_type].pBuffMat,m_model[m_type].nNumMat);
	// �ǂ�肿����Ƒ傫�߂ɓ����蔻����Ƃ�
	D3DXVECTOR3 collisionSize = m_size + D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	if (m_rot.y == 0)
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
void CFurniture::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}

	CModel::Uninit();
}

//==================================
// �X�V����
//==================================
void CFurniture::Update(void)
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
void CFurniture::Draw(void)
{
	CModel::Draw();
}

//==================================
// �v���C���[�ƕǂ̓����蔻��
//==================================
void CFurniture::CollisionPlayer(void)
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
void CFurniture::CollisionEnemy(void)
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
void CFurniture::CollisionBoss(void)
{

	CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);
	while (pBoss != NULL)
	{
		if (CCollision::CollisionSphereToBox(pBoss->GetCollision(), m_pCollision))
		{
			// �v���C���[���W�̎擾
			D3DXVECTOR3 playerPos = pBoss->GetPos();
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
			playerPos = shortrectPos + playerPos * pBoss->GetCollision()->GetCollisionRadius();
			// �v���C���[���W�̃Z�b�g
			pBoss->SetPos(playerPos);
			// �v���C���[�̃R���W�����̍��W�̃Z�b�g
			pBoss->GetCollision()->SetPos(playerPos);
		}
		pBoss = (CBoss*)pBoss->GetNext();
	}

}

//==================================
// �e�ƕǂ̓����蔻��
//==================================
void CFurniture::CollisionBullet(void)
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
