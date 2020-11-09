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
#include "debug_log.h"

//*****************************
// マクロ定義
//*****************************
#define BOSS_PATH	"./data/Texts/BossData.txt"	//運びネズミのモデル情報

#define WALK_PATH    "data/Texts/BossMotion/Boss_taiki.txt"             // 歩きモーションのパス
#define BREATH_PATH  "data/Texts/BossMotion/Boss_Attack_breath.txt"     // ブレスモーションのパス
#define SCRATH_PATH  "data/Texts/BossMotion/Boss_Attack_hikkaki.txt"    // ひっかきモーションのパス
#define TAIL_PATH    "data/Texts/BossMotion/Boss_Attack_kaiten.txt"     // しっぽモーションのパス

#define ENEMY_SPEED 5
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  100
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_DIRECTION_RATE 0.1f  // 向きを変えるときの係数
#define TAIL_RADIUS 50             // しっぽの半径

#define ATTACK_PATTARN 3            // 攻撃パターン
#define ATTACK_BASE 200             // 攻撃するタイミングのベース値
#define BOSS_LIFE 1500              // ボスのライフ
#define BULLET_INTERVAL 20          // 弾のインターバル

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
	
	m_pMotion[WALK]->SetActiveAnimation(true);

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

	CModelHierarchy::Uninit();
}

//******************************
// 更新処理
//******************************
void CBoss::Update(void)
{
	// 目標値の初期化
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 座標
	D3DXVECTOR3 pos = GetPos();

	// 向き
	D3DXVECTOR3 rot = GetRot();

	// 向きの設定
	SetRot(rot);

	// 向きの管理
	Direction();

	// コリジョンの位置更新
	m_pCollision->SetPos(GetPos());
	m_pRadiusColision->SetPos(GetPos());

	// 慣性
	m_move += (m_moveDest - m_move) * ENEMY_MOVE_RATE;

	// 移動量を足す
	pos += m_move;

	// 座標のセット
	SetPos(pos);


	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		SetMotion(BREARH);
		m_bMotion = true;
	}

	if (m_motionState == BREARH)
	{
		Brearh();
	}

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
		Uninit();
		return;
	}
}

////******************************
//// 敵の移動処理
////******************************


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
// Author : AYANO KUDO
//=============================================================================
void CBoss::Attack(void)
{
    // ランダムなタイミングで攻撃する
    if (rand() % ATTACK_BASE == 0)
    {
        // プレイヤーとの距離をを確認

    }

}

//=============================================================================
// ブレス
// Author : 増澤 未来
//=============================================================================
void CBoss::Brearh(void)
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
			CBullet::Create(GetPos(), bulletMove, 100, CBullet::BULLETUSER_ENEMY);
		}
	}

}

void CBoss::Tail(void)
{
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
	}
}
