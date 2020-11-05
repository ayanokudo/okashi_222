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
#define NUMBER_POS_LEFT 100
#define NUMBER_POS_Y  SCREEN_HEIGHT / 2
#define NUMBER_SIZE D3DXVECTOR3(50.0f,50.0f,0.0f)
#define PATH "./data/Textures/" // �e�N�X�`��
//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
LPDIRECT3DTEXTURE9 CCollect::m_pTexture = NULL;
int CCollect::m_nNumObj = 10;       // ����Ώۂ̐�
int CCollect::m_nNumCollect = 0;   // ���������

//******************************
// �R���X�g���N�^
//******************************
CCollect::CCollect() :CScene(OBJTYPE_UI)
{
	// �ϐ��̃N���A
	m_fPerCollect = 0.0f;
	m_pPolygon = NULL;
	memset(m_pNumObj, 0, sizeof(m_pNumObj));
	memset(m_pNumCollect, 0, sizeof(m_pNumCollect));
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
	D3DXCreateTextureFromFile(pDevice, PATH, &m_pTexture);

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
	// �i���o�[�̍��W
	D3DXVECTOR3 numberPos = D3DXVECTOR3(NUMBER_POS_LEFT, NUMBER_POS_Y, 0.0f);

	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		// �i���o�[�̐���
		m_pNumCollect[nCnt] = CNumber::Create(0, numberPos, NUMBER_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// �ʒu�����炷�@
		numberPos.x += NUMBER_SIZE.x * 2;
	}

	// �|���S������
	m_pPolygon = CPolygon::Create(numberPos, NUMBER_SIZE);
	m_pPolygon->SetTexture(m_pTexture);
	// �ʒu�����炷�@
	numberPos.x += NUMBER_SIZE.x*2;

	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		// �i���o�[�̐���
		m_pNumObj[nCnt] = CNumber::Create(0, numberPos, NUMBER_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		// �ʒu�����炷�@
		numberPos.x += NUMBER_SIZE.x * 2;
	}

	return S_OK;
}

//******************************
// �I������
//******************************
void CCollect::Uninit(void)
{
	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		// �I������
		m_pNumCollect[nCnt]->Uninit();
	}

	// �I������
	m_pPolygon->Uninit();
	// �������̉��
	delete m_pPolygon;
	m_pPolygon = NULL;

	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		// �I������
		m_pNumObj[nCnt]->Uninit();
		// �������̉��
		delete m_pNumObj[nCnt];
		m_pNumObj[nCnt] = NULL;
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
	if (m_nNumCollect != 0 && m_nNumObj != 0)
	{
		m_fPerCollect = (m_nNumCollect / m_nNumObj) * 100;
	}

	// ������������i���o�[�ɂ���
	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		 m_pNumCollect[nCnt]->SetNumber((m_nNumCollect % (int)(powf(10.0f, (COLLET_NUM_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_NUM_DIGIT - nCnt - 1))));
	}
	// ����Ώې����i���o�[�ɂ���
	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		m_pNumObj[nCnt]->SetNumber((m_nNumObj % (int)(powf(10.0f, (COLLET_OBJ_NUM_DIGIT - nCnt)))) / (float)(powf(10.0, (COLLET_OBJ_NUM_DIGIT - nCnt - 1))));
	}
}

//******************************
// �`�揈��
//******************************
void CCollect::Draw(void)
{
	for (int nCnt = 0; nCnt < COLLET_NUM_DIGIT; nCnt++)
	{
		// �i���o�[�̕`��
		m_pNumCollect[nCnt]->Draw();
	}
	// �|���S���̕`��
	m_pPolygon->Draw();

	for (int nCnt = 0; nCnt < COLLET_OBJ_NUM_DIGIT; nCnt++)
	{
		// �i���o�[�̕`��
		m_pNumObj[nCnt] ->Draw();
	}
}

//******************************
// �ÓI�ϐ��̏�����
//******************************
void CCollect::InitVariable(void)
{
	m_nNumObj = 0;       // ����Ώۂ̐�
	m_nNumCollect = 0;   // ���������
}