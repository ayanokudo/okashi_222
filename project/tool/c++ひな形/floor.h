//=============================================================================
//
// ���N���X [flooh.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �G�N���X
class CFloor : public CModel
{
public:
    //���̃e�N�X�`���̎��
    typedef enum
    {
        FLOOR_FLOORING = 0,	//�t���[�����O
        FLOOR_MAT,			//�}�b�g
        FLOOR_KITCHEN,		//�L�b�`��
        FLOOR_MAX,
    }FLOOR;

    // �����o�֐�
    CFloor();
    ~CFloor();

    static CFloor *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    // �^�C�v�̃Z�b�^/�Q�b�^
    void SetType(FLOOR type) { m_Type = type; }
    FLOOR GetType(void) { return m_Type; }

private:
    // �����o�ϐ�
    static LPD3DXMESH           m_pMeshModel;       //���b�V�����ւ̃|�C���^
    static LPD3DXBUFFER         m_pBuffMatModel;    //�}�e���A�����ւ̃|�C���^
    static DWORD                m_nNumMatModel;     //�}�e���A�����̐�
    static LPDIRECT3DTEXTURE9   m_apTexture;        // �e�N�X�`��
    FLOOR m_Type;
};
#endif      // _FLOOR_H_