////////////////////////////////////////////////////
//
//    particle�N���X�̏���[particle.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "scene3d.h"
#include "object.h"

//*****************************
// �}�N����`
//*****************************
#define MODEL_PATH "./data/Models/cat V1.x"    //���f���̃p�X
#define PLAYER_SPEED 10
#define PLAYER_MOVE_RATE 0.05f

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
char* CPlayer::m_apModelData[CPlayer::MODEL_MAX] = {
   "./data/Models/cat V1.x",
   "./data/Models/test000.x"
};// ���f���̃t�@�C����

LPD3DXMESH   CPlayer::m_pMeshModel[CPlayer::MODEL_MAX] = {};   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CPlayer::m_pBuffMatModel[CPlayer::MODEL_MAX] = {};	//�}�e���A�����ւ̃|�C���^
DWORD        CPlayer::m_nNumMatModel[CPlayer::MODEL_MAX] = {};	    //�}�e���A�����̐�

//******************************
// �R���X�g���N�^
//******************************
CPlayer::CPlayer() : CModel(OBJTYPE_PLAYER)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//******************************
// �f�X�g���N�^
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// �N���G�C�g
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	// �������̊m��
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	// ������
	pPlayer->Init();
	pPlayer->SetPos(pos);
	// �e�l�̑���E�Z�b�g
	pPlayer->SetObjType(OBJTYPE_PLAYER); // �I�u�W�F�N�g�^�C�v

	return pPlayer;
}

//******************************
// �e�N�X�`���̃��[�h
//******************************
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
    for (int nCntModel = 0; nCntModel <MODEL_MAX; nCntModel++)
    {
	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[nCntModel],
		NULL,
		&m_nNumMatModel[nCntModel],
		&m_pMeshModel[nCntModel]);
    }

	return S_OK;
}

//******************************
// �e�N�X�`���̃A�����[�h
//******************************
void CPlayer::Unload(void)
{
	//���b�V���̔j��
    for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
    {
        if (m_pMeshModel[nCntModel] != NULL)
        {
            m_pMeshModel[nCntModel]->Release();
            m_pMeshModel[nCntModel] = NULL;
        }
        //�}�e���A���̔j��
        if (m_pBuffMatModel[nCntModel] != NULL)
        {
            m_pBuffMatModel[nCntModel]->Release();
            m_pBuffMatModel[nCntModel] = NULL;
        }
    }
}

//******************************
// ����������
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`�����蓖��
	BindModel(m_pMeshModel[MODEL_PLAYER], m_pBuffMatModel[MODEL_PLAYER], m_nNumMatModel[MODEL_PLAYER]);

	return S_OK;
}

//******************************
// �I������
//******************************
void CPlayer::Uninit(void)
{

	CModel::Uninit();
}

//******************************
// �X�V����
//******************************
void CPlayer::Update(void)
{
    CModel::Update();
	D3DXVECTOR3 rot = GetRot();
	
	SetRot(rot);
    // ����̊Ǘ�
	//Controll();
}

//******************************
// �`�揈�� 
//******************************
void CPlayer::Draw(void)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    // ���C���[�t���[��
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	CModel::Draw();
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//******************************
// ����̊Ǘ�
//******************************
void CPlayer::Controll(void)
{
	// ���W
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʂ̖ڕW�l
	D3DXVECTOR3 moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// �W���C�X�e�B�b�N�̎擾
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

	if (CManager::GetKeyboard()->GetKeyPress(DIK_W) || js.lY <= -600)
	{// ���ړ�
		moveDest.z = -PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
	{// ���ړ�

		moveDest.z = PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
	{// ���ړ�
		moveDest.x = PLAYER_SPEED;

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
	{// ���ړ�
		moveDest.x = -PLAYER_SPEED;
	}

	// ����
	m_move = (moveDest);
	
	// �ړ��ʂ𑫂�
	pos += m_move;

	// ���W�̃Z�b�g
	SetPos(pos);
}
