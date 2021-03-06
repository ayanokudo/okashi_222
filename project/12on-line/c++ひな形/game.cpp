////////////////////////////////////////////////////
//
//    ゲームクラスの処理[game.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//=============================
// インクルード
//=============================
#include "game.h"
#include "renderer.h"
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
#include "collision.h"
#include "sound.h"
#include "start.h"

//=============================
// インクルード
//=============================
#define BOSS_MARK_PATH "./data/Textures/BOSS_mark.png"    //モデルのパス

//=============================
// 静的メンバ変数宣言
//=============================
CCamera *CGame::m_pCamera = NULL;   // カメラクラスのポインタ変数
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};	// プレイヤークラスのポインタ変数
CEnemy  *CGame::m_pEnemy  = NULL;	// エネミークラスのポインタ変数
CBoss   *CGame::m_pBoss   = NULL;   // ボスクラスのポインタ変数
CItem   *CGame::m_pItem	  = NULL;	// アイテムクラスのポインタ変数
CScore  *CGame::m_pScore  = NULL;	// スコアクラスのポインタ変数
CTime   *CGame::m_pTime   = NULL;	// タイムクラスのポインタ変数
CLight  *CGame::m_pLight  = NULL;	// ライトクラスのポインタ変数
CLostPoint *CGame::m_pLostPoint = NULL;// ロストポイントのポインタ変数
CFurniture *CGame::m_pFurniture = NULL;// ロストポイントのポインタ変数
CGame::GAME_MODE CGame::m_gameMode = GAME_NORMAL;

//=============================
// コンストラクタ
//=============================
CGame::CGame() :CScene(OBJTYPE_NONE)
{
	memset(m_pUi, 0, sizeof(m_pUi));
}

//=============================
// デストラクタ
//=============================
CGame::~CGame()
{
}

//=============================
// クリエイト
//=============================
CGame * CGame::Create(void)
{
	// メモリの確保
	CGame *pGame = new CGame;
	
	// 初期化
	pGame->Init();

	return pGame;
}

//=============================
// 初期化処理
//=============================
HRESULT CGame::Init(void)
{	
	CCollect::InitVariable();
	// ゲームモードの初期化
	m_gameMode = GAME_NORMAL;

	//ライトクラスの生成
	m_pLight = new CLight;
	// 初期化
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// カメラの生成
	m_pCamera = CCamera::Create();
	
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER;nCntPlayer++)
	{
		// プレイヤーの生成
		m_pPlayer[nCntPlayer] = CPlayer::Create(D3DXVECTOR3(100.0f + (300 - (nCntPlayer * 600)), 0.0f, 1200.0f), nCntPlayer);
	}

	//UIの生成
	Ui();
	//スコアの初期化
	m_pScore->ResetScore();
	// スコアの生成
	m_pScore = CScore::Create(
		D3DXVECTOR3(950.0f, 80.0f, 0.0f), 
		D3DXVECTOR3(30.0f, 30.0f, 0.0f));
	// タイムの生成
	m_pTime = CTime::Create();

    // ステージファイルの読み込み
    CFile::Read();

	// ポーズの初期化
	CManager::SetActivePause(false);

	// ロストポイントの生成
	m_pLostPoint = CLostPoint::Create();

	// 背景
	CBg::Create();

	// テクスチャの読み込み
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), BOSS_MARK_PATH, &pTexture);
	// ボス前のマークの生成
	CScene3d::Create(D3DXVECTOR3(CFile::BossRoomCollision()->GetPos().x, 20.0f, CFile::BossRoomCollision()->GetPos().z + 400), D3DXVECTOR3(200.0f, 0.0f, 200.0f))->BindTexture(pTexture);
	// スタートの生成
	CStart::Create();
	return S_OK;
}

//=============================
// 終了処理
//=============================
void CGame::Uninit(void)
{
	// 開放処理
	CCamera::Release();

	// ライト
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	for (int nCount = 0; nCount < 5; nCount++)
	{
		if (m_pUi[nCount] != NULL)
		{
			m_pUi[nCount]->Uninit();
			//delete m_pUi[nCount];
			m_pUi[nCount] = NULL;
		}
	}

	// 開放処理
	Release();
}


//=============================
// 更新処理
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
// 描画処理
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
	//サウンドのポインタ変数宣言
	CSound*pSound = CManager::GetSound();
	m_gameMode = mode;
	if (m_gameMode == GAME_BOSS)
	{
		pSound->Stop(CSound::SOUND_BGM_GAME);
		pSound->Play(CSound::SOUND_BGM_BOSS_GAME);
		// ボスの生成
		m_pBoss = CBoss::Create(D3DXVECTOR3(-15000.0f, 0.0f, -18000.0f));

		// プレイヤーの瞬間移動
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (!CPlayer::GetDeath(nCnt))
			{
				m_pPlayer[nCnt]->SetPos(D3DXVECTOR3(-15000.0f - (400 - nCnt * 800), 0.0f, -16900.0f));
				m_pPlayer[nCnt]->SetMotion(CPlayer::WAIT);
			}
		}

		// 敵をいったん全部消す
		CEnemy*pEnemy = (CEnemy*)GetTop(OBJTYPE_ENEMY);

		while (pEnemy != NULL)
		{
			// ネクストの保存
			CEnemy*pNext = (CEnemy*)pEnemy->GetNext();
			// 消す
			pEnemy->Uninit();
			// ネクストにする
			pEnemy = pNext;
		}

		// 敵の配置
		// 何体敵を沸かすか
		const int c_nNumEnemy = 10;

		for (int nCnt = 0; nCnt < c_nNumEnemy; nCnt++)
		{
			// 敵を沸かす位置
			D3DXVECTOR3 enemyPos;
			enemyPos.x = -15000.0f + (-600+(nCnt % 5)*300);
			enemyPos.y = 0;
			enemyPos.z = -19000.0f - ((nCnt / 5) * 200);
			// 敵の生成
			CEnemy::Create(enemyPos, CEnemy::ENEMY_ESCORT);
		}
		//// ボスの生成
		//m_pBoss = CBoss::Create(D3DXVECTOR3(-15000.0f, 0.0f, -18000.0f));
	}
}

//=============================
// UIの生成処理
//=============================
void CGame::Ui(void)
{
	// ダッシュのUIの生成
	m_pUi[0] = CUi::Create(D3DXVECTOR3(640.0f, 660.0f, 0.0f),
		D3DXVECTOR3(135, 50, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
		CUi::UI_ATTACK);

	// アタックのUIの生成
	m_pUi[1] = CUi::Create(D3DXVECTOR3(550.0f, 660.0f, 0.0f),
		D3DXVECTOR3(45, 45, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f),
		CUi::UI_ATTACK_NAIL);

	// ダッシュのUIの生成
	m_pUi[2] = CUi::Create(D3DXVECTOR3(640.0f, 660.0f, 0.0f),
		D3DXVECTOR3(45, 45, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f),
		CUi::UI_ATTACK_CRY);

	// ダッシュのUIの生成
	m_pUi[3] = CUi::Create(D3DXVECTOR3(730.0f, 660.0f, 0.0f),
		D3DXVECTOR3(45, 45, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f),
		CUi::UI_DASH);

	// アタックのUIの生成
	m_pUi[4] = CUi::Create(D3DXVECTOR3(120.0f, 630.0f, 0.0f),
		D3DXVECTOR3(110, 60, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_CHOCO);

	// ダッシュのUIの生成
	m_pUi[5] = CUi::Create(D3DXVECTOR3(1160.0f, 630.0f, 0.0f),
		D3DXVECTOR3(110, 60, 0),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		CUi::UI_MILK);

}
