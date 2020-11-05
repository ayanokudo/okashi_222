////////////////////////////////////////////////////
//
//    Collect�N���X�̏���[Collect.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "collect.h"
#include "number.h"
#include "polygon.h"
#include "manager.h"
#include "renderer.h"

//*****************************
// �}�N����`
//*****************************
#define COLLECT_MAX_NUM 20                 // �ő�����
#define COLLECT_POS_LEFT 100               // ������̍��W�̍��[
#define COLLECT_POS_Y  SCREEN_HEIGHT / 2   // ������̍��W�̍���

#define PERCENT_POS_LEFT 100                   // �p�[�Z���g�̍��W�̍��[
#define PERCENT_POS_Y  SCREEN_HEIGHT / 2-120   // �p�[�Z���g�̍��W�̍���

#define COLLECT_NUM_SIZE D3DXVECTOR3(50.0f,50.0f,0.0f) // ������i���o�[�̃T�C�Y
#define PERCENT_NUM_SIZE D3DXVECTOR3(70.0f,70.0f,0.0f) // �p�[�Z���g�i���o�[�̃T�C�Y

// �e�N�X�`���̃p�X
#define SLASH_TEX_PATH   "./data/Textures/slash.png" 
#define PERCENT_TEX_PATH "./data/Textures/percent.png"
//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPDIRECT3DTEXTURE9 CCollect::m_apTexture[CCollect::MAX_PARTS] = {};
int CCollect::m_nNumCollect = 0;   // ���������

//******************************
// �R���X�g���N�^
//******************************
CCollect::CCollect() :CScene(OBJTYPE_UI)
{
	// �ϐ��̃N���A
	m_nPerCollect = 0.0f;
	memset(m_pPolygon, 0, sizeof(m_pPolygon));
	memset(m_pNumObj, 0, sizeof(m_pNumObj));
	memset(m_pNumCollect, 0, sizeof(m_pNumCollect));
	memset(m_pNumPer, 0, sizeof(m_pNumPer));
}

//******************************
// �f�X�g���N�^
//******************************
CCollect::~CCollect()
{
	
}

//******************************
// �N���G�C�g
//******************************
CCollect * CCollect::Create(void)
{
	// �������̊m��
	CCollect *pCollect;
	pCollect = new CCollect;
	// ������
	pCollect->Init();

	return pCollect;
}

//******************************
// ���[�h
//******************************
HRESULT CCollect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, SLASH_TEX_PATH, &m_apTexture[SLASH]);
	D3DXCreateTextureFromFile(pDevice, PERCENT_TEX_PATH, &m_apTexture[PERCENT]);

	return S_OK;
}

//******************************
// �A�����[�h
//******************************
void CCollect::Unload(void)
{
}

//******************************
// ����������
//******************************
HRESULT CCollect::Init(void)
{
	// �����UI

	// �����ʒu
	D3DXVECTOR3 numberPos = D3DXVECTOR3(COLLECT_POS_LEFT, COLLECT_POS_Y, 0.0f);

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// �i���o�[�̐���
		m_pNumCollect[nCnt] = CNumber::Create(0, numberPos, COLLECT_NUM_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// �ʒu�����炷�@
		numberPos.x += COLLECT_NUM_SIZE.x * 2;
	}

	// �|���S������
	m_pPolygon[SLASH] = CPolygon::Create(numberPos, COLLECT_NUM_SIZE);
	m_pPolygon[SLASH]->SetTexture(m_apTexture[SLASH]);

	// �ʒu�����炷�@
	numberPos.x += COLLECT_NUM_SIZE.x*2;

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// �i���o�[�̐���
		m_pNumObj[nCnt] = CNumber::Create(0, numberPos, COLLECT_NUM_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// �ʒu�����炷�@
		numberPos.x += COLLECT_NUM_SIZE.x * 2;
	}

	// �p�[�Z���gUI
	
	// �����ʒu
	numberPos = D3DXVECTOR3(PERCENT_POS_LEFT, PERCENT_POS_Y, 0.0f);

	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		// �i���o�[�̐���
		m_pNumPer[nCnt] = CNumber::Create(0, numberPos, PERCENT_NUM_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// �ʒu�����炷�@
		numberPos.x += PERCENT_NUM_SIZE.x * 2;
	}

	// �|���S������
	m_pPolygon[PERCENT] = CPolygon::Create(numberPos, PERCENT_NUM_SIZE+D3DXVECTOR3(5.0f, 5.0f, 0.0f));
	m_pPolygon[PERCENT]->SetTexture(m_apTexture[PERCENT]);

	return S_OK;
}

//******************************
// �I������
//******************************
void CCollect::Uninit(void)
{
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		if (m_pNumCollect[nCnt] != NULL)
		{
			// �I������
			m_pNumCollect[nCnt]->Uninit();
			delete m_pNumCollect[nCnt];
			m_pNumCollect[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		if (m_pNumObj[nCnt] != NULL)
		{
			// �I������
			m_pNumObj[nCnt]->Uninit();
			// �������̉��
			delete m_pNumObj[nCnt];
			m_pNumObj[nCnt] = NULL;
		}
	}
	
	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		if (m_pNumPer[nCnt] != NULL)
		{
			// �I������
			m_pNumPer[nCnt]->Uninit();
			// �������̉��
			delete m_pNumPer[nCnt];
			m_pNumPer[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			// �I������
			m_pPolygon[nCnt]->Uninit();
			// �������̉��
			delete m_pPolygon[nCnt];
			m_pPolygon[nCnt] = NULL;
		}
	}

	// �ϐ��̏�����
	InitVariable();

	// ���
	Release();
}

//******************************
// �X�V����
//******************************
void CCollect::Update(void)
{
	// ������̌v�Z
	if (m_nNumCollect != 0)
	{
		m_nPerCollect = ((float)m_nNumCollect / (float)COLLECT_MAX_NUM) * 100;
	}
	else
	{
		m_nPerCollect = 0.0f;
	}

	// ������������i���o�[�ɂ���
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		 m_pNumCollect[nCnt]->SetNumber((m_nNumCollect % (int)(powf(10.0f, (COLLET_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_DIGIT - nCnt - 1))));
	}
	// ����Ώې����i���o�[�ɂ���
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		m_pNumObj[nCnt]->SetNumber((COLLECT_MAX_NUM % (int)(powf(10.0f, (COLLET_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_DIGIT - nCnt - 1))));
	}

	// ��������������i���o�[�ɂ���
	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		m_pNumPer[nCnt]->SetNumber((m_nPerCollect % (int)(powf(10.0f, (COLLET_PAR_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_PAR_DIGIT - nCnt - 1))));
	}
}

//******************************
// �`�揈��
//******************************
void CCollect::Draw(void)
{
	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// �i���o�[�̕`��
		m_pNumCollect[nCnt]->Draw();
	}

	for (int nCnt = 0; nCnt < COLLET_DIGIT; nCnt++)
	{
		// �i���o�[�̕`��
		m_pNumObj[nCnt] ->Draw();
	}

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// �|���S���̕`��
		m_pPolygon[nCnt]->Draw();
	}
	for (int nCnt = 0; nCnt < COLLET_PAR_DIGIT; nCnt++)
	{
		// �i���o�[�̕`��
		m_pNumPer[nCnt]->Draw();
	}

}

//******************************
// �ÓI�ϐ��̏�����
//******************************
void CCollect::InitVariable(void)
{
	m_nNumCollect = 0;   // ���������
}