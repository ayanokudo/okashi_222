//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 筒井 ＆ 増澤
//
//=============================================================================

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
#include "floor.h"
#include "wall.h"
#include "bullet.h"
#include "enemy.h"
#include "boss.h"
#include "item.h"
#include "debug_log.h"
#include "scratch.h"
#include "ui.h"
#include "boss.h"
#include "collect.h"
#include "life.h"
#include "win.h"
#include "lose.h"
#include "time.h"
#include "furniture.h"
#include "rogo.h"
#include "gage.h"
#include "explosion.h"
#include "start.h"

//=============================
// 静的メンバ変数宣言
//=============================
CManager::MODE   CManager::m_mode = MODE_ROGO;      // ゲームモード
CRenderer       *CManager::m_pRenderer = NULL;       // レンダラーポインタ
CInputKeyboard  *CManager::m_pInputKeyboard = NULL;  // キーボード
CInputJoypad    *CManager::m_pJoypad = NULL;         // ジョイパッド
CInputMouse     *CManager::m_pInputMouse = NULL;     //　マウス
CSound          *CManager::m_pSound = NULL;          // サウンド
CGame           *CManager::m_pGame = NULL;           // ゲーム
CTitle          *CManager::m_pTitle = NULL;          // タイトル
CResult         *CManager::m_pResult = NULL;         // リザルト
CFade           *CManager::m_pFade = NULL;           // フェード
CTutorial       *CManager::m_pTutorial = NULL;       // チュートリアル
CWin            *CManager::m_pWin = NULL;            // フェード
CLose           *CManager::m_pLose = NULL;			 // チュートリアル
CRogo		    *CManager::m_pRogo = NULL;
CPause          *CManager::m_pPause = NULL;          // ポーズポインタ
bool             CManager::m_bPause = false;         // ポーズフラグ

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

	// サウンド
	m_pSound = new CSound;
	// サウンドクラスの初期化
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}
	
	// デバッグログ
	CDebugLog::Init();

	// フェードの生成
	m_pFade = CFade::Create();
	m_pFade->SetFade(m_mode);

	// テクスチャの読み込み
	CBg::Load();        // 背景
	CUi::Load();		// ui
	CNumber::Load();	// ナンバー
	CParticle::Load();	// パーティクル
	CPause::Load();		// ポーズ
	CPlayer::Load();	// プレイヤー
	CFloor::Load();		// 床
	CWall::Load();		// 壁
	CBullet::Load();    // 弾
	CEnemy::Load();		// 敵
    CBoss::Load();      // ボス
	CItem::Load();		// アイテム
	CScratch::Load();	// ひっかき
	CBoss::Load();      // ボス
	CCollect::Load();   // コレクト
	CLife::Load();		//
	CTitle::Load();		//
    CFurniture::Load();
	CRogo::Load();
	CGage::Load();      // ボスのHPゲージ
	CExplosion::Load(); // 爆発
	CStart::Load();     // スタートロゴ

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
	CBg::Unload();       // 背景
	CUi::Unload();		 // ui
	CNumber::Unload();	 // ナンバー
	CParticle::Unload(); // パーティクル
	CPause::UnLoad();	 // ポーズ
	CPlayer::Unload();	 // プレイヤー
	CFloor::Unload();	 // 床
	CBullet::Unload();   // 弾
	CWall::Unload();	 //	壁
	CEnemy::Unload();	 // 敵
    CBoss::Unload();     // ボス
	CItem::Unload();	 //	アイテム
	CScratch::Unload();  // ひっかき
	CBoss::Unload();     // ボス
	CCollect::Unload();  // コレクト
	CLife::Unload();
	CTitle::Unload();
    CFurniture::Unload();
	CRogo::Unload();
	CGage::Unload();      // ボスのHPゲージ
	CExplosion::Unload(); // 爆発
	CStart::Unload();     // スタートロゴ

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
	
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = NULL;
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

			if (m_pInputKeyboard->GetKeyTrigger(DIK_TAB) || m_pJoypad->GetJoystickTrigger(11, 0)|| m_pJoypad->GetJoystickTrigger(11, 1))
			{// TAB

				if (m_pPause == NULL)
				{
					// 生成
					m_pPause = CPause::Create();
				}
				// ポーズの切り替え
				m_bPause ^= true;

				// ポーズに入った時間の保存
				if (m_bPause)
				{
					CTime::SetPauseTime();
				}
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
	case MODE_ROGO:
		// NULLクリア
		m_pRogo = NULL;
		m_pSound->Stop(CSound::SOUND_SE_ROGO_BGM);
		break;
	case MODE_TITLE:
		// NULLクリア
		m_pTitle = NULL;
		// タイトルBGM停止
		m_pSound->Stop(CSound::SOUND_BGM_TITLE);
		break;
	case MODE_TUTORIAL:
		// NULLクリア
		m_pTutorial = NULL;
		// タイトルBGM停止
		m_pSound->Stop(CSound::SOUND_BGM_TUTORIAL);
		break;
	case MODE_GAME:
		// NULLクリア
		m_pGame = NULL;
		// ゲームBGM停止
		m_pSound->Stop();
		break;
	case MODE_WIN:
		// NULLクリア
		m_pWin = NULL;
		// ゲームBGM停止
		m_pSound->Stop(CSound::SOUND_BGM_RESULT_WIN);
		break;
	case MODE_LOSE:
		// NULLクリア
		m_pLose = NULL;
		// ゲームBGM停止
		m_pSound->Stop(CSound::SOUND_BGM_RESULT_LOSE);
		break;
	case MODE_RESULT:
		// NULLクリア
		m_pResult = NULL;
		// リザルトBGM停止
		m_pSound->Stop(CSound::SOUND_BGM_RESULT_LOSE);
		break;

	default:
		break;
	}

	m_mode = mode;
	// 開放処理

	CScene::ReleaseAll();

	switch (m_mode)
	{
	case MODE_ROGO:
		// タイトル生成
		m_pRogo = CRogo::Create();
		// タイトルBGM再生
		m_pSound->Play(CSound::SOUND_SE_ROGO_BGM);
		break;
	case MODE_TITLE:
		// タイトル生成
		m_pTitle = CTitle::Create();
		// タイトルBGM再生
		m_pSound->Play(CSound::SOUND_BGM_TITLE);
		break;
	case MODE_TUTORIAL:
		// チュートリアル生成
		m_pTutorial = CTutorial::Create();
		// タイトルBGM再生
		m_pSound->Play(CSound::SOUND_BGM_TUTORIAL);
		break;
	case MODE_GAME:
		// ゲーム生成
		m_pGame = CGame::Create();
		// ゲームBGM再生
		m_pSound->Play(CSound::SOUND_BGM_GAME);
		break;
	case MODE_WIN:
		// ゲーム生成
		m_pWin = CWin::Create();
		// ゲームBGM再生
		m_pSound->Play(CSound::SOUND_BGM_RESULT_WIN);
		break;
	case MODE_LOSE:
		// ゲーム生成
		m_pLose = CLose::Create();
		// ゲームBGM再生
		m_pSound->Play(CSound::SOUND_BGM_RESULT_LOSE);
		break;
	case MODE_RESULT:
		// リザルト生成
		m_pResult = CResult::Create();
		// リザルトBGM再生
		m_pSound->Play(CSound::SOUND_BGM_RESULT_LOSE);
		break;

	default:
		break;
	}
}
