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
    // �G�̎��
    typedef enum
    {
        ENEMY_CARRIER = 0,		//���َq�^��ł�G
        ENEMY_ESCORT,			//BOSS����Ă�G
        ENEMY_MAX,
    }ENEMY;

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

    void ChangeType(void);

    // �^�C�v�̃Z�b�^/�Q�b�^
    void SetType(ENEMY type) { m_type = type; }
    ENEMY GetType(void) { return m_type; }
    
private:
    // �����o�ϐ�
    ENEMY m_type;       // �^�C�v
    static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
    static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
    static DWORD m_nNumMatModel;	//�}�e���A�����̐�
    static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
};
#endif      // _ENEMY_H_