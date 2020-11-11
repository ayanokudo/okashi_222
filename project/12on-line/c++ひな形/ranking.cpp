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
	// �ő包�������[�v
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
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
	//�����L���O����
	for (int nCntDigit = 0; nCntDigit < MAX_RANKING_DIGIT; nCntDigit++)
	{
		for (int nCntNumber = 0; nCntNumber < MAX_NUMBER_DIGIT; nCntNumber++)
		{
			m_apNumber[nCntDigit][nCntNumber]->Uninit();
			delete m_apNumber[nCntDigit][nCntNumber];
			m_apNumber[nCntDigit][nCntNumber] = NULL;
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
// �`�揈��
//=============================================================================
void CRanking::Draw(void)
{
	//�f�o�C�X�̎擾
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
