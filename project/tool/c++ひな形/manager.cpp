//=============================
// インクルード
//=============================
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "scene.h"
#include "input.h"
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera.h"
#include "fade.h"
#include "particle.h"
#include "tutorial.h"
#include "pause.h"
#include "player.h"
#include "grid.h"
#include "object.h"
#include "stage.h"
#include "enemy.h"
#include "wall.h"
#include "floor.h"
#include "furniture.h"
#include "cube.h"

//=============================
// 静的メンバ変数宣言
//=============================
CManager::MODE   CManager::m_mode           = MODE_GAME;    // ゲームモード
CRenderer       *CManager::m_pRenderer      = NULL;         // レンダラーポインタ
CInputKeyboard  *CManager::m_pInputKeyboard = NULL;         // キーボード
CInputJoypad    *CManager::m_pJoypad        = NULL;         // ジョイパッド
CInputMouse     *CManager::m_pInputMouse    = NULL;         //　マウス
CSound          *CManager::m_pSound         = NULL;         // サウンド
CGame           *CManager::m_pGame          = NULL;         // ゲーム
CTitle          *CManager::m_pTitle         = NULL;         // タイトル
CResult         *CManager::m_pResult        = NULL;         // リザルト
CFade           *CManager::m_pFade          = NULL;         // フェード
CTutorial       *CManager::m_pTutorial      = NULL;         // チュートリアル
CPause          *CManager::m_pPause         = NULL;         // ポーズポインタ
bool             CManager::m_bPause = false;                // ポーズフラグ

//=============================
// コンストラクタ
//=============================
CManager::CManager()
{
	
}

//=============================
// デストラクタ
//=============================
CManager::~CManager()
{
}

//=============================
// 初期化処理
//=============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	
	// メモリの確保・初期化

	// キーボード
	m_pInputKeyboard = new CInputKeyboard;
	// キーボード初期化
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパッド
	m_pJoypad = new CInputJoypad;
	// ジョイパッドの初期化
	if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// マウス
	m_pInputMouse = new CInputMouse;
	// マウス初期化
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// レンダラー
	m_pRenderer = new CRenderer;
	// レンダラークラスの初期化
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

    // UI
#ifdef IMGUI_ON
    CUI::Create(hWnd);
#endif // IMGUI_ON

	// フェードの生成
	m_pFade = CFade::Create();
	m_pFade->SetFade(m_mode);

	// テクスチャの読み込み
	CBg::Load();        // 背景
	CNumber::Load();	// ナンバー
	CParticle::Load();	// パーティクル
	CPause::Load();		// ポーズ
	CPlayer::Load();	// プレイヤー
	CGrid::Load();		// 床
    CObject::Load();    // オブジェクト
    CStage::Load();     // ステージ
    CEnemy::Load();     // 敵
    CWall::Load();      // 壁
    CFloor::Load();     // 床
    CFumiture::Load();  // 家具
    CCube::Load();      // キューブ

	// ポーズ状態の時
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CManager::Uninit(void)
{
    // 開放処理
    CScene::ReleaseAll();

    // テクスチャのアンロード
    CBg::Unload();
    CNumber::Unload();
    CParticle::Unload();
    CPause::UnLoad();
    CPlayer::Unload();
    CGrid::Unload();
    CObject::Unload();
    CStage::Unload();
    CEnemy::Unload();     // 敵
    CWall::Unload();      // 壁
    CFloor::Unload();     // 床
    CFumiture::Unload();  // 家具
    CCube::Unload();      // キューブ

    if (m_pSound != NULL)
    {
        // 終了処理
        m_pSound->Uninit();
        // メモリの解放
        delete m_pSound;
        m_pSound = NULL;
    }

    if (m_pRenderer != NULL)
    {
        // 終了処理
        m_pRenderer->Uninit();
        // メモリの解放
        delete m_pRenderer;
        m_pRenderer = NULL;
    }

    if (m_pInputKeyboard != NULL)
    {
        // 終了処理
        m_pInputKeyboard->Uninit();
        // メモリの解放
        delete m_pInputKeyboard;
        m_pInputKeyboard = NULL;
    }

    if (m_pJoypad != NULL)
    {
        // 終了処理
        m_pJoypad->Uninit();
        // メモリの解放
        delete m_pJoypad;
        m_pJoypad = NULL;
    }

    if (m_pInputMouse != NULL)
    {
        // 終了処理
        m_pInputMouse->Uninit();
        // メモリの解放
        delete m_pInputMouse;
        m_pInputMouse = NULL;
    }

    if (m_pFade != NULL)
    {
        // 終了処理
        m_pFade->Uninit();
        // メモリの解放
        delete m_pFade;
        m_pFade = NULL;
    }


}

//=============================
// 更新処理
//=============================
void CManager::Update(void)
{

	// ジョイパッドクラスの更新処理
	if (m_pJoypad != NULL)
	{
		m_pJoypad->Update();
	}
	// キーボードクラスの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// マウスクラスの更新処理
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	// レンダラークラスの更新処理
	if (m_pRenderer != NULL)
	{

		if (m_mode == MODE_GAME)
		{// モードゲームのときポーズ画面の処理

			
			if (m_pInputKeyboard->GetKeyTrigger(DIK_TAB) || m_pJoypad->GetJoystickTrigger(11, 0))
			{// TAB

				if (m_pPause == NULL)
				{
					// 生成
					m_pPause = CPause::Create();
				}
				// ポーズの切り替え
				m_bPause ^= true;
			}
			if (!m_bPause)
			{// ポーズじゃないとき

				if (m_pPause != NULL)
				{
					m_pPause->Uninit();
					delete m_pPause;
					m_pPause = NULL;
				}
				m_pRenderer->Update();
			}
			else
			{// ポーズ状態
				if (m_pPause != NULL)
				{
					// ポーズの更新処理
					m_pPause->Update();
				}
			}
		}

		else
		{
			m_pRenderer->Update();
		}
		
	}

	// フェードクラスの更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

}

//=============================
// 描画処理
//=============================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================
// セットモード
//=============================
void CManager::SetMode(MODE mode)
{

	switch (m_mode)
	{
	case MODE_TITLE:
		// NULLクリア
		m_pTitle = NULL;
		break;
	case MODE_TUTORIAL:
		// NULLクリア
		m_pTutorial = NULL;
		// タイトルBGM停止
		//m_pSound->Stop(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_GAME:
		// NULLクリア
		m_pGame = NULL;
		// ゲームBGM停止
		//m_pSound->Stop(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// NULLクリア
		m_pResult = NULL;
		// リザルトBGM停止
		//m_pSound->Stop(CSound::LABEL_BGM_RESULT);
		break;

	default:
		break;
	}

	m_mode = mode;
	// 開放処理
	CScene::ReleaseAll();

	switch (m_mode)
	{
	case MODE_TITLE:
		// タイトル生成
		m_pTitle = CTitle::Create();
		// タイトルBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;
	case MODE_TUTORIAL:
		// チュートリアル生成
		m_pTutorial = CTutorial::Create();
		break;
	case MODE_GAME:
		// ゲーム生成
		m_pGame = CGame::Create();
		// ゲームBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_GAME);
		break;

	case MODE_RESULT:
		// リザルト生成
		m_pResult = CResult::Create();
		// リザルトBGM再生
		//m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;

	default:
		break;
	}
}
