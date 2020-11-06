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

//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MENU_MAX] = {};

//**********************************
// マクロ定義
//**********************************
#define  EXIT_TEXTURE_PATH "./data/Textures/title00.png" // テクスチャ
#define  START_TEXTURE_PATH "./data/Textures/title00.png" // テクスチャ
#define  TUTORIAL_TEXTURE_PATH "./data/Textures/title00.png" // テクスチャ

#define BACK_SIZE D3DXVECTOR3(200.0f,180.0f,0.0f)                  // 背面サイズ
#define BACK_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f) // 背面座標

#define STRING_SIZE D3DXVECTOR3(120.0f,50.0f,0.0f)                                  // 文字列
#define TUTORIAL_POS  D3DXVECTOR3(150.0f,600.0f,0.0f) // 続ける
#define START_POS D3DXVECTOR3(640.0f, 600.0f,0.0f)                        // リスタート
#define EXIT_POS   	D3DXVECTOR3(1150.0f,600.0f,0.0f) // 終了

#define MENU_ENTER_COL D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f)     // 選んでるメニューの色
#define MENU_NOT_ENTER_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) // 選んでないメニューの色

//=============================
// コンストラクタ
//=============================
CTitle::CTitle()
{
	memset(&m_apPolygon, 0, sizeof(m_apPolygon));
	m_pUi = NULL;
	m_nMenu = BG;
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
	D3DXCreateTextureFromFile(pDevice, "data/Textures/Voice.png", &m_apTexture[EXIT]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/Voice.png", &m_apTexture[START]);
	D3DXCreateTextureFromFile(pDevice, "data/Textures/Voice.png", &m_apTexture[TUTORIAL]);

	return S_OK;
}

//=============================
// テクスチャ破棄
//=============================
void CTitle::UnLoad(void)
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

	//タイムの文字表示
	m_pUi = CUi::Create(D3DXVECTOR3(650.0f, 200.0f, 0.0f),
		D3DXVECTOR3(300, 200, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_TITLE);

	// 再開のやつ
	m_apPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
	m_apPolygon[EXIT]->SetTexture(m_apTexture[EXIT]);
	// リスタートのやつ
	m_apPolygon[START] = CPolygon::Create(START_POS, STRING_SIZE);
	m_apPolygon[START]->SetTexture(m_apTexture[START]);
	// EXITのやつ
	m_apPolygon[TUTORIAL] = CPolygon::Create(TUTORIAL_POS, STRING_SIZE);
	m_apPolygon[TUTORIAL]->SetTexture(m_apTexture[EXIT]);
	
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTitle::Uninit(void)
{
	for (int nCntTex = 0; nCntTex < MENU_MAX; nCntTex++)
	{
		// テクスチャの解放
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
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
		}
		else
		{// 選んでないとき
			m_apPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
		}
	}

	// メニュー操作
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_A) || CManager::GetKeyboard()->GetKeyTrigger(DIK_LEFT))
	{// ↑
		m_nMenu--;
	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_D) || CManager::GetKeyboard()->GetKeyTrigger(DIK_RIGHT))
	{// ↓
		m_nMenu++;
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
		CManager::GetJoypad()->GetJoystickTrigger(3, 0))
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
