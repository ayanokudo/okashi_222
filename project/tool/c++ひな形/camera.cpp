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
#include "object.h"

//******************************
// �}�N����`
//******************************
#define CAMERA_DISTANCE (250)    // �J�����̋���
#define CAMERA_LOCAL_POS D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
#define CAMERA_ROTATION (1.0f) // �J�����̉�]�p�x

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
	m_posV = D3DXVECTOR3(0.0f, 500.0f, 100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_fRad = CAMERA_DISTANCE;
	m_fTheta = D3DXToRadian(-90);
	m_fPhi = atanf(m_posV.z / m_posV.x);
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
	m_posV = CObject::GetPlayer()->GetPos() + CAMERA_LOCAL_POS;
    RotateCamera();
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
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.0f, 1000.0f);
	
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera->m_mtxProjection);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 0, 255), 1.0f, 0);

}

//===============================================================
// [RotateCamera] �J�����̉�]�@Author : AYANO KUDO
//===============================================================
void CCamera::RotateCamera(void)
{
    // �ϐ��錾
    m_posR = CObject::GetPlayer()->GetPos();
    D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };

    //�J�������W�̉�]
    if (CManager::GetKeyboard()->GetKeyPress(DIK_LEFT))
    {
        m_fTheta += D3DXToRadian(CAMERA_ROTATION);
    }
    if (CManager::GetKeyboard()->GetKeyPress(DIK_RIGHT))
    {
        m_fTheta -= D3DXToRadian(CAMERA_ROTATION);

    }
    if (CManager::GetKeyboard()->GetKeyPress(DIK_UP))
    {
        m_fPhi -= D3DXToRadian(CAMERA_ROTATION);
    }
    if (CManager::GetKeyboard()->GetKeyPress(DIK_DOWN))
    {
        m_fPhi += D3DXToRadian(CAMERA_ROTATION);
    }

        m_posV.x = m_posR.x + 1500 * sinf(m_fPhi) * cosf(m_fTheta);
        m_posV.y = m_posR.y + 1500 * cosf(m_fPhi);
        m_posV.z = m_posR.z + 1500 * sinf(m_fPhi) * sinf(m_fTheta);
}
