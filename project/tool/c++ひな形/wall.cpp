//=============================================================================
//
// 壁クラス [wall.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PATH "./data/Models/wall010.x"    //モデルのパス

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH   CWall::m_pMeshModel    = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CWall::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CWall::m_nNumMatModel  = 0;	    //マテリアル情報の数

//=============================================================================
// [CWall] コンストラクタ
//=============================================================================
CWall::CWall() : CModel(OBJTYPE_WALL)
{
    m_type = TYPE_NORMAL;
}

//=============================================================================
// [~CWall] デストラクタ
//=============================================================================
CWall::~CWall()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CWall * CWall::Create(D3DXVECTOR3 pos, TYPE ntype)
{
    CWall *pObject = NULL;
    if (!pObject)
    {
        pObject = new CWall;
        // 初期化
        pObject->m_type = ntype;
        pObject->SetPos(pos);
        pObject->Init();
        // 各値の代入・セット
        pObject->SetObjType(OBJTYPE_WALL); // オブジェクトタイプ
    }
    return pObject;
}

//=============================================================================
// [Load] テクスチャの読み込み
//=============================================================================
HRESULT CWall::Load(void)
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
void CWall::Unload(void)
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
HRESULT CWall::Init(void)
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
void CWall::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CWall::Update(void)
{
    CModel::Update();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CWall::Draw(void)
{
    D3DXMATERIAL*pMat;  	//マテリアルデータへのポインタ

                            //マテリアルデータへのポインタを取得
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case TYPE_NORMAL:// ノーマル : 青
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,128 };
            break;

        case TYPE_RIGHT:// 右 : 赤
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,128 };
            break;

        case TYPE_LEFT:// 左 : 緑
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,255,0,128 };
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
void CWall::ChangeType(void)
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
        nType = TYPE_NORMAL;
    }
    if (nType < TYPE_NORMAL)
    {
        nType = TYPE_MAX - 1;
    }

    // 種類を反映
    SetType((TYPE)nType);
}