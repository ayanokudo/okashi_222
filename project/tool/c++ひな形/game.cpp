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
#include "file.h"
#include "debug.h"

//=============================
// 静的メンバ変数宣言
//=============================
CCamera *CGame::m_pCamera = NULL;   // カメラクラスのポインタ変数
CLight *CGame::m_pLight = NULL;		// ライトクラスのポインタ変数
CObject *CGame::m_pObject = NULL;   // オブジェクトへのポインタ
#if _DEBUG
CDebug *CGame::m_pDebug = NULL;     // デバッグ用テキストのポインタ
#endif //_DEBUG

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
    CStage::Create({ 0.0f,-1.0f,0.0f });

    // オブジェクトの生成
    m_pObject = CObject::Create({ 0.0f,0.0f,0.0f });

    // ファイルの読み込み
    CFile::Read();
	// ポリゴンの生成
	//CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	//床の生成
	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(GRID_SIZE * MAX_GRID, 0.0f, GRID_SIZE * MAX_GRID),CFloor::FLOOR_FLOORING);
	// ポーズの初期化
	CManager::SetActivePause(false);

#if _DEBUG
    m_pDebug = CDebug::Create();
#endif // _DEBUG

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

#if _DEBUG
    m_pDebug->Uninit();
#endif // _DEBUG
	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CGame::Update(void)
{
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
#if _DEBUG
    if (m_pDebug)
    {
        m_pDebug->Draw();
    }
#endif // _DEBUG
}