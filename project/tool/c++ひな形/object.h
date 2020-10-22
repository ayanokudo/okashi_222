//=============================================================================
//
// �I�u�W�F�N�g�N���X [object.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECT (128)            // �z�u�ł���I�u�W�F�N�g�̐�

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
// �I�u�W�F�N�g�N���X
class CObject : public CScene
{
public:
    typedef struct
    {
        D3DXVECTOR3 pos;    // �ʒu
        
    }OBJECT_DATA;

    // �����o�֐�
    CObject();
    ~CObject();

    static CObject *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void SetObject(void);

    static CModel *GetObjectData(int nNumObj) { return pModel[nNumObj]; }
private:
    static int ObjctNum;                    // �I�u�W�F�N�g�̐�
    static CModel *pModel[MAX_OBJECT];             // �V�[��


};
#endif      // _OBJECT_H_