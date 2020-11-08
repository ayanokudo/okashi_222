//===================================================
//
//    ポリゴンクラスの処理[polygon.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

#define FLASH_RATE 0.04f
//==================================
// コンストラクタ
//==================================
CPolygon::CPolygon()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_bFlash = true;
	m_FlashState = FLASH_STATE_IN;
}

//==================================
// デストラクタ
//==================================
CPolygon::~CPolygon()
{
}

//==================================
// クリエイト
//==================================
CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col)
{
	// メモリの確保
	CPolygon *pPolygon = new CPolygon;

	// 初期化処理
	pPolygon->Init(pos, size, col);

	return pPolygon;
}

//==================================
// 初期化処理
//==================================
HRESULT CPolygon::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// 頂点バッファのロック
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

	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		pVtx[nCnt].col = col;
		pVtx[nCnt].rhw = 1.0f;
	}
	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CPolygon::Uninit(void)
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
void CPolygon::Update(void)
{
}

//==================================
// 描画処理
//==================================
void CPolygon::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (m_pTexture != NULL)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetTexture(0, 0);
}

//==================================
// 座標設定
//==================================
void CPolygon::SetVertexPos(D3DXVECTOR3 pos[NUM_VERTEX])
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].pos = pos[0];
	pVtx[1].pos = pos[1];
	pVtx[2].pos = pos[2];
	pVtx[3].pos = pos[3];

	// アンロック
	m_pVtxBuff->Unlock();
}

//==================================
// カラー設定
//==================================
void CPolygon::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// アンロック
	m_pVtxBuff->Unlock();
}

//==================================
// フラッシング
//==================================
void CPolygon::Flashing(void)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	if (m_FlashState == FLASH_STATE_IN)
	{
		m_col.a -= FLASH_RATE;
		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_FlashState = FLASH_STATE_OUT;
		}
	}
	else if (m_FlashState == FLASH_STATE_OUT)
	{
		m_col.a += FLASH_RATE;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_FlashState = FLASH_STATE_IN;
		}
	}
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();

}
