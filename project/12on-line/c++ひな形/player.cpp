////////////////////////////////////////////////////
//
//    playerクラスの処理[player.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "bullet.h"
#include "scene3d.h"
#include "debug_log.h"
#include "collision.h"
#include "scratch.h"
#include "model_hierarchy.h"
#include "motion.h"
#include "life.h"
#include "fade.h"
#include "sound.h"
#include "file.h"
#include"boss.h"

//*****************************
// マクロ定義
//*****************************
#define PLAYER_1_PATH "data/Texts/CatData_Choco.txt"          // モデルのパス
#define PLAYER_2_PATH "data/Texts/CatData_Milk.txt"           // モデルのパス

#define WAIT_ANIM_PATH  "data/Texts/NekoMotion/Wait.txt"      // 待機アニメーションのパス
#define WALK_ANIM_PATH  "data/Texts/NekoMotion/Walk.txt"      // 歩きアニメーションのパス
#define VOICE_ANIM_PATH "data/Texts/NekoMotion/Voice.txt"     // 鳴き声アニメーションのパス
#define PUNCH_ANIM_PATH "data/Texts/NekoMotion/Punch.txt"     // パンチアニメーションのパス
#define DASH_ANIM_PATH  "data/Texts/NekoMotion/Dash.txt"      // 走りアニメーションのパス

#define PLAYER_SPEED 20                          // 移動スピード
#define PLAYER_MOVE_RATE 0.2f                   // 移動の慣性の係数
#define PLAYER_DIRECTION_RATE 0.2f              // 向きを変えるときの係数
#define PLAYER_RADIUS 100                       // プレイヤーの半径
#define PLAYER_SPEED_MAX 5
#define PLAYER_DASH_SPEED PLAYER_SPEED * 1.5f                 // ダッシュ時のスピード

#define STATE_COUNT_DAMAGE 20                               // ダメージ状態のカウント
#define DAMAGE_STATE_COLOR D3DXCOLOR(0.7f,0.0f,0.0f,1.0f)   // ダメージ状態のカラー


//*****************************
// 静的メンバ変数宣言
//*****************************
CModel::Model CPlayer::m_model[MAX_PLAYER][MAX_PARTS_NUM] = {};
int CPlayer::m_nNumModel = 0;
bool CPlayer::m_bDeath[MAX_PLAYER] = {};
char CPlayer::m_achAnimPath[MOTION_MAX][64]
{
    { WAIT_ANIM_PATH },    // 待機アニメーション
    { WALK_ANIM_PATH },	   // 歩きアニメーション
    { VOICE_ANIM_PATH },   // 鳴き声アニメーション
    { PUNCH_ANIM_PATH },   // パンチアニメーション
    { DASH_ANIM_PATH }	   // 走りアニメーション
};

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer() :CModelHierarchy(OBJTYPE_PLAYER)
{
	// 変数のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_fRotYDist = 0.0f;
    m_nPlayerNum = 0;
    m_pCollision = NULL;
	memset(&m_pMotion, 0, sizeof(m_pMotion));
	m_motionState = WAIT;
	m_nSpeed = 0;
	m_bMotion = false;
	memset(&m_pLife, 0, sizeof(m_pLife));
	m_nLife = 0;
	m_bKeyboardMove = false;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = STATE_NORMAL;
	m_nCntState = 0;
}

//******************************
// デストラクタ
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// クリエイト
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
    // メモリの確保
    CPlayer *pPlayer;
    pPlayer = new CPlayer;

	// プレイヤー番号の設定
	pPlayer->m_nPlayerNum = nPlayerNum;

    // 初期化
    pPlayer->Init();

    // 各値の代入・セット
    pPlayer->SetPos(pos);                // 座標
    pPlayer->SetObjType(OBJTYPE_PLAYER); // オブジェクトタイプ
    
    return pPlayer;
}

