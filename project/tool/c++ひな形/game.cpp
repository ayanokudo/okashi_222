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
#include "file.h"
#include "debug.h"

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CCamera *CGame::m_pCamera = NULL;   // �J�����N���X�̃|�C���^�ϐ�
CLight *CGame::m_pLight = NULL;		// ���C�g�N���X�̃|�C���^�ϐ�
CObject *CGame::m_pObject = NULL;   // �I�u�W�F�N�g�ւ̃|�C���^
#if _DEBUG
CDebug *CGame::m_pDebug = NULL;     // �f�o�b�O�p�e�L�X�g�̃|�C���^
#endif //_DEBUG

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
    CStage::Create({ 0.0f,-1.0f,0.0f });

    // �I�u�W�F�N�g�̐���
    m_pObject = CObject::Create({ 0.0f,0.0f,0.0f });

    // �t�@�C���̓ǂݍ���
    CFile::Read();
	// �|���S���̐���
	//CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	//���̐���
	CFloor::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(GRID_SIZE * MAX_GRID, 0.0f, GRID_SIZE * MAX_GRID),CFloor::FLOOR_FLOORING);
	// �|�[�Y�̏�����
	CManager::SetActivePause(false);

#if _DEBUG
    m_pDebug = CDebug::Create();
#endif // _DEBUG

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

#if _DEBUG
    m_pDebug->Uninit();
#endif // _DEBUG
	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CGame::Update(void)
{
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
#if _DEBUG
    if (m_pDebug)
    {
        m_pDebug->Draw();
    }
#endif // _DEBUG
}