//=============================================================================
//
// ファイルクラス [file.h]
// Author:KUDO AYANO
//
//=============================================================================
#ifndef _FILE_H_
#define _FILE_H_
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFile
{
public:
    // 読み込んだデータ
    typedef struct
    {

    }FILE_DATA;

    CFile();
    ~CFile();

    static void Read(void);
    static void Writing(void);


private:

};
#endif // !_FILE_H_
