////////////////////////////////////////////////////
//
//    �^�C�g���N���X�̏���[title.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "title.h"
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
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[MENU_MAX] = {};
LPDIRECT3DTEXTURE9 CTitle::m_apCatTex[CAT_MAX];        // �e�N�X�`���ւ̃|�C���^

//**********************************
// �}�N����`
//**********************************
#define  TITLE_TEXTURE_PATH "./data/Textures/Title.png"			// �e�N�X�`��
#define  EXIT_TEXTURE_PATH "./data/Textures/Out_button.png"			// �e�N�X�`��
#define  START_TEXTURE_PATH "./data/Textures/Play_button.png"		// �e�N�X�`��
#define  TUTORIAL_TEXTURE_PATH "./data/Textures/Tutorial_button.png" // �e�N�X�`��

#define  MILK_TEXTURE_PATH  "./data/Textures/WhiteCatAnimation.png"		 // �e�N�X�`��
#define  CHOCO_TEXTURE_PATH "./data/Textures/ChocolateCatAnimation.png"	 // �e�N�X�`��


#define CAT_SIZE D3DXVECTOR3(750.0f,311.0f,0.0f)/3
#define CAT_POS D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f)

#define ANIM_SPEED 7          // �A�j���[�V�������x
#define MAX_ANIMATION_X 3      // �A�j���[�V������ ��
#define MAX_ANIMATION_Y 2      // �A�j���[�V������ �c


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
CTitle::CTitle()
{
	memset(&m_apPolygon, 0, sizeof(m_apPolygon));
	m_pUi = NULL;
	m_nMenu = START;
	m_bStick = false;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
}

//=============================
// �f�X�g���N�^
//=============================
CTitle::~CTitle()
{
}

//=============================
// �N���G�C�g
//=============================
CTitle * CTitle::Create(void)
{
	// �������̊m��
	CTitle *pTitle = new CTitle;

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
HRESULT CTitle::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_PATH, &m_apTexture[BG]);
	D3DXCreateTextureFromFile(pDevice, EXIT_TEXTURE_PATH, &m_apTexture[EXIT]);
	D3DXCreateTextureFromFile(pDevice, START_TEXTURE_PATH, &m_apTexture[START]);
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_PATH, &m_apTexture[TUTORIAL]);
	
	D3DXCreateTextureFromFile(pDevice, MILK_TEXTURE_PATH, &m_apCatTex[MILK]);
	D3DXCreateTextureFromFile(pDevice, CHOCO_TEXTURE_PATH, &m_apCatTex[CHOCO]);
	return S_OK;
}

//=============================
// �e�N�X�`���j��
//=============================
void CTitle::Unload(void)
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
HRESULT CTitle::Init(void)
{
	m_apPolygon[BG] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apPolygon[BG]->SetTexture(m_apTexture[BG]);

	//�^�C���̕����\��
	m_pUi = CUi::Create(D3DXVECTOR3(650.0f, 200.0f, 0.0f),
		D3DXVECTOR3(300, 200, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_TITLE);

	// EXIT�̂��
	m_apPolygon[EXIT] = CPolygon::Create(EXIT_POS, STRING_SIZE);
	m_apPolygon[EXIT]->SetTexture(m_apTexture[EXIT]);
	// �X�^�[�g�̂��
	m_apPolygon[START] = CPolygon::Create(START_POS, STRING_SIZE);
	m_apPolygon[START]->SetTexture(m_apTexture[START]);
	// Tutorial�̂��
	m_apPolygon[TUTORIAL] = CPolygon::Create(TUTORIAL_POS, STRING_SIZE);
	m_apPolygon[TUTORIAL]->SetTexture(m_apTexture[TUTORIAL]);
	
	// �L�̐���
	for (int nCnt = 0; nCnt < CAT_MAX; nCnt++)
	{
		m_pScene2d[nCnt] = CScene2d::Create(OBJTYPE_UI);
		m_pScene2d[nCnt]->SetSize(CAT_SIZE);
		m_pScene2d[nCnt]->SetPos(CAT_POS);

		// �e�N�X�`��UV���W�̏�����
		m_nAnimX = 2;
		m_nAnimY = 0;

		// UV���W�̐ݒ�
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / MAX_ANIMATION_X;
		float fv = 1.0f / MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

		// UV���W�Z�b�g
		m_pScene2d[nCnt]->SetTextureUV(uv);
	}
	m_pScene2d[MILK]->BindTexture(m_apCatTex[CHOCO]);
	m_pScene2d[CHOCO]->BindTexture(m_apCatTex[CHOCO]);

	return S_OK;
}

//=============================
// �I������
//=============================
void CTitle::Uninit(void)
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

	if (m_pUi != NULL)
	{
		// �|���S���̏I������
		m_pUi->Uninit();

		// �������̉��
		delete m_pUi;
		m_pUi = NULL;
	}

	// �J������
	Release();
}


