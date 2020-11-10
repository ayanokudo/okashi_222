//=============================================================================
//
// ���N���X [floor.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "floor.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PATH "./data/Models/floor000.x"    //���f���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH   CFloor::m_pMeshModel = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CFloor::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CFloor::m_nNumMatModel = 0;	    //�}�e���A�����̐�

//=============================================================================
// [CFloor] �R���X�g���N�^
//=============================================================================
CFloor::CFloor() : CModel(OBJTYPE_FLOOR)
{

}

//=============================================================================
// [~CFloor] �f�X�g���N�^
//=============================================================================
CFloor::~CFloor()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CFloor * CFloor::Create(D3DXVECTOR3 pos, FLOOR type)
{
    CFloor *pObject = NULL;
    if (!pObject)
    {
        pObject = new CFloor;
        // ������
        pObject->Init(type);
        pObject->SetPos(pos);

        // �e�l�̑���E�Z�b�g
        pObject->SetObjType(OBJTYPE_FLOOR); // �I�u�W�F�N�g�^�C�v
    }
    return pObject;
}

//=============================================================================
// [Load] �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CFloor::Load(void)
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
void CFloor::Unload(void)
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
HRESULT CFloor::Init(FLOOR type)
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
void CFloor::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CFloor::Update(void)
{
    CModel::Update();

    D3DXMATERIAL*pMat;      //�}�e���A���f�[�^�ւ̃|�C���^
                            //�}�e���A���f�[�^�ւ̃|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case FLOOR_FLOORING:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,255 };
            break;
        case FLOOR_MAT:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
            break;

        case FLOOR_KITCHEN:
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,255,0,255 };
            break;
        }
    }
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CFloor::Draw(void)
{
    CModel::Draw();
}

//=============================================================================
// [ChangeType] ��ނ̕ύX
//=============================================================================
void CFloor::ChangeType(void)
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
    if (nType >= FLOOR_MAX)
    {
        nType = FLOOR_FLOORING;
    }
    if (nType < FLOOR_FLOORING)
    {
        nType = FLOOR_MAX - 1;
    }

    // ��ނ𔽉f
    SetType((FLOOR)nType);
}
