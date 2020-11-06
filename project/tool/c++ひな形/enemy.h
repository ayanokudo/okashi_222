//=============================================================================
//
// 敵クラス [enemy.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "model.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
// 敵クラス
class CEnemy : public CModel
{
public:
    // 敵の種類
    typedef enum
    {
        ENEMY_CARRIER = 0,		//お菓子運んでる敵
        ENEMY_ESCORT,			//BOSS守ってる敵
        ENEMY_MAX,
    }ENEMY;

    // メンバ関数
    CEnemy();
    ~CEnemy();

    static CEnemy *Create(D3DXVECTOR3 pos);
    static HRESULT Load(void);
    static void Unload(void);
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void ChangeType(void);

    // タイプのセッタ/ゲッタ
    void SetType(ENEMY type) { m_type = type; }
    ENEMY GetType(void) { return m_type; }
    
private:
    // メンバ変数
    ENEMY m_type;       // タイプ
    static LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
    static LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
    static DWORD m_nNumMatModel;	//マテリアル情報の数
    static LPDIRECT3DTEXTURE9 m_apTexture; // テクスチャ
};
#endif      // _ENEMY_H_