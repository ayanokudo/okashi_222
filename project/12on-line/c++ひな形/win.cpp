////////////////////////////////////////////////////
//
//    WINクラスの処理[win.cpp]
//    Author:筒井　俊稀
//
////////////////////////////////////////////////////
//=============================
// インクルード
//=============================
#include "win.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"

//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CWin::m_pTexture = NULL;
//**********************************
// マクロ定義
//**********************************
#define  WIN_TEXTURE_PATH "./data/Textures/Clear.png" // テクスチャ

//=============================
// コンストラクタ
//=============================
CWin::CWin()
{
	m_pPolygon = NULL;
}

//=============================
// デストラクタ
//=============================
CWin::~CWin()
{
}

//=============================
// クリエイト
//=============================
CWin * CWin::Create(void)
{
	// メモリの確保
	CWin *pWin = new CWin;

	if (pWin != NULL)
	{
		// 初期化
		pWin->Init();
	}
	return pWin;
}

//=============================
// 初期化処理
//=============================
HRESULT CWin::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, WIN_TEXTURE_PATH, &m_pTexture);


	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pPolygon->SetTexture(m_pTexture);

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CWin::Uninit(void)
{
	// テクスチャの解放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	if (m_pPolygon != NULL)
	{
		// ポリゴンの終了処理
		m_pPolygon->Uninit();

		// メモリの解放
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CWin::Update(void)
{
	// ポリゴンの更新処理
	m_pPolygon->Update();

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetMouse()->GetMouseTrigger(0) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
}

//=============================
// 描画処理
//=============================
void CWin::Draw(void)
{
	// ポリゴンの描画処理
	m_pPolygon->Draw();
}
