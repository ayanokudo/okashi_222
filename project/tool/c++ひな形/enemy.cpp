//=============================================================================
//
// 敵クラス [enemy.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PATH "./data/Models/Mouse_jouhanshin.x"    //モデルのパス

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPD3DXMESH   CEnemy::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CEnemy::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CEnemy::m_nNumMatModel = 0;	    //マテリアル情報の数

//=============================================================================
// [CEnemy] コンストラクタ
//=============================================================================
CEnemy::CEnemy() : CModel(OBJTYPE_ENEMY)
{
    m_type = ENEMY::ENEMY_CARRIER;
}

//=============================================================================
// [~CEnemy] デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos)
{
    CEnemy *pObject = NULL;
    if (!pObject)
    {
        pObject = new CEnemy;
        pObject->Init();
        // 初期化
        pObject->Init();
        pObject->SetPos(pos);

        // 各値の代入・セット
        pObject->SetObjType(OBJTYPE_ENEMY); // オブジェクトタイプ
    }
    return pObject;
}

//=============================================================================
// [Load] テクスチャの読み込み
//=============================================================================
HRESULT CEnemy::Load(void)
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
void CEnemy::Unload(void)
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
HRESULT CEnemy::Init(void)
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
void CEnemy::Uninit(void)
{
    CModel::Uninit();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CEnemy::Update(void)
{
    CModel::Update();

    D3DXMATERIAL*pMat;  	//マテリアルデータへのポインタ

    //マテリアルデータへのポインタを取得
    pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
    {
        switch (m_type)
        {
        case ENEMY_CARRIER:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 0,0,255,255 };
            break;
        case ENEMY_ESCORT:
            //マテリアルのアンビエントにディフューズカラーを設定
            pMat[nCntMat].MatD3D.Diffuse = { 255,0,0,255 };
            break;

        }
    }

}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
    CModel::Draw();
}


//=============================================================================
// [ChangeType] 種類の変更
//=============================================================================
void CEnemy::ChangeType(void)
{
    int nType=m_type;
    
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_3))
    {
        nType -= 1;
    }
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_4))
    {
        nType += 1;
    }

    // 最大値以上/最小値以下になったらループ
    if (nType >= ENEMY_MAX)
    {
        nType = ENEMY_CARRIER;
    }
    if (nType < ENEMY_CARRIER)
    {
        nType = ENEMY_MAX - 1;
    }

    // 種類を反映
    SetType((ENEMY)nType);
}
