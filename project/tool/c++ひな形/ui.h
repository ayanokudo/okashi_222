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
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CUI
{
public:
    CUI();
    ~CUI();

    CUI* Create(void);

    void Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:

};
#endif // !_UI_H_
