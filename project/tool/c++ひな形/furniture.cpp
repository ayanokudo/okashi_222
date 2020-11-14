//=============================================================================
//
// 家具クラス [furniture.cpp]
// Author : AYANO KUDO

//
//=============================================================================
#include "furniture.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PATH "./data/Models/item.x"    //モデルのパス

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH   CFumiture::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CFumiture::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CFumiture::m_nNumMatModel = 0;	    //マテリアル情報の数

//=============================================================================
// [CFumiture] コンストラクタ
//=============================================================================
CFumiture::CFumiture() : CModel(OBJTYPE_FURNITURE)
{
    m_type = TYPE::TYPE_000;
}

//=============================================================================
// [~CFumiture] デストラクタ
//=============================================================================
CFumiture::~CFumiture()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CFumiture * CFumiture::Create(D3DXVECTOR3 pos)
{
    CFumiture *pObject = NULL;
    if (!pObject)
    {
        pObject = new CFumiture;
        pObject->Init();
        // 初期化
        pObject->Init();
        pObject->SetPos(pos);

        // 各値の代入・セット
        pObject->SetObjType(OBJTYPE_FURNITURE); // オブジェクトタイプ
    }
    return pObject;
}

//=============================================================================
// [Load] テクスチャの読み込み
//=============================================================================
HRESULT CFumiture::Load(void)
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
void CFumiture::Unload(void)
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
HRESULT CFumiture::Init(void)
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
void CFumiture::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CFumiture::Update(void)
{
    CModel::Update();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CFumiture::Draw(void)
{
    D3DXMATERIAL*pMat;  	//マテリアルデータへのポインタ

                            //マテリアルデータへのポインタを取得
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case TYPE_000:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,255 };
            break;

        case TYPE_001:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
            break;

        case TTPE_002:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
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
void CFumiture::ChangeType(void)
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
    if (nType >= TYPE_MAX)
    {
        nType = TYPE_000;
    }
    if (nType < TYPE_000)
    {
        nType = TYPE_MAX - 1;
    }

    // 種類を反映
    SetType((TYPE)nType);
}
