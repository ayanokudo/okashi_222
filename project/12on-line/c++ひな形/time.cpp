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
#include <time.h>

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
#define MAX_TIME 300


//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
int CTime::m_nTime = 0;

//=============================
// �R���X�g���N�^
//=============================
CTime::CTime()
{
	// �i���o�[�̃N���A
	memset(m_apNumber, 0, sizeof(m_apNumber));

	//���ݎ��Ԃ��擾
	m_start = timeGetTime();
	m_end = NULL;
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
			D3DXVECTOR3(580 + nCntDigit * 35 * 2, 60.0f, 0.0f),
			D3DXVECTOR3(40, 40, 0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
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

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CTime::Update(void)
{
	int nTime = 0;
	//���ݎ��Ԃ��擾
	m_end = timeGetTime();
	nTime = (m_end - m_start) / 1000;
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Update();
		m_apNumber[nCntDigit]->SetNumber((m_nTime- nTime % (int)(powf(10.0f, (MAX_TIME_DIGIT - nCntDigit)))) / (float)(powf(10.0, (MAX_TIME_DIGIT - nCntDigit - 1))));
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
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);
}
