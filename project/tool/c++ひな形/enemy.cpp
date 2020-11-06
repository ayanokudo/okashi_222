//=============================================================================
//
// �G�N���X [enemy.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PATH "./data/Models/Mouse_jouhanshin.x"    //���f���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH   CEnemy::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CEnemy::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CEnemy::m_nNumMatModel = 0;	    //�}�e���A�����̐�

//=============================================================================
// [CEnemy] �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy() : CModel(OBJTYPE_ENEMY)
{
    m_type = ENEMY::ENEMY_CARRIER;
}

//=============================================================================
// [~CEnemy] �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos)
{
    CEnemy *pObject = NULL;
    if (!pObject)
    {
        pObject = new CEnemy;
        pObject->Init();
        // ������
        pObject->Init();
        pObject->SetPos(pos);

        // �e�l�̑���E�Z�b�g
        pObject->SetObjType(OBJTYPE_ENEMY); // �I�u�W�F�N�g�^�C�v
    }
    return pObject;
}

//=============================================================================
// [Load] �e�N�X�`���̓ǂݍ���
//=============================================================================
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

//=============================================================================
// [Unload] �e�N�X�`���̔j��
//=============================================================================
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

//=============================================================================
// [Init] ����������
//=============================================================================
HRESULT CEnemy::Init(void)
{
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    // �e�N�X�`�����蓖��
    BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);

    return S_OK;
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CEnemy::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CEnemy::Update(void)
{
    CModel::Update();

    D3DXMATERIAL*pMat;  	//�}�e���A���f�[�^�ւ̃|�C���^

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case ENEMY_CARRIER:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,255 };
            break;
        case ENEMY_ESCORT:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
            break;

        }
    }

}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
    CModel::Draw();
}


//=============================================================================
// [ChangeType] ��ނ̕ύX
//=============================================================================
void CEnemy::ChangeType(void)
{
    int nType=m_type;
    
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_3))
    {
        nType -= 1;
    }
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_4))
    {
        nType += 1;
    }

    // �ő�l�ȏ�/�ŏ��l�ȉ��ɂȂ����烋�[�v
    if (nType >= ENEMY_MAX)
    {
        nType = ENEMY_CARRIER;
    }
    if (nType < ENEMY_CARRIER)
    {
        nType = ENEMY_MAX - 1;
    }

    // ��ނ𔽉f
    SetType((ENEMY)nType);
}
