//=============================================================================
//
// �Ƌ�N���X [furniture.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _FURNITURE_H_
#define _FURNITURE_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �G�N���X
class CFumiture : public CModel
{
public:
    // �G�̎��
    typedef enum
    {
        TYPE_000 = 0,   //�A��
        TYPE_001,       // �^���X
        TTPE_002,       // �֎q
        TYPE_003,       // T���b�N�X
        TYPE_004,       // �؂̃��f��
        TYPE_005,       // �x���`
        TYPE_006,       // 
        TYPE_MAX,
    }TYPE;

    // �����o�֐�
    CFumiture();
    ~CFumiture();       

    static CFumiture *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void ChangeType(void);

    // �^�C�v�̃Z�b�^/�Q�b�^
    void SetType(TYPE type) { m_type = type; }
    TYPE GetType(void) { return m_type; }

private:
    // �����o�ϐ�
    TYPE m_type;       // �^�C�v
    static LPD3DXMESH m_pMeshModel;	//���b�V�����ւ̃|�C���^
    static LPD3DXBUFFER m_pBuffMatModel;	//�}�e���A�����ւ̃|�C���^
    static DWORD m_nNumMatModel;	//�}�e���A�����̐�
    static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
};
#endif      // _FURNITURE_H_