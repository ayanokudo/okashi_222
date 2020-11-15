//===================================================
//
//    �X�R�A�N���X�̏���[score.cpp]
//    Author:���V ����
//
//====================================================

//**********************************
//�C���N���[�h
//**********************************
#include "score.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "ui.h"
//==============================
//�ÓI�����o�ϐ��錾
//==============================
#define SCORE_DATA_PATH "./data/Texts/RankingData.txt"

//==============================
//�ÓI�����o�ϐ��錾
//==============================
int CScore::m_nScore = 0;
int CScore::m_nRankingScore[MAX_RANKING] = {};

//==================================
// �R���X�g���N�^
//==================================
CScore::CScore() :CScene(OBJTYPE_NUMBER)
{
	// �i���o�[�̃N���A
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pUi = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==================================
// �f�X�g���N�^
//==================================
CScore::~CScore()
{
}

//==================================
// �N���G�C�g
//==================================
CScore * CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �������̊m��
	CScore *pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->m_pos = pos;
		pScore->m_size = size;
		// ����������
		pScore->Init();
		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		pScore->SetObjType(OBJTYPE_UI);
	}

	return pScore;
}

//==================================
// ����������
//==================================
HRESULT CScore::Init(void)
{
	
	// �ő包�������[�v
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3(m_pos.x + nCntDigit * 27 * 2, m_pos.y, m_pos.y),
			D3DXVECTOR3(m_size),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		//�^�C���̕����\��
		m_pUi = CUi::Create(D3DXVECTOR3(1070.0f, 80.0f, 0.0f),
			D3DXVECTOR3(200, 90, 0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			CUi::UI_SCORE);
	}
	return S_OK;
}

//==================================
// �I������
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

	// �J������
	Release();
}

//==================================
// �X�V����
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
// �`�揈��
//==================================
void CScore::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);	
	for (int nCntDigit = 0; nCntDigit < MAX_SCORE_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
	pDevice->SetRenderState(D3DRS_ALPHAREF,50);
}

//==================================
// �t�@�C���ǂݍ���
//==================================
void CScore::ReadFile(void)
{
	// �t�@�C���I�[�v��
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
// �t�@�C����������
//==================================
void CScore::WriteFile(void)
{
	// �t�@�C���I�[�v��
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
// �`�揈��
//==================================
int CScore::SaveScore(void)
{
	int nCount;

	ReadFile();

 	for (nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		//�����L���O���X�V����ꏊ�̔���
		if (m_nScore > m_nRankingScore[nCount])
		{
			//�ȍ~�̃����L���O�f�[�^�����Ɉړ�
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
