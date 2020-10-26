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
//*****************************
// マクロ定義
//*****************************
#define WALL_1_TEXTURE_PATH		"./data/Textures/wall000.jpg"		 // フローリングのテクスチャのパス
#define WALL_2_TEXTURE_PATH		"./data/Textures/particle001.png"	 // まっとのテクスチャのパス
#define WALL_3_TEXTURE_PATH		"./data/Textures/particle001.png"    // キッチンの床のテクスチャのパス

//==================================
// コンストラクタ
//==================================
LPDIRECT3DTEXTURE9 CWall::m_apTexture[WALL_MAX] = {};

//==================================
// コンストラクタ
//==================================
CWall::CWall():CScene3d(OBJTYPE_WALL)
{
	m_type   =   WALL_1;			// 床の種類の初期化
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
CWall * CWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, WALL type)
{
	//インスタンスを生成
	CWall *pWall = new CWall;
	//NULLチェック
	if (pWall != NULL)
	{
		//それぞれの初期化処理
		pWall->m_pos = pos;
		pWall->m_size = size;
		pWall->Init();
		pWall->m_type = type;
		pWall->SetPos(pos);
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
	D3DXCreateTextureFromFile(pDevice, WALL_1_TEXTURE_PATH, &m_apTexture[WALL_1]);
	D3DXCreateTextureFromFile(pDevice, WALL_2_TEXTURE_PATH, &m_apTexture[WALL_2]);
	D3DXCreateTextureFromFile(pDevice, WALL_3_TEXTURE_PATH, &m_apTexture[WALL_3]);

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
	CScene3d::Init();
	CScene3d::BindTexture(m_apTexture[m_type]);
	// 壁よりちょっと大きめに当たり判定をとる
	D3DXVECTOR3 collisionSize = m_size + D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	// 当たり判定の生成
	m_pCollision = CCollision::CreateBox(m_pos , collisionSize *2);
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CWall::Uninit(void)
{
	CScene3d::Uninit();
}

//==================================
// 更新処理
//==================================
void CWall::Update(void)
{
	CollisionPlayer();
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
	if (CCollision::CollisionSphereToBox(CGame::GetPlayer()->GetCollision(), m_pCollision))
	{
		// プレイヤー座標の取得
		D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();
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
		playerPos = shortrectPos + playerPos * CGame::GetPlayer()->GetCollision()->GetCollisionRadius();
		// プレイヤー座標のセット
		CGame::GetPlayer()->SetPos(playerPos);
		// プレイヤーのコリジョンの座標のセット
		CGame::GetPlayer()->GetCollision()->SetPos(playerPos);
	}
}
