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

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/cube.x"    //���f���̃p�X
#define ENEMY_SPEED 10
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  50

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPD3DXMESH   CEnemy::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CEnemy::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CEnemy::m_nNumMatModel = 0;	    //�}�e���A�����̐�

//******************************
// �R���X�g���N�^
//******************************
CEnemy::CEnemy() :CModel(OBJTYPE_ENEMY)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pCollision = NULL;
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
CEnemy * CEnemy::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CEnemy *pPlayer;
	pPlayer = new CEnemy;

	// ������
	pPlayer->Init();
	
	// �e�l�̑���E�Z�b�g
	pPlayer->SetPos(pos);
	pPlayer->SetObjType(OBJTYPE_ENEMY); // �I�u�W�F�N�g�^�C�v

	return pPlayer;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CEnemy::Load(void)
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
void CEnemy::Unload(void)
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
HRESULT CEnemy::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);
	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);
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

	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CEnemy::Update(void)
{
	D3DXVECTOR3 rot = GetRot();

	SetRot(rot);
	// �R���W�����̈ʒu�X�V
	m_pCollision->SetPos(GetPos());
}

//******************************
// �`�揈��
//******************************
void CEnemy::Draw(void)
{
	CModel::Draw();
}
