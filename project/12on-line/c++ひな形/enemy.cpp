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
#include "particle.h"
#include "item.h"
#include "score.h"
#include "scene.h"
#include "particle.h"
#include "lostpoint.h"
#include "wall.h"
#include "sound.h"

//*****************************
// マクロ定義
//*****************************
#define ENEMY_CARRIER_MODEL_PATH	"./data/Texts/MouseData_Bule.txt"	//運びネズミのモデル情報
#define ENEMY_ESCORT_MODEL_PATH		"./data/Texts/MouseData_Red.txt"	//守りネズミのモデル情報

#define WALK_ANIM_PATH  "data/Texts/nezumi_walk.txt"      // 歩きアニメーションのパス

#define ENEMY_SPEED 10
#define ENEMY_RAND rand() % 8 + 1
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  80
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_MOVE_RATE 0.05f 
#define ENEMY_DIRECTION_RATE 0.1f              // 向きを変えるときの係数
#define ENEMY_ESCORT_LIFE 100
#define ENEMY_CARRIER_LIFE 200
#define ENEMY_UP_SCORE 1000

#define ITEM_DROP_RANDOM_KOBAN rand() % 10 + 1 == 5
#define ITEM_DROP_RANDOM_LIFE rand() % 6 + 1 == 4

//*****************************
// 静的メンバ変数宣言
//*****************************
CModel::Model CEnemy::m_model[ENEMY_MAX][MAX_PARTS_NUM] = {};
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
	m_bCarrier = false;
	m_nLife = 0;
	memset(&m_pMotion, 0, sizeof(m_pMotion));
	m_bRoute = false;
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, ENEMY type)
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
		//運びネズミ
	case ENEMY_CARRIER:
		m_nLife = ENEMY_CARRIER_LIFE;
		break;
		//守りネズミ
	case ENEMY_ESCORT:
		m_nLife = ENEMY_ESCORT_LIFE;
		break;
	}
	
	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);
	
	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);

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
	// 座標
	D3DXVECTOR3 pos = GetPos();
	m_nLife -= nDamage;

	if (m_nLife <= 0)
	{
		switch (m_type)
		{
		case ENEMY_CARRIER:
			//スコアUP
			CScore::AddScore(ENEMY_UP_SCORE);
			if (ITEM_DROP_RANDOM_KOBAN)
			{
				CItem::Create(pos, CItem::KOBAN);
			}
			else if (ITEM_DROP_RANDOM_LIFE)
			{
				CItem::Create(pos, CItem::LIFE);
			}
			break;
		case ENEMY_ESCORT:
			//スコアUP
			CScore::AddScore(ENEMY_UP_SCORE);
			if (ITEM_DROP_RANDOM_KOBAN)
			{
				CItem::Create(pos, CItem::KOBAN);
			}
			else if (ITEM_DROP_RANDOM_LIFE)
			{
				CItem::Create(pos, CItem::LIFE);
			}
		default:
			break;
		}

		for (int nCntPart = 0; nCntPart < 5; nCntPart++)
		{
			int nRandSize = rand() % 10 + 20;
			int nRandSpeed = rand() % 2 + 2;
			float fRandAngle = D3DXToRadian(rand() % 360);
			D3DXVECTOR3 partMove;
			partMove.x = cosf(fRandAngle)*nRandSpeed;
			partMove.y = 0.0f;
			partMove.z = sinf(fRandAngle)*nRandSpeed;
			CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y+20, GetPos().z), partMove, D3DXVECTOR3(nRandSize, nRandSize, 0.0f), 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		Uninit();
		return;
	}
}

//******************************
// 運びネズミの範囲判定の更新処理
//******************************
void CEnemy::RangeDecisionCarrier(void)
{

	// プレイヤーとの距離*初期値は適当に大きい値を入れとく
	float fDistance = 99999.0f;

	//プレイヤーの情報を取得
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			if (!CPlayer::GetDeath(nCount))
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
					m_bCarrier = true;
				}
			}
		}
	}
}

