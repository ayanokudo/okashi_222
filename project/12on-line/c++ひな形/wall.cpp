//===================================================
//
//    壁の処理[wall.cpp]
//    Author:筒井　俊稀
//
//====================================================
//**********************************
//インクルード
//**********************************
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "boss.h"

//*****************************
// マクロ定義
//*****************************
#define WALL_1_TEXTURE_PATH		"./data/Textures/w.png"		 // フローリングのテクスチャのパス
#define WALL_2_TEXTURE_PATH		"./data/Textures/wall_right.png"	 // まっとのテクスチャのパス
#define WALL_3_TEXTURE_PATH		"./data/Textures/wall_left.png"    // キッチンの床のテクスチャのパス

//==================================
// コンストラクタ
//==================================
LPDIRECT3DTEXTURE9 CWall::m_apTexture[WALL_MAX] = {};

//==================================
// コンストラクタ
//==================================
CWall::CWall():CScene3d(OBJTYPE_WALL)
{
	m_type   =   WALL_NORMAL;			// 床の種類の初期化
	m_pos    =	{ 0.0f,0.0f,0.0f };	// posの初期化
	m_posold =	{ 0.0f,0.0f,0.0f };	// 前の位置の初期化
	m_size   =	{ 0.0f,0.0f,0.0f };	// sizeの初期化
}

//==================================
// デストラクタ
//==================================
CWall::~CWall()
{
}

//==================================
// 生成処理
//==================================
CWall * CWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, WALL type)
{
	//インスタンスを生成
	CWall *pWall = new CWall;
	//NULLチェック
	if (pWall != NULL)
	{
		//それぞれの初期化処理
		pWall->m_pos = pos;
        pWall->m_rot = rot;
		pWall->m_size = size;
		pWall->m_type = type;
		pWall->Init();
		pWall->SetPos(pos);
        pWall->SetRot(rot);
		pWall->SetSize(size);
		pWall->SetObjType(OBJTYPE_WALL);
	}
	//ポインタを返す
	return pWall;
}

//==================================
// テクスチャロード処理
//==================================
HRESULT CWall::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, WALL_1_TEXTURE_PATH, &m_apTexture[WALL_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, WALL_2_TEXTURE_PATH, &m_apTexture[WALL_RIGHT]);
	D3DXCreateTextureFromFile(pDevice, WALL_3_TEXTURE_PATH, &m_apTexture[WALL_LEFT]);

	return S_OK;
}

//==================================
// テクスチャ破棄
//==================================
void CWall::Unload(void)
{
	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		// テクスチャの解放処理
		if (m_apTexture[nCntWall] != NULL)
		{
			m_apTexture[nCntWall]->Release();
			m_apTexture[nCntWall] = NULL;
		}
	}
}

//==================================
// 初期化処理
//==================================
HRESULT CWall::Init(void)
{
    if (m_type == 2)
    {
        int a = 0;
    }
	CScene3d::Init();
	CScene3d::BindTexture(m_apTexture[m_type]);
	// 壁よりちょっと大きめに当たり判定をとる
	D3DXVECTOR3 collisionSize = m_size + D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	if (m_rot.y == 0|| m_rot.y == D3DXToRadian(180))
	{
		// 当たり判定の生成
		m_pCollision = CCollision::CreateBox(m_pos, collisionSize * 2);
	}
	else
	{
		float fSize = collisionSize.x;
		collisionSize.x = collisionSize.z;
		collisionSize.z = fSize;
		// 当たり判定の生成
		m_pCollision = CCollision::CreateBox(m_pos, collisionSize * 2);
	}
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CWall::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}

	CScene3d::Uninit();
}

//==================================
// 更新処理
//==================================
void CWall::Update(void)
{
	// 当たり判定
	CollisionPlayer(); // プレイヤー
	CollisionEnemy();  // エネミー
	CollisionBoss();   // ボス
	CollisionBullet(); // 弾
}

//==================================
// 描画処理
//==================================
void CWall::Draw(void)
{
	CScene3d::Draw();
}

//==================================
// プレイヤーと壁の当たり判定
//==================================
void CWall::CollisionPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		CPlayer*pPlayer = CGame::GetPlayer(nCntPlayer);
		if (pPlayer != NULL)
		{
			if (!CPlayer::GetDeath(nCntPlayer))
			{
				if (CCollision::CollisionSphereToBox(pPlayer->GetCollision(), m_pCollision))
				{
					// プレイヤー座標の取得
					D3DXVECTOR3 playerPos = pPlayer->GetPos();
					// 当たり判定のサイズの取得
					D3DXVECTOR3 collsionSize = m_pCollision->GetCollisionSize();

					// ボックス内の最短地点の検索
					D3DXVECTOR3 shortrectPos;
					shortrectPos.x = CCollision::OnRange(playerPos.x, GetPos().x - collsionSize.x / 2, GetPos().x + collsionSize.x / 2);
					shortrectPos.y = CCollision::OnRange(playerPos.y, GetPos().y - collsionSize.y / 2, GetPos().y + collsionSize.y / 2);
					shortrectPos.z = CCollision::OnRange(playerPos.z, GetPos().z - collsionSize.z / 2, GetPos().z + collsionSize.z / 2);
					// ボックスからプレイヤーの方向ベクトル
					playerPos = playerPos - shortrectPos;
					// 正規化
					D3DXVec3Normalize(&playerPos, &playerPos);
					// 最短地点から当たり判定の半径分離す
					playerPos = shortrectPos + playerPos * pPlayer->GetCollision()->GetCollisionRadius();
					// プレイヤー座標のセット
					pPlayer->SetPos(playerPos);
					// プレイヤーのコリジョンの座標のセット
					pPlayer->GetCollision()->SetPos(playerPos);
				}
			}
		}
	}
}

