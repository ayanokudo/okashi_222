//=============================================================================
//
// �G�N���X [enemy.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �G�N���X
class CEnemy : public CModel
{
public:
    // �����o�֐�
    CEnemy();
    ~CEnemy();

    static CEnemy *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    // �����o�ϐ�
    static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
    static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
    static DWORD m_nNumMatModel;	//�}�e���A�����̐�
    static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
};
#endif      // _ENEMY_H_