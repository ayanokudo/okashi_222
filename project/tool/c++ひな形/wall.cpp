//=============================================================================
//
// �ǃN���X [wall.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PATH "./data/Models/wall010.x"    //���f���̃p�X

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
LPD3DXMESH   CWall::m_pMeshModel    = NULL;   	//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CWall::m_pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD        CWall::m_nNumMatModel  = 0;	    //�}�e���A�����̐�

//=============================================================================
// [CWall] �R���X�g���N�^
//=============================================================================
CWall::CWall() : CModel(OBJTYPE_WALL)
{
    m_type = TYPE_NORMAL;
}

//=============================================================================
// [~CWall] �f�X�g���N�^
//=============================================================================
CWall::~CWall()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CWall * CWall::Create(D3DXVECTOR3 pos, TYPE ntype)
{
    CWall *pObject = NULL;
    if (!pObject)
    {
        pObject = new CWall;
        // ������
        pObject->m_type = ntype;
        pObject->SetPos(pos);
        pObject->Init();
        // �e�l�̑���E�Z�b�g
        pObject->SetObjType(OBJTYPE_WALL); // �I�u�W�F�N�g�^�C�v
    }
    return pObject;
}

//=============================================================================
// [Load] �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CWall::Load(void)
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
void CWall::Unload(void)
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
HRESULT CWall::Init(void)
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
void CWall::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CWall::Update(void)
{
    CModel::Update();
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CWall::Draw(void)
{
    D3DXMATERIAL*pMat;  	//�}�e���A���f�[�^�ւ̃|�C���^

                            //�}�e���A���f�[�^�ւ̃|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case TYPE_NORMAL:// �m�[�}�� : ��
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,128 };
            break;

        case TYPE_RIGHT:// �E : ��
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,128 };
            break;

        case TYPE_LEFT:// �� : ��
            //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
            pMat[nCntMat].MatD3D.Diffuse = { 0,255,0,128 };
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
void CWall::ChangeType(void)
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
        nType = TYPE_NORMAL;
    }
    if (nType < TYPE_NORMAL)
    {
        nType = TYPE_MAX - 1;
    }

    // ��ނ𔽉f
    SetType((TYPE)nType);
}