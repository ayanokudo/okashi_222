////////////////////////////////////////////////////
//
//    scratchクラスの処理[scratch.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "scratch.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "enemy.h"
#include "boss.h"

//*****************************
// マクロ定義
//*****************************
#define SCRATCH_TEXTURE_PATH_PLAYER "./data/Textures/scratch.png" //テクスチャのパス
#define SCRATCH_TEXTURE_PATH_ENEMY  "./data/Textures/Enemy_Attack.png" //テクスチャのパス
#define SCRATCH_COLOR D3DXCOLOR(1.0f,1.0f,0.3f,1.0f)       // アニメーション速度
#define SCRATCH_ANIM_SPEED 2                               // アニメーション速度
#define SCRATCH_MAX_ANIMATION_X 5                          // アニメーション数 横
#define SCRATCH_MAX_ANIMATION_Y 2                          // アニメーション数 縦
#define SCRATCH_ANIM_PATTERN 10                            // アニメーションのパターン数
#define SCRATCH_ATTACK_PLAYER 50							//プレイヤー攻撃力
#define SCRATCH_ATTACK_ENEMY 1								//エネミー攻撃力

//******************************
// 静的メンバ変数宣言
//******************************
LPDIRECT3DTEXTURE9  CScratch::m_apTexture[SCRATCHUSER_MAX] = {}; // テクスチャポインタ

//******************************
// コンストラクタ
//******************************
CScratch::CScratch() :CScene3d(OBJTYPE_ATTACK)
{
	// 変数のクリア
	m_user = SCRATCHUSER_PLAYER;
	m_pCollision = NULL;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
	m_bAttackPlayer = true;
	m_bAttackEnemy = true;
}

//******************************
// デストラクタ
//******************************
CScratch::~CScratch()
{
}

