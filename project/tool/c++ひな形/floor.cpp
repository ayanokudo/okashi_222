//=============================================================================
//
// 床クラス [floor.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "floor.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PATH "./data/Models/floor000.x"    //モデルのパス

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH   CFloor::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CFloor::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CFloor::m_nNumMatModel = 0;	    //マテリアル情報の数

//=============================================================================
// [CFloor] コンストラクタ
//=============================================================================
CFloor::CFloor() : CModel(OBJTYPE_FLOOR)
{

}

//=============================================================================
// [~CFloor] デストラクタ
//=============================================================================
CFloor::~CFloor()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CFloor * CFloor::Create(D3DXVECTOR3 pos, FLOOR type)
{
    CFloor *pObject = NULL;
    if (!pObject)
    {
        pObject = new CFloor;
        // 初期化
        pObject->Init(type);
        pObject->SetPos(pos);

        // 各値の代入・セット
        pObject->SetObjType(OBJTYPE_FLOOR); // オブジェクトタイプ
    }
    return pObject;
}

//=============================================================================
// [Load] テクスチャの読み込み
//=============================================================================
HRESULT CFloor::Load(void)
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
void CFloor::Unload(void)
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
HRESULT CFloor::Init(FLOOR type)
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
void CFloor::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CFloor::Update(void)
{
    CModel::Update();

    D3DXMATERIAL*pMat;      //マテリアルデータへのポインタ
                            //マテリアルデータへのポインタを取得
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case FLOOR_FLOORING:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,255 };
            break;
        case FLOOR_MAT:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
            break;

        case FLOOR_KITCHEN:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,255,0,255 };
            break;
        }
    }
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CFloor::Draw(void)
{
    CModel::Draw();
}

//=============================================================================
// [ChangeType] 種類の変更
//=============================================================================
void CFloor::ChangeType(void)
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
    if (nType >= FLOOR_MAX)
    {
        nType = FLOOR_FLOORING;
    }
    if (nType < FLOOR_FLOORING)
    {
        nType = FLOOR_MAX - 1;
    }

    // 種類を反映
    SetType((FLOOR)nType);
}
