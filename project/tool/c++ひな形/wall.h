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
// 壁クラス
class CWall : public CModel
{
public:
    // 壁の種類
    typedef enum
    {
        TYPE_NORMAL = 0,       // 普通の壁
        TYPE_RIGHT,            // 右半分に穴がある壁
        TYPE_LEFT,             // 左半分に穴がある壁
        TYPE_MAX,
    }TYPE;

    // メンバ関数
    CWall();
    ~CWall();

    static CWall *Create(D3DXVECTOR3 pos,TYPE ntype);
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
    TYPE                        m_type;             // 種類
    static LPD3DXMESH           m_pMeshModel;       // メッシュ情報へのポインタ
    static LPD3DXBUFFER         m_pBuffMatModel;    // マテリアル情報へのポインタ
    static DWORD                m_nNumMatModel;     // マテリアル情報の数
    static LPDIRECT3DTEXTURE9   m_apTexture;        // テクスチャ
};
#endif      // _ENEMY_H_