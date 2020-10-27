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

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //���f���̃p�X

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CItem::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CItem::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CItem::m_nNumMatModel = 0;	    //�}�e���A�����̐�

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
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CItem::Unload(void)
{
	//���b�V���̔j��
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	//�}�e���A���̔j��
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
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
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);
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
}

//******************************
// �`�揈��
//******************************
void CItem::Draw(void)
{
	CModel::Draw();
}