//=============================
// �X�V����
//=============================
void CTitle::Update(void)
{
	//�T�E���h�̃|�C���^�ϐ��錾
	CSound*pSound = CManager::GetSound();
	// �A�j���[�V�����J�E���g��i�߂�
	m_nCntAnim++;

	if (m_nCntAnim % ANIM_SPEED == 0)
	{
		// �A�j���[�V����X���̉��Z
		m_nAnimX++;

		if (m_nAnimX >= MAX_ANIMATION_X)
		{
			// �A�j���[�V����X���̏�����
			m_nAnimX = 0;

			m_nAnimY++;
			if (m_nAnimY >= MAX_ANIMATION_X)
			{
				m_nAnimY = 0;
			}
		}
		else
		{
			// UV���W�̐ݒ�
			D3DXVECTOR2 uv[NUM_VERTEX];

			float fu = 1.0f / MAX_ANIMATION_X;
			float fv = 1.0f / MAX_ANIMATION_Y;

			uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY - fv);
			uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY - fv);
			uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
			uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
			// �L�̃A�j���[�V����
			for (int nCnt = 0; nCnt < CAT_MAX; nCnt++)
			{
				if (m_pScene2d[nCnt] != NULL)
				{
					// UV���W�Z�b�g
					m_pScene2d[nCnt]->SetTextureUV(uv);
				}
			}
		}
	}

	m_pUi->Update();
	// �I��ł郁�j���[�ŐF����
	for (int nCntMenu = EXIT; nCntMenu < MENU_MAX; nCntMenu++)
	{
		if (m_nMenu == nCntMenu)
		{// �I��ł�Ƃ�
			m_apPolygon[nCntMenu]->SetColor(MENU_ENTER_COL);
			m_apPolygon[nCntMenu]->Flashing();
		}
		else
		{// �I��łȂ��Ƃ�
			m_apPolygon[nCntMenu]->SetColor(MENU_NOT_ENTER_COL);
		}
	}

	DIJOYSTATE js[MAX_PLAYER] ={ CManager::GetJoypad()->GetStick(0), CManager::GetJoypad()->GetStick(1) };
	// ���j���[����
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_A) ||
		CManager::GetKeyboard()->GetKeyTrigger(DIK_LEFT) ||
		js[0].lX <= -100 || js[1].lX <= -100)
	{// ��
		pSound->Play(CSound::SOUND_SE_SELECT);
		if (!m_bStick)
		{
			m_nMenu--;
			m_bStick = true;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyTrigger(DIK_D) ||
		CManager::GetKeyboard()->GetKeyTrigger(DIK_RIGHT) ||
		js[0].lX >= 100 || js[1].lX >= 100)
	{// ��
		pSound->Play(CSound::SOUND_SE_SELECT);
		if (!m_bStick)
		{
			m_nMenu++;
			m_bStick = true;
		}
	}
	else
	{
		m_bStick = false;
	}
	// �͈͊O�ɍs���Ȃ��悤��
	if (m_nMenu > TUTORIAL)
	{
		m_nMenu = EXIT;
	}
	else if (m_nMenu < EXIT)
	{
		m_nMenu = TUTORIAL;
	}

	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN) || 
		CManager::GetMouse()->GetMouseTrigger(0) || 
		CManager::GetJoypad()->GetJoystickTrigger(3, 0)|| 
		CManager::GetJoypad()->GetJoystickTrigger(3, 1))
	{
		pSound->Play(CSound::SOUND_SE_DECISION);
		switch (m_nMenu)
		{
		case EXIT:
			// �I������
			DestroyWindow(FindWindow(WINDOW_CLASS_NAME, NULL));
			break;
		case START:
			// ���X�^�[�g
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
			break;
		case TUTORIAL:
			CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
			break;
		default:
			break;
		}
	}
}


//=============================
// �`�揈��
//=============================
void CTitle::Draw(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MENU_MAX; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			// �|���S���̕`�揈��
			m_apPolygon[nCntPolygon]->Draw();
		}
	}
	m_pUi->Draw();
}
