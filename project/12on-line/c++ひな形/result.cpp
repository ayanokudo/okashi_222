////////////////////////////////////////////////////
//
//    リザルトクラスの処理[result.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////
//=============================
// インクルード
//=============================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "score.h"
#include "ranking.h"
#include "collect.h"

//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CRanking *CResult::m_pRanking = NULL;
CScore *CResult::m_pScore = NULL;
//**********************************
// マクロ定義
//**********************************
#define  TITLE_TEXTURE_PATH "./data/Textures/Ranking.png" // テクスチャ

//=============================
// コンストラクタ
//=============================
CResult::CResult()
{
	m_pPolygon = NULL;
}

//=============================
// デストラクタ
//=============================
CResult::~CResult()
{
}

//=============================
// クリエイト
//=============================
CResult * CResult::Create(void)
{
	// メモリの確保
	CResult *pResult = new CResult;

	if (pResult != NULL)
	{
		// 初期化
		pResult->Init();
	}
	return pResult;
}

//=============================
// 初期化処理
//=============================
HRESULT CResult::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_PATH, &m_pTexture);


	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pRanking = CRanking::Create();

	m_pScore = CScore::Create(D3DXVECTOR3(870.0f, 520.0f, 0.0f), D3DXVECTOR3(35.0f, 35.0f, 0.0f));

	m_pPolygon->SetTexture(m_pTexture);
	
	// 生成
	CCollect::Create();
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CResult::Uninit(void)
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
void CResult::Update(void)
{
	// ポリゴンの更新処理
	m_pPolygon->Update();

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
		CManager::GetMouse()->GetMouseTrigger(0) || 
		CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		CManager::GetFade()->SetFade(CManager::MODE_ROGO);
	}
}


//=============================
// 描画処理
//=============================
void CResult::Draw(void)
{
	// ポリゴンの描画処理
	m_pPolygon->Draw();
}
