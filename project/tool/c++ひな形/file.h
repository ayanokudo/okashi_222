//=============================================================================
//
// ファイルクラス [file.h]
// Author:KUDO AYANO
//
//=============================================================================
#ifndef _FILE_H_
#define _FILE_H_
#include "main.h"
#include "scene.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFile
{
public:
    CFile();
    ~CFile();

    static void Read(void);
    static void Writing(void);

    static void ObjctWriting(FILE *pFile, CScene::OBJTYPE type);
    static int GetObjectType(CScene* pScene);
};
#endif // !_FILE_H_
