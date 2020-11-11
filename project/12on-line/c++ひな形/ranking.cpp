//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : トシキ
//
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "score.h"
#include "game.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
	//ナンバーのクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CRanking * CRanking::Create(void)
{
	CRanking *pRanking = new CRanking;

	if (pRanking != NULL)
	{
		pRanking->Init();
	}

	// オブジェクトタイプの設定
	pRanking->SetObjType(OBJTYPE_UI);

	return pRanking;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	// 最大桁数分ループ
	for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
	{
		for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
		{
			m_apNumber[nCntDigit][nCntNumber] = CNumber::Create(0,
				D3DXVECTOR3((640 + nCntDigit * 30 * 2), (350.0f + nCntNumber * 30 * 2), 0.0f),
				D3DXVECTOR3(40, 40, 0),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	//ランキング数回す
	for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
	{
		for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
		{
			m_apNumber[nCntDigit][nCntNumber]->Uninit();
			delete m_apNumber[nCntDigit][nCntNumber];
			m_apNumber[nCntDigit][nCntNumber] = NULL;
		}
	}

	// 開放処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
	{
		for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
		{
			m_apNumber[nCntDigit][nCntNumber]->Update();

			//m_apNumber[nCntDigit][nCntNumber]->SetNumber
			//((m_nScore % (int)(powf(10.0f, (MAX_SCORE_DIGIT - nCntDigit)))) / 
			//	(float)(powf(10.0, (MAX_SCORE_DIGIT - nCntDigit - 1))));
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);
	for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
	{
		for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
		{
			m_apNumber[nCntDigit][nCntNumber]->Draw();
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}