//==================================
// エネミーと壁の当たり判定
//==================================
void CWall::CollisionEnemy(void)
{

	CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
	while (pEnemy != NULL)
	{
		if (CCollision::CollisionSphereToBox(pEnemy->GetCollision(), m_pCollision))
		{
			// プレイヤー座標の取得
			D3DXVECTOR3 playerPos = pEnemy->GetPos();
			// 当たり判定のサイズの取得
			D3DXVECTOR3 collsionSize = m_pCollision->GetCollisionSize();

			// ボックス内の最短地点の検索
			D3DXVECTOR3 shortrectPos;
			shortrectPos.x = CCollision::OnRange(playerPos.x, GetPos().x - collsionSize.x / 2, GetPos().x + collsionSize.x / 2);
			shortrectPos.y = CCollision::OnRange(playerPos.y, GetPos().y - collsionSize.y / 2, GetPos().y + collsionSize.y / 2);
			shortrectPos.z = CCollision::OnRange(playerPos.z, GetPos().z - collsionSize.z / 2, GetPos().z + collsionSize.z / 2);
			// ボックスからプレイヤーの方向ベクトル
			playerPos = playerPos - shortrectPos;
			// 正規化
			D3DXVec3Normalize(&playerPos, &playerPos);
			// 最短地点から当たり判定の半径分離す
			playerPos = shortrectPos + playerPos * pEnemy->GetCollision()->GetCollisionRadius();
			// プレイヤー座標のセット
			pEnemy->SetPos(playerPos);
			// プレイヤーのコリジョンの座標のセット
			pEnemy->GetCollision()->SetPos(playerPos);
		}
		pEnemy = (CEnemy*)pEnemy->GetNext();
	}

}

//==================================
// ボスと壁の当たり判定
//==================================
void CWall::CollisionBoss(void)
{

	CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);
	while (pBoss != NULL)
	{
		if (CCollision::CollisionSphereToBox(pBoss->GetCollision(), m_pCollision))
		{
			// プレイヤー座標の取得
			D3DXVECTOR3 bossPos = pBoss->GetPos();
			// 当たり判定のサイズの取得
			D3DXVECTOR3 collsionSize = m_pCollision->GetCollisionSize();

			// ボックス内の最短地点の検索
			D3DXVECTOR3 shortrectPos;
			shortrectPos.x = CCollision::OnRange(bossPos.x, GetPos().x - collsionSize.x / 2, GetPos().x + collsionSize.x / 2);
			shortrectPos.y = CCollision::OnRange(bossPos.y, GetPos().y - collsionSize.y / 2, GetPos().y + collsionSize.y / 2);
			shortrectPos.z = CCollision::OnRange(bossPos.z, GetPos().z - collsionSize.z / 2, GetPos().z + collsionSize.z / 2);
			// ボックスからプレイヤーの方向ベクトル
			bossPos = bossPos - shortrectPos;
			// 正規化
			D3DXVec3Normalize(&bossPos, &bossPos);
			// 最短地点から当たり判定の半径分離す
			bossPos = shortrectPos + bossPos * pBoss->GetCollision()->GetCollisionRadius();
			// プレイヤー座標のセット
			pBoss->SetPos(bossPos);
			// プレイヤーのコリジョンの座標のセット
			pBoss->GetCollision()->SetPos(bossPos);
		}
		pBoss = (CBoss*)pBoss->GetNext();
	}

}

//==================================
// 弾と壁の当たり判定
//==================================
void CWall::CollisionBullet(void)
{
	CBullet*pBullet = (CBullet*)CScene::GetTop(OBJTYPE_BULLET);
	while (pBullet != NULL)
	{
		if (!pBullet->GetReleaseFlag())
		{
			// 元の半径を保持
			float fRadius = pBullet->GetCollision()->GetCollisionRadius();
			// 半径を半分にする
			pBullet->GetCollision()->SetCollisionRadius(fRadius / 2);
			if (CCollision::CollisionSphereToBox(pBullet->GetCollision(), m_pCollision))
			{
				// プレイヤーのコリジョンの座標のセット
				pBullet->Uninit();
			}
			else
			{
				// 元の半径に戻す
				pBullet->GetCollision()->SetCollisionRadius(fRadius);
			}
		}
		pBullet = (CBullet*)pBullet->GetNext();
	}

}