//******************************
// ロード
//******************************
HRESULT CPlayer::Load(void)
{
    // デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		// ファイルオープン
		FILE*pFile = NULL;
		
		if (nCntPlayer == 0)
		{// プレイヤー１
			pFile = fopen(PLAYER_1_PATH, "r");

		}
		else
		{// プレイヤー２
			pFile = fopen(PLAYER_2_PATH, "r");
		}

		if (pFile != NULL)
		{
			// テキストファイルの解析

			char chChar[256] = {};
			fscanf(pFile, "%s", chChar);

			// "NUM_MODEL"読み込むまでループ
			while (strcmp(chChar, "NUM_MODEL") != 0)
			{
				fscanf(pFile, "%s", chChar);
			}

			// 読み込むモデルの数
			fscanf(pFile, "%*s %d # %*s", &m_nNumModel);

			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				// 読み込んだ文字格納用
				char chPath[64] = {};
				// "MODEL_FILENAME"を読み込むまでループ
				while (strcmp(chChar, "MODEL_FILENAME") != 0)
				{
					fscanf(pFile, "%s", chChar);
				}
				// ファイルパスの読み込み
				fscanf(pFile, "%*s %s", chPath);

				// Xファイルの読み込み
				D3DXLoadMeshFromX(chPath,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_model[nCntPlayer][nCnt].pBuffMat,
					NULL,	
					&m_model[nCntPlayer][nCnt].nNumMat,
					&m_model[nCntPlayer][nCnt].pMesh);

				// 次の文字を読み込む
				fscanf(pFile, "%s", chChar);
			}
		}
	}

    return S_OK;
}

