////////////////////////////////////////////////////
//
//    player�N���X�̏���[player.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "bullet.h"
#include "debug_log.h"

//*****************************
// �}�N����`
//*****************************
#define PLAYER_SPEED 10                          // �ړ��X�s�[�h
#define PLAYER_MOVE_RATE 0.05f                   // �ړ��̊����̌W��
#define PLAYER_DIRECTION_RATE 0.1f              // ������ς���Ƃ��̌W��

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************


//******************************
// �R���X�g���N�^
//******************************
CCollision::CCollision():CModel(OBJTYPE_COLLISION)
{
	// �ϐ��̃N���A
	m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
	m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
	m_nNumMatModel = 0;	    //�}�e���A�����̐�
}

//******************************
// �f�X�g���N�^
//******************************
CCollision::~CCollision()
{
}

//******************************
// �N���G�C�g
//******************************
CCollision * CCollision::CreateSphere(D3DXVECTOR3 pos,float fRadius)
{
	// �������̊m��
	CCollision *pCollision;
	pCollision = new CCollision;

	// init�Ŏg�������ɑ��
	pCollision->m_type = COLLISIONTYPE_SPHERE;
	pCollision->m_fRadius = fRadius;

	// ������
	pCollision->Init();
	
	// �e�l�̑���E�Z�b�g
	pCollision->SetPos(pos);
	pCollision->SetObjType(OBJTYPE_MAP); // �I�u�W�F�N�g�^�C�v
	
	return pCollision;
}

//******************************
// ���Ƌ��̓����蔻��
//******************************
bool CCollision::CollisionSphere(CCollision * pCollision1, CCollision * pCollision2)
{
	if (pow(pCollision1->GetPos().x - pCollision2->GetPos().x, 2) + 
		pow(pCollision1->GetPos().y - pCollision2->GetPos().y, 2) +
		pow(pCollision1->GetPos().z - pCollision2->GetPos().z, 2) <= pow(pCollision1->m_fRadius + pCollision2->m_fRadius, 2))
	{

		return true;
	}
	else
	{
		return false;
	}
}


//******************************
// ����������
//******************************
HRESULT CCollision::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}
	CreateMesh();
	// �e�N�X�`�����蓖��
	BindModel(m_pMeshModel, m_pBuffMatModel, 1);

	return S_OK;
}

//******************************
// �I������
//******************************
void CCollision::Uninit(void)
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

	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CCollision::Update(void)
{
}

//******************************
// �`�揈��
//******************************
void CCollision::Draw(void)
{
	// �F�̐ݒ�
	D3DXMATERIAL* mat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
	mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// ���C���[�t���[���ŕ`��
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//�@�`��
	CModel::Draw();
	// ���C���[�t���[�������ǂ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//******************************
// ���b�V������
//******************************
void CCollision::CreateMesh(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	switch (m_type)
	{
	case COLLISIONTYPE_CUBE:

		break;
	case COLLISIONTYPE_SPHERE:
		// ���̂̐���
		D3DXCreateSphere(pDevice, m_fRadius, 10, 10, &m_pMeshModel, &m_pBuffMatModel);
		break;
	default:
		break;
	}
}
