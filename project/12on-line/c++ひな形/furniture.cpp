//===================================================
//
//    壁の処理[wall.cpp]
//    Author:筒井　俊稀
//
//====================================================
//**********************************
//インクルード
//**********************************
#include "furniture.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "boss.h"

//==================================
// コンストラクタ
//==================================
LPDIRECT3DTEXTURE9 CFurniture::m_apTexture[FURNITURE_MAX] = {};
CModel::Model CFurniture::m_model[FURNITURE_MAX] = {};
char *CFurniture::m_apTextureName[FURNITURE_MAX] = 
{
    "./data/Models/furniture/ueki.x",
    "./data/Models/furniture/ueki.x",
    "./data/Models/furniture/ueki.x"
};

//==================================
// コンストラクタ
//==================================
CFurniture::CFurniture() :CModel(OBJTYPE_FURNITURE)
{
	m_type = FURNITURE_CHAIR;		// 床の種類の初期化
	m_pos = { 0.0f,0.0f,0.0f };		// posの初期化
	m_posold = { 0.0f,0.0f,0.0f };	// 前の位置の初期化
	m_size = { 0.0f,0.0f,0.0f };	// sizeの初期化
}

//==================================
// デストラクタ
//==================================
CFurniture::~CFurniture()
{
}

//==================================
// 生成処理
//==================================
CFurniture * CFurniture::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, FURNITURE type)
{
	//インスタンスを生成
	CFurniture *pWall = new CFurniture;
	//NULLチェック
	if (pWall != NULL)
	{
		//それぞれの初期化処理
		pWall->m_pos = pos;
		pWall->m_rot = rot;
		pWall->m_size = size;
		pWall->Init();
		pWall->m_type = type;
		pWall->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));
		pWall->SetRot(rot);
		//pWall->SetSize(size);
		pWall->SetObjType(OBJTYPE_FURNITURE);
	}
	//ポインタを返す
	return pWall;
}

//==================================
// テクスチャロード処理
//==================================
HRESULT CFurniture::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    for (int nCount = 0; nCount < FURNITURE_MAX; nCount++)
    {
	// Xファイルの読み込み
	D3DXLoadMeshFromX(m_apTextureName[nCount],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_model[nCount].pBuffMat,
		NULL,
		&m_model[nCount].nNumMat,
		&m_model[nCount].pMesh);
    }

	
	return S_OK;
}

//==================================
// テクスチャ破棄
//==================================
void CFurniture::Unload(void)
{
    for (int nCntType = 0; nCntType < FURNITURE_MAX; nCntType++)
    {
        //メッシュの破棄
        if (m_model[nCntType].pMesh != NULL)
        {
            m_model[nCntType].pMesh->Release();
            m_model[nCntType].pMesh = NULL;
        }
        //マテリアルの破棄
        if (m_model[nCntType].pBuffMat != NULL)
        {
            m_model[nCntType].pBuffMat->Release();
            m_model[nCntType].pBuffMat = NULL;
        }
    }
}

//==================================
// 初期化処理
//==================================
HRESULT CFurniture::Init(void)
{
	CModel::Init();
	CModel::BindModel(m_model[m_type].pMesh,m_model[m_type].pBuffMat,m_model[m_type].nNumMat);
	// 壁よりちょっと大きめに当たり判定をとる
	D3DXVECTOR3 collisionSize = m_size + D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	if (m_rot.y == 0)
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
void CFurniture::Uninit(void)
{
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}

	CModel::Uninit();
}

//==================================
// 更新処理
//==================================
void CFurniture::Update(void)
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
void CFurniture::Draw(void)
{
	CModel::Draw();
}

//==================================
// プレイヤーと壁の当たり判定
//==================================
void CFurniture::CollisionPlayer(void)
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
void CFurniture::CollisionEnemy(void)
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
void CFurniture::CollisionBoss(void)
{

	CBoss*pBoss = (CBoss*)CScene::GetTop(OBJTYPE_BOSS);
	while (pBoss != NULL)
	{
		if (CCollision::CollisionSphereToBox(pBoss->GetCollision(), m_pCollision))
		{
			// プレイヤー座標の取得
			D3DXVECTOR3 playerPos = pBoss->GetPos();
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
			playerPos = shortrectPos + playerPos * pBoss->GetCollision()->GetCollisionRadius();
			// プレイヤー座標のセット
			pBoss->SetPos(playerPos);
			// プレイヤーのコリジョンの座標のセット
			pBoss->GetCollision()->SetPos(playerPos);
		}
		pBoss = (CBoss*)pBoss->GetNext();
	}

}

//==================================
// 弾と壁の当たり判定
//==================================
void CFurniture::CollisionBullet(void)
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