//******************************
// アンロード
//******************************
void CPlayer::Unload(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			//メッシュの破棄
			if (m_model[nCntPlayer][nCnt].pMesh != NULL)
			{
				m_model[nCntPlayer][nCnt].pMesh->Release();
				m_model[nCntPlayer][nCnt].pMesh = NULL;
			}
			//マテリアルの破棄
			if (m_model[nCntPlayer][nCnt].pBuffMat != NULL)
			{
				m_model[nCntPlayer][nCnt].pBuffMat->Release();
				m_model[nCntPlayer][nCnt].pBuffMat = NULL;
			}
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CPlayer::Init(void)
{
	if (m_nPlayerNum == 0)
	{
		if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[m_nPlayerNum][0], PLAYER_1_PATH)))
		{
			return E_FAIL;
		}
	}
	else
	{
		if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[m_nPlayerNum][0], PLAYER_2_PATH)))
		{
			return E_FAIL;
		}
	}

	//プレイヤーライフ設定
	switch (m_nPlayerNum)
	{
		//1P
	case 0:
		m_nLife = PLAYER_LIFE;
		break;
		//2P
	case 1:
		m_nLife = PLAYER_LIFE;
	default:
		break;
	}
	
	m_bDeath[m_nPlayerNum] = false;
	m_bKeyboardMove = false;
    // サイズの調整
    SetSize(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
    // アニメーションの生成
    for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
    {
        m_pMotion[nCntAnim]= CMotion::Create(GetPartsNum(), m_achAnimPath[nCntAnim], &m_model[m_nPlayerNum][0]);
    }

	// サイズの調整
	SetSize(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	// アニメーションの生成
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_pMotion[nCntAnim] = CMotion::Create(GetPartsNum(), m_achAnimPath[nCntAnim], GetModelData());
	}
	// モーション状態の初期化
	SetMotion(WAIT);

	//プレイヤー１のライフ表示
	if (m_nPlayerNum == 0)
	{
		for (int nCount = 0; nCount < PLAYER_LIFE; nCount++)
		{
			m_pLife[nCount] = CLife::Create(D3DXVECTOR3(160 + nCount * LIFE_SIZE.x * 2, 660.0f, 0.0f));
		}
	}
	//プレイヤー2のライフ表示
	else
	{
		for (int nCount = 0; nCount < PLAYER_LIFE; nCount++)
		{
			m_pLife[nCount] = CLife::Create(D3DXVECTOR3(1120 - nCount * LIFE_SIZE.x * 2, 660.0f, 0.0f));
		}
	}

	// 当たり判定の生成
	m_pCollision = CCollision::CreateSphere(GetPos(), PLAYER_RADIUS);

	// 攻撃フラグの初期化
	m_bMotion = false;
	// 状態の初期化
	m_state = STATE_NORMAL;
	// カウントの初期化
	m_nCntState = 0;

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
{
    // コリジョンの終了処理
    if (m_pCollision != NULL)
    {
        m_pCollision->Uninit();
		m_pCollision = NULL;
	}
	// ライフの終了処理・メモリの解放
	for (int nCount = 0; nCount < PLAYER_LIFE; nCount++)
	{
		if (m_pLife[nCount] != NULL)
		{
			m_pLife[nCount]->Uninit();
			delete m_pLife[nCount];
			m_pLife[nCount] = NULL;
		}
	}
	// モーションの削除
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		if (m_pMotion[nCntAnim] != NULL)
		{
			m_pMotion[nCntAnim]->Uninit();
			m_pMotion[nCntAnim] = NULL;
		}
	}

    CModelHierarchy::Uninit();
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	// ボス戦じゃないときか ボスの出現演出中じゃないとき
	if (CGame::GetGameMode() == CGame::GAME_NORMAL || GetTop(OBJTYPE_BOSS) != NULL && ((CBoss*)GetTop(OBJTYPE_BOSS))->GetMotion() != CBoss::SPAWN)
	{
		// 位置の保管
		m_posOld = GetPos();

		// 目標値の初期化
		m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (!m_bMotion)
		{// 攻撃中じゃないとき

			 // 移動（コントローラー）
			MoveController();
			if (m_nPlayerNum == 1)
			{
				// 移動（キーボード）
				MoveKeyboard();
			}

			// 慣性
			m_move += (m_moveDest - m_move) * PLAYER_MOVE_RATE;

			// 座標
			D3DXVECTOR3 pos = GetPos();

			// 移動量を足す
			pos += m_move;

			// 座標のセット
			SetPos(pos);
		}

		// ダッシュ処理
		Dash();

		// 攻撃
		Attack();

		// 向きの管理
		Direction();

		// モーション管理
		MotionManager();

		// 当たり判定の位置更新
		m_pCollision->SetPos(GetPos());
	}

	// ボス戦前の当たり判定
	
	if (CCollision::CollisionSphereToBox(m_pCollision, CFile::BossRoomCollision()))
	{
		// プレイヤー座標の取得
		D3DXVECTOR3 playerPos = GetPos();
		// 当たり判定のサイズの取得
		D3DXVECTOR3 collsionSize = CFile::BossRoomCollision()->GetCollisionSize();

		// ボックス内の最短地点の検索
		D3DXVECTOR3 shortrectPos;
		shortrectPos.x = CCollision::OnRange(playerPos.x, CFile::BossRoomCollision()->GetPos().x - collsionSize.x / 2, CFile::BossRoomCollision()->GetPos().x + collsionSize.x / 2);
		shortrectPos.y = CCollision::OnRange(playerPos.y, CFile::BossRoomCollision()->GetPos().y - collsionSize.y / 2, CFile::BossRoomCollision()->GetPos().y + collsionSize.y / 2);
		shortrectPos.z = CCollision::OnRange(playerPos.z, CFile::BossRoomCollision()->GetPos().z - collsionSize.z / 2, CFile::BossRoomCollision()->GetPos().z + collsionSize.z / 2);
		// ボックスからプレイヤーの方向ベクトル
		playerPos = playerPos - shortrectPos;
		// 正規化
		D3DXVec3Normalize(&playerPos, &playerPos);
		// 最短地点から当たり判定の半径分離す
		playerPos = shortrectPos + playerPos * m_pCollision->GetCollisionRadius();
		// プレイヤー座標のセット
		SetPos(playerPos);
		// プレイヤーのコリジョンの座標のセット
		GetCollision()->SetPos(playerPos);

		if (CGame::GetGameMode() == CGame::GAME_NORMAL)
		{

			CGame::SetGameMode(CGame::GAME_BOSS);
		}

	}

	// 状態の管理

	if (m_state == STATE_DAMAGE)
	{// ダメージ状態の時

	 // カウントを進める
		m_nCntState++;
		if (m_nCntState > STATE_COUNT_DAMAGE)
		{// カウントが規定値を超えたら

		 // カウントの初期化
			m_nCntState = 0;
			// 状態をノーマルに戻す
			m_state = STATE_NORMAL;
		}
	}

#ifdef _DEBUG
	// デバッグ用死亡コマンド
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_NUMPAD1))
	{
		if (m_nPlayerNum == 0)
		{
			Hit(999);
		}
	}
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_NUMPAD2))
	{
		if (m_nPlayerNum == 1)
		{
			Hit(999);
		}
	}
