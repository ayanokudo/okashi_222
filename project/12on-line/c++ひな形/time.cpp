////////////////////////////////////////////////////
//
//    タイムクラスの処理[time.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "time.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "ui.h"
#include <time.h>

//**********************************
// 静的メンバ変数宣言
//**********************************
#define MAX_TIME 300


//**********************************
// 静的メンバ変数宣言
//**********************************
int CTime::m_nTime = 0;
int CTime::m_nPauseCurrentTime = 0;
//=============================
// コンストラクタ
//=============================
CTime::CTime()
{
	// ナンバーのクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pUi = NULL;
	//現在時間を取得
	m_start = timeGetTime();
	m_end = NULL;
	m_bTime = true;
	m_nAllTime = 0;
}

//=============================
// デストラクタ
//=============================
CTime::~CTime()
{

}

//=============================
// 生成処理
//=============================
CTime * CTime::Create(void)
{
	CTime *pTime = new CTime;

	if (pTime != NULL)
	{
		pTime->Init();
		pTime->SetObjType(OBJTYPE_UI);
	}
	return pTime;
}

//=============================
// 初期化処理
//=============================
HRESULT CTime::Init(void)
{
	// 最大桁数分ループ
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3(55 + nCntDigit * 25 * 2, 75.0f, 0.0f),
			D3DXVECTOR3(30, 25, 0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//タイムの文字表示
	m_pUi = CUi::Create(D3DXVECTOR3(100.0f, 30.0f, 0.0f),
		D3DXVECTOR3(50, 20, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_TIME);

	// TIMEの初期化
	m_nTime = MAX_TIME;
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CTime::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{
			m_apNumber[nCntDigit]->Uninit();
			delete m_apNumber[nCntDigit];
			m_apNumber[nCntDigit] = NULL;
		}
	}
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = NULL;
	}

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CTime::Update(void)
{
	//現在時間を取得
	m_end = timeGetTime();

	// ポーズ画面中のタイムのプラス
	if (!CManager::GetActivePause() && m_nPauseCurrentTime != 0)
	{
		// ポーズ中のタイムの加算
		m_start += (m_end - m_nPauseCurrentTime);
		// ポーズタイムの初期化
		m_nPauseCurrentTime = 0;
	}

	int nTime = 0;
	nTime = (m_end - m_start) / 1000;
	
	//代入
	m_nAllTime = m_nTime - nTime;
	//trueの時
	if (m_bTime)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntDigit]->Update();
			m_apNumber[nCntDigit]->SetNumber((m_nAllTime % (int)(powf(10.0f, (MAX_TIME_DIGIT - nCntDigit)))) / (float)(powf(10.0, (MAX_TIME_DIGIT - nCntDigit - 1))));
		}

		m_pUi->Update();
	}

	//０になったら
	if (m_nAllTime == 0)
	{
		m_bTime = false;
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
}

//=============================
// 描画処理
//=============================
void CTime::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
	m_pUi->Draw();

	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}
