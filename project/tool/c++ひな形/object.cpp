//=============================================================================
//
// オブジェクトクラス [object.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "file.h"
#include "joypad.h"
#include "cursor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PATH "./data/Models/cat V1.x"    //モデルのパス
#define GRID_MODE_MOVE   (10.0f)      // グリッドモード時の移動量
#define NORMAL_MODE_MOVE (3.0f)     // ノーマルモードの字の移動量
#define INTERVAL         (7)                    //操作を受け付けるまでの間隔

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CObject::m_ObjctNum = 0;
CModel *CObject::m_pModel[MAX_OBJECT] = {};
CPlayer *CObject::m_pPlayer = NULL;
CCursor *CObject::m_pCursor = NULL;                     // カーソルへのポインタ


//=============================================================================
// [CObject] コンストラクタ
//=============================================================================
CObject::CObject()
{
    m_pos = { 0.0f,0.0f,0.0f };
    m_ObjctNum = 0;
    m_bGridMode = false;
    m_nCountInterval = INTERVAL;
    
}

//=============================================================================
// [~CObject] デストラクタ
//=============================================================================
CObject::~CObject()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos)
{
    CObject *pObject = NULL;
    if (!pObject)
    {
        pObject = new CObject;
        pObject->Init();
        // 各値の代入・セット
    }
    return pObject;
}

//=============================================================================
// [Load] テクスチャの読み込み
//=============================================================================
HRESULT CObject::Load(void)
{
    return S_OK;
}

//=============================================================================
// [Unload] テクスチャの破棄
//=============================================================================
void CObject::Unload(void)
{

}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
HRESULT CObject::Init(void)
{
    // プレイヤーの生成
    m_pPlayer = CPlayer::Create({ 0.0f, 0.0f, 0.0f });
    m_pCursor = CCursor::Create({ 0.0f, 0.0f, 0.0f });
    return S_OK;
}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CObject::Uninit(void)
{

}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CObject::Update(void)
{
    // 座標の移動
    Move();

    // オブジェクトの配置
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE))
    {
        SetObject(CObject::GetPlayer()->GetPos());
    }

    // ファイル書き込み
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
    {
        CFile::Writing();
    }
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CObject::Draw(void)
{

}

//=============================================================================
// [SetObject] オブジェクトの配置
// Author : AYANO KUDO
// 引数
//pos : 位置
//=============================================================================
void CObject::SetObject(D3DXVECTOR3 pos)
{
        // 現在の位置にオブジェクトの配置をする
        for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
        {
            if (m_pModel[nCnt] == NULL)
            {
                m_pModel[nCnt] = CEnemy::Create(pos);
                break;// 一体ずつ配置するためにループを抜ける
            }
        }
}

//=============================================================================
// [Move] 移動処理
//=============================================================================
void CObject::Move(void)
{

    //移動量の目標値
    D3DXVECTOR3 moveDest = {0.0f,0.0f,0.0f};
    // ジョイスティックの取得
    DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

    float fMove;// 移動量

    if (m_bGridMode)
    {
        fMove = GRID_MODE_MOVE;

    }
    else
    {
        fMove = NORMAL_MODE_MOVE;
    }

    if (CManager::GetKeyboard()->GetKeyPress(DIK_W) || js.lY <= -600)
    {// ↑移動
        moveDest.z = -fMove;

        if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
        {
            moveDest.z = sinf(45) * -fMove;
            moveDest.x = cosf(45) * fMove;
        }
        if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
        {
            moveDest.z = sinf(45) * -fMove;
            moveDest.x = cosf(45) * -fMove;
        }
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
    {// ↓移動

        moveDest.z = fMove;

        if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
        {
            moveDest.z = sinf(45) * fMove;
            moveDest.x = cosf(45) * fMove;
        }
        if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
        {
            moveDest.z = sinf(45) * fMove;
            moveDest.x = cosf(45) * -fMove;
        }
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
    {// ←移動
        moveDest.x = fMove;

    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
    {// →移動
        moveDest.x = -fMove;
    }

    // 移動量を足す
    m_pos += moveDest;
    m_pPlayer->SetPos(m_pos);
    m_pCursor->SetPos(m_pos);

}
