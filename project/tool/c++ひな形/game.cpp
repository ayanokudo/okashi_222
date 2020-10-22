////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "player.h"
#include "light.h"
#include "floor.h"
#include "stage.h"
#include "object.h"

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CCamera *CGame::m_pCamera = NULL;   // �J�����N���X�̃|�C���^�ϐ�
CPlayer *CGame::m_pPlayer = NULL;
CLight *CGame::m_pLight = NULL;		// ���C�g�N���X�̃|�C���^�ϐ�

//=============================
// �R���X�g���N�^
//=============================
CGame::CGame()
{
}

//=============================
// �f�X�g���N�^
//=============================
CGame::~CGame()
{
}

//=============================
// �N���G�C�g
//=============================
CGame * CGame::Create(void)
{
	// �������̊m��
	CGame *pGame = new CGame;
	// ������
	pGame->Init();
	return pGame;
}

//=============================
// ����������
//=============================
HRESULT CGame::Init(void)
{	
	//���C�g�N���X�̐���
	m_pLight = new CLight;

	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// �J�����̐���
	m_pCamera = CCamera::Create();

    // �X�e�[�W�̐���
    CStage::Create({ 0.0f,0.0f,0.0f });

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
    CObject::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	// �|���S���̐���
	//CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	//���̐���
	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f),CFloor::FLOOR_FLOORING);
	// �|�[�Y�̏�����
	CManager::SetActivePause(false);
	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{
	// �J������
	CCamera::Release();
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CGame::Update(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
}

//=============================
// �`�揈��
//=============================
void CGame::Draw(void)
{
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}