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
#include "stage.h"
#include "object.h"

//=============================
// 静的メンバ変数宣言
//=============================
CCamera *CGame::m_pCamera = NULL;   // カメラクラスのポインタ変数
CPlayer *CGame::m_pPlayer = NULL;
CLight *CGame::m_pLight = NULL;		// ライトクラスのポインタ変数

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

	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// カメラの生成
	m_pCamera = CCamera::Create();

    // ステージの生成
    CStage::Create({ 0.0f,0.0f,0.0f });

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
    CObject::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	// ポリゴンの生成
	//CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	//床の生成
	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f),CFloor::FLOOR_FLOORING);
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
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
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