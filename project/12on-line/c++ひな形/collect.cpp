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
#define NUMBER_POS_LEFT 100
#define NUMBER_POS_Y  SCREEN_HEIGHT / 2
#define NUMBER_SIZE D3DXVECTOR3(50.0f,50.0f,0.0f)
#define PATH "./data/Textures/" // テクスチャ
//*****************************
// 静的メンバ変数宣言
//*****************************
LPDIRECT3DTEXTURE9 CCollect::m_pTexture = NULL;
int CCollect::m_nNumObj = 10;       // 回収対象の数
int CCollect::m_nNumCollect = 0;   // 回収した数

//******************************
// コンストラクタ
//******************************
CCollect::CCollect() :CScene(OBJTYPE_UI)
{
	// 変数のクリア
	m_fPerCollect = 0.0f;
	m_pPolygon = NULL;
	memset(m_pNumObj, 0, sizeof(m_pNumObj));
	memset(m_pNumCollect, 0, sizeof(m_pNumCollect));
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
	D3DXCreateTextureFromFile(pDevice, PATH, &m_pTexture);

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
	// ナンバーの座標
	D3DXVECTOR3 numberPos = D3DXVECTOR3(NUMBER_POS_LEFT, NUMBER_POS_Y, 0.0f);

	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		// ナンバーの生成
		m_pNumCollect[nCnt] = CNumber::Create(0, numberPos, NUMBER_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// 位置をずらす　
		numberPos.x += NUMBER_SIZE.x * 2;
	}

	// ポリゴン生成
	m_pPolygon = CPolygon::Create(numberPos, NUMBER_SIZE);
	m_pPolygon->SetTexture(m_pTexture);
	// 位置をずらす　
	numberPos.x += NUMBER_SIZE.x*2;

	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		// ナンバーの生成
		m_pNumObj[nCnt] = CNumber::Create(0, numberPos, NUMBER_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// 位置をずらす　
		numberPos.x += NUMBER_SIZE.x * 2;
	}

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CCollect::Uninit(void)
{
	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		// 終了処理
		m_pNumCollect[nCnt]->Uninit();
	}

	// 終了処理
	m_pPolygon->Uninit();
	// メモリの解放
	delete m_pPolygon;
	m_pPolygon = NULL;

	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		// 終了処理
		m_pNumObj[nCnt]->Uninit();
		// メモリの解放
		delete m_pNumObj[nCnt];
		m_pNumObj[nCnt] = NULL;
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
	if (m_nNumCollect != 0 && m_nNumObj != 0)
	{
		m_fPerCollect = (m_nNumCollect / m_nNumObj) * 100;
	}

	// 回収した数をナンバーにする
	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		 m_pNumCollect[nCnt]->SetNumber((m_nNumCollect % (int)(powf(10.0f, (COLLET_NUM_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_NUM_DIGIT - nCnt - 1))));
	}
	// 回収対象数をナンバーにする
	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		m_pNumObj[nCnt]->SetNumber((m_nNumObj % (int)(powf(10.0f, (COLLET_OBJ_NUM_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_OBJ_NUM_DIGIT - nCnt - 1))));
	}
}

//******************************
// 描画処理
//******************************
void CCollect::Draw(void)
{
	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		// ナンバーの描画
		m_pNumCollect[nCnt]->Draw();
	}
	// ポリゴンの描画
	m_pPolygon->Draw();

	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		// ナンバーの描画
		m_pNumObj[nCnt] ->Draw();
	}
}

//******************************
// 静的変数の初期化
//******************************
void CCollect::InitVariable(void)
{
	m_nNumObj = 0;       // 回収対象の数
	m_nNumCollect = 0;   // 回収した数
}