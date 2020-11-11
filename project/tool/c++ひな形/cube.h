//=============================================================================
//
// �G�N���X [cube.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _CUBE_H_
#define _CUBE_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �G�N���X
class CCube : public CModel
{
public:
    // �G�̎��
    typedef enum
    {
        CUBE_CARRIER = 0,		//���َq�^��ł�G
        CUBE_ESCORT,			//BOSS����Ă�G
        CUBE_MAX,
    }CUBE;

    // �����o�֐�
    CCube();
    ~CCube();

    static CCube *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void ChangeType(void);

    // �^�C�v�̃Z�b�^/�Q�b�^
    void SetType(CUBE type) { m_type = type; }
    CUBE GetType(void) { return m_type; }

private:
    // �����o�ϐ�
    CUBE m_type;       // �^�C�v
    static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
    static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
    static DWORD m_nNumMatModel;	//�}�e���A�����̐�
    static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
};
#endif      // _CUBE_H_