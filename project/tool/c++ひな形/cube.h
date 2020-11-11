//=============================================================================
//
// 敵クラス [cube.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _CUBE_H_
#define _CUBE_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// 敵クラス
class CCube : public CModel
{
public:
    // 敵の種類
    typedef enum
    {
        CUBE_CARRIER = 0,		//お菓子運んでる敵
        CUBE_ESCORT,			//BOSS守ってる敵
        CUBE_MAX,
    }CUBE;

    // メンバ関数
    CCube();
    ~CCube();

    static CCube *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void ChangeType(void);

    // タイプのセッタ/ゲッタ
    void SetType(CUBE type) { m_type = type; }
    CUBE GetType(void) { return m_type; }

private:
    // メンバ変数
    CUBE m_type;       // タイプ
    static LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
    static LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
    static DWORD m_nNumMatModel;	//マテリアル情報の数
    static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
};
#endif      // _CUBE_H_