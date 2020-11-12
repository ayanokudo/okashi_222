////////////////////////////////////////////////////
//
//    enemyクラスの処理[enemy.cpp]
//    Author:筒井　俊稀
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "boss.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "motion.h"
#include "score.h"
#include "debug_log.h"
#include "scratch.h"
#include "player.h"
#include "fade.h"

//*****************************
// マクロ定義
//*****************************
#define BOSS_PATH	"./data/Texts/BossData.txt"	//運びネズミのモデル情報

#define WALK_PATH    "data/Texts/BossMotion/Boss_taiki.txt"             // 歩きモーションのパス
#define BREATH_PATH  "data/Texts/BossMotion/Boss_Attack_breath.txt"     // ブレスモーションのパス
#define SCRATH_PATH  "data/Texts/BossMotion/Boss_Attack_hikkaki.txt"    // ひっかきモーションのパス
#define TAIL_PATH    "data/Texts/BossMotion/Boss_Attack_kaiten.txt"     // しっぽモーションのパス

#define BOSS_SPEED 8
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  130
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_DIRECTION_RATE 0.1f   // 向きを変えるときの係数
#define TAIL_RADIUS 100             // しっぽの半径

#define ATTACK_PATTARN 3            // 攻撃パターン
#define ATTACK_BASE 200             // 攻撃するタイミングのベース値
#define BOSS_LIFE 2000              // ボスのライフ
#define BULLET_INTERVAL 15          // 弾のインターバル
#define BOSS_SCORE_UP 15000

#define MOVE_COUNT 100             // 移動時のカウント

//*****************************
// 静的メンバ変数宣言
//*****************************
//LPD3DXMESH   CBoss::m_pMeshModel = {};   	//メッシュ情報へのポインタ
//LPD3DXBUFFER CBoss::m_pBuffMatModel = {};	//マテリアル情報へのポインタ
//DWORD        CBoss::m_nNumMatModel = {};	//マテリアル情報の数
CModel::Model CBoss::m_model[MAX_PARTS_NUM] = {};
int CBoss::m_nNumModel = 0;
char CBoss::m_achAnimPath[MOTION_MAX][64]
{
	{ WALK_PATH },	  // 歩きモーション
	{ BREATH_PATH },  // ブレスモーション
	{ SCRATH_PATH },  // ひっかきモーション
	{ TAIL_PATH },	  // しっぽモーション
};

//******************************
// コンストラクタ
//******************************
CBoss::CBoss() :CModelHierarchy(OBJTYPE_BOSS)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pCollision = NULL;
	m_pRadiusColision = NULL;
	m_fRotYDist = 0.0f;
	m_nCount = 0;
	m_nCountMotion = 0;
	m_bRd = false;
	m_nLife = 0;
	memset(&m_pMotion, 0, sizeof(m_pMotion));
	m_motionState = WALK;
	m_bMotion = false;
	m_nCntBullet = 0;
	m_pCollisionTail = NULL;
	memset(m_bHitTail, 0, sizeof(m_bHitTail));
	m_nCntMove = 0;
	m_nTargetNum = 0;
}

//******************************
// デストラクタ
//******************************
CBoss::~CBoss()
{

}

//******************************
// クリエイト
//******************************
CBoss * CBoss::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CBoss *pBoss;
	pBoss = new CBoss;

	if (pBoss != NULL)
	{
		// 初期化
		pBoss->Init();

		// 各値の代入・セット
		pBoss->SetPos(pos);               // 座標
		pBoss->SetObjType(OBJTYPE_BOSS); // オブジェクトタイプ
	}

	return pBoss;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CBoss::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ファイルオープン
	FILE*pFile = NULL;

	pFile = fopen(BOSS_PATH, "r");

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
				&m_model[nCnt].pBuffMat,
				NULL,
				&m_model[nCnt].nNumMat,
				&m_model[nCnt].pMesh);

			// 次の文字を読み込む
			fscanf(pFile, "%s", chChar);
		}
	}

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CBoss::Unload(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		//メッシュの破棄
		if (m_model[nCnt].pMesh != NULL)
		{
			m_model[nCnt].pMesh->Release();
			m_model[nCnt].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_model[nCnt].pBuffMat != NULL)
		{
			m_model[nCnt].pBuffMat->Release();
			m_model[nCnt].pBuffMat = NULL;
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CBoss::Init(void)
{
	if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[0], BOSS_PATH)))
	{
		return E_FAIL;
	}

	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);

	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);

	m_pCollisionTail = CCollision::CreateSphere(GetPos(), TAIL_RADIUS);
	
	m_nLife = BOSS_LIFE;
	// モーションの生成
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_pMotion[nCntAnim] = CMotion::Create(GetPartsNum(), m_achAnimPath[nCntAnim], GetModelData());
	}
	// 初期モーションを歩きに
	SetMotion(WALK);
	// ターゲットの初期化
	ChangeTarget(1);

	// しっぽのヒット確認の初期化
	memset(m_bHitTail, 0, sizeof(m_bHitTail));
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CBoss::Uninit(void)
{
	// コリジョンの終了処理
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}
	if (m_pRadiusColision != NULL)
	{
		m_pRadiusColision->Uninit();
	}
	if (m_pCollisionTail != NULL)
	{
		m_pCollisionTail->Uninit();
	}

	CModelHierarchy::Uninit();
}