#endif // _DEBUG

}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	if (m_state == STATE_DAMAGE)
	{// ダメージ状態の時

		// すべてのパーツを赤色にする
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			D3DXMATERIAL*pMat = (D3DXMATERIAL*)GetModelData()[nCnt].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)GetModelData()[nCnt].nNumMat; nCntMat++)
			{
				pMat[nCntMat].MatD3D.Diffuse = DAMAGE_STATE_COLOR;
			}
		}
	}

    CModelHierarchy::Draw();

	for (int nCount = 0; nCount < m_nLife; nCount++)
	{
		if (m_pLife[nCount] != NULL)
		{
			m_pLife[nCount]->Draw();
		}
	}
}

//******************************
// 移動操作(キーボード)
//******************************
void CPlayer::MoveKeyboard(void)
{
    // 移動処理
    // ジョイスティックの取得
    DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

    if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
    {// ↑移動

		// 移動中にする
		m_bKeyboardMove = true;

        m_moveDest.z = -PLAYER_SPEED - m_nSpeed;

        // 向きの設定
        m_fRotYDist = D3DXToRadian(0);

		// モーションの設定
		SetMotion(WALK);

        if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
        {
            // 向きの設定
            m_fRotYDist = D3DXToRadian(-45);

            m_moveDest.z = sinf(45) * -PLAYER_SPEED - m_nSpeed;
            m_moveDest.x = cosf(45) * PLAYER_SPEED + m_nSpeed;
        }
        if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
        {
            // 向きの設定
            m_fRotYDist = D3DXToRadian(45);

            m_moveDest.z = sinf(45) * -PLAYER_SPEED - m_nSpeed;
            m_moveDest.x = cosf(45) * -PLAYER_SPEED - m_nSpeed;
        }
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
    {// ↓移動
	   
	    // 移動中にする
		m_bKeyboardMove = true;

		m_moveDest.z = PLAYER_SPEED + m_nSpeed;

        // 向きの設定
        m_fRotYDist  = D3DXToRadian(180);
       
		// モーションの設定
		SetMotion(WALK);

        if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
        {
            // 向きの設定
            m_fRotYDist = D3DXToRadian(225);

            m_moveDest.z = sinf(45) * PLAYER_SPEED + m_nSpeed;
            m_moveDest.x = cosf(45) * PLAYER_SPEED + m_nSpeed;
        }
        if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
        {
            // 向きの設定
            m_fRotYDist = D3DXToRadian(135);

            m_moveDest.z = sinf(45) * PLAYER_SPEED + m_nSpeed;
            m_moveDest.x = cosf(45) * -PLAYER_SPEED - m_nSpeed;
        }
    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
    {// ←移動
     
	    // 移動中にする
		m_bKeyboardMove = true;
        // 向きの設定
        m_fRotYDist = D3DXToRadian(-90);

        m_moveDest.x = PLAYER_SPEED + m_nSpeed;

		// モーションの設定
		SetMotion(WALK);

    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
    {// →移動
     
	   // 移動中にする
		m_bKeyboardMove = true;

        // 向きの設定
        m_fRotYDist = D3DXToRadian(90);

        m_moveDest.x = -PLAYER_SPEED - m_nSpeed;

		// モーションの設定
		SetMotion(WALK);
    }
	else
	{
		// 移動状態の解除
		m_bKeyboardMove = false;
	}

	//ダッシュ処理
	if (CManager::GetKeyboard()->GetKeyPress(DIK_LSHIFT))
	{
		m_nSpeed = PLAYER_SPEED_MAX;
	}
	else
	{
		m_nSpeed = 0;
	}
}

//******************************
// 移動操作(コントローラー)
//******************************
void CPlayer::MoveController(void)
{
    // ジョイスティックの情報の取得
    DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);

    // スティックがどれくらい倒されているかでスピードの調整
    float fSpeedX = 0.0f;
    float fSpeedZ = 0.0f;
    if (js.lX < 0)
    {
        fSpeedX = 0 - js.lX;
    }
    else if (js.lX > 0)
    {
        fSpeedX = js.lX - 0;
    }

    if (js.lY < 0)
    {
        fSpeedZ = 0 - js.lY;
    }

    else if (js.lY > 0)
    {
        fSpeedZ = js.lY - 0;
    }

    // スティックが倒されている角度
    float fAngle = atan2f(js.lY, js.lX);
    // スティックが一定以上倒されているとき
    if (js.lX >= 10 || js.lX <= -10 || js.lY >= 10 || js.lY <= -10)
    {
        // 移動量の目標値
        m_moveDest.x = cosf(fAngle) * -fSpeedX / 50.0f;
        m_moveDest.z = sinf(fAngle) * fSpeedZ / 50.0f;
        // 向きの設定
        m_fRotYDist = atan2f(js.lX, -js.lY);

		// モーションの設定
		SetMotion(WALK);

    }
	else
	{
		if (!m_bKeyboardMove)
		{
			// モーションの設定
			SetMotion(WAIT);
		}
	}
}

//******************************
// キャラクターの向きの設定
//******************************
void CPlayer::Direction(void)
{
    // 現在のロットの取得
    D3DXVECTOR3 rot = GetRot();

    // グルんと回転しないよう調整
    while (m_fRotYDist - rot.y > D3DXToRadian(180))
    {
        m_fRotYDist -= D3DXToRadian(360);
    }
    while (m_fRotYDist - rot.y < D3DXToRadian(-180))
    {
        m_fRotYDist += D3DXToRadian(360);
    }

    // 向きの更新
    rot.y += (m_fRotYDist - rot.y)*PLAYER_DIRECTION_RATE;
    // 向きの設定
    SetRot(rot);
}

//******************************
// 攻撃操作
//******************************
void CPlayer::Attack(void)
{
	//サウンドのポインタ変数宣言
	CSound*pSound = CManager::GetSound();


	if (!m_bMotion || m_motionState == DASH)
	{// ダッシュからすぐパンチできるように

		if (m_nPlayerNum == 1 && CManager::GetKeyboard()->GetKeyTrigger(DIK_B) || CManager::GetJoypad()->GetJoystickTrigger(0, m_nPlayerNum))
		{// 弾を撃つ
		 // プレイヤーの向いている方向の取得
			float fRotY = GetRot().y - D3DXToRadian(90);
			// 弾を撃つ位置の調整
			D3DXVECTOR3 pos = GetPos();
			pos.x = pos.x + cosf(fRotY)*-SCRATCH_SIZE_PLAYER;
			pos.y = pos.y + SCRATCH_HEIGHT;
			pos.z = pos.z + sinf(fRotY) * SCRATCH_SIZE_PLAYER;

			// ひっかきの生成
			CScratch::Create(pos, fRotY, CScratch::SCRATCHUSER_PLAYER, m_nPlayerNum);

			pSound->Play(CSound::SOUND_SE_PL_ATTACK_NAIL);
			// モーションステートの設定
			SetMotion(PUNCH);

			// 攻撃フラグを立てる
			m_bMotion = true;
		}
	}
	if (!m_bMotion)
	{// 攻撃中じゃないとき

		if (m_nPlayerNum == 1&& CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE) || CManager::GetJoypad()->GetJoystickTrigger(2, m_nPlayerNum))
		{// 弾を撃つ
			
			pSound->Play(CSound::SOUND_SE_PL_ATTACK_BREATH);
		    // モーションステートの設定
			SetMotion(VOICE);

			// 攻撃フラグを立てる
			m_bMotion = true;
		}
	}
	else
	{
		if (m_motionState == VOICE&& m_pMotion[VOICE]->GetKey() == 2 && m_pMotion[VOICE]->GetFrame() == 0)
		{// モーションのキーフレームが2の時

			D3DXVECTOR3 bulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			// ジョイスティックの取得
			DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);
			if (js.lX > 10 || js.lX < -10 || js.lX>10 || js.lX < -10)
			{
				// 移動量

				bulletMove.x = cosf(atan2f(js.lY, js.lX))*-BULLET_SPEED_PLAYER;
				bulletMove.y = 0.0f;
				bulletMove.z = sinf(atan2f(js.lY, js.lX))*BULLET_SPEED_PLAYER;

				m_fRotYDist = atan2f(js.lX, -js.lY);
			}
			else
			{
				// プレイヤーの向いている方向の取得
				float fRotY = GetRot().y - D3DXToRadian(90);
				// 移動量
				
				bulletMove.x = cosf(fRotY)*-BULLET_SPEED_PLAYER;
				bulletMove.y = 0.0f;
				bulletMove.z = sinf(fRotY)*BULLET_SPEED_PLAYER;
			}

			// 弾を撃つ位置の調整
			D3DXVECTOR3 pos = GetPos();
			pos.y += 10.0f;
			// 弾の生成
			CBullet::Create(pos, bulletMove, 70, CBullet::BULLETUSER_PLAYER)->SetRot(GetRot());
		}
	}
}

