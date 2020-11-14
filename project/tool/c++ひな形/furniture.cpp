//=============================================================================
//
// �Ƌ�N���X [furniture.cpp]
// Author : AYANO KUDO

//
//=============================================================================
#include "furniture.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PATH "./data/Models/item.x"    //���f���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH   CFumiture::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CFumiture::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CFumiture::m_nNumMatModel = 0;	    //�}�e���A�����̐�

//=============================================================================
// [CFumiture] �R���X�g���N�^
//=============================================================================
CFumiture::CFumiture() : CModel(OBJTYPE_FURNITURE)
{
    m_type = TYPE::TYPE_000;
}

//=============================================================================
// [~CFumiture] �f�X�g���N�^
//=============================================================================
CFumiture::~CFumiture()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CFumiture * CFumiture::Create(D3DXVECTOR3 pos)
{
    CFumiture *pObject = NULL;
    if (!pObject)
    {
        pObject = new CFumiture;
        pObject->Init();
        // ������
        pObject->Init();
        pObject->SetPos(pos);

        // �e�l�̑���E�Z�b�g
        pObject->SetObjType(OBJTYPE_FURNITURE); // �I�u�W�F�N�g�^�C�v
    }
    return pObject;
}

//=============================================================================
// [Load] �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CFumiture::Load(void)
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
void CFumiture::Unload(void)
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
HRESULT CFumiture::Init(void)
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
void CFumiture::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CFumiture::Update(void)
{
    CModel::Update();
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CFumiture::Draw(void)
{
    D3DXMATERIAL*pMat;  	//�}�e���A���f�[�^�ւ̃|�C���^

                            //�}�e���A���f�[�^�ւ̃|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case TYPE_000:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,255 };
            break;

        case TYPE_001:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
            break;

        case TTPE_002:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
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
void CFumiture::ChangeType(void)
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
    if (nType >= TYPE_MAX)
    {
        nType = TYPE_000;
    }
    if (nType < TYPE_000)
    {
        nType = TYPE_MAX - 1;
    }

    // ��ނ𔽉f
    SetType((TYPE)nType);
}
