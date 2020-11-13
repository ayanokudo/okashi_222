////////////////////////////////////////////////////
//
//    �J�����N���X�̏���[camera.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "debug_log.h"
#include "mouse.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_DISTANCE 250    // �J�����̋���
#define CAMERA_LOCAL_POS D3DXVECTOR3(0.0f, 2300.0f, 200.0f) // �����_����̃��[�J�����W
#define CAMERA_LOOK_RATE 0.5f  // �����_���������ς���Ƃ��̌W��
#define PLAYER_DEATH_COUNT 40  // �v���C���[������ł��琶���Ă�v���C���[�̕��ɏ����������_��ς���p
#define BOSS_MODE_POS_R D3DXVECTOR3(-15000.0f, 0.0f, -17700.0f)
#define BOSS_MODE_POS_V D3DXVECTOR3(-15000.0f, 4600.0f, -17700.0f+200)
#define FOV_Y D3DXToRadian(45.0f)
#define FOV_X D3DXToRadian(80.0f)

//******************************
// �ÓI�����o�ϐ��錾
//******************************
CCamera*CCamera::m_pCamera = NULL;

//******************************
// �R���X�g���N�^
//******************************
CCamera::CCamera()
{
	// �ϐ��̃N���A
	m_posV = { 0.0f,0.0f,0.0f };
	m_posR = { 0.0f,0.0f,0.0f };
	m_vecU = { 0.0f,0.0f,0.0f };
	D3DXMatrixIdentity(&m_mtxProjection);
	D3DXMatrixIdentity(&m_mtxView);
	m_fViewExtent = 0.0f;
	m_nCntPlayerDeath = 0;
#ifdef _DEBUG
	m_fRad = CAMERA_DISTANCE;
	m_fTheta = D3DXToRadian(-90);
	m_fPhi = D3DXToRadian(-70);
#endif
}

//******************************
// �f�X�g���N�^
//******************************
CCamera::~CCamera()
{
}

//******************************
// �N���G�C�g
//******************************
CCamera * CCamera::Create()
{

	m_pCamera = new CCamera;
	m_pCamera->Init();

	return m_pCamera;
}

//******************************
// �������
//******************************
void CCamera::Release(void)
{
	if (m_pCamera != NULL)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}
}

//******************************
// ����������
//******************************
HRESULT CCamera::Init(void)
{
	// ������
	m_posV = CAMERA_LOCAL_POS;
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_nCntPlayerDeath = 0;
#ifdef _DEBUG
	m_fRad = CAMERA_DISTANCE;
	m_fTheta = D3DXToRadian(-90);
	m_fPhi = atanf(m_posV.z / m_posV.x);
	m_fViewExtent = 1.0f;
#endif
	return S_OK;
}

//******************************
// �I������
//******************************
void CCamera::Uninit(void)
{
}

