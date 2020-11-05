////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "player.h"
#include "light.h"
#include "floor.h"
#include "wall.h"
#include "enemy.h"
#include "boss.h"
#include "item.h"
#include "time.h"
#include "ui.h"
#include "file.h"

//=============================
// 静的メンバ変数宣言
//=============================
CCamera *CGame::m_pCamera = NULL;   // カメラクラスのポインタ変数
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};	// プレイヤークラスのポインタ変数
CEnemy  *CGame::m_pEnemy  = NULL;	// エネミークラスのポインタ変数
CBoss   *CGame::m_pBoss   = NULL;   // ボスクラスのポインタ変数
CItem   *CGame::m_pItem	  = NULL;	// アイテムクラスのポインタ変数
CScore  *CGame::m_pScore  = NULL;	// スコアクラスのポインタ変数
CTime   *CGame::m_pTime   = NULL;	// タイムクラスのポインタ変数
CLight  *CGame::m_pLight  = NULL;	// ライトクラスのポインタ変数

//=============================
// コンストラクタ
//=============================
CGame::CGame()
{
}

//=============================
// デストラクタ
//=============================
CGame::~CGame()
{
}

//=============================
// クリエイト
//=============================
CGame * CGame::Create(void)
{
	// メモリの確保
	CGame *pGame = new CGame;
	// 初期化
	pGame->Init();
	return pGame;
}

//=============================
// 初期化処理
//=============================
HRESULT CGame::Init(void)
{	
	//ライトクラスの生成
	m_pLight = new CLight;
	// 初期化
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// カメラの生成
	m_pCamera = CCamera::Create();
	
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER;nCntPlayer++)
	{
		// プレイヤーの生成
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(0.0f,0.0f, 0.0f), nCntPlayer);
	}
	
	// エネミーの生成
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -800.0f), CEnemy::ENEMY_ESCORT);

    // ボスの生成
    m_pBoss = CBoss::Create(D3DXVECTOR3(100.0f, 0.0f, -500.0f));
	// アイテムの生成
	m_pItem = CItem::Create(D3DXVECTOR3(200.0f, 0.0f, -800.0f));
	// スコアの生成
	m_pScore = CScore::Create();
	// タイムの生成
	m_pTime = CTime::Create();
	
    // ステージファイルの読み込み
    CFile::Read();

	//// 床の生成
	//CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 2000.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(-2000.0f, 0.0f, 2000.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(2000.0f, 0.0f, -2000.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(-2000.0f, 0.0f, -2000.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(-2000.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);
	//CFloor::Create(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), CFloor::FLOOR_FLOORING);

	//// 壁の生成
	//CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 3000.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CWall::WALL_1);
	//CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -3000.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CWall::WALL_1);
	//CWall::Create(D3DXVECTOR3(2000.0f, 0.0f, 3000.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CWall::WALL_1);
	//CWall::Create(D3DXVECTOR3(2000.0f, 0.0f, -3000.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CWall::WALL_1);
	//CWall::Create(D3DXVECTOR3(-2000.0f, 0.0f, 3000.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CWall::WALL_1);
	//CWall::Create(D3DXVECTOR3(-2000.0f, 0.0f, -3000.0f), D3DXVECTOR3(1000.0f, 1000.0f, 0.0f), CWall::WALL_1);

	// ポーズの初期化
	CManager::SetActivePause(false);
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CGame::Uninit(void)
{
	// 開放処理
	CCamera::Release();

	// ライト
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CGame::Update(void)
{
	//if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	//{
	//	CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	//}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
}


//=============================
// 描画処理
//=============================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}