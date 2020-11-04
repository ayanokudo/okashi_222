////////////////////////////////////////////////////
//
//    enemyクラスの処理[enemy.cpp]
//    Author:筒井　俊稀
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "scratch.h"
#include "motion.h"

//*****************************
// マクロ定義
//*****************************
#define ENEMY_CARRIER_MODEL_PATH	"./data/Texts/MouseData.txt"	//運びネズミのモデル情報
#define ENEMY_ESCORT_MODEL_PATH		"./data/Texts/MouseData.txt"	//守りネズミのモデル情報

#define WALK_ANIM_PATH  "data/Texts/nezumi_walk.txt"      // 歩きアニメーションのパス

#define ENEMY_SPEED 5
#define ENEMY_RAND rand() % 8 + 1
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  50
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_MOVE_RATE 0.05f 
#define ENEMY_DIRECTION_RATE 0.1f              // 向きを変えるときの係数
#define ENEMY_ESCORT_LIFE 100
#define ENEMY_CARRIER_LIFE 100

//*****************************
// 静的メンバ変数宣言
//*****************************
CModel::Model CEnemy::m_model[MAX_PLAYER][MAX_PARTS_NUM] = {};
int CEnemy::m_nNumModel = 0;
char CEnemy::m_achAnimPath[MOTION_MAX][64]
{
	{ WALK_ANIM_PATH },	   // 歩きアニメーション
};

//******************************
// コンストラクタ
//******************************
CEnemy::CEnemy() :CModelHierarchy(OBJTYPE_ENEMY)
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
}

//******************************
// デストラクタ
//******************************
CEnemy::~CEnemy()
{

}

//******************************
// クリエイト
//******************************
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, ENEMY type)
{
	// メモリの確保
	CEnemy *pEnemy;
	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		pEnemy->m_type = type;

		// 初期化
		pEnemy->Init();

		// 各値の代入・セット
		pEnemy->SetPos(pos);
		pEnemy->SetObjType(OBJTYPE_ENEMY); // オブジェクトタイプ
	}

	return pEnemy;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CEnemy::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_MAX; nCntEnemy++)
	{
		// ファイルオープン
		FILE*pFile = NULL;

		if (nCntEnemy == ENEMY_CARRIER)
		{// プレイヤー１
			pFile = fopen(ENEMY_CARRIER_MODEL_PATH, "r");

		}
		else
		{// プレイヤー２
			pFile = fopen(ENEMY_ESCORT_MODEL_PATH, "r");
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
					&m_model[nCntEnemy][nCnt].pBuffMat,
					NULL,
					&m_model[nCntEnemy][nCnt].nNumMat,
					&m_model[nCntEnemy][nCnt].pMesh);

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
void CEnemy::Unload(void)
{
	for (int nCntType = 0; nCntType < ENEMY_MAX; nCntType++)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			//メッシュの破棄
			if (m_model[nCntType][nCnt].pMesh != NULL)
			{
				m_model[nCntType][nCnt].pMesh->Release();
				m_model[nCntType][nCnt].pMesh = NULL;
			}
			//マテリアルの破棄
			if (m_model[nCntType][nCnt].pBuffMat != NULL)
			{
				m_model[nCntType][nCnt].pBuffMat->Release();
				m_model[nCntType][nCnt].pBuffMat = NULL;
			}
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CEnemy::Init(void)
{
	if (m_type == ENEMY_CARRIER)
	{// 運びネズミ
		if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[m_type][0], ENEMY_CARRIER_MODEL_PATH)))
		{
			return E_FAIL;
		}
	}
	else
	{// 守りネズミ
		if (FAILED(CModelHierarchy::Init(m_nNumModel, &m_model[m_type][0], ENEMY_ESCORT_MODEL_PATH)))
		{
			return E_FAIL;
		}
	}

	//ライフ設定
	switch (m_type)
	{
	case ENEMY_CARRIER:
		m_nLife = ENEMY_CARRIER_LIFE;
		break;

	case ENEMY_ESCORT:
		m_nLife = ENEMY_ESCORT_LIFE;
		break;
	}
	
	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);
	
	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);

	// アニメーションの生成
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
void CEnemy::Uninit(void)
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
void CEnemy::Update(void)
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

	//敵ごとの動きの処理分け
	switch (m_type)
	{
		//運びネズミ
	case ENEMY_CARRIER:
		RangeDecisionCarrier();
		MotionCarrier();
		break;
		//守りネズミ
	case ENEMY_ESCORT:
		RangeDecisionEscort();
		MotionEscort();
		break;
	}
	// 慣性
	m_move += (m_moveDest - m_move) * ENEMY_MOVE_RATE;

	// 移動量を足す
	pos += m_move;

	// 座標のセット
	SetPos(pos);
}

