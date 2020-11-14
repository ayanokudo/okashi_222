//===================================================
//
//    背景クラスの処理[bg.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "camera.h"
#include "game.h"

//*****************************
// マクロ定義
//*****************************

// テクスチャのパス
#define BG_TEXTURE_PATH1 "./data/Textures/shibahu.png"
#define BG_TEXTURE_PATH2 "./data/Textures/sky.png"

#define SKY_SIZE D3DXVECTOR3(1200.0f,464.0f,0.0f)*30
#define SKY_POS D3DXVECTOR3(-15000.0f, 5000.0f, -55000.0f)

//**********************************
//静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[BG_TEXTURE_NUM] = {};

//==================================
// コンストラクタ
//==================================
CBg::CBg()
{
	// Oクリア
	memset(m_afTexMoveU, 0, sizeof(m_afTexMoveU));
	memset(m_afTexMoveV, 0, sizeof(m_afTexMoveV));
	memset(m_apScene3d, 0, sizeof(m_apScene3d));
}

//==================================
// デストラクタ
//==================================
CBg::~CBg()
{
}

//==================================
// クリエイト
//==================================
CBg * CBg::Create(void)
{
	// メモリの確保
	CBg *pBg = new CBg;
	if (pBg != NULL)
	{
		// 初期化処理
		pBg->Init();
	}

	return pBg;
}

//==================================
// ロード
//==================================
HRESULT CBg::Load(void)
{

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_PATH1, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_PATH2, &m_apTexture[1]);
	return S_OK;
}

//==================================
// アンロード
//==================================
void CBg::Unload(void)
{
	// テクスチャ数分、テクスチャの開放処理
	for (int nCntTex = 0; nCntTex < BG_TEXTURE_NUM; nCntTex++)
	{
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//==================================
// 初期化処理
//==================================
HRESULT CBg::Init(void)
{


	if (m_apScene3d[0] == NULL)
	{
		// ポリゴン生成
		m_apScene3d[0] = CScene3d::Create(D3DXVECTOR3(-5900, -10, -8000), D3DXVECTOR3(800000, -10, 800000));
		// オブジェクトタイプの設定
		m_apScene3d[0]->SetObjType(OBJTYPE_BG);
		// テクスチャ割り当て
		m_apScene3d[0]->BindTexture(m_apTexture[0]);

		D3DXVECTOR2 UV[NUM_VERTEX];
		UV[0] = D3DXVECTOR2(0.0f, 0.0f);
		UV[1] = D3DXVECTOR2(8000.0f, 0.0f);
		UV[2] = D3DXVECTOR2(0.0f, 8000.0f);
		UV[3] = D3DXVECTOR2(8000.0f, 8000.0f);

		m_apScene3d[0]->SetTextureUV(UV);
	}
	else
	{
		return E_FAIL;
	}

	if (m_apScene3d[1] == NULL)
	{
		// ポリゴン生成
		m_apScene3d[1] = CScene3d::Create(SKY_POS, SKY_SIZE);
		// オブジェクトタイプの設定
		m_apScene3d[1]->SetObjType(OBJTYPE_BG);
		// テクスチャ割り当て
		m_apScene3d[1]->BindTexture(m_apTexture[1]);

		D3DXVECTOR2 UV[NUM_VERTEX];
		UV[0] = D3DXVECTOR2(0.0f, 0.0f);
		UV[1] = D3DXVECTOR2(1.0f, 0.0f);
		UV[2] = D3DXVECTOR2(0.0f, 1.0f);
		UV[3] = D3DXVECTOR2(1.0f, 1.0f);

		m_apScene3d[1]->SetTextureUV(UV);
	}
	else
	{
		return E_FAIL;
	}



	return S_OK;
}

//==================================
// 終了処理
//==================================
void CBg::Uninit(void)
{
	// 背景のパーツ数分開放処理
	for (int nCntBg = 0; nCntBg < BG_PARTS_NUM; nCntBg++)
	{
		if (m_apScene3d[nCntBg] != NULL)
		{
			m_apScene3d[nCntBg]->Uninit();
			m_apScene3d[nCntBg] = NULL;
		}
	}

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CBg::Update(void)
{
}

//==================================
// 描画処理
//==================================
void CBg::Draw(void)
{

}
