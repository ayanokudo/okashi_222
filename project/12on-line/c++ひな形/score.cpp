//===================================================
//
//    スコアクラスの処理[score.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
//インクルード
//**********************************
#include "score.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "ui.h"
//==============================
//静的メンバ変数宣言
//==============================
#define SCORE_DATA_PATH "./data/Texts/RankingData.txt"

//==============================
//静的メンバ変数宣言
//==============================
int CScore::m_nScore = 0;
int CScore::m_nRankingScore[MAX_RANKING] = {};

//==================================
// コンストラクタ
//==================================
CScore::CScore() :CScene(OBJTYPE_NUMBER)
{
	// ナンバーのクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pUi = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==================================
// デストラクタ
//==================================
CScore::~CScore()
{
}

//==================================
// クリエイト
//==================================
CScore * CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// メモリの確保
	CScore *pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->m_pos = pos;
		pScore->m_size = size;
		// 初期化処理
		pScore->Init();
		// オブジェクトタイプの設定
		pScore->SetObjType(OBJTYPE_UI);
	}

	return pScore;
}

//==================================
// 初期化処理
//==================================
HRESULT CScore::Init(void)
{
	
	// 最大桁数分ループ
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3(m_pos.x + nCntDigit * 27 * 2, m_pos.y, m_pos.y),
			D3DXVECTOR3(m_size),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		//タイムの文字表示
		m_pUi = CUi::Create(D3DXVECTOR3(1070.0f, 80.0f, 0.0f),
			D3DXVECTOR3(200, 90, 0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			CUi::UI_SCORE);
	}
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CScore::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
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
		if (!m_pUi->GetReleaseFlag())
		{
			m_pUi->Uninit();
			//delete m_pUi;
			m_pUi = NULL;
		}
	}

	// 開放処理
	Release();
}

//==================================
// 更新処理
//==================================
void CScore::Update(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Update();

		m_apNumber[nCntDigit]->SetNumber((m_nScore % (int)(powf(10.0f, (MAX_SCORE_DIGIT - nCntDigit)))) / (float)(powf(10.0, (MAX_SCORE_DIGIT - nCntDigit - 1))));
	}
}

//==================================
// 描画処理
//==================================
void CScore::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);	
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
	pDevice->SetRenderState(D3DRS_ALPHAREF,50);
}

//==================================
// ファイル読み込み
//==================================
void CScore::ReadFile(void)
{
	// ファイルオープン
	FILE*pFile = NULL;

	pFile = fopen(SCORE_DATA_PATH, "r");
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fscanf(pFile, "%d", &m_nRankingScore[nCount]);
		}
		fclose(pFile);
	}
}

//==================================
// ファイル書き込み
//==================================
void CScore::WriteFile(void)
{
	// ファイルオープン
	FILE*pFile = NULL;

	pFile = fopen(SCORE_DATA_PATH, "w");
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fprintf(pFile, "%d\n", m_nRankingScore[nCount]);
		}
		fclose(pFile);
	}
}

//==================================
// 描画処理
//==================================
int CScore::SaveScore(void)
{
	int nCount;

	ReadFile();

 	for (nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		//ランキングを更新する場所の判定
		if (m_nScore > m_nRankingScore[nCount])
		{
			//以降のランキングデータを後ろに移動
			for (int nCntMove = MAX_RANKING - 1; nCntMove > nCount; nCntMove--)
			{
				m_nRankingScore[nCntMove] = m_nRankingScore[nCntMove - 1];
			}
			m_nRankingScore[nCount] = m_nScore;

			break;
		}
	}
	WriteFile();

	return nCount;
}
