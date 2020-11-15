////////////////////////////////////////////////////
//
//    タイトルクラスの処理[title.cpp]
//    Author:筒井 俊稀
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "rogo.h"
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
#include "scene2d.h"
#include "sound.h"

//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CRogo::m_apTexture[MENU_MAX] = {};
LPDIRECT3DTEXTURE9 CRogo::m_apCatTex[CAT_MAX];        // テクスチャへのポインタ

//**********************************
// マクロ定義
//**********************************
#define  M_TEXTURE_PATH "./data/Textures/M.png"			// テクスチャ

#define CAT_SIZE D3DXVECTOR3(750.0f,311.0f,0.0f)/3
#define CAT_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)

#define ANIM_SPEED 14          // アニメーション速度
#define MAX_ANIMATION_X 5      // アニメーション数 横
#define MAX_ANIMATION_Y 3      // アニメーション数 縦


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
CRogo::CRogo()
{
	memset(&m_apPolygon, 0, sizeof(m_apPolygon));
	m_nMenu = START;
	m_bStick = false;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
	m_nCount = 0;
}

//=============================
// デストラクタ
//=============================
CRogo::~CRogo()
{
}

//=============================
// クリエイト
//=============================
CRogo * CRogo::Create(void)
{
	// メモリの確保
	CRogo *pTitle = new CRogo;

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
HRESULT CRogo::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, M_TEXTURE_PATH, &m_apTexture[BG]);

	return S_OK;
}

//=============================
// テクスチャ破棄
//=============================
void CRogo::Unload(void)
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
HRESULT CRogo::Init(void)
{
	m_apPolygon[BG] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[BG]->SetTexture(m_apTexture[BG]);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CRogo::Uninit(void)
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

	// 開放処理
	Release();
}


//=============================
// 更新処理
//=============================
void CRogo::Update(void)
{
	//サウンドのポインタ変数宣言
	CSound*pSound = CManager::GetSound();
	m_nCount++;
	if (m_nCount >= 500 ||
		CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 1))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}


//=============================
// 描画処理
//=============================
void CRogo::Draw(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MENU_MAX; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			// ポリゴンの描画処理
			m_apPolygon[nCntPolygon]->Draw();
		}
	}
}
