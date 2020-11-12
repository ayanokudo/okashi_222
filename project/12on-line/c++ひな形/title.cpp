////////////////////////////////////////////////////
//
//    タイトルクラスの処理[title.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "ui.h"
#include "player.h"
//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MENU_MAX] = {};

//**********************************
// マクロ定義
//**********************************
#define  TITLE_TEXTURE_PATH "./data/Textures/Title.png"			// テクスチャ
#define  EXIT_TEXTURE_PATH "./data/Textures/Out_button.png"			// テクスチャ
#define  START_TEXTURE_PATH "./data/Textures/Play_button.png"		// テクスチャ
#define  TUTORIAL_TEXTURE_PATH "./data/Textures/Tutorial_button.png" // テクスチャ

#define BACK_SIZE D3DXVECTOR3(200.0f,180.0f,0.0f)					// 背面サイズ
#define BACK_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)	// 背面座標

#define STRING_SIZE D3DXVECTOR3(170.0f,100.0f,0.0f)					// 文字列
#define EXIT_POS  D3DXVECTOR3(180.0f,580.0f,0.0f)					// 続ける
#define START_POS D3DXVECTOR3(645.0f, 580.0f,0.0f)                  // リスタート
#define TUTORIAL_POS   	D3DXVECTOR3(1100.0f,580.0f,0.0f)			// 終了

#define MENU_ENTER_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)			// 選んでるメニューの色
#define MENU_NOT_ENTER_COL D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f)		// 選んでないメニューの色

//=============================
// コンストラクタ
//=============================
CTitle::CTitle()
{
	memset(&m_apPolygon, 0, sizeof(m_apPolygon));
	m_pUi = NULL;
	m_nMenu = START;
	m_bStick = false;
}

//=============================
// デストラクタ
//=============================
CTitle::~CTitle()
{
}

//=============================
// クリエイト
//=============================
CTitle * CTitle::Create(void)
{
	// メモリの確保
	CTitle *pTitle = new CTitle;

	if (pTitle != NULL)
	{
		// 初期化
		pTitle->Init();
	}
	return pTitle;
}

//=============================
// テクスチャロード
//=============================
HRESULT CTitle::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_PATH, &m_apTexture[BG]);
	D3DXCreateTextureFromFile(pDevice, EXIT_TEXTURE_PATH, &m_apTexture[EXIT]);
	D3DXCreateTextureFromFile(pDevice, START_TEXTURE_PATH, &m_apTexture[START]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_PATH, &m_apTexture[TUTORIAL]);

	return S_OK;
}

//=============================
// テクスチャ破棄
//=============================
void CTitle::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MENU_MAX; nCntTex++)
	{
		// テクスチャの開放
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//=============================
// 初期化処理
//=============================
HRESULT CTitle::Init(void)
{
	m_apPolygon[BG] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[BG]->SetTexture(m_apTexture[BG]);

	//タイムの文字表示
	m_pUi = CUi::Create(D3DXVECTOR3(650.0f, 200.0f, 0.0f),
		D3DXVECTOR3(300, 200, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_TITLE);

	// EXITのやつ
	m_apPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
	m_apPolygon[EXIT]->SetTexture(m_apTexture[EXIT]);
	// スタートのやつ
	m_apPolygon[START] = CPolygon::Create(START_POS, STRING_SIZE);
	m_apPolygon[START]->SetTexture(m_apTexture[START]);
	// Tutorialのやつ
	m_apPolygon[TUTORIAL] = CPolygon::Create(TUTORIAL_POS, STRING_SIZE);
	m_apPolygon[TUTORIAL]->SetTexture(m_apTexture[TUTORIAL]);
	
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTitle::Uninit(void)
{
	for (int nCntTex = 0; nCntTex < MENU_MAX; nCntTex++)
	{
		if (m_apPolygon[nCntTex] != NULL)
		{
			// ポリゴンの終了処理
			m_apPolygon[nCntTex]->Uninit();

			// メモリの解放
			delete m_apPolygon[nCntTex];
			m_apPolygon[nCntTex] = NULL;
		}
	}

	if (m_pUi != NULL)
	{
		// ポリゴンの終了処理
		m_pUi->Uninit();

		// メモリの解放
		delete m_pUi;
		m_pUi = NULL;
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CTitle::Update(void)
{
	
	m_pUi->Update();
	// 選んでるメニューで色分け
	for (int nCntMenu = EXIT; nCntMenu < MENU_MAX; nCntMenu++)
	{
		if (m_nMenu == nCntMenu)
		{// 選んでるとき
			m_apPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
			m_apPolygon[nCntMenu]->Flashing();
		}
		else
		{// 選んでないとき
			m_apPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
		}
	}

	DIJOYSTATE js[MAX_PLAYER] ={ CManager::GetJoypad()->GetStick(0), CManager::GetJoypad()->GetStick(1) };
	// メニュー操作
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_A) ||
		CManager::GetKeyboard()->GetKeyTrigger(DIK_LEFT) ||
		js[0].lX <= -100 || js[1].lX <= -100)
	{// ←
		if (!m_bStick)
		{
			m_nMenu--;
			m_bStick = true;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_D) ||
		CManager::GetKeyboard()->GetKeyTrigger(DIK_RIGHT) ||
		js[0].lX >= 100 || js[1].lX >= 100)
	{// →
		if (!m_bStick)
		{
			m_nMenu++;
			m_bStick = true;
		}
	}
	else
	{
		m_bStick = false;
	}
	// 範囲外に行かないように
	if (m_nMenu > TUTORIAL)
	{
		m_nMenu = EXIT;
	}
	else if (m_nMenu < EXIT)
	{
		m_nMenu = TUTORIAL;
	}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
		CManager::GetMouse()->GetMouseTrigger(0) || 
		CManager::GetJoypad()->GetJoystickTrigger(3, 0)|| 
		CManager::GetJoypad()->GetJoystickTrigger(3, 1))
	{
		switch (m_nMenu)
		{
		case EXIT:
			// 終了処理
			DestroyWindow(FindWindow(WINDOW_CLASS_NAME, NULL));
			break;
		case START:
			// リスタート
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
			break;
		case TUTORIAL:
			CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
			break;
		default:
			break;
		}
	}
}


//=============================
// 描画処理
//=============================
void CTitle::Draw(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MENU_MAX; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			// ポリゴンの描画処理
			m_apPolygon[nCntPolygon]->Draw();
		}
	}
	m_pUi->Draw();
}
