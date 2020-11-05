////////////////////////////////////////////////////
//
//    Collectクラスの処理[Collect.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "collect.h"
#include "number.h"
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//*****************************
// マクロ定義
//*****************************
#define COLLECT_MAX_NUM 20                 // 最大回収数
#define COLLECT_POS_LEFT 100               // 回収数の座標の左端
#define COLLECT_POS_Y  SCREEN_HEIGHT / 2   // 回収数の座標の高さ

#define PERCENT_POS_LEFT 100                   // パーセントの座標の左端
#define PERCENT_POS_Y  SCREEN_HEIGHT / 2-120   // パーセントの座標の高さ

#define COLLECT_NUM_SIZE D3DXVECTOR3(50.0f,50.0f,0.0f) // 回収数ナンバーのサイズ
#define PERCENT_NUM_SIZE D3DXVECTOR3(70.0f,70.0f,0.0f) // パーセントナンバーのサイズ

// テクスチャのパス
#define SLASH_TEX_PATH   "./data/Textures/slash.png" 
#define PERCENT_TEX_PATH "./data/Textures/percent.png"
//*****************************
// 静的メンバ変数宣言
//*****************************
LPDIRECT3DTEXTURE9 CCollect::m_apTexture[CCollect::MAX_PARTS] = {};
int CCollect::m_nNumCollect = 0;   // 回収した数

//******************************
// コンストラクタ
//******************************
CCollect::CCollect() :CScene(OBJTYPE_UI)
{
	// 変数のクリア
	m_nPerCollect = 0.0f;
	memset(m_pPolygon, 0, sizeof(m_pPolygon));
	memset(m_pNumObj, 0, sizeof(m_pNumObj));
	memset(m_pNumCollect, 0, sizeof(m_pNumCollect));
	memset(m_pNumPer, 0, sizeof(m_pNumPer));
}

//******************************
// デストラクタ
//******************************
CCollect::~CCollect()
{
	
}

//******************************
// クリエイト
//******************************
CCollect * CCollect::Create(void)
{
	// メモリの確保
	CCollect *pCollect;
	pCollect = new CCollect;
	// 初期化
	pCollect->Init();

	return pCollect;
}

//******************************
// ロード
//******************************
HRESULT CCollect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, SLASH_TEX_PATH, &m_apTexture[SLASH]);
	D3DXCreateTextureFromFile(pDevice, PERCENT_TEX_PATH, &m_apTexture[PERCENT]);

	return S_OK;
}

//******************************
// アンロード
//******************************
void CCollect::Unload(void)
{
}

//******************************
// 初期化処理
//******************************
HRESULT CCollect::Init(void)
{
	// 回収数UI

	// 初期位置
	D3DXVECTOR3 numberPos = D3DXVECTOR3(COLLECT_POS_LEFT, COLLECT_POS_Y, 0.0f);

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// ナンバーの生成
		m_pNumCollect[nCnt] = CNumber::Create(0, numberPos, COLLECT_NUM_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// 位置をずらす　
		numberPos.x += COLLECT_NUM_SIZE.x * 2;
	}

	// ポリゴン生成
	m_pPolygon[SLASH] = CPolygon::Create(numberPos, COLLECT_NUM_SIZE);
	m_pPolygon[SLASH]->SetTexture(m_apTexture[SLASH]);

	// 位置をずらす　
	numberPos.x += COLLECT_NUM_SIZE.x*2;

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// ナンバーの生成
		m_pNumObj[nCnt] = CNumber::Create(0, numberPos, COLLECT_NUM_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// 位置をずらす　
		numberPos.x += COLLECT_NUM_SIZE.x * 2;
	}

	// パーセントUI
	
	// 初期位置
	numberPos = D3DXVECTOR3(PERCENT_POS_LEFT, PERCENT_POS_Y, 0.0f);

	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		// ナンバーの生成
		m_pNumPer[nCnt] = CNumber::Create(0, numberPos, PERCENT_NUM_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// 位置をずらす　
		numberPos.x += PERCENT_NUM_SIZE.x * 2;
	}

	// ポリゴン生成
	m_pPolygon[PERCENT] = CPolygon::Create(numberPos, PERCENT_NUM_SIZE+D3DXVECTOR3(5.0f, 5.0f, 0.0f));
	m_pPolygon[PERCENT]->SetTexture(m_apTexture[PERCENT]);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CCollect::Uninit(void)
{
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		if (m_pNumCollect[nCnt] != NULL)
		{
			// 終了処理
			m_pNumCollect[nCnt]->Uninit();
			delete m_pNumCollect[nCnt];
			m_pNumCollect[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		if (m_pNumObj[nCnt] != NULL)
		{
			// 終了処理
			m_pNumObj[nCnt]->Uninit();
			// メモリの解放
			delete m_pNumObj[nCnt];
			m_pNumObj[nCnt] = NULL;
		}
	}
	
	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		if (m_pNumPer[nCnt] != NULL)
		{
			// 終了処理
			m_pNumPer[nCnt]->Uninit();
			// メモリの解放
			delete m_pNumPer[nCnt];
			m_pNumPer[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			// 終了処理
			m_pPolygon[nCnt]->Uninit();
			// メモリの解放
			delete m_pPolygon[nCnt];
			m_pPolygon[nCnt] = NULL;
		}
	}

	// 変数の初期化
	InitVariable();

	// 解放
	Release();
}

//******************************
// 更新処理
//******************************
void CCollect::Update(void)
{
	// 回収率の計算
	if (m_nNumCollect != 0)
	{
		m_nPerCollect = ((float)m_nNumCollect / (float)COLLECT_MAX_NUM) * 100;
	}
	else
	{
		m_nPerCollect = 0.0f;
	}

	// 回収した数をナンバーにする
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		 m_pNumCollect[nCnt]->SetNumber((m_nNumCollect % (int)(powf(10.0f, (COLLET_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_DIGIT - nCnt - 1))));
	}
	// 回収対象数をナンバーにする
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		m_pNumObj[nCnt]->SetNumber((COLLECT_MAX_NUM % (int)(powf(10.0f, (COLLET_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_DIGIT - nCnt - 1))));
	}

	// 回収した割合をナンバーにする
	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		m_pNumPer[nCnt]->SetNumber((m_nPerCollect % (int)(powf(10.0f, (COLLET_PAR_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_PAR_DIGIT - nCnt - 1))));
	}
}

//******************************
// 描画処理
//******************************
void CCollect::Draw(void)
{
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// ナンバーの描画
		m_pNumCollect[nCnt]->Draw();
	}

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// ナンバーの描画
		m_pNumObj[nCnt] ->Draw();
	}

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// ポリゴンの描画
		m_pPolygon[nCnt]->Draw();
	}
	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		// ナンバーの描画
		m_pNumPer[nCnt]->Draw();
	}

}

//******************************
// 静的変数の初期化
//******************************
void CCollect::InitVariable(void)
{
	m_nNumCollect = 0;   // 回収した数
}