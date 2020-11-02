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
//*****************************************************************************
// �N���X�̒�`
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
