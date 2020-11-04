//=============================================================================
//
// 床クラス [flooh.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _FLOOR_H_
#define _FLOOR_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// 敵クラス
class CFloor : public CModel
{
public:
    // メンバ関数
    CFloor();
    ~CFloor();

    static CFloor *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    // メンバ変数
    static LPD3DXMESH           m_pMeshModel;       //メッシュ情報へのポインタ
    static LPD3DXBUFFER         m_pBuffMatModel;    //マテリアル情報へのポインタ
    static DWORD                m_nNumMatModel;     //マテリアル情報の数
    static LPDIRECT3DTEXTURE9   m_apTexture;        // テクスチャ
};
#endif      // _FLOOR_H_