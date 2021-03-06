//=======================================================================================
//
// ポーズ処理 [pause.cpp]
// Author : 筒井　俊稀
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "life.h"
#include "renderer.h"
#include "manager.h"

//=======================================================================================
// 静的メンバ変数宣言
//=======================================================================================
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//=======================================================================================
// マクロ定義
//=======================================================================================
#define HP_TEXTURE_PATH "./data/Textures/HP02.png"		// ワーニングのパス

//=======================================================================================
// コンストラクタ
//=======================================================================================
CLife::CLife()
{
	m_pVtxBuff = NULL;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CLife::~CLife()
{
}

//=======================================================================================
// 生成処理
//=======================================================================================
CLife * CLife::Create(const D3DXVECTOR3 pos)
{
	CLife *pLife = new CLife;

	if (pLife != NULL)
	{
		pLife->Init(pos);
	}
	return pLife;
}

//=======================================================================================
// テクスチャロード
//=======================================================================================
HRESULT CLife::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, HP_TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//=======================================================================================
// テクスチャ破棄
//=======================================================================================
void CLife::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CLife::Init(const D3DXVECTOR3 pos)
{
	CPolygon::Init(pos,LIFE_SIZE,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	SetTexture(m_pTexture);
	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CLife::Uninit(void)
{
	CPolygon::Uninit();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CLife::Update(void)
{
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CLife::Draw(void)
{	
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// アルファテストのしきい値の変更
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);

	// 描画
	CPolygon::Draw();

	// アルファテストのしきい値をもどす
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}