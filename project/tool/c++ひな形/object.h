//=============================================================================
//
// オブジェクトクラス [object.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT (128)            // 配置できるオブジェクトの数

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// オブジェクトクラス
class CObject : public CScene
{
public:
    typedef struct
    {
        D3DXVECTOR3 pos;    // 位置
        
    }OBJECT_DATA;

    // メンバ関数
    CObject();
    ~CObject();

    static CObject *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void SetObject(void);

    static CModel *GetObjectData(int nNumObj) { return pModel[nNumObj]; }
private:
    static int ObjctNum;                    // オブジェクトの数
    static CModel *pModel[MAX_OBJECT];             // シーン


};
#endif      // _OBJECT_H_