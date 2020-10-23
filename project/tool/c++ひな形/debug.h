//=============================================================================
//
// デバッグ処理 [debug.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CDebug
{
public:
    CDebug();
    ~CDebug();

    static CDebug *Create(void);

    void Init();
    void Uninit();

    static void Print(int nX, int nY, D3DCOLOR color, const char* pFormat, ...);
    static void Draw(void);

private:
    static LPD3DXFONT m_pFont;          // フォントへのポインタ
    static char m_astr[1024];

    static CDebug *m_pDebug;                        // デバックテキストへのポインタ
};

#endif // !_DEBUG_H_