//******************************
// �X�V����
//******************************
void CCamera::Update(void)
{
#ifdef _DEB/UG

	m_fPhi -= CManager::GetMouse()->GetMouseMove().y / 100.0f;
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x / 100.0f;
	// �����_���v���C���[�ɂ���
	m_posR = CGame::GetPlayer(1)->GetPos();
	// ���ʍ��W�̐ݒ�
	m_posV.x = m_posR.x + (m_fRad)* sinf(-m_fPhi)*cosf(m_fTheta);
	m_posV.y = m_posR.y + (m_fRad)* cosf(-m_fPhi);
	m_posV.z = m_posR.z + (m_fRad)* sinf(-m_fPhi)*sinf(m_fTheta);

	if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
	{
		m_fRad += 4.0f;
	}
	if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
	{
		m_fRad -= 4.0f;
	}

#else
	if (CGame::GetGameMode() == CGame::GAME_NORMAL)
	{// �Q�[�����[�h���m�[�}���̎�

		if (!CPlayer::GetDeath(0) && !CPlayer::GetDeath(1))
		{
			CPlayer*pPlayer[MAX_PLAYER] = {};       // �v���C���[���
			D3DXVECTOR3 playerPos[MAX_PLAYER] = {}; // �v���C���[���W
			// �v���C���[�������[�v
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				// �v���C���[���̎擾
				pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
				if (pPlayer[nCntPlayer] != NULL)
				{
					// �v���C���[���W�̎擾
					playerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPos();
				}
			}

			// �v���C���[���m�̋���
			float fDistance = sqrtf(powf(playerPos[0].x - playerPos[1].x, 2) + powf(playerPos[0].z - playerPos[1].z, 2));
			// �v���C���[���m�̈ʒu�̊p�x
			float fAngle = atan2f(playerPos[1].z - playerPos[0].z, playerPos[1].x - playerPos[0].x);

			// ���S�_���v���C���[�Ԃ̒��S�ɐݒ�
			m_posR.x = playerPos[0].x + cosf(fAngle)*(fDistance / 2);
			m_posR.z = playerPos[0].z + sinf(fAngle)*(fDistance / 2);

			if (fDistance >= 500 && fDistance <= 2000)
			{
				// �����ŃJ����������
				m_fViewExtent = fDistance - 500;
			}

			// �J�����ʒu�̐ݒ�
			m_posV = m_posR + CAMERA_LOCAL_POS;
			m_posV.y = CAMERA_LOCAL_POS.y + m_fViewExtent;
		}
		else if (!CPlayer::GetDeath(0))
		{

			if (m_nCntPlayerDeath < PLAYER_DEATH_COUNT)
			{
				// �J�E���g��i�߂�
				m_nCntPlayerDeath++;
				// ���񂾂�ƒ����_��ς���
				m_posR += (CGame::GetPlayer(0)->GetPos() - m_posR)*CAMERA_LOOK_RATE;
			}
			else
			{
				// ��u�Œ����_��ς���
				m_posR = CGame::GetPlayer(0)->GetPos();
			}

			// �J�����ʒu�̐ݒ�
			m_posV = m_posR + CAMERA_LOCAL_POS;
			m_posV.y = CAMERA_LOCAL_POS.y + 300;
		}
		else if (!CPlayer::GetDeath(1))
		{
			if (m_nCntPlayerDeath < PLAYER_DEATH_COUNT)
			{
				// �J�E���g��i�߂�
				m_nCntPlayerDeath++;
				// ���񂾂�ƒ����_��ς���
				m_posR += (CGame::GetPlayer(1)->GetPos() - m_posR)*CAMERA_LOOK_RATE;
			}
			else
			{
				// ��u�Œ����_��ς���
				m_posR = CGame::GetPlayer(1)->GetPos();
			}

			// �J�����ʒu�̐ݒ�
			m_posV = m_posR + CAMERA_LOCAL_POS;
			m_posV.y = CAMERA_LOCAL_POS.y + 300;
		}

		// �J�����Ɏʂ��Ă��邩���肷��
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (!CPlayer::GetDeath(nCntPlayer))
			{
				// �J�����̊O������ǂꂭ�炢�O���肩
				const float c_fAdjust_X = 800.0f;
				const float c_fAdjust_Y = 400.0f;

				// �v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 playerPos = CGame::GetPlayer(nCntPlayer)->GetPos();

				// �J�����̊O�ɏo�Ă����瓮�����~�߂�

				// X��
				if ((playerPos.x) + c_fAdjust_X > m_posR.x + (m_posV.y *tanf(FOV_X / 2)))
				{
					playerPos.x = m_posR.x + m_posV.y *tanf(FOV_X / 2) - c_fAdjust_X;
					CGame::GetPlayer(nCntPlayer)->SetPos(playerPos);
				}

				if ((playerPos.x) - c_fAdjust_X < m_posR.x + (m_posV.y *tanf(-FOV_X / 2)))
				{
					playerPos.x = m_posR.x + m_posV.y *tanf(-FOV_X / 2) + c_fAdjust_X;
					CGame::GetPlayer(nCntPlayer)->SetPos(playerPos);
				}

				// Z��
				if ((playerPos.z) + c_fAdjust_Y > m_posR.z + (m_posV.y *tanf(FOV_Y / 2)))
				{
					playerPos.z = m_posR.z + m_posV.y *tanf(FOV_Y / 2) - c_fAdjust_Y;
					CGame::GetPlayer(nCntPlayer)->SetPos(playerPos);
				}

				if ((playerPos.z) - c_fAdjust_Y < m_posR.z + (m_posV.y *tanf(-FOV_Y / 2)))
				{
					playerPos.z = m_posR.z + m_posV.y *tanf(-FOV_Y / 2) + c_fAdjust_Y;
					CGame::GetPlayer(nCntPlayer)->SetPos(playerPos);
				}
			}
		}
	}
	else
	{// �{�X���[�h�̎�
		m_posR = BOSS_MODE_POS_R;
		m_posV = BOSS_MODE_POS_V;
	}

#endif



}

//******************************
// �J�����̃Z�b�g
//******************************
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIXA16 matWorld;

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera->m_mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_pCamera->m_mtxView, &m_pCamera->m_posV, &m_pCamera->m_posR, &m_pCamera->m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera->m_mtxView);

	//�v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera->m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_pCamera->m_mtxProjection,
		FOV_Y,
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,10.0f, 40000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera->m_mtxProjection);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
}
