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

//==============================
//静的メンバ変数宣言
//==============================
int CScore::m_nScore = 0;

//==================================
// コンストラクタ
//==================================
CScore::CScore()
{
	// ナンバーのクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
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
CScore * CScore::Create(void)
{
	// メモリの確保
	CScore *pScore = new CScore;

	if (pScore != NULL)
	{
		// 初期化処理
		pScore->Init();
	}

	// オブジェクトタイプの設定
	pScore->SetObjType(OBJTYPE_UI);

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
			D3DXVECTOR3(950 + nCntDigit * 30 * 2, 40.0f, 0.0f),
			D3DXVECTOR3(30, 30, 0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	// スコアの初期化
	m_nScore = 0;

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