//******************************
// 体力設定
//******************************
void CPlayer::Life(int nLife)
{
	//ライフが最大値以下だった場合
	if (m_nLife <= PLAYER_LIFE)
	{
		m_nLife += nLife;
		//超えてしまった場合
		if (m_nLife >= PLAYER_LIFE)
		{
			//マックスを代入
			m_nLife = PLAYER_LIFE;
		}
	}
}

//******************************
// ダメージ判定
//******************************
void CPlayer::Hit(int nDamage)
{

	//サウンドのポインタ変数宣言
	CSound*pSound = CManager::GetSound();

	if (CGame::GetGameMode() == CGame::GAME_NORMAL || ((CBoss*)GetTop(OBJTYPE_BOSS))->GetMotion() != CBoss::SPAWN)
	{
		if (m_state == STATE_NORMAL)
		{
			// SE
			CManager::GetSound()->Play(CSound::SOUND_SE_PL_DAMAGE);
			m_nLife -= nDamage;
			m_state = STATE_DAMAGE;
		}
	}

	if (m_nLife <= 0)
	{
		pSound->Play(CSound::SOUND_SE_PL_DAMAGE);
		m_bDeath[m_nPlayerNum] = true;
		Uninit();
		if (m_bDeath[0] == true && m_bDeath[1] == true)
		{
			CManager::GetFade()->SetFade(CManager::MODE_LOSE);
		}
		return;
	}
}

