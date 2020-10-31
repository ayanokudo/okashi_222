//=============================================================================
//
// xファイル管理クラスヘッダ [scene_x.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "scene_x.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// [CObject] コンストラクタ
//=============================================================================
CSceneX::CSceneX()
{
    // 各メンバ変数の初期化
    m_pos = { 0.0f,0.0f,0.0f };
    m_rot = { 0.0f,0.0f,0.0f };
}

//=============================================================================
// [~CObject] デストラクタ
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CSceneX * CSceneX::Create(char* pModelName,D3DXVECTOR3 pos)
{
    CSceneX *pSceneX = NULL;
    if (!pSceneX)
    {
        pSceneX = new CSceneX;
        pSceneX->Init(pModelName,pos);
    }
    return pSceneX;
}

//=============================================================================
// [Init] 初期化処理
// 引数
// pModelName : モデルのファイル名
// pos        : 表示する位置
//=============================================================================
void CSceneX::Init(char* pModelName,D3DXVECTOR3 pos)
{
    // Xファイルの読み込み
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //Xファイルの読み込み
        D3DXLoadMeshFromX(pModelName,
            D3DXMESH_SYSTEMMEM,
            pDevice,
            NULL,
            &m_pBuffMatModel,
            NULL,
            &m_nNumMatModel,
            &m_pMeshModel);

    // 位置向きの設定
    m_pos = pos;
}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CSceneX::Uninit(void)
{
    delete this;
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CSceneX::Update(void)
{

}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CSceneX::Draw(void)
{
    //デバイス情報の取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans;
    D3DMATERIAL9 matDef;	//現在のマテリアル保持用
    D3DXMATERIAL*pMat;  	//マテリアルデータへのポインタ

                            //ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxWorldModel);

    //向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxRot);

    //位置を反映
    D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
    D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxTrans);

    //ワールドマトリックスの設定
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);

    //現在のマテリアルを取得する
    pDevice->GetMaterial(&matDef);

    //マテリアルデータへのポインタを取得
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        //マテリアルのアンビエントにディフューズカラーを設定
        pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

        //マテリアルの設定
        pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

        //モデルパーツの描画
        m_pMeshModel->DrawSubset(nCntMat);
    }
    //保持していたマテリアルを戻す
    pDevice->SetMaterial(&matDef);
}
