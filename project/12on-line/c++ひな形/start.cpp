//===================================================
//
//    startの処理[Start.cpp]
//    Author:増澤 未来
//
//====================================================
//**********************************
//インクルード
//**********************************
#include "start.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"

//*****************************
// マクロ定義
//*****************************
#define TEXTURE_PATH "./data/Textures/Start_Text.png"    //フローリングのテクスチャのパス
#define LOST_COUNT 50
#define SIZE D3DXVECTOR3(1313.0f, 394.0f, 0.0f)/4

//==================================
// コンストラクタ
//==================================
LPDIRECT3DTEXTURE9 CStart::m_pTexture = {};

//==================================
// コンストラクタ
//==================================
CStart::CStart() :CScene2d(OBJTYPE_UI)
{
	m_nCntLost = 0;
}

//==================================
// デストラクタ
//==================================
CStart::~CStart()
{
}

//==================================
// 生成処理
//==================================
CStart * CStart::Create(void)
{
	//CStartのポインタ作成
	CStart *pStart;
	//インスタンスを生成
	pStart = new CStart;
	//NULLチェック
	if (pStart != NULL)
	{
		//それぞれの初期化処理
		pStart->Init();
	}
	//ポインタを返す
	return pStart;
}

//==================================
// テクスチャロード処理
//==================================
HRESULT CStart::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//==================================
// テクスチャ破棄
//==================================
void CStart::Unload(void)
{

	// テクスチャの解放処理
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================
// 初期化処理
//==================================
HRESULT CStart::Init(void)
{
	CScene2d::Init();
	m_nCntLost = 0;
	SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	SetSize(SIZE);
	BindTexture(m_pTexture);

	
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CStart::Uninit(void)
{
	CScene2d::Uninit();
}

//==================================
// 更新処理
//==================================
void CStart::Update(void)
{
	// カウントを進める
	m_nCntLost++;
	if (m_nCntLost > LOST_COUNT)
	{// 一定カウントで消す
		Uninit();
	}
	else
	{
		if (m_nCntLost == 10)
		{// SE
			CManager::GetSound()->Play(CSound::SOUND_SE_START);
		}
		if (m_nCntLost >= 20)
		{
			D3DXCOLOR minasCol =D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.01f);
			SetColor(GetColor() - minasCol);
		}
	}
}

//==================================
// 描画処理
//==================================
void CStart::Draw(void)
{
	CScene2d::Draw();
}
