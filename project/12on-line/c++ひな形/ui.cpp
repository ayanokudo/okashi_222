//===================================================
//
//    UIクラスの処理[ui.cpp]
//    Author:筒井　俊稀
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "ui.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"

//**********************************
// マクロ定義
//**********************************
#define UI_TIME_TEXTURE_PATH		"./data/Textures/TIME.png"			// タイムのパス
#define UI_TITLE_TEXTURE_PATH		"./data/Textures/title000.png"		// タイトルのパス
#define UI_ENTER_TEXTURE_PATH		"./data/Textures/title000.png"		// エンターのパス
#define UI_WARNING_TEXTURE_PATH		"./data/Textures/TIME.png"			// ワーニングのパス
#define UI_ATTACK_NAIL_TEXTURE_PATH	"./data/Textures/Attack.png"		// アタックのパス
#define UI_ATTACK_CRY_TEXTURE_PATH	"./data/Textures/Voice.png"			// 鳴き声のパス
#define UI_DASH_TEXTURE_PATH		"./data/Textures/Dash.png"			// ダッシュのパス
#define UI_CHOCO_TEXTURE_PATH		"./data/Textures/chocolate_HPicon.png"	// チョコのパス
#define UI_MILK_TEXTURE_PATH		"./data/Textures/Milk_HPicon.png"		// ミルクのパス

#define UI_SIZE 100
//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CUi::m_apTexture[UI_MAX] = {};

//==================================
// コンストラクタ
//==================================
CUi::CUi()
{
	m_pVtxBuff = NULL;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3();
	m_move = D3DXVECTOR3();
	m_type = UI_TIME;
}

//==================================
// デストラクタ
//==================================
CUi::~CUi()
{

}

//==================================
// クリエイト
//==================================
CUi * CUi::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type)
{
	// メモリの確保
	CUi * pUi = new CUi;

	if (pUi != NULL)
	{
		// 初期化処理
		pUi->Init(pos, size, col, type);
	}

	return pUi;
}

//==================================
// ロード
//==================================
HRESULT CUi::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, UI_TIME_TEXTURE_PATH, &m_apTexture[UI_TIME]);
	D3DXCreateTextureFromFile(pDevice, UI_TITLE_TEXTURE_PATH, &m_apTexture[UI_TITLE]);
	D3DXCreateTextureFromFile(pDevice, UI_ENTER_TEXTURE_PATH, &m_apTexture[UI_ENTER]);
	D3DXCreateTextureFromFile(pDevice, UI_WARNING_TEXTURE_PATH, &m_apTexture[UI_WARNING]);
	D3DXCreateTextureFromFile(pDevice, UI_ATTACK_CRY_TEXTURE_PATH, &m_apTexture[UI_ATTACK_NAIL]);
	D3DXCreateTextureFromFile(pDevice, UI_ATTACK_NAIL_TEXTURE_PATH, &m_apTexture[UI_ATTACK_CRY]);
	D3DXCreateTextureFromFile(pDevice, UI_DASH_TEXTURE_PATH, &m_apTexture[UI_DASH]);
	D3DXCreateTextureFromFile(pDevice, UI_CHOCO_TEXTURE_PATH, &m_apTexture[UI_CHOCO]);
	D3DXCreateTextureFromFile(pDevice, UI_MILK_TEXTURE_PATH, &m_apTexture[UI_MILK]);

	return S_OK;
}

//==================================
// アンロード
//==================================
void CUi::Unload(void)
{
	for (int nCount = UI_TIME; nCount < UI_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//==================================
// 初期化処理
//==================================
HRESULT CUi::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col, const UI type)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0);

	// テクスチャUV座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_col = col;
	m_type = type;
	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		pVtx[nCnt].col = m_col;
		pVtx[nCnt].rhw = 1.0f;
	}
	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CUi::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==================================
// 更新処理
//==================================
void CUi::Update(void)
{

}

//==================================
// 描画処理
//==================================
void CUi::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// アルファテストのしきい値の変更
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);


	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (m_apTexture[m_type] != NULL)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, m_apTexture[m_type]);
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetTexture(0, 0);

	// アルファテストのしきい値をもどす
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}

//==================================
// カラーのセット
//==================================
void CUi::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	m_col = col;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// アンロック
	m_pVtxBuff->Unlock();
}