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
#include "grid.h"
#include "collision.h"
#include "wall.h"
#include "floor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PATH "./data/Models/cat V1.x"    //モデルのパス
#define GRID_MODE_MOVE   (GRID_SIZE * 2)      // グリッドモード時の移動量
#define NORMAL_MODE_MOVE (10.0f)     // ノーマルモードの字の移動量
#define INTERVAL         (10)                    //操作を受け付けるまでの間隔
#define OBJECT_RADIUS    (50.0f)                // 選択範囲の半径

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CObject::MODEL CObject::m_type= MODEL_PLAYER;
int CObject::m_ObjctNum = 0;
CModel *CObject::m_pModel = NULL;
CPlayer *CObject::m_pPlayer = NULL;
CCursor *CObject::m_pCursor = NULL;                     // カーソルへのポインタ


//=============================================================================
// [CObject] コンストラクタ
//=============================================================================
CObject::CObject()
{
    m_type = MODEL_PLAYER;
    m_pos = { GRID_SIZE,0.0f,GRID_SIZE };
    m_ObjctNum = 0;
    m_bGridMode = true;
    m_nCountInterval = INTERVAL;
    m_pCollision = NULL;
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
    m_pPlayer = CPlayer::Create(m_pos);
    m_pCursor = CCursor::Create(m_pos);
    m_pCollision = CCollision::CreateSphere(m_pos, OBJECT_RADIUS);
    return S_OK;
}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CObject::Uninit(void)
{

    // コリジョンの終了処理
    if (m_pCollision != NULL)
    {
        m_pCollision->Uninit();
        m_pCollision = NULL;
    }
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CObject::Update(void)
{
    // 座標の移動
    Move();

    // 配置するオブジェクトの変更
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_1)||
        CManager::GetKeyboard()->GetKeyTrigger(DIK_2))
    {
        ChangeObject();
    }

    // オブジェクトの配置
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE))
    {
        // タイプを配置用に変換
        SetObject(CObject::GetPlayer()->GetPos(), changeType());
    }

    // ファイル書き込み
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F1))
    {
        CFile::Writing();
    }

    // モード切替
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F2))
    {
        m_bGridMode ^= true;
        GridTransform();
    }

    // オブジェクトの削除
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_BACK))
    {
        DeleteObject();
    }
    // オブジェクトの回転
    Rotation();
    // 当たり判定の位置更新
    m_pCollision->SetPos(GetPos());
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CObject::Draw(void)
{

}

//=============================================================================
// [changeType] 配置用にタイプを変換
//=============================================================================
CModel::OBJTYPE CObject::changeType(void)
{
    CModel::OBJTYPE type;
    switch (m_type)
    {
    case MODEL_PLAYER:
        type = OBJTYPE_PLAYER;
        break;

    case MODEL_ENEMY:
        type = OBJTYPE_ENEMY;
        break;

    case MODEL_WALL:
        type = OBJTYPE_WALL;
        break;

    case MODEL_FLOOR:
        type = OBJTYPE_FLOOR;
        break;
        
    }

    return type;
}

//=============================================================================
// [GridTransform] グリッドの座標に変換
//=============================================================================
void CObject::GridTransform(void)
{
    m_pos = { GRID_SIZE,0.0f,GRID_SIZE };
}

//=============================================================================
// [Rotation] オブジェクトの回転
//=============================================================================
void CObject::Rotation(void)
{
    // 配置したオブジェクトと当たっているか調べる
    for (int nCount = 0; nCount < PRIORITY_NUM; nCount++)
    {
        // 先頭のアドレスを取得
        CScene *pScene = CScene::GetTop(nCount);
        while (pScene != NULL)
        {
            // 次のアドレスを保存
            CScene *pNext = pScene->GetNext();

            if (pScene != m_pPlayer&&
                pScene->GetType() == OBJTYPE_PLAYER ||
                pScene->GetType() == OBJTYPE_ENEMY ||
                pScene->GetType() == OBJTYPE_WALL ||
                pScene->GetType() == OBJTYPE_FLOOR)
            {
                if (CCollision::CollisionSphere(m_pCollision, ((CModel*)pScene)->GetCollision()))
                {
                    D3DXVECTOR3 rot = ((CModel*)pScene)->GetRot();
                    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_I))
                    {
                        rot.y += D3DXToRadian(90);
                    }
                    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_K))
                    {
                        rot.y -= D3DXToRadian(90);
                    }
                    ((CModel*)pScene)->SetRot(rot);
                }
            }
            // 次のアドレスを取得
            pScene = pNext;
        }
    }
}

