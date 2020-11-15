////////////////////////////////////////////////////
//
//    �^�C�g���N���X�̏���[title.cpp]
//    Author:���� �r�H
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "rogo.h"
#include "manager.h"
#include "renderer.h"
#include "polygon.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "fade.h"
#include "sound.h"
#include "ui.h"
#include "player.h"
#include "scene2d.h"
#include "sound.h"

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CRogo::m_apTexture[MENU_MAX] = {};
LPDIRECT3DTEXTURE9 CRogo::m_apCatTex[CAT_MAX];        // �e�N�X�`���ւ̃|�C���^

//**********************************
// �}�N����`
//**********************************
#define  M_TEXTURE_PATH "./data/Textures/M.png"			// �e�N�X�`��

#define CAT_SIZE D3DXVECTOR3(750.0f,311.0f,0.0f)/3
#define CAT_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)

#define ANIM_SPEED 14          // �A�j���[�V�������x
#define MAX_ANIMATION_X 5      // �A�j���[�V������ ��
#define MAX_ANIMATION_Y 3      // �A�j���[�V������ �c


#define BACK_SIZE D3DXVECTOR3(200.0f,180.0f,0.0f)					// �w�ʃT�C�Y
#define BACK_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)	// �w�ʍ��W

#define STRING_SIZE D3DXVECTOR3(170.0f,100.0f,0.0f)					// ������
#define EXIT_POS  D3DXVECTOR3(180.0f,580.0f,0.0f)					// ������
#define START_POS D3DXVECTOR3(645.0f, 580.0f,0.0f)                  // ���X�^�[�g
#define TUTORIAL_POS   	D3DXVECTOR3(1100.0f,580.0f,0.0f)			// �I��

#define MENU_ENTER_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)			// �I��ł郁�j���[�̐F
#define MENU_NOT_ENTER_COL D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f)		// �I��łȂ����j���[�̐F

//=============================
// �R���X�g���N�^
//=============================
CRogo::CRogo()
{
	memset(&m_apPolygon, 0, sizeof(m_apPolygon));
	m_nMenu = START;
	m_bStick = false;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
	m_nCount = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CRogo::~CRogo()
{
}

//=============================
// �N���G�C�g
//=============================
CRogo * CRogo::Create(void)
{
	// �������̊m��
	CRogo *pTitle = new CRogo;

	if (pTitle != NULL)
	{
		// ������
		pTitle->Init();
	}
	return pTitle;
}

//=============================
// �e�N�X�`�����[�h
//=============================
HRESULT CRogo::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, M_TEXTURE_PATH, &m_apTexture[BG]);

	return S_OK;
}

//=============================
// �e�N�X�`���j��
//=============================
void CRogo::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MENU_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//=============================
// ����������
//=============================
HRESULT CRogo::Init(void)
{
	m_apPolygon[BG] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[BG]->SetTexture(m_apTexture[BG]);

	return S_OK;
}

//=============================
// �I������
//=============================
void CRogo::Uninit(void)
{
	for (int nCntTex = 0; nCntTex < MENU_MAX; nCntTex++)
	{
		if (m_apPolygon[nCntTex] != NULL)
		{
			// �|���S���̏I������
			m_apPolygon[nCntTex]->Uninit();

			// �������̉��
			delete m_apPolygon[nCntTex];
			m_apPolygon[nCntTex] = NULL;
		}
	}

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CRogo::Update(void)
{
	//�T�E���h�̃|�C���^�ϐ��錾
	CSound*pSound = CManager::GetSound();
	m_nCount++;
	if (m_nCount >= 500 ||
		CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 0) ||
		CManager::GetJoypad()->GetJoystickTrigger(3, 1))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TITLE);
	}
}


//=============================
// �`�揈��
//=============================
void CRogo::Draw(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MENU_MAX; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			// �|���S���̕`�揈��
			m_apPolygon[nCntPolygon]->Draw();
		}
	}
}