//******************************
// 更新処理
//******************************
void CBoss::Update(void)
{
	// コリジョンの位置更新
	m_pCollision->SetPos(GetPos());
	m_pRadiusColision->SetPos(GetPos());


	if (!m_bMotion)
	{
		// ターゲット管理
		ChangeTarget();
		// 移動処理
		Move();
	}
	// 向きの管理
	Direction();

	Scratch();
	// ブレス
	Brearh();

	// しっぽ
	Tail();
	
	// モーション管理
	MotionManager();
}

//******************************
// 描画処理
//******************************
void CBoss::Draw(void)
{
	CModelHierarchy::Draw();
}

//******************************
// ヒット処理
//******************************
void CBoss::Hit(int nDamage)
{
	m_nLife -= nDamage;

	if (m_nLife <= 0)
	{
		CScore::AddScore(BOSS_SCORE_UP);
		Uninit();
		CManager::GetFade()->SetFade(CManager::MODE_WIN);
		return;
	}
}

//******************************
// 移動処理
// Author : 増澤 未来
//******************************
void CBoss::Move(void)
{

	if (!CPlayer::GetDeath(0) || !CPlayer::GetDeath(1))
	{// どっちかのプレイヤーが生きているとき

		// 座標
		D3DXVECTOR3 pos = GetPos();

		// 目標値の初期化
		m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ターゲットのプレイヤー座標の設定
		D3DXVECTOR3 playerPos = CGame::GetPlayer(m_nTargetNum)->GetPos();

		// 移動量の計算
		m_moveDest = playerPos - pos;
		D3DXVec3Normalize(&m_moveDest, &m_moveDest);
		m_moveDest *= BOSS_SPEED;
		m_moveDest.y = 0.0f;

		// 慣性
		m_move += (m_moveDest - m_move) * ENEMY_MOVE_RATE;

		// 移動量を足す
		pos += m_move;

		m_fRotYDist = atan2f(m_move.x, m_move.z) + D3DXToRadian(180);
		// 座標のセット
		SetPos(pos);
	}

}

//******************************
// ターゲットを変える
// Author : 増澤 未来
//******************************
void CBoss::ChangeTarget(int nNum)
{

	if (!CPlayer::GetDeath(0) && CPlayer::GetDeath(1))
	{// プレイヤー0だけが生きているとき
		m_nTargetNum = 0;

		// カウントを進める
		m_nCntMove++;

		if (m_nCntMove%MOVE_COUNT == 0)
		{// 一定カウントで

			// 攻撃する
			Attack();
		}
	}
	else if (!CPlayer::GetDeath(1) && CPlayer::GetDeath(0))
	{// プレイヤー1だけが生きているとき
		m_nTargetNum = 1;


		// カウントを進める
		m_nCntMove++;

		if (m_nCntMove%MOVE_COUNT == 0)
		{// 一定カウントで

		 // 攻撃する
			Attack();
		}
	}
	else
	{// 両方生きているとき

		if (nNum == 1)
		{// 引数が一の時
		
			// ターゲットをランダムに変更
			m_nTargetNum = rand() % MAX_PLAYER;
			// カウントの初期化
			m_nCntMove = 0;
		}
		else
		{// 引数が一じゃないとき

			// カウントを進める
			m_nCntMove++;
		
			if (m_nCntMove%MOVE_COUNT == 0)
			{// 一定カウントで

				// ターゲットをランダムに変更
				m_nTargetNum = rand() % MAX_PLAYER;

				// 攻撃する
				Attack();
			}
		}
	}
}

//******************************
// キャラクターの向きの設定
//******************************
void CBoss::Direction(void)
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
	rot.y += (m_fRotYDist - rot.y)*ENEMY_DIRECTION_RATE;
	// 向きの設定
	SetRot(rot);
}

//=============================================================================
// 攻撃処理
// Author : 増澤 未来
//=============================================================================
void CBoss::Attack(void)
{
    // ランダムなタイミングで攻撃する
	int nRandAttack = rand() % ATTACK_PATTARN;

	switch (nRandAttack)
	{
	case ATTACK_BREARH:
		// ブレス
		SetMotion(BREARH);
		m_bMotion = true;
		break;
	case ATTACK_SCRATCH:
		// ひっかき
		SetMotion(SCRATCH);
		m_bMotion = true;
		break;
	case ATTACK_TAIL:
		// しっぽ
		SetMotion(TAIL);
		m_bMotion = true;
		break;
	default:
		break;
	}

}

