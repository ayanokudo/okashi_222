//=============================================================================
//
// x�t�@�C���Ǘ��N���X�w�b�_ [scene_x.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _SCENE_X_H_
#define _SCENE_X_H_
#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneX
{
public:
    CSceneX();
    ~CSceneX();

    CSceneX* Create(char* pModelName, D3DXVECTOR3 pos);

    void Init(char* pModelName, D3DXVECTOR3 pos);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    LPD3DXMESH m_pMeshModel;                //���b�V�����ւ̃|�C���^
    LPD3DXBUFFER m_pBuffMatModel;           //�}�e���A�����ւ̃|�C���^
    DWORD m_nNumMatModel;                   //�}�e���A�����̐�
    D3DXVECTOR3 m_pos;      // �ʒu
    D3DXVECTOR3 m_rot;      // �p�x
    D3DXMATRIX m_mtxWorldModel;             //���[���h�}�g���b�N�X
};


#endif // !_SCENE_X_H_
