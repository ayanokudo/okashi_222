//=============================================================================
//
// カーソルクラスヘッダ [cursor.h]
// Author:KUDO AYANO
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "scene3d.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCursor : public CScene3d
{
public:
    CCursor();
    ~CCursor();

    static CCursor *Create(D3DXVECTOR3 pos);
    
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);





private:
};
#endif
