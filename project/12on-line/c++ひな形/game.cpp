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

//=============================
// 静的メンバ変数宣言
//=============================
CCamera *CGame::m_pCamera = NULL;   // カメラ


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
	// カメラの生成
	m_pCamera = CCamera::Create();
	// ポリゴンの生成
	CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
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