//=============================================================================
// [ChangeObject] オブジェクトの変更
//=============================================================================
void CObject::ChangeObject(void)
{
    int nModel = m_type;
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_1))
    {
        nModel -=  1;
    }
    if (CManager::GetKeyboard()->GetKeyTrigger(DIK_2))
    {
        nModel += 1;
    }
    // 最大値以上/最小値以下になったらループ
    if (nModel >= MODEL_MAX)
    {
        nModel = MODEL_PLAYER;
    }
    if (nModel < MODEL_PLAYER)
    {
        nModel = MODEL_MAX-1;
    }

    m_type = (MODEL)nModel;
}

//=============================================================================
// [DeleteObject] オブジェクトの削除
//=============================================================================
void CObject::DeleteObject(void)
{
    // 配置したオブジェクトと当たっているか調べる
    for (int nCount = 0; nCount < PRIORITY_NUM; nCount++)
    {
        // 先頭のアドレスを取得
        CScene *pScene = CScene::GetTop(nCount);
        while (pScene != NULL)
        {
            // 次のアドレスを保存
            CScene *pNext = pScene->GetNext();

            if (pScene !=m_pPlayer&&
                pScene->GetType() == OBJTYPE_PLAYER ||
                pScene->GetType() == OBJTYPE_ENEMY ||
                pScene->GetType() == OBJTYPE_WALL||
                pScene->GetType() == OBJTYPE_FLOOR)
            {
                if (CCollision::CollisionSphere(m_pCollision, ((CModel*)pScene)->GetCollision()))
                {
                    pScene->Uninit();
                    pScene = NULL;
                    return;
                }
            }
            // 次のアドレスを取得
            pScene = pNext;
        }
    }
}

//=============================================================================
// [SetObject] オブジェクトの配置
// Author : AYANO KUDO
// 引数
//pos : 位置
//=============================================================================
void CObject::SetObject(D3DXVECTOR3 pos, CModel::OBJTYPE type)
{
    switch (type)
    {
    case CModel::OBJTYPE_PLAYER:

        m_pModel= CPlayer::Create(pos);
        break;

    case CModel::OBJTYPE_ENEMY:
        m_pModel = CEnemy::Create(pos);
        break;

    case CModel::OBJTYPE_WALL:
        m_pModel = CWall::Create(pos);
        break;

    case CModel::OBJTYPE_FLOOR:
        m_pModel = CFloor::Create(pos);
        break;
    }
}

//=============================================================================
// [Move] 移動処理
//=============================================================================
void CObject::Move(void)
{

    //移動量の目標値
    D3DXVECTOR3 moveDest = { 0.0f,0.0f,0.0f };
    // ジョイスティックの取得
    DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);
    float fMove = 0.0f;// 移動量

    m_ObjctNum++;
    if (m_bGridMode)
    {
        if (m_ObjctNum >= INTERVAL)
        {
            fMove = GRID_MODE_MOVE;
            m_ObjctNum = 0;
        }
    }
    else
    {
        fMove = NORMAL_MODE_MOVE;
    }

    if (CManager::GetKeyboard()->GetKeyPress(DIK_W) || js.lY <= -600)
    {// ↑移動
        moveDest.z = -fMove;
        if (!m_bGridMode)
        {
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
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
    {// ↓移動

        moveDest.z = fMove;
        if (!m_bGridMode)
        {
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
