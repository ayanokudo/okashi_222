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
//*****************************
// マクロ定義
//*****************************
#define PLAYER_1_PATH "data/Texts/CatData_Milk.txt"              //モデルのパス
#define PLAYER_2_PATH "data/Texts/CatData_Choco.txt"              //モデルのパス

#define WAIT_ANIM_PATH  "data/Texts/NekoMotion/Wait.txt"      // 待機アニメーションのパス
#define WALK_ANIM_PATH  "data/Texts/NekoMotion/Walk.txt"      // 歩きアニメーションのパス
#define VOICE_ANIM_PATH "data/Texts/NekoMotion/Voice.txt"     // 鳴き声アニメーションのパス
#define PUNCH_ANIM_PATH "data/Texts/NekoMotion/Punch.txt"     // パンチアニメーションのパス
#define DASH_ANIM_PATH  "data/Texts/NekoMotion/Dash.txt"      // 走りアニメーションのパス

#define PLAYER_SPEED 20                          // 移動スピード
#define PLAYER_MOVE_RATE 0.2f                   // 移動の慣性の係数
#define PLAYER_DIRECTION_RATE 0.1f              // 向きを変えるときの係数
#define PLAYER_RADIUS 100						// プレイヤーの半径
#define PLAYER_1_LIFE 100						// プレイヤー１のライフ
#define PLAYER_2_LIFE 100						// プレイヤー２のライフ
#define PLAYER_SPEED_MAX 5


//*****************************
// 静的メンバ変数宣言
//*****************************
CModel::Model CPlayer::m_model[MAX_PLAYER][MAX_PARTS_NUM] = {};
int CPlayer::m_nNumModel = 0;
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
    m_nLife = 0;
	memset(&m_pMotion, 0, sizeof(m_pMotion));
	m_motionState = WAIT;
	m_nSpeed = 0;
	m_bAttack = false;
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
    pPlayer->SetPos(pos);
    pPlayer->SetObjType(OBJTYPE_PLAYER); // オブジェクトタイプ
    
    return pPlayer;
}

//******************************
// テクスチャのロード
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
// テクスチャのアンロード
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

    m_nLife = PLAYER_1_LIFE;

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

	// 当たり判定の生成
	m_pCollision = CCollision::CreateSphere(GetPos(), PLAYER_RADIUS);

	// 攻撃フラグの初期化
	m_bAttack = false;

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
    }

    CModelHierarchy::Uninit();
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	// 目標値の初期化
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (!m_bAttack)
	{// 攻撃中じゃないとき

		// 移動（キーボード）
		MoveKeyboard();

		// 移動（コントローラー）
		MoveController();

		// 慣性
		m_move += (m_moveDest - m_move) * PLAYER_MOVE_RATE;

		// 座標
		D3DXVECTOR3 pos = GetPos();

		// 移動量を足す
		pos += m_move;

		// 座標のセット
		SetPos(pos);
	}

	// 攻撃
	Attack();

	// 向きの管理
	Direction();

	// モーション管理
	MotionManager();

    // 当たり判定の位置更新
    m_pCollision->SetPos(GetPos());
}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
    CModelHierarchy::Draw();
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
     
        // 向きの設定
        m_fRotYDist = D3DXToRadian(-90);

        m_moveDest.x = PLAYER_SPEED + m_nSpeed;

		// モーションの設定
		SetMotion(WALK);

    }
    else if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
    {// →移動
     
        // 向きの設定
        m_fRotYDist = D3DXToRadian(90);

        m_moveDest.x = -PLAYER_SPEED - m_nSpeed;

		// モーションの設定
		SetMotion(WALK);
    }
	else
	{
		// モーションの設定
		//SetMotion(WAIT);
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
		// モーションの設定
		SetMotion(WAIT);
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
	if (!m_bAttack)
	{// 攻撃中じゃないとき

		if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE) || CManager::GetJoypad()->GetJoystickTrigger(2, m_nPlayerNum))
		{// 弾を撃つ
			//// プレイヤーの向いている方向の取得
			//float fRotY = GetRot().y - D3DXToRadian(90);
			//// 移動量
			//D3DXVECTOR3 bulletMove;
			//bulletMove.x = cosf(fRotY)*-BULLET_SPEED_PLAYER;
			//bulletMove.y = 0.0f;
			//bulletMove.z = sinf(fRotY)*BULLET_SPEED_PLAYER;
			//// 弾を撃つ位置の調整
			//D3DXVECTOR3 pos = GetPos();
			//pos.y += 10.0f;
			//// 弾の生成
			//CBullet::Create(pos, bulletMove, 300, CBullet::BULLETUSER_PLAYER);

			// モーションステートの設定
			SetMotion(VOICE);

			// 攻撃フラグを立てる
			m_bAttack = true;

		}

		if (CManager::GetKeyboard()->GetKeyTrigger(DIK_B) || CManager::GetJoypad()->GetJoystickTrigger(0, m_nPlayerNum))
		{// 弾を撃つ
			// プレイヤーの向いている方向の取得
			float fRotY = GetRot().y - D3DXToRadian(90);
			// 弾を撃つ位置の調整
			D3DXVECTOR3 pos = GetPos();
			pos.x = pos.x + cosf(fRotY)*-SCRATCH_SIZE;
			pos.y = pos.y + SCRATCH_HEIGHT;
			pos.z = pos.z + sinf(fRotY) * SCRATCH_SIZE;

			// ひっかきの生成
			CScratch::Create(pos, fRotY, CScratch::SCRATCHUSER_PLAYER, m_nPlayerNum);

			// モーションステートの設定
			SetMotion(PUNCH);

			// 攻撃フラグを立てる
			m_bAttack = true;
		}
	}
	else
	{
		if (m_pMotion[VOICE]->GetKey() == 2)
		{// モーションのキーフレームが2の時

			 // プレイヤーの向いている方向の取得
			float fRotY = GetRot().y - D3DXToRadian(90);
			// 移動量
			D3DXVECTOR3 bulletMove;
			bulletMove.x = cosf(fRotY)*-BULLET_SPEED_PLAYER;
			bulletMove.y = 0.0f;
			bulletMove.z = sinf(fRotY)*BULLET_SPEED_PLAYER;
			// 弾を撃つ位置の調整
			D3DXVECTOR3 pos = GetPos();
			pos.y += 10.0f;
			// 弾の生成
			CBullet::Create(pos, bulletMove, 300, CBullet::BULLETUSER_PLAYER);

			m_bAttack = false;
		}
	}
}

//******************************
// モーション管理関数
//******************************
void CPlayer::MotionManager(void)
{
	if (m_bAttack)
	{// 攻撃フラグが立ってるとき
		if (!m_pMotion[VOICE]->GetActiveAnimation() && !m_pMotion[PUNCH]->GetActiveAnimation())
		{// 攻撃モーションがfalseの時
			m_motionState = WAIT;
			m_bAttack = false;
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