//=============================================================================
// ブレス
// Author : 増澤 未来
//=============================================================================
void CBoss::Brearh(void)
{
	if (m_motionState == BREARH)
	{
		if (m_pMotion[BREARH]->GetKey() >= 3)
		{
			// カウントを進める
			m_nCntBullet++;

			if (m_nCntBullet%BULLET_INTERVAL == 0)
			{//一定の間隔で球を出す

				// 弾を出す方向
				float fAngle = GetModelData()[0].rot.y + GetModelData()[1].rot.y + GetRot().y - D3DXToRadian(90);
				// 弾の移動量
				D3DXVECTOR3 bulletMove;
				bulletMove.x = cosf(fAngle) * -BULLET_SPEED_ENEMY;
				bulletMove.y = 0.0f;
				bulletMove.z = sinf(fAngle) * BULLET_SPEED_ENEMY;
				CBullet::Create(GetPos(), bulletMove, 150, CBullet::BULLETUSER_ENEMY);
			}
		}
	}

}

//=============================================================================
// ひっかき
// Author : 増澤 未来
//=============================================================================]
void CBoss::Scratch(void)
{
	if (m_pMotion[SCRATCH]->GetKey() == 1 && m_pMotion[SCRATCH]->GetFrame() == 0)
	{
		CScratch::Create(GetPos(), 0.0f, CScratch::SCRATCHUSER_BOSS, GetID());
	}
}

//=============================================================================
// しっぽ攻撃
// Author : 増澤 未来
//=============================================================================
void CBoss::Tail(void)
{
	// しっぽの位置に当たり判定を置く
	// 角度の算出
	float fAngleTail = (GetModelData()[6].rot.y + GetModelData()[0].rot.y + GetRot().y) + D3DXToRadian(90);
	// 座標の算出
	D3DXVECTOR3 tailPos;
	tailPos.x = GetPos().x + cosf(fAngleTail)*-TAIL_RADIUS * 2;
	tailPos.y = GetPos().y;
	tailPos.z = GetPos().z + sinf(fAngleTail)*TAIL_RADIUS * 2;
	// 座標の設定
	m_pCollisionTail->SetPos(tailPos);

	// 攻撃の判定

	if (m_motionState == TAIL)
	{
		// 最初の数フレームは当たらないようにする
		if (m_pMotion[TAIL]->GetKey() >= 2)
		{
			// プレイヤー数分ループ
			for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
			{
				// プレイヤーの生存状態の確認
				if (!CPlayer::GetDeath(nCnt))
				{
					// プレイヤー情報の取得
					CPlayer*pPlayer = CGame::GetPlayer(nCnt);
					if (pPlayer != NULL)
					{
						if (CCollision::CollisionSphere(m_pCollisionTail, pPlayer->GetCollision()))
						{
							// 多段ヒットしないようフラグをかます
							if (!m_bHitTail[nCnt])
							{
								// ダメージ判定
								pPlayer->Hit(1);
								// しっぽを当たった状態に
								m_bHitTail[nCnt] = true;
							}
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// モーション管理
// Author : 増澤 未来
//=============================================================================
void CBoss::MotionManager(void)
{
	if (m_bMotion)
	{// 攻撃フラグが立ってるとき
		if (!m_pMotion[BREARH]->GetActiveAnimation() && !m_pMotion[SCRATCH]->GetActiveAnimation() && !m_pMotion[TAIL]->GetActiveAnimation())
		{// 攻撃モーションがfalseの時
			SetMotion(WALK);
			m_bMotion = false;
		}
	}
}

//=============================================================================
// モーションをすべてfalseにする
// Author : 増澤 未来
//=============================================================================
void CBoss::MotionFalse(void)
{
	// アニメーションをすべてfalseにする
	for (int nCntAnim = 0; nCntAnim < MOTION_MAX; nCntAnim++)
	{
		m_pMotion[nCntAnim]->SetActiveAnimation(false);
	}
}

//=============================================================================
// モーションセット
// Author : 増澤 未来
//=============================================================================
void CBoss::SetMotion(MOTION motionState)
{
	m_motionState = motionState;

	if (!m_pMotion[m_motionState]->GetActiveAnimation())
	{// 現在のモーションがfalseのとき
	 // モーションの初期化
		MotionFalse();
		// 現在のモーションをtrueにする
		m_pMotion[m_motionState]->SetActiveAnimation(true);

		if (motionState == TAIL)
		{
			// しっぽのヒット確認の初期化
			memset(m_bHitTail, 0, sizeof(m_bHitTail));
		}
	}
}