//******************************
// クリエイト
//******************************
CScratch * CScratch::Create(const D3DXVECTOR3 pos, const float fAngle,  const  SCRATCHUSER user,const int nPlayerNum)
{
	// メモリの確保
	CScratch *pScratch;
	pScratch = new CScratch;

	// ユーザーの設定
	pScratch->m_user = user;
	// 初期化
	pScratch->Init();

	// 各値の代入・セット
	pScratch->SetPos(pos);                             // 座標
	pScratch->SetRot(D3DXVECTOR3(0.0f, fAngle, 0.0f)); // 角度
	pScratch->SetObjType(OBJTYPE_ATTACK);              // オブジェクトタイプ
	
	pScratch->m_nPlayerNum = nPlayerNum;
	// 当たり判定の生成
	pScratch->m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(pos.x, pos.y-SCRATCH_HEIGHT, pos.z), SCRATCH_COLLISION_SIZE);

	return pScratch;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CScratch::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, SCRATCH_TEXTURE_PATH_PLAYER, &m_apTexture[SCRATCHUSER_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, SCRATCH_TEXTURE_PATH_ENEMY, &m_apTexture[SCRATCHUSER_ENEMY]);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CScratch::Unload(void)
{
	for (int nCnt = 0; nCnt < SCRATCHUSER_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CScratch::Init(void)
{
	if (FAILED(CScene3d::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindTexture(m_apTexture[m_user]);
	if (m_user == SCRATCHUSER_PLAYER)
	{
		// サイズの設定
		SetSize(D3DXVECTOR3(-SCRATCH_SIZE_PLAYER, 0.0f, -SCRATCH_SIZE_PLAYER));
	}
	else
	{
		// サイズの設定
		SetSize(D3DXVECTOR3(-SCRATCH_SIZE_ENEMY, 0.0f, -SCRATCH_SIZE_ENEMY));
	}

	// UV座標の設定
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
	float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX     , fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

	// UV座標セット
	SetTextureUV(uv);

	// カラーの設定
	SetColor(SCRATCH_COLOR);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CScratch::Uninit(void)
{
	// コリジョンの終了処理
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}

	CScene3d::Uninit();
}

//******************************
// 更新処理
//******************************
void CScratch::Update(void)
{
	// 当たり判定
	CollisionScratch(m_user);
	switch (m_user)
	{
	case SCRATCHUSER_ENEMY:
	{
		// プレイヤーの取得
		CEnemy*pEnemy = (CEnemy*)GetTop(OBJTYPE_ENEMY);
		while (pEnemy != NULL)
		{
			if (m_nPlayerNum == pEnemy->GetID())
			{
				// 座標の設定
				D3DXVECTOR3 pos;
				float fRotY = pEnemy->GetRot().y - D3DXToRadian(90);
				pos.x = pEnemy->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE_ENEMY;
				pos.y = pEnemy->GetPos().y + SCRATCH_HEIGHT;
				pos.z = pEnemy->GetPos().z + sinf(fRotY) * SCRATCH_SIZE_ENEMY;
				SetPos(pos);

				// 角度
				SetRot(D3DXVECTOR3(0.0f, fRotY + D3DXToRadian(90), 0.0f));
				m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
			}
			pEnemy = (CEnemy*)pEnemy->GetNext();
		}
		
	}
		break;
	case SCRATCHUSER_PLAYER:
	{
		// プレイヤーの取得
		CPlayer*pPlayer = CGame::GetPlayer(m_nPlayerNum);
		if (pPlayer != NULL)
		{
			// 座標の設定
			D3DXVECTOR3 pos;
			float fRotY = pPlayer->GetRot().y - D3DXToRadian(90);
			pos.x = pPlayer->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE_PLAYER;
			pos.y = pPlayer->GetPos().y + SCRATCH_HEIGHT;
			pos.z = pPlayer->GetPos().z + sinf(fRotY) * SCRATCH_SIZE_PLAYER;
			SetPos(pos);

			// 角度
			SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
			m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
		}
	}
	default:
		break;
	}
	// アニメーション*アニメーションが終了したら消える
	Animation();
}

//******************************
// 描画処理
//******************************
void CScratch::Draw(void)
{
	CScene3d::Draw();
}


//******************************
// 当たり判定
//******************************
void CScratch::CollisionScratch(SCRATCHUSER user)
{

	switch (user)
	{
	case SCRATCHUSER_ENEMY:
	{
		if (m_bAttackEnemy)
		{
			for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
			{
				CPlayer*pPlayer = CGame::GetPlayer(nCount);
				if (pPlayer != NULL)
				{
					if (!CPlayer::GetDeath(nCount))
					{
						if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
						{
							pPlayer->Hit(SCRATCH_ATTACK_ENEMY);
							m_bAttackEnemy = false;
							//Uninit();
							//break;
						}
					}
				}
			}
		}
		break;
	}
	case SCRATCHUSER_PLAYER:
	{
		if (m_bAttackPlayer)
		{
			CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
			CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);
			
			//敵全般
			while (pEnemy != NULL)
			{

				if (CCollision::CollisionSphere(m_pCollision, pEnemy->GetCollision()))
				{
					pEnemy->Hit(SCRATCH_ATTACK_PLAYER);
					m_bAttackPlayer = false;
					//Uninit();
					//break;
				}
				pEnemy = (CEnemy*)pEnemy->GetNext();
			}

			//ボス
			while (pBoss != NULL)
			{
				if (CCollision::CollisionSphere(m_pCollision, pBoss->GetCollision()))
				{
					pBoss->Hit(SCRATCH_ATTACK_PLAYER);
					m_bAttackPlayer = false;
					//Uninit();
					//
					break;
				}
				pBoss = (CBoss*)pBoss->GetNext();
			}

		}
	default:
		break;
	}
	}
}

//******************************
// アニメーション
//******************************
void CScratch::Animation(void)
{
	// アニメーションカウントを進める
	m_nCntAnim++;

	// アニメーションした数のカウント
	if (m_nCntAnim % SCRATCH_ANIM_SPEED == 0)
	{

		if (m_nCntAnim >= SCRATCH_ANIM_PATTERN*SCRATCH_ANIM_SPEED)
		{
			m_bAttackPlayer = true;
			m_bAttackEnemy = true;
			Uninit();
			return;
		}

		// アニメーションX軸の加算
		m_nAnimX++;

		if (m_nAnimX >= SCRATCH_MAX_ANIMATION_X)
		{
			// アニメーションX軸の初期化
			m_nAnimX = 0;
			m_nAnimY++;
		}

		// UV座標の設定
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
		float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

		// UV座標セット
		SetTextureUV(uv);
	}
}
