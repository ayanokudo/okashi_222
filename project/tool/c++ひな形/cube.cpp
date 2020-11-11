//=============================================================================
//
// �G�N���X [cube.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "cube.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PATH "./data/Models/cube.x"    //���f���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH   CCube::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CCube::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CCube::m_nNumMatModel = 0;	    //�}�e���A�����̐�

//=============================================================================
// [CCube] �R���X�g���N�^
//=============================================================================
CCube::CCube() : CModel(OBJTYPE_COLLISION)
{
    m_type = CUBE::CUBE_CARRIER;
}

//=============================================================================
// [~CCube] �f�X�g���N�^
//=============================================================================
CCube::~CCube()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CCube * CCube::Create(D3DXVECTOR3 pos)
{
    CCube *pObject = NULL;
    if (!pObject)
    {
        pObject = new CCube;
        // ������
        pObject->Init();
        pObject->SetPos(pos);

        // �e�l�̑���E�Z�b�g
        pObject->SetObjType(OBJTYPE_COLLISION); // �I�u�W�F�N�g�^�C�v
    }
    return pObject;
}

//=============================================================================
// [Load] �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CCube::Load(void)
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
void CCube::Unload(void)
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
HRESULT CCube::Init(void)
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
void CCube::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CCube::Update(void)
{
    CModel::Update();
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CCube::Draw(void)
{

    D3DXMATERIAL*pMat;  	//�}�e���A���f�[�^�ւ̃|�C���^

                            //�}�e���A���f�[�^�ւ̃|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case CUBE_CARRIER:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,0,128 };
            break;
        case CUBE_ESCORT:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,0,128 };
            break;

        }
    }
    CModel::Draw();

    // �}�e���A���������ɖ߂�
    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        pMat[nCntMat].MatD3D.Diffuse = { 255,255,255,255 };
    }

}

//=============================================================================
// [ChangeType] ��ނ̕ύX
//=============================================================================
void CCube::ChangeType(void)
{
    int nType = m_type;

    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_3))
    {
        nType -= 1;
    }
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_4))
    {
        nType += 1;
    }

    // �ő�l�ȏ�/�ŏ��l�ȉ��ɂȂ����烋�[�v
    if (nType >= CUBE_MAX)
    {
        nType = CUBE_CARRIER;
    }
    if (nType < CUBE_CARRIER)
    {
        nType = CUBE_MAX - 1;
    }

    // ��ނ𔽉f
    SetType((CUBE)nType);
}
