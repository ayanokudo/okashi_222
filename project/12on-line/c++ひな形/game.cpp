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
#include "wall.h"
#include "enemy.h"
#include "boss.h"
#include "item.h"
#include "time.h"
#include "collect.h"
#include "boss.h"
#include "ui.h"
#include "file.h"
#include "lostpoint.h"
#include "furniture.h"

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CCamera *CGame::m_pCamera = NULL;   // �J�����N���X�̃|�C���^�ϐ�
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};	// �v���C���[�N���X�̃|�C���^�ϐ�
CEnemy  *CGame::m_pEnemy  = NULL;	// �G�l�~�[�N���X�̃|�C���^�ϐ�
CBoss   *CGame::m_pBoss   = NULL;   // �{�X�N���X�̃|�C���^�ϐ�
CItem   *CGame::m_pItem	  = NULL;	// �A�C�e���N���X�̃|�C���^�ϐ�
CScore  *CGame::m_pScore  = NULL;	// �X�R�A�N���X�̃|�C���^�ϐ�
CTime   *CGame::m_pTime   = NULL;	// �^�C���N���X�̃|�C���^�ϐ�
CLight  *CGame::m_pLight  = NULL;	// ���C�g�N���X�̃|�C���^�ϐ�
CLostPoint *CGame::m_pLostPoint = NULL;// ���X�g�|�C���g�̃|�C���^�ϐ�
CFurniture *CGame::m_pFurniture = NULL;// ���X�g�|�C���g�̃|�C���^�ϐ�
CGame::GAME_MODE CGame::m_gameMode = GAME_NORMAL;

//=============================
// �R���X�g���N�^
//=============================
CGame::CGame() :CScene(OBJTYPE_NONE)
{
	memset(m_pUi, 0, sizeof(m_pUi));
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
	// �Q�[�����[�h�̏�����
	m_gameMode = GAME_NORMAL;

	//���C�g�N���X�̐���
	m_pLight = new CLight;
	// ������
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// �J�����̐���
	m_pCamera = CCamera::Create();
	
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER;nCntPlayer++)
	{
		// �v���C���[�̐���
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(100.0f + (300 - (nCntPlayer * 600)), 0.0f, 1200.0f), nCntPlayer);
	}
	
	//// �A�C�e���̐���
	//m_pItem = CItem::Create(D3DXVECTOR3(200.0f, 0.0f, -800.0f),CItem::LIFE);
	//m_pItem = CItem::Create(D3DXVECTOR3(200.0f, 0.0f, -900.0f), CItem::CANDY);
	//m_pItem = CItem::Create(D3DXVECTOR3(200.0f, 0.0f, -1000.0f), CItem::KOBAN);

	//�X�R�A�̏�����
	m_pScore->ResetScore();
	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(950.0f, 40.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	// �^�C���̐���
	m_pTime = CTime::Create();

	//UI�̐���
	Ui();

    // �X�e�[�W�t�@�C���̓ǂݍ���
    CFile::Read();

	// �|�[�Y�̏�����
	CManager::SetActivePause(false);

	// ���X�g�|�C���g�̐���
	m_pLostPoint = CLostPoint::Create();

	// �w�i
	CBg::Create();

	//CCollect::Create();
	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{
	// �J������
	CCamera::Release();

	// ���C�g
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	for (int nCount = 0; nCount <= 5; nCount++)
	{
		if (m_pUi[nCount] != NULL)
		{
			m_pUi[nCount]->Uninit();
			//delete m_pUi[nCount];
			m_pUi[nCount] = NULL;
		}
	}

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

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_F9))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

#endif // _DEBUG

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
	/*for (int nCount = 0; nCount <= 5; nCount++)
	{
		if (m_pUi != NULL)
		{
			m_pUi[nCount]->Draw();
		}
	}*/
}

void CGame::SetGameMode(GAME_MODE mode)
{
	m_gameMode = mode;
	if (m_gameMode == GAME_BOSS)
	{
		// �{�X�̐���
		m_pBoss = CBoss::Create(D3DXVECTOR3(-15000.0f, 0.0f, -18000.0f));

		// �v���C���[�̏u�Ԉړ�
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (!CPlayer::GetDeath(nCnt))
			{
				m_pPlayer[nCnt]->SetPos(D3DXVECTOR3(-15000.0f - (400 - nCnt * 800), 0.0f, -16900.0f));
				m_pPlayer[nCnt]->SetMotion(CPlayer::WAIT);
			}
		}

		// �G����������S������
		CEnemy*pEnemy = (CEnemy*)GetTop(OBJTYPE_ENEMY);

		while (pEnemy != NULL)
		{
			// �l�N�X�g�̕ۑ�
			CEnemy*pNext = (CEnemy*)pEnemy->GetNext();
			// ����
			pEnemy->Uninit();
			// �l�N�X�g�ɂ���
			pEnemy = pNext;
		}

		// �G�̔z�u
		// ���̓G�𕦂�����
		const int c_nNumEnemy = 10;

		for (int nCnt = 0; nCnt < c_nNumEnemy; nCnt++)
		{
			// �G�𕦂����ʒu
			D3DXVECTOR3 enemyPos;
			enemyPos.x = -15000.0f + (-600+(nCnt % 5)*300);
			enemyPos.y = 0;
			enemyPos.z = -19000.0f - ((nCnt / 5) * 200);
			// �G�̐���
			CEnemy::Create(enemyPos, CEnemy::ENEMY_ESCORT);
		}
		//// �{�X�̐���
		//m_pBoss = CBoss::Create(D3DXVECTOR3(-15000.0f, 0.0f, -18000.0f));
	}
}

//=============================
// UI�̐�������
//=============================
void CGame::Ui(void)
{
	// �_�b�V����UI�̐���
	m_pUi[0] = CUi::Create(D3DXVECTOR3(640.0f, 660.0f, 0.0f),
		D3DXVECTOR3(135, 50, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
		CUi::UI_ATTACK);

	// �A�^�b�N��UI�̐���
	m_pUi[1] = CUi::Create(D3DXVECTOR3(550.0f, 660.0f, 0.0f),
		D3DXVECTOR3(45, 45, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f),
		CUi::UI_ATTACK_NAIL);

	// �_�b�V����UI�̐���
	m_pUi[2] = CUi::Create(D3DXVECTOR3(640.0f, 660.0f, 0.0f),
		D3DXVECTOR3(45, 45, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f),
		CUi::UI_ATTACK_CRY);

	// �_�b�V����UI�̐���
	m_pUi[3] = CUi::Create(D3DXVECTOR3(730.0f, 660.0f, 0.0f),
		D3DXVECTOR3(45, 45, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f),
		CUi::UI_DASH);

	// �A�^�b�N��UI�̐���
	m_pUi[4] = CUi::Create(D3DXVECTOR3(120.0f, 630.0f, 0.0f),
		D3DXVECTOR3(110, 60, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_CHOCO);

	// �_�b�V����UI�̐���
	m_pUi[5] = CUi::Create(D3DXVECTOR3(1160.0f, 630.0f, 0.0f),
		D3DXVECTOR3(110, 60, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_MILK);

}
