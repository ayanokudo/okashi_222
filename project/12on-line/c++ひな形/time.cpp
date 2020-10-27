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
#include <time.h>

//**********************************
// 静的メンバ変数宣言
//**********************************
#define MAX_TIME 300


//**********************************
// 静的メンバ変数宣言
//**********************************
int CTime::m_nTime = 0;

//=============================
// コンストラクタ
//=============================
CTime::CTime()
{
	// ナンバーのクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));

	//現在時間を取得
	m_start = timeGetTime();
	m_end = NULL;
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
			D3DXVECTOR3(580 + nCntDigit * 35 * 2, 60.0f, 0.0f),
			D3DXVECTOR3(40, 40, 0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
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

	// 開放処理
	Release();
}

//=============================
// 更新処理
//=============================
void CTime::Update(void)
{
	int nTime = 0;
	//現在時間を取得
	m_end = timeGetTime();
	nTime = (m_end - m_start) / 1000;
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Update();
		m_apNumber[nCntDigit]->SetNumber((m_nTime- nTime % (int)(powf(10.0f, (MAX_TIME_DIGIT - nCntDigit)))) / (float)(powf(10.0, (MAX_TIME_DIGIT - nCntDigit - 1))));
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
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}
