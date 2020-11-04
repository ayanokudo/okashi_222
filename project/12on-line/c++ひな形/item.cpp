////////////////////////////////////////////////////
//
//    item�N���X�̏���[item.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "bullet.h"
#include "scene3d.h"
#include "debug_log.h"
#include "collision.h"
#include "player.h"
#include "score.h"
#include "collect.h"

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //���f���̃p�X
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //���f���̃p�X
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //���f���̃p�X
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //���f���̃p�X

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CItem::m_pMeshModel[ITEM_MAX] = {};   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CItem::m_pBuffMatModel[ITEM_MAX] = {};	//�}�e���A�����ւ̃|�C���^
DWORD        CItem::m_nNumMatModel[ITEM_MAX] = {};	    //�}�e���A�����̐�

//******************************
// �R���X�g���N�^
//******************************
CItem::CItem() :CModel(OBJTYPE_PLAYER)
{
	m_pCollision = NULL;
}

//******************************
// �f�X�g���N�^
//******************************
CItem::~CItem()
{
}

//******************************
// �N���G�C�g
//******************************
CItem * CItem::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CItem *pItem;
	pItem = new CItem;

	// ������
	pItem->Init();

	// �e�l�̑���E�Z�b�g
	pItem->SetPos(pos);
	// �e�l�̑���E�Z�b�g
	pItem->SetObjType(OBJTYPE_ITEM); // �I�u�W�F�N�g�^�C�v
	return pItem;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CItem::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[CANDY],
		NULL,
		&m_nNumMatModel[CANDY],
		&m_pMeshModel[CANDY]);

	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[KOBAN],
		NULL,
		&m_nNumMatModel[KOBAN],
		&m_pMeshModel[KOBAN]);

	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[LIFE],
		NULL,
		&m_nNumMatModel[LIFE],
		&m_pMeshModel[LIFE]);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CItem::Unload(void)
{
	//���b�V���̔j��
	for (int nCount = 0; nCount < ITEM_MAX; nCount++)
	{
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
HRESULT CItem::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	for (int nCount = 0; nCount < ITEM_MAX; nCount++)
	{
		BindModel(m_pMeshModel[nCount], m_pBuffMatModel[nCount], m_nNumMatModel[nCount]);
	}
	// �����蔻��̐���
	m_pCollision = CCollision::CreateSphere(GetPos(), 100);
	return S_OK;
}

//******************************
// �I������
//******************************
void CItem::Uninit(void)
{
	// �R���W�����̏I������
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}

	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CItem::Update(void)
{
	// ���W
	D3DXVECTOR3 pos = GetPos();

	// ���W�̃Z�b�g
	SetPos(pos);

	// �����蔻��̈ʒu�X�V
	m_pCollision->SetPos(GetPos());

	CollisionItem();
}

//******************************
// �`�揈��
//******************************
void CItem::Draw(void)
{
	CModel::Draw();
}

//******************************
// �`�揈��
//******************************
void CItem::CollisionItem(void)
{
	//�v���C���[�̏����擾
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			//�v���C���[�̈ʒu�����擾
			D3DXVECTOR3 playerPos = pPlayer->GetPos();
			//�v���C���[�ƓG�͈̔͂̓����蔻��
			if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
			{
				CScore::AddScore(1000);
				CCollect::Collect();
				Uninit();
				break;
			}
		}
	}
}
