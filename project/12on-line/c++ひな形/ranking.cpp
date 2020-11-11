//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �g�V�L
//
//=============================================================================
#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "score.h"
#include "game.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking()
{
	//�i���o�[�̃N���A
	memset(m_apNumber, 0, sizeof(m_apNumber));
	memset(m_anRankingDate, 0, sizeof(m_anRankingDate));
	m_nRank = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// ��������
//=============================================================================
CRanking * CRanking::Create(void)
{
	CRanking *pRanking = new CRanking;

	if (pRanking != NULL)
	{
		pRanking->Init();
	}

	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	pRanking->SetObjType(OBJTYPE_UI);

	return pRanking;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	CScore *pScore = CGame::GetScore();
	m_nRank = pScore->SaveScore();

	// �ő包�������[�v
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
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	//�����L���O����
	for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntNumber][nCntDigit]->Uninit();
			delete m_apNumber[nCntNumber][nCntDigit];
			m_apNumber[nCntNumber][nCntDigit] = NULL;
		}
	}

	// �J������
	Release();
}

//=============================================================================
// �X�V����
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
// �`�揈��
//=============================================================================
void CRanking::Draw(void)
{
	//�f�o�C�X�̎擾
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