//******************************
// 描画処理
//******************************
void CEnemy::Draw(void)
{
	CModelHierarchy::Draw();
}

//******************************
// ヒット処理
//******************************
void CEnemy::Hit(int nDamage)
{

}

//******************************
// 運びネズミの範囲判定の更新処理
//******************************
void CEnemy::RangeDecisionCarrier(void)
{
	//プレイヤーの情報を取得
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			//プレイヤーの位置情報を取得
			D3DXVECTOR3 playerPos = pPlayer->GetPos();
			//エネミーの位置情報を取得
			D3DXVECTOR3 enemyPos = GetPos();
			//プレイヤーと敵の範囲の当たり判定
			if (CCollision::CollisionSphere(m_pRadiusColision, pPlayer->GetCollision()))
			{
				//エネミーの移動をしなくする
				m_bRd = true;
				//向きの設定
				m_fRotYDist = atan2((playerPos.x - enemyPos.x), (playerPos.z - enemyPos.z));

				// 移動量
				D3DXVECTOR3 Move;
				Move.x = sinf(m_fRotYDist)*10.0f;
				Move.y = 0.0f;
				Move.z = cosf(m_fRotYDist)*10.0f;

				m_moveDest -= Move;
				break;
			}
			else
			{
				m_bRd = false;
			}
		}
	}
}

//******************************
// 守りネズミの範囲判定の更新処理
//******************************
void CEnemy::RangeDecisionEscort(void)
{
	//プレイヤーの情報を取得
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			//プレイヤーの位置情報を取得
			D3DXVECTOR3 playerPos = pPlayer->GetPos();
			//エネミーの位置情報を取得
			D3DXVECTOR3 enemyPos = GetPos();


			//プレイヤーと敵の範囲の当たり判定
			if (CCollision::CollisionSphere(m_pRadiusColision, pPlayer->GetCollision()))
			{
				m_bRd = true;
				m_nCount++;
				m_nCntAttack++;
				//向きの設定
				m_fRotYDist = atan2((playerPos.x - enemyPos.x), (playerPos.z - enemyPos.z));

				// 移動量
				D3DXVECTOR3 Move;
				Move.x = sinf(m_fRotYDist)*10.0f;
				Move.y = 0.0f;
				Move.z = cosf(m_fRotYDist)*10.0f;

				m_moveDest = Move;
				//等間隔で打つ
				if (m_nCount == 50)
				{
					// 弾の生成
					CScratch::Create(enemyPos, m_fRotYDist, CScratch::SCRATCHUSER_ENEMY, -1);
					m_nCount = 0;
				}
				//弾の向きの設定
				m_fRotYDist = atan2(-(playerPos.x - enemyPos.x), -(playerPos.z - enemyPos.z));
				break;
			}
			else
			{
				//エネミーを再度動かす
				m_bRd = false;
			}
		}
	}
}

//******************************
// 運びネズミの動き更新処理
//******************************
void CEnemy::MotionCarrier(void)
{
	//falseの時
	if (!m_bRd)
	{
		//移動処理
		Move();
	}
}

//******************************
// 守りネズミの動き更新処理
//******************************
void CEnemy::MotionEscort(void)
{
	//falseの時
	if (!m_bRd)
	{
		//移動処理
		Move();
	}
}

//******************************
// 敵の移動処理
//******************************
void CEnemy::Move(void)
{
	//カウントプラス
	m_nCountMotion++;
	//50カウント言ったら乱数処理に入る
	if (m_nCountMotion == 50)
	{
		//乱数
		m_nCountRand = ENEMY_RAND;
		m_nCountMotion = 0;
	}
	switch (m_nCountRand)
	{
	case 1:
		// ↓移動
		m_moveDest.z = ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(180);
		break;
	case 2:
		// ↑移動
		m_moveDest.z = -ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(0);
		break;
	case 3:
		// ←移動
		m_moveDest.x = ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(-90);
		break;
	case 4:
		// →移動
		m_moveDest.x = -ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(90);
		break;
	case 5:
		//　斜め
		m_moveDest.z = sinf(45) * -ENEMY_SPEED;
		m_moveDest.x = cosf(45) * ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(-45);
		break;
	case 6:
		//　斜め
		m_moveDest.z = sinf(45) * -ENEMY_SPEED;
		m_moveDest.x = cosf(45) * -ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(45);
		break;
	case 7:
		//　斜め
		m_moveDest.z = sinf(45) * ENEMY_SPEED;
		m_moveDest.x = cosf(45) * ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(225);
		break;
	case 8:
		//　斜め
		m_moveDest.z = sinf(45) * ENEMY_SPEED;
		m_moveDest.x = cosf(45) * -ENEMY_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(135);
		break;
	}
}

//******************************
// キャラクターの向きの設定
//******************************
void CEnemy::Direction(void)
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
