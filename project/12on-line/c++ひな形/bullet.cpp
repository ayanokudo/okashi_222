////////////////////////////////////////////////////
//
//    bulletクラスの処理[bullet.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "bullet.h"
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
#define BULLET_TEXTURE_PATH_PLAYER "./data/Textures/Catvoice_Barrett.png" //テクスチャのパス
#define BULLET_TEXTURE_PATH_ENEMY  "./data/Textures/MouseBoss_Voice.png" //テクスチャのパス
#define PLAYER_BULLET_DAMAGE 100				//プレイヤーの攻撃力
#define ENEMY_BULLET_DAMAGE 1
#define BULLET_SIZE_PLAYER 100                  // サイズ
#define BULLET_SIZE_ENEMY 70                    // サイズ
//******************************
// 静的メンバ変数宣言
//******************************
LPDIRECT3DTEXTURE9  CBullet::m_apTexture[BULLETUSER_MAX] = {}; // テクスチャポインタ

//******************************
// コンストラクタ
//******************************
CBullet::CBullet():CScene3d(OBJTYPE_BULLET)
{
	// 変数のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_user = BULLETUSER_PLAYER;
	m_pCollision = NULL;
}

//******************************
// デストラクタ
//******************************
CBullet::~CBullet()
{
}

//******************************
// クリエイト
//******************************
CBullet * CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const  BULLETUSER user)
{
	// メモリの確保
	CBullet *pBullet;
	pBullet = new CBullet;

	// バレットユーザーの設定
	pBullet->m_user = user;

	// 初期化
	pBullet->Init();

	// 各値の代入・セット
	pBullet->SetPos(pos);                // 座標
	pBullet->SetObjType(OBJTYPE_BULLET); // オブジェクトタイプ
	pBullet->m_move = move;              // 移動量
	pBullet->m_nLife = nLife;            // 寿命

	// 当たり判定の生成
	pBullet->m_pCollision = CCollision::CreateSphere(pos, BULLET_SIZE_PLAYER);
	return pBullet;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CBullet::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_PATH_PLAYER, &m_apTexture[BULLETUSER_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_PATH_ENEMY, &m_apTexture[BULLETUSER_ENEMY]);
	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CBullet::Unload(void)
{
	for (int nCnt = 0; nCnt < BULLETUSER_MAX; nCnt++)
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
HRESULT CBullet::Init(void)
{
	if (FAILED(CScene3d::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindTexture(m_apTexture[m_user]);

	switch (m_user)
	{
	case BULLETUSER_PLAYER:
		// サイズの設定
		SetSize(D3DXVECTOR3(BULLET_SIZE_PLAYER, 0.0f, BULLET_SIZE_PLAYER));
		break;
	case BULLETUSER_ENEMY:
		// サイズの設定
		SetSize(D3DXVECTOR3(BULLET_SIZE_ENEMY, 0.0f, BULLET_SIZE_ENEMY));
		break;
	default:
		break;
	}
	

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CBullet::Uninit(void)
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
void CBullet::Update(void)
{
	// 座標の取得
	D3DXVECTOR3 pos = GetPos();
	// 移動量のプラス
	pos += m_move;
	// 座標のセット
	SetPos(pos);

	// 当たり判定の位置更新
	m_pCollision->SetPos(GetPos());
	// 当たり判定
	CollisionBullet(m_user);

	// 寿命を減らす
	m_nLife--;
	if (m_nLife <= 0)
	{// 寿命が0以下になったとき
	 // 消す
		Uninit();
		return;
	}
	
}

//******************************
// 描画処理
//******************************
void CBullet::Draw(void)
{
	CScene3d::Draw();
}


//******************************
// 当たり判定
//******************************
void CBullet::CollisionBullet(BULLETUSER user)
{
	switch (user)
	{
	case BULLETUSER_ENEMY:
	{
		CPlayer*pPlayer = (CPlayer*)CScene::GetTop(OBJTYPE_PLAYER);

		while (pPlayer != NULL)
		{

			if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
			{
				pPlayer->Hit(ENEMY_BULLET_DAMAGE);
				Uninit();
				break;
			}

			pPlayer = (CPlayer*)pPlayer->GetNext();
		}
	}
		break;
	case BULLETUSER_PLAYER:
	{
		CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
		CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);

		//敵全般
		while (pEnemy != NULL)
		{

			if (CCollision::CollisionSphere(m_pCollision, pEnemy->GetCollision()))
			{
				pEnemy->Hit(PLAYER_BULLET_DAMAGE);
				Uninit();
				break;
			}
			pEnemy = (CEnemy*)pEnemy->GetNext();
		}

		//ボス
		while (pBoss != NULL)
		{
			if (CCollision::CollisionSphere(m_pCollision, pBoss->GetCollision()))
			{
				pBoss->Hit(PLAYER_BULLET_DAMAGE);
				Uninit();
				break;
			}
			pBoss = (CBoss*)pBoss->GetNext();
		}
	}
		break;
	default:
		break;
	}
}
