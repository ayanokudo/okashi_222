////////////////////////////////////////////////////
//
//    �^�C���N���X�̏���[time.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "time.h"
#include "number.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "ui.h"
#include <time.h>

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
#define MAX_TIME 300


//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
int CTime::m_nTime = 0;
int CTime::m_nPauseCurrentTime = 0;
//=============================
// �R���X�g���N�^
//=============================
CTime::CTime()
{
	// �i���o�[�̃N���A
	memset(m_apNumber, 0, sizeof(m_apNumber));
	m_pUi = NULL;
	//���ݎ��Ԃ��擾
	m_start = timeGetTime();
	m_end = NULL;
	m_bTime = true;
	m_nAllTime = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CTime::~CTime()
{

}

//=============================
// ��������
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
// ����������
//=============================
HRESULT CTime::Init(void)
{
	// �ő包�������[�v
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(0,
			D3DXVECTOR3(55 + nCntDigit * 25 * 2, 75.0f, 0.0f),
			D3DXVECTOR3(30, 25, 0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//�^�C���̕����\��
	m_pUi = CUi::Create(D3DXVECTOR3(100.0f, 30.0f, 0.0f),
		D3DXVECTOR3(50, 20, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_TIME);

	// TIME�̏�����
	m_nTime = MAX_TIME;
	return S_OK;
}

//=============================
// �I������
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

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CTime::Update(void)
{
	//���ݎ��Ԃ��擾
	m_end = timeGetTime();

	// �|�[�Y��ʒ��̃^�C���̃v���X
	if (!CManager::GetActivePause() && m_nPauseCurrentTime != 0)
	{
		// �|�[�Y���̃^�C���̉��Z
		m_start += (m_end - m_nPauseCurrentTime);
		// �|�[�Y�^�C���̏�����
		m_nPauseCurrentTime = 0;
	}

	int nTime = 0;
	nTime = (m_end - m_start) / 1000;
	
	//���
	m_nAllTime = m_nTime - nTime;
	//true�̎�
	if (m_bTime)
	{
		for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
		{
			m_apNumber[nCntDigit]->Update();
			m_apNumber[nCntDigit]->SetNumber((m_nAllTime % (int)(powf(10.0f, (MAX_TIME_DIGIT - nCntDigit)))) / (float)(powf(10.0, (MAX_TIME_DIGIT - nCntDigit - 1))));
		}

		m_pUi->Update();
	}

	//�O�ɂȂ�����
	if (m_nAllTime == 0)
	{
		m_bTime = false;
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
}

//=============================
// �`�揈��
//=============================
void CTime::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
	m_pUi->Draw();

	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}
