//=============================================================================
//
// 家具クラス [furniture.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _FURNITURE_H_
#define _FURNITURE_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// 敵クラス
class CFumiture : public CModel
{
public:
    // 敵の種類
    typedef enum
    {
        TYPE_000 = 0,   //植木
        TYPE_001,       // タンス
        TTPE_002,       // 椅子
        TYPE_003,       // Tレックス
        TYPE_004,       // 木のモデル
        TYPE_005,       // ベンチ
        TYPE_006,       // 
        TYPE_MAX,
    }TYPE;

    // メンバ関数
    CFumiture();
    ~CFumiture();       

    static CFumiture *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void ChangeType(void);

    // タイプのセッタ/ゲッタ
    void SetType(TYPE type) { m_type = type; }
    TYPE GetType(void) { return m_type; }

private:
    // メンバ変数
    TYPE m_type;       // タイプ
    static LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
    static LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
    static DWORD m_nNumMatModel;	//マテリアル情報の数
    static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
};
#endif      // _FURNITURE_H_