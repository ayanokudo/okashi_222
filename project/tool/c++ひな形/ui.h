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
#include "imgui/imgui.h"
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

    void Manual(void);
private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);// 色
};
#endif // IMGUI_ON
#endif // !_UI_H_