//******************************
// モーション管理関数
//******************************
void CPlayer::MotionManager(void)
{
	if (m_bMotion)
	{// 攻撃フラグが立ってるとき
		if (!m_pMotion[VOICE]->GetActiveAnimation() && !m_pMotion[PUNCH]->GetActiveAnimation() && !m_pMotion[DASH]->GetActiveAnimation())
		{// 攻撃モーションがfalseの時
			m_motionState = WAIT;
			m_bMotion = false;
		}
	}
}

//******************************
// モーションをすべてfalseにする
//******************************
void CPlayer::MotionFalse(void)
{
	// アニメーションをすべてfalseにする
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_pMotion[nCntAnim]->SetActiveAnimation(false);
	}
}

//******************************
// モーションセット
//******************************
void CPlayer::SetMotion(MOTION motionState)
{
	m_motionState = motionState;

	if (!m_pMotion[m_motionState]->GetActiveAnimation())
	{// 現在のモーションがfalseのとき
	 // モーションの初期化
		MotionFalse();
		// 現在のモーションをtrueにする
		m_pMotion[m_motionState]->SetActiveAnimation(true);
	}
}

//******************************
// ダッシュの処理
//******************************
void CPlayer::Dash(void)
{
	//サウンドのポインタ変数宣言
	CSound*pSound = CManager::GetSound();

	if (m_motionState != DASH)
	{// モーションがダッシュ状態じゃないとき
		if (m_nPlayerNum == 1 && CManager::GetKeyboard()->GetKeyTrigger(DIK_LSHIFT) || CManager::GetJoypad()->GetJoystickTrigger(5, m_nPlayerNum))
		{// ダッシュ
			pSound->Play(CSound::SOUND_SE_PL_DASH);
			// モーションフラグをtrue
			m_bMotion = true;
			// モーションセット
			SetMotion(DASH);
			// SE
			CManager::GetSound()->Play(CSound::SOUND_SE_PL_DASH);
		}
	}
	else
	{// モーションがダッシュ状態の時

		DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);

		D3DXVECTOR3 move;
		if (js.lX > 10.0f || js.lX<-10.0f || js.lY>10.0f || js.lY < -10.0f)
		{
			move.x = cosf(atan2f(js.lY, js.lX))*-PLAYER_DASH_SPEED;
			move.y = 0.0f;
			move.z = sinf(atan2f(js.lY, js.lX))*PLAYER_DASH_SPEED;
			// 向きの設定
			m_fRotYDist = atan2f(js.lX, -js.lY);
		}
		else
		{
			
			move.x = cosf(GetRot().y + D3DXToRadian(-90))*-PLAYER_DASH_SPEED;
			move.y = 0.0f;
			move.z = sinf(GetRot().y + D3DXToRadian(-90))*PLAYER_DASH_SPEED;
		}

		// 座標
		D3DXVECTOR3 pos = GetPos();

		// 移動量を足す
		pos += move;

		// 座標のセット
		SetPos(pos);
	}
}

