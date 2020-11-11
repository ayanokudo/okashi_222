//=============================================================================
//
// 敵クラス [cube.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "cube.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PATH "./data/Models/cube.x"    //モデルのパス

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH   CCube::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CCube::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CCube::m_nNumMatModel = 0;	    //マテリアル情報の数

//=============================================================================
// [CCube] コンストラクタ
//=============================================================================
CCube::CCube() : CModel(OBJTYPE_COLLISION)
{
    m_type = CUBE::CUBE_CARRIER;
}

//=============================================================================
// [~CCube] デストラクタ
//=============================================================================
CCube::~CCube()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CCube * CCube::Create(D3DXVECTOR3 pos)
{
    CCube *pObject = NULL;
    if (!pObject)
    {
        pObject = new CCube;
        // 初期化
        pObject->Init();
        pObject->SetPos(pos);

        // 各値の代入・セット
        pObject->SetObjType(OBJTYPE_COLLISION); // オブジェクトタイプ
    }
    return pObject;
}

//=============================================================================
// [Load] テクスチャの読み込み
//=============================================================================
HRESULT CCube::Load(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    //Xファイルの読み込み
    D3DXLoadMeshFromX(MODEL_PATH,
        D3DXMESH_SYSTEMMEM,
        pDevice,
        NULL,
        &m_pBuffMatModel,
        NULL,
        &m_nNumMatModel,
        &m_pMeshModel);

    return S_OK;
}

//=============================================================================
// [Unload] テクスチャの破棄
//=============================================================================
void CCube::Unload(void)
{
    //メッシュの破棄
    if (m_pMeshModel != NULL)
    {
        m_pMeshModel->Release();
        m_pMeshModel = NULL;
    }
    //マテリアルの破棄
    if (m_pBuffMatModel != NULL)
    {
        m_pBuffMatModel->Release();
        m_pBuffMatModel = NULL;
    }
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
HRESULT CCube::Init(void)
{
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    // テクスチャ割り当て
    BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);

    return S_OK;
}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CCube::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CCube::Update(void)
{
    CModel::Update();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CCube::Draw(void)
{

    D3DXMATERIAL*pMat;  	//マテリアルデータへのポインタ

                            //マテリアルデータへのポインタを取得
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case CUBE_CARRIER:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,0,128 };
            break;
        case CUBE_ESCORT:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,0,128 };
            break;

        }
    }
    CModel::Draw();

    // マテリアル情報を元に戻す
    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        pMat[nCntMat].MatD3D.Diffuse = { 255,255,255,255 };
    }

}

//=============================================================================
// [ChangeType] 種類の変更
//=============================================================================
void CCube::ChangeType(void)
{
    int nType = m_type;

    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_3))
    {
        nType -= 1;
    }
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_4))
    {
        nType += 1;
    }

    // 最大値以上/最小値以下になったらループ
    if (nType >= CUBE_MAX)
    {
        nType = CUBE_CARRIER;
    }
    if (nType < CUBE_CARRIER)
    {
        nType = CUBE_MAX - 1;
    }

    // 種類を反映
    SetType((CUBE)nType);
}
