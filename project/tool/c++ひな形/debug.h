//=============================================================================
//
// �f�o�b�O���� [debug.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "main.h"

//*****************************************************************************
// �N���X�̒�`
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
    static LPD3DXFONT m_pFont;          // �t�H���g�ւ̃|�C���^
    static char m_astr[1024];

    static CDebug *m_pDebug;                        // �f�o�b�N�e�L�X�g�ւ̃|�C���^
};

#endif // !_DEBUG_H_
