//=============================================================================
//
// �ǃN���X [wall.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �ǃN���X
class CWall : public CModel
{
public:
    // �ǂ̎��
    typedef enum
    {
        TYPE_NORMAL = 0,       // ���ʂ̕�
        TYPE_RIGHT,            // �E�����Ɍ��������
        TYPE_LEFT,             // �������Ɍ��������
        TYPE_MAX,
    }TYPE;

    // �����o�֐�
    CWall();
    ~CWall();

    static CWall *Create(D3DXVECTOR3 pos,TYPE ntype);
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
    TYPE                        m_type;             // ���
    static LPD3DXMESH           m_pMeshModel;       // ���b�V�����ւ̃|�C���^
    static LPD3DXBUFFER         m_pBuffMatModel;    // �}�e���A�����ւ̃|�C���^
    static DWORD                m_nNumMatModel;     // �}�e���A�����̐�
    static LPDIRECT3DTEXTURE9   m_apTexture;        // �e�N�X�`��
};
#endif      // _ENEMY_H_