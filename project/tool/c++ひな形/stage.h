//=============================================================================
//
// �X�e�[�W�N���X [stage.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �I�u�W�F�N�g�N���X
class CStage : public CModel
{
public:
    // �����o�֐�
    CStage();
    ~CStage();

    static CStage *Create(D3DXVECTOR3 pos);
    static HRESULT  Load(void);
    static void     Unload(void);
    HRESULT         Init(void);
    void            Uninit(void);
    void            Update(void);
    void            Draw(void);

private:
    // �����o�ϐ�
    static LPD3DXMESH         m_pMeshModel;	//���b�V�����ւ̃|�C���^
    static LPD3DXBUFFER       m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
    static DWORD              m_nNumMatModel;	//�}�e���A�����̐�
    static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
};
#endif      // _STAGE_H_