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
#include "mouse.h"

//******************************
// マクロ定義
//******************************
#define CAMERA_DISTANCE 250    // カメラの距離
#define CAMERA_LOCAL_POS D3DXVECTOR3(0.0f, 2300.0f, 200.0f) // 注視点からのローカル座標
#define CAMERA_LOOK_RATE 0.5f  // 注視点を少しずつ変えるときの係数
#define PLAYER_DEATH_COUNT 40  // プレイヤーが死んでから生きてるプレイヤーの方に少しずつ注視点を変える用
#define BOSS_MODE_POS_R D3DXVECTOR3(-15000.0f, 0.0f, -17700.0f)
#define BOSS_MODE_POS_V D3DXVECTOR3(-15000.0f, 4600.0f, -17700.0f+200)
#define FOV_Y D3DXToRadian(45.0f)
#define FOV_X D3DXToRadian(80.0f)

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
	m_fViewExtent = 0.0f;
	m_nCntPlayerDeath = 0;
#ifdef _DEBUG
	m_fRad = CAMERA_DISTANCE;
	m_fTheta = D3DXToRadian(-90);
	m_fPhi = D3DXToRadian(-70);
#endif
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
#ifdef _DEB/UG

	m_fPhi -= CManager::GetMouse()->GetMouseMove().y / 100.0f;
	m_fTheta -= CManager::GetMouse()->GetMouseMove().x / 100.0f;
	// 注視点をプレイヤーにする
	m_posR = CGame::GetPlayer(1)->GetPos();
	// 球面座標の設定
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
	{// ゲームモードがノーマルの時

		if (!CPlayer::GetDeath(0) && !CPlayer::GetDeath(1))
		{
			CPlayer*pPlayer[MAX_PLAYER] = {};       // プレイヤー情報
			D3DXVECTOR3 playerPos[MAX_PLAYER] = {}; // プレイヤー座標
			// プレイヤー数分ループ
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				// プレイヤー情報の取得
				pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
				if (pPlayer[nCntPlayer] != NULL)
				{
					// プレイヤー座標の取得
					playerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPos();
				}
			}

			// プレイヤー同士の距離
			float fDistance = sqrtf(powf(playerPos[0].x - playerPos[1].x, 2) + powf(playerPos[0].z - playerPos[1].z, 2));
			// プレイヤー同士の位置の角度
			float fAngle = atan2f(playerPos[1].z - playerPos[0].z, playerPos[1].x - playerPos[0].x);

			// 中心点をプレイヤー間の中心に設定
			m_posR.x = playerPos[0].x + cosf(fAngle)*(fDistance / 2);
			m_posR.z = playerPos[0].z + sinf(fAngle)*(fDistance / 2);

			if (fDistance >= 500 && fDistance <= 2000)
			{
				// 距離でカメラを引く
				m_fViewExtent = fDistance - 500;
			}

			// カメラ位置の設定
			m_posV = m_posR + CAMERA_LOCAL_POS;
			m_posV.y = CAMERA_LOCAL_POS.y + m_fViewExtent;
		}
		else if (!CPlayer::GetDeath(0))
		{

			if (m_nCntPlayerDeath < PLAYER_DEATH_COUNT)
			{
				// カウントを進める
				m_nCntPlayerDeath++;
				// だんだんと注視点を変える
				m_posR += (CGame::GetPlayer(0)->GetPos() - m_posR)*CAMERA_LOOK_RATE;
			}
			else
			{
				// 一瞬で注視点を変える
				m_posR = CGame::GetPlayer(0)->GetPos();
			}

			// カメラ位置の設定
			m_posV = m_posR + CAMERA_LOCAL_POS;
			m_posV.y = CAMERA_LOCAL_POS.y + 300;
		}
		else if (!CPlayer::GetDeath(1))
		{
			if (m_nCntPlayerDeath < PLAYER_DEATH_COUNT)
			{
				// カウントを進める
				m_nCntPlayerDeath++;
				// だんだんと注視点を変える
				m_posR += (CGame::GetPlayer(1)->GetPos() - m_posR)*CAMERA_LOOK_RATE;
			}
			else
			{
				// 一瞬で注視点を変える
				m_posR = CGame::GetPlayer(1)->GetPos();
			}

			// カメラ位置の設定
			m_posV = m_posR + CAMERA_LOCAL_POS;
			m_posV.y = CAMERA_LOCAL_POS.y + 300;
		}

		// カメラに写っているか判定する
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (!CPlayer::GetDeath(nCntPlayer))
			{
				// カメラの外側からどれくらい外判定か
				const float c_fAdjust_X = 800.0f;
				const float c_fAdjust_Y = 400.0f;

				// プレイヤーの位置の取得
				D3DXVECTOR3 playerPos = CGame::GetPlayer(nCntPlayer)->GetPos();

				// カメラの外に出ていたら動きを止める

				// X軸
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

				// Z軸
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
	{// ボスモードの時
		m_posR = BOSS_MODE_POS_R;
		m_posV = BOSS_MODE_POS_V;
	}

#endif



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
		FOV_Y,
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,10.0f, 40000.0f);
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera->m_mtxProjection);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
}