//******************************
// 守りネズミの範囲判定の更新処理
//******************************
void CEnemy::RangeDecisionEscort(void)
{
	//サウンドのポインタ変数宣言
	CSound*pSound = CManager::GetSound();
	// プレイヤーとの距離*初期値は適当に大きい値を入れとく
	float fDistance = 99999.0f;
	//プレイヤーの情報を取得
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCount);

		if (pPlayer != NULL)
		{
			if (!CPlayer::GetDeath(nCount))
			{
				//プレイヤーの位置情報を取得
				D3DXVECTOR3 playerPos = pPlayer->GetPos();
				//エネミーの位置情報を取得
				D3DXVECTOR3 enemyPos = GetPos();

				//プレイヤーと敵の範囲の当たり判定
				if (CCollision::CollisionSphere(m_pRadiusColision, pPlayer->GetCollision()))
				{
					// 距離を比べる
					if (sqrtf(powf(enemyPos.x - playerPos.x, 2) + powf(enemyPos.y - playerPos.y, 2) + powf(enemyPos.z - playerPos.z, 2)) <= fDistance)
					{// 距離が近かった時
						fDistance = sqrtf(powf(enemyPos.x - playerPos.x, 2) + powf(enemyPos.y - playerPos.y, 2) + powf(enemyPos.z - playerPos.z, 2));
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
							//pSound->Play(CSound::SOUND_SE_EN_ATTACK_NAIL);
							// 攻撃の生成
							CScratch::Create(enemyPos, m_fRotYDist + D3DXToRadian(90), CScratch::SCRATCHUSER_ENEMY,GetID());
							m_nCount = 0;
						}
						//弾の向きの設定
						m_fRotYDist = atan2(-(playerPos.x - enemyPos.x), -(playerPos.z - enemyPos.z));
					}
					//break;
				}	
			}

			if (!CPlayer::GetDeath(0) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(0)->GetCollision()) &&
				!CPlayer::GetDeath(1) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(1)->GetCollision()) ||
				!CPlayer::GetDeath(0) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(0)->GetCollision()) && CPlayer::GetDeath(1) ||
				!CPlayer::GetDeath(1) && !CCollision::CollisionSphere(m_pRadiusColision, CGame::GetPlayer(1)->GetCollision()) && CPlayer::GetDeath(0))
			{// どっちのプレイヤーにも当たってないとき
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
	// プレイヤーとの距離*初期値は適当に大きい値を入れとく
	float fDistance = 99999.0f;
	//falseの時
	if (!m_bRd)
	{
		//移動処理
		Move();
	}
	if (m_bCarrier)
	{
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			CPlayer*pPlayer = CGame::GetPlayer(nCount);
			if (pPlayer != NULL)
			{
			}
		}
		// 座用の取得
		D3DXVECTOR3 pos = GetPos();
		CGame::GetLostPoint()->sort(pos);

		if (!m_bRoute)
		{
			// 何番目に近い目標地点に行くか
			int nNumPoint = 0;
			// 目標座標の取得
			D3DXVECTOR3 distPos = CGame::GetLostPoint()->GetLostPos(nNumPoint);
			
			// 何回ループしたか
			int nLoop = 0;
			
			// プレイヤー最大数分ループ
			for (int nCnt = 0; nCnt < MAX_PLAYER; )
			{
				
				if (GetDistance(pos, distPos) > GetDistance(CGame::GetPlayer(nCnt)->GetPos(), distPos))
				{//自身よりプレイヤーのほうが近かった場合

					// カウントの初期化
					nCnt = 0;
					// 近い順を一つ増やす
					nNumPoint++;
					
					if (nNumPoint >= CGame::GetLostPoint()->GetNumLostPoint())
					{
						nNumPoint = 0;
					}

					// ループ数のカウント
					nLoop++;
					if (nLoop >= CGame::GetLostPoint()->GetNumLostPoint())
					{// 全部のポイントがプレイヤーより遠い
						nNumPoint = 0;
						// 目標地点の更新
						distPos = CGame::GetLostPoint()->GetLostPos(nNumPoint);
						break;
					}

					// 目標地点の更新
					distPos = CGame::GetLostPoint()->GetLostPos(nNumPoint);
					
				}
				else
				{
					// カウントを進める
					nCnt++;
				}
			}

			if (GetDistance(pos, distPos) >= 1000)
			{// 目標と一定距離以上の時
				// 壁との当たり判定
				CWall*pWall = (CWall*)GetTop(OBJTYPE_WALL);
				while (pWall != NULL)
				{
					if (CCollision::CollisionSphereToBox(m_pCollision, pWall->GetCollision()))
					{// 当たってた時
					 
						// 一回道の真ん中を経由して目標地点に行く
						m_bRoute = true;
					}

					pWall = (CWall*)pWall->GetNext();
				}
			}

			// 目標に向かって移動量の設定
			m_moveDest = distPos - pos;
			D3DXVec3Normalize(&m_moveDest, &m_moveDest);
			m_moveDest *= ENEMY_SPEED;
			
		}
		else
		{// 一回道の真ん中を経由して目標地点に行く
			// 目標座標の取得
			D3DXVECTOR3 distPos = CGame::GetLostPoint()->GetRoutePos(0);

			// 目標に向かって移動量の設定
			m_moveDest = distPos - pos;
			D3DXVec3Normalize(&m_moveDest, &m_moveDest);
			m_moveDest *= ENEMY_SPEED;

			// 当たり判定をの二分の一にする
			m_pCollision->SetCollisionRadius(m_pCollision->GetCollisionRadius() / 2);

			if (CCollision::CollisionSphere(m_pCollision, CGame::GetLostPoint()->GetRouteCollision(0)))
			{
				m_bRoute = false;
			}

			// 当たり判定を戻す
			m_pCollision->SetCollisionRadius(m_pCollision->GetCollisionRadius() * 2);
		}

		// 向きの目標値
		m_fRotYDist = atan2f(-m_moveDest.z, m_moveDest.x) - D3DXToRadian(90);

		if (CCollision::CollisionSphere(m_pCollision, CGame::GetLostPoint()->GetLostCollision(0)))
		{// ロストポイントに触れたときに消す

			// パーティクル生成
			for (int nCntPart= 0; nCntPart < 5; nCntPart++)
			{
				int nRandSize = rand() % 10 + 40;
				int nRandSpeed = rand() % 2 + 2;
				float fRandAngle = D3DXToRadian(rand() % 360);
				D3DXVECTOR3 partMove;
				partMove.x = cosf(fRandAngle)*nRandSpeed;
				partMove.y = 0.0f;
				partMove.z = sinf(fRandAngle)*nRandSpeed;
				CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 20, GetPos().z),
					partMove,
					D3DXVECTOR3(nRandSize, nRandSize, 0.0f),
					50,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					CParticle::PARTICLE_SMOKE);
			}
			// 消す
			Uninit();
		}
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
