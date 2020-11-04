//=============================================================================
//
// 壁クラス [wall.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// 敵クラス
class CWall : public CModel
{
public:
    // メンバ関数
    CWall();
    ~CWall();

    static CWall *Create(D3DXVECTOR3 pos);
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
#endif      // _ENEMY_H_