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
	memset(m_anRankingDate, 0, sizeof(m_anRankingDate));
	m_nRank = 0;
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
	CScore *pScore = CGame::GetScore();
	m_nRank = pScore->SaveScore();

	// 最大桁数分ループ
	for (int  nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
	{
		m_anRankingDate[nCntNumber] = CScore::GetScore(nCntNumber);

		for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
		{
			int nValue = (int)powf(10.0f, (float)MAX_RANKING_DIGIT - (float)nCntDigit);
			int nScore2 = (int)powf(10.0f, (float)MAX_RANKING_DIGIT - (float)nCntDigit - 1.0f);
			int nAnswer = (m_anRankingDate[nCntNumber] % nValue) / nScore2;

			m_apNumber[nCntNumber][nCntDigit] = CNumber::Create(0,
				D3DXVECTOR3(460 + nCntDigit * 37 * 2, 355.0f + nCntNumber * 40 * 2, 0.0f),
				D3DXVECTOR3(40, 40, 0),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apNumber[nCntNumber][nCntDigit]->SetNumber(nAnswer);
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
	for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntNumber][nCntDigit]->Uninit();
			delete m_apNumber[nCntNumber][nCntDigit];
			m_apNumber[nCntNumber][nCntDigit] = NULL;
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
	for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntNumber][nCntDigit]->Update();
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
	for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntNumber][nCntDigit]->Draw();
		}
	}
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}
