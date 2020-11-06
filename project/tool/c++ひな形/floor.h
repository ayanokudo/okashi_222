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
    //床のテクスチャの種類
    typedef enum
    {
        FLOOR_FLOORING = 0,	//フローリング
        FLOOR_MAT,			//マット
        FLOOR_KITCHEN,		//キッチン
        FLOOR_MAX,
    }FLOOR;

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

    // タイプのセッタ/ゲッタ
    void SetType(FLOOR type) { m_Type = type; }
    FLOOR GetType(void) { return m_Type; }

private:
    // メンバ変数
    static LPD3DXMESH           m_pMeshModel;       //メッシュ情報へのポインタ
    static LPD3DXBUFFER         m_pBuffMatModel;    //マテリアル情報へのポインタ
    static DWORD                m_nNumMatModel;     //マテリアル情報の数
    static LPDIRECT3DTEXTURE9   m_apTexture;        // テクスチャ
    FLOOR m_Type;
};
#endif      // _FLOOR_H_