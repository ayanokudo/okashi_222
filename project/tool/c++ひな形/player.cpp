////////////////////////////////////////////////////
//
//    particleクラスの処理[particle.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "scene3d.h"
#include "object.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/cat V1.x"    //モデルのパス
#define PLAYER_SPEED 10
#define PLAYER_MOVE_RATE 0.05f

//*****************************
// 静的メンバ変数宣言
//*****************************
char* CPlayer::m_apModelData[CPlayer::MODEL_MAX] = {
   "./data/Models/cat V1.x",
   "./data/Models/test000.x"
};// モデルのファイル名

LPD3DXMESH   CPlayer::m_pMeshModel[CPlayer::MODEL_MAX] = {};   	//メッシュ情報へのポインタ
LPD3DXBUFFER CPlayer::m_pBuffMatModel[CPlayer::MODEL_MAX] = {};	//マテリアル情報へのポインタ
DWORD        CPlayer::m_nNumMatModel[CPlayer::MODEL_MAX] = {};	    //マテリアル情報の数

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer() : CModel(OBJTYPE_PLAYER)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//******************************
// デストラクタ
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// クリエイト
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	// 初期化
	pPlayer->Init();
	pPlayer->SetPos(pos);
	// 各値の代入・セット
	pPlayer->SetObjType(OBJTYPE_PLAYER); // オブジェクトタイプ

	return pPlayer;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CPlayer::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
    for (int nCntModel = 0; nCntModel <MODEL_MAX; nCntModel++)
    {
	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[nCntModel],
		NULL,
		&m_nNumMatModel[nCntModel],
		&m_pMeshModel[nCntModel]);
    }

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CPlayer::Unload(void)
{
	//メッシュの破棄
    for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
    {
        if (m_pMeshModel[nCntModel] != NULL)
        {
            m_pMeshModel[nCntModel]->Release();
            m_pMeshModel[nCntModel] = NULL;
        }
        //マテリアルの破棄
        if (m_pBuffMatModel[nCntModel] != NULL)
        {
            m_pBuffMatModel[nCntModel]->Release();
            m_pBuffMatModel[nCntModel] = NULL;
        }
    }
}

//******************************
// 初期化処理
//******************************
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindModel(m_pMeshModel[MODEL_PLAYER], m_pBuffMatModel[MODEL_PLAYER], m_nNumMatModel[MODEL_PLAYER]);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{

	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
    CModel::Update();
	D3DXVECTOR3 rot = GetRot();
	
	SetRot(rot);
    // 操作の管理
	//Controll();
}

//******************************
// 描画処理 
//******************************
void CPlayer::Draw(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    // ワイヤーフレーム
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	CModel::Draw();
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//******************************
// 操作の管理
//******************************
void CPlayer::Controll(void)
{
	// 座標
	D3DXVECTOR3 pos = GetPos();
	//移動量の目標値
	D3DXVECTOR3 moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ジョイスティックの取得
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

	if (CManager::GetKeyboard()->GetKeyPress(DIK_W) || js.lY <= -600)
	{// ↑移動
		moveDest.z = -PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
	{// ↓移動

		moveDest.z = PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
	{// ←移動
		moveDest.x = PLAYER_SPEED;

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
	{// →移動
		moveDest.x = -PLAYER_SPEED;
	}

	// 慣性
	m_move = (moveDest);
	
	// 移動量を足す
	pos += m_move;

	// 座標のセット
	SetPos(pos);
}
