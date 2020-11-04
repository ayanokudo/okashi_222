//=============================================================================
//
// UI�N���X [ui.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#define IMGUI_ON    // imgui�I��
//#undef  IMGUI_ON    // imgui�I�t

#ifdef IMGUI_ON
#include "main.h"

//*****************************************************************************
// �N���X�̒�`
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
