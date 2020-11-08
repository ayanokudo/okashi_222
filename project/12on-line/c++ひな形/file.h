//=============================================================================
//
// �t�@�C���N���X [file.h]
// Author:KUDO AYANO
//
//=============================================================================
#ifndef _FILE_H_
#define _FILE_H_
#include "main.h"
#include "scene.h"
#include "model.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFile
{
public:
    CFile();
    ~CFile();

    static void Read(void);

private:
    static void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::OBJTYPE type, int ntype);
};
#endif // !_FILE_H_
