//=============================================================================
//
// xファイル管理クラスヘッダ [scene_x.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef _SCENE_X_H_
#define _SCENE_X_H_
#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneX
{
public:
    CSceneX();
    ~CSceneX();

    CSceneX* Create(char* pModelName, D3DXVECTOR3 pos);

    void Init(char* pModelName, D3DXVECTOR3 pos);
    void Uninit(void);
    void Update(void);
    void Draw(void);

private:
    LPD3DXMESH m_pMeshModel;                //メッシュ情報へのポインタ
    LPD3DXBUFFER m_pBuffMatModel;           //マテリアル情報へのポインタ
    DWORD m_nNumMatModel;                   //マテリアル情報の数
    D3DXVECTOR3 m_pos;      // 位置
    D3DXVECTOR3 m_rot;      // 角度
    D3DXMATRIX m_mtxWorldModel;             //ワールドマトリックス
};


#endif // !_SCENE_X_H_
