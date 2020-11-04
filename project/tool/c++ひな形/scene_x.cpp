//=============================================================================
//
// x�t�@�C���Ǘ��N���X�w�b�_ [scene_x.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "scene_x.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// [CObject] �R���X�g���N�^
//=============================================================================
CSceneX::CSceneX()
{
    // �e�����o�ϐ��̏�����
    m_pos = { 0.0f,0.0f,0.0f };
    m_rot = { 0.0f,0.0f,0.0f };
}

//=============================================================================
// [~CObject] �f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CSceneX * CSceneX::Create(char* pModelName,D3DXVECTOR3 pos)
{
    CSceneX *pSceneX = NULL;
    if (!pSceneX)
    {
        pSceneX = new CSceneX;
        pSceneX->Init(pModelName,pos);
    }
    return pSceneX;
}

//=============================================================================
// [Init] ����������
// ����
// pModelName : ���f���̃t�@�C����
// pos        : �\������ʒu
//=============================================================================
void CSceneX::Init(char* pModelName,D3DXVECTOR3 pos)
{
    // X�t�@�C���̓ǂݍ���
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //X�t�@�C���̓ǂݍ���
        D3DXLoadMeshFromX(pModelName,
            D3DXMESH_SYSTEMMEM,
            pDevice,
            NULL,
            &m_pBuffMatModel,
            NULL,
            &m_nNumMatModel,
            &m_pMeshModel);

    // �ʒu�����̐ݒ�
    m_pos = pos;
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CSceneX::Uninit(void)
{
    delete this;
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CSceneX::Update(void)
{

}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CSceneX::Draw(void)
{
    //�f�o�C�X���̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;
    D3DMATERIAL9 matDef;	//���݂̃}�e���A���ێ��p
    D3DXMATERIAL*pMat;  	//�}�e���A���f�[�^�ւ̃|�C���^

                            //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorldModel);

    //�����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxRot);

    //�ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
    D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxTrans);

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);

    //���݂̃}�e���A�����擾����
    pDevice->GetMaterial(&matDef);

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
        pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

        //���f���p�[�c�̕`��
        m_pMeshModel->DrawSubset(nCntMat);
    }
    //�ێ����Ă����}�e���A����߂�
    pDevice->SetMaterial(&matDef);
}
