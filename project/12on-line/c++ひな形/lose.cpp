////////////////////////////////////////////////////
//
//    LOSE�N���X�̏���[lose.cpp]
//    Author:����@�r�H
//
////////////////////////////////////////////////////
//=============================
// �C���N���[�h
//=============================
#include "lose.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CLose::m_pTexture = NULL;
//**********************************
// �}�N����`
//**********************************
#define  WIN_TEXTURE_PATH "./data/Textures/Lose.png" // �e�N�X�`��

//=============================
// �R���X�g���N�^
//=============================
CLose::CLose()
{
	m_pPolygon = NULL;
}

//=============================
// �f�X�g���N�^
//=============================
CLose::~CLose()
{
}

//=============================
// �N���G�C�g
//=============================
CLose * CLose::Create(void)
{
	// �������̊m��
	CLose *pLose = new CLose;

	if (pLose != NULL)
	{
		// ������
		pLose->Init();
	}
	return pLose;
}

//=============================
// ����������
//=============================
HRESULT CLose::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, WIN_TEXTURE_PATH, &m_pTexture);


	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pPolygon->SetTexture(m_pTexture);

	return S_OK;
}

//=============================
// �I������
//=============================
void CLose::Uninit(void)
{
	// �e�N�X�`���̉��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	if (m_pPolygon != NULL)
	{
		// �|���S���̏I������
		m_pPolygon->Uninit();

		// �������̉��
		delete m_pPolygon;
		m_pPolygon = NULL;
	}

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CLose::Update(void)
{
	// �|���S���̍X�V����
	m_pPolygon->Update();

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetMouse()->GetMouseTrigger(0) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
}

//=============================
// �`�揈��
//=============================
void CLose::Draw(void)
{
	// �|���S���̕`�揈��
	m_pPolygon->Draw();
}
