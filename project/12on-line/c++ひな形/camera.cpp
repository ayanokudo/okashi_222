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

//******************************
// �}�N����`
//******************************
#define CAMERA_DISTANCE 250    // �J�����̋���
#define CAMERA_LOCAL_POS D3DXVECTOR3(0.0f, 2000.0f, 1000.0f)

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
	m_fRad = 0.0f;
	m_fTheta = 0.0f;
	m_fPhi = 0.0f;
	m_fViewExtent = 1.0f;
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
	m_posV = D3DXVECTOR3(1.0f, 500.0f, 100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fRad = CAMERA_DISTANCE;
	m_fTheta = D3DXToRadian(-90);
	m_fPhi = atanf(m_posV.z / m_posV.x);
	m_fViewExtent = 1.0f;
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
	CPlayer*pPlayer[MAX_PLAYER] = {};
	D3DXVECTOR3 playerPos[MAX_PLAYER] = {};
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
		if (pPlayer[nCntPlayer] != NULL)
		{
			playerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPos();
		}
	}

	// �v���C���[���m�̋���
	float fDistance = sqrtf(powf(playerPos[0].x - playerPos[1].x, 2) + powf(playerPos[0].z - playerPos[1].z, 2));
	// �v���C���[���m�̈ʒu�̊p�x
	float fAngle = atan2f(playerPos[1].z - playerPos[0].z, playerPos[1].x - playerPos[0].x);
	
	if (fDistance >= 3000)
	{
		playerPos[1].x= playerPos[0].x + cosf(fAngle)*(3000);
		playerPos[1].z = playerPos[0].z + sinf(fAngle)*(3000);
		pPlayer[1]->SetPos(playerPos[1]);
	}

	// ���S�_���v���C���[�Ԃ̒��S�ɐݒ�
	m_posR.x = playerPos[0].x + cosf(fAngle)*(fDistance / 2);
	m_posR.z = playerPos[0].z + sinf(fAngle)*(fDistance / 2);

	// �����ŃJ����������
	m_fViewExtent = fDistance/2;

	// �J�����ʒu�̐ݒ�
	m_posV = m_posR + CAMERA_LOCAL_POS;
	m_posV.y = CAMERA_LOCAL_POS.y + m_fViewExtent;
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
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,10.0f, 6000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera->m_mtxProjection);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 0, 255), 1.0f, 0);

	
}
