////////////////////////////////////////////////////
//
//    カメラクラスの処理[camera.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "debug_log.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_DISTANCE 250    // カメラの距離
#define CAMERA_LOCAL_POS D3DXVECTOR3(0.0f, 2000.0f, 1000.0f)

//******************************
// 静的メンバ変数宣言
//******************************
CCamera*CCamera::m_pCamera = NULL;

//******************************
// コンストラクタ
//******************************
CCamera::CCamera()
{
	// 変数のクリア
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
// デストラクタ
//******************************
CCamera::~CCamera()
{
}

//******************************
// クリエイト
//******************************
CCamera * CCamera::Create()
{

	m_pCamera = new CCamera;
	m_pCamera->Init();

	return m_pCamera;
}

//******************************
// 解放処理
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
// 初期化処理
//******************************
HRESULT CCamera::Init(void)
{
	// 初期化
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
// 終了処理
//******************************
void CCamera::Uninit(void)
{
}

//******************************
// 更新処理
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

	// プレイヤー同士の距離
	float fDistance = sqrtf(powf(playerPos[0].x - playerPos[1].x, 2) + powf(playerPos[0].z - playerPos[1].z, 2));
	// プレイヤー同士の位置の角度
	float fAngle = atan2f(playerPos[1].z - playerPos[0].z, playerPos[1].x - playerPos[0].x);
	
	if (fDistance >= 3000)
	{
		playerPos[1].x= playerPos[0].x + cosf(fAngle)*(3000);
		playerPos[1].z = playerPos[0].z + sinf(fAngle)*(3000);
		pPlayer[1]->SetPos(playerPos[1]);
	}

	// 中心点をプレイヤー間の中心に設定
	m_posR.x = playerPos[0].x + cosf(fAngle)*(fDistance / 2);
	m_posR.z = playerPos[0].z + sinf(fAngle)*(fDistance / 2);

	// 距離でカメラを引く
	m_fViewExtent = fDistance/2;

	// カメラ位置の設定
	m_posV = m_posR + CAMERA_LOCAL_POS;
	m_posV.y = CAMERA_LOCAL_POS.y + m_fViewExtent;
}

//******************************
// カメラのセット
//******************************
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIXA16 matWorld;

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_pCamera->m_mtxView);
	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_pCamera->m_mtxView, &m_pCamera->m_posV, &m_pCamera->m_posR, &m_pCamera->m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera->m_mtxView);

	//プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(&m_pCamera->m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_pCamera->m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,10.0f, 6000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera->m_mtxProjection);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 0, 255), 1.0f, 0);

	
}
