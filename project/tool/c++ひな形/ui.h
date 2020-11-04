//=============================================================================
//
// UIクラス [ui.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#define IMGUI_ON    // imguiオン
//#undef  IMGUI_ON    // imguiオフ

#ifdef IMGUI_ON
#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CUI
{
public:
    CUI();
    ~CUI();

    static CUI* Create(HWND hWnd);

    void Init(HWND hWnd);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:

};
#endif // IMGUI_ON
#endif // !_UI_H_
