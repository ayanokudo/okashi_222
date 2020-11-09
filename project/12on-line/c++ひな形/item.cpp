////////////////////////////////////////////////////
//
//    itemクラスの処理[item.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "bullet.h"
#include "scene3d.h"
#include "debug_log.h"
#include "collision.h"
#include "player.h"
#include "score.h"
#include "collect.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //モデルのパス
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //モデルのパス
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //モデルのパス
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //モデルのパス

#define CANDY_MAX 20

//*****************************
// 静的メンバ変数宣言
//*****************************
LPD3DXMESH   CItem::m_pMeshModel[ITEM_MAX] = {};   	//メッシュ情報へのポインタ
LPD3DXBUFFER CItem::m_pBuffMatModel[ITEM_MAX] = {};	//マテリアル情報へのポインタ
DWORD        CItem::m_nNumMatModel[ITEM_MAX] = {};	    //マテリアル情報の数

//******************************
// コンストラクタ
//******************************
CItem::CItem() :CModel(OBJTYPE_PLAYER)
{
	m_pCollision = NULL;
	m_type = CANDY;
	m_nCandy = 0;
	m_fRotYDist = 0.0f;
}

//******************************
// デストラクタ
//******************************
CItem::~CItem()
{
}

//******************************
// クリエイト
//******************************
CItem * CItem::Create(D3DXVECTOR3 pos, ITEM type)
{
	// メモリの確保
	CItem *pItem;
	pItem = new CItem;

	// 初期化
	pItem->Init();

	// 各値の代入・セット
	pItem->SetPos(pos);
	pItem->m_type = type;
	// 各値の代入・セット
	pItem->SetObjType(OBJTYPE_ITEM); // オブジェクトタイプ
	return pItem;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CItem::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[CANDY],
		NULL,
		&m_nNumMatModel[CANDY],
		&m_pMeshModel[CANDY]);

	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[KOBAN],
		NULL,
		&m_nNumMatModel[KOBAN],
		&m_pMeshModel[KOBAN]);

	D3DXLoadMeshFromX(MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel[LIFE],
		NULL,
		&m_nNumMatModel[LIFE],
		&m_pMeshModel[LIFE]);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CItem::Unload(void)
{
	//メッシュの破棄
	for (int nCount = 0; nCount < ITEM_MAX; nCount++)
	{
		if (m_pMeshModel[nCount] != NULL)
		{
			m_pMeshModel[nCount]->Release();
			m_pMeshModel[nCount] = NULL;
		}
		//マテリアルの破棄
		if (m_pBuffMatModel[nCount] != NULL)
		{
			m_pBuffMatModel[nCount]->Release();
			m_pBuffMatModel[nCount] = NULL;
		}
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CItem::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	for (int nCount = 0; nCount < ITEM_MAX; nCount++)
	{
		BindModel(m_pMeshModel[nCount], m_pBuffMatModel[nCount], m_nNumMatModel[nCount]);
	}

	m_nCandy = CANDY_MAX;
	// 当たり判定の生成
	m_pCollision = CCollision::CreateSphere(GetPos(), 100);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CItem::Uninit(void)
{
	// コリジョンの終了処理
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
		m_pCollision = NULL;
	}

	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CItem::Update(void)
{
	// 座標
	D3DXVECTOR3 pos = GetPos();

	// 座標のセット
	SetPos(pos);

	// 当たり判定の位置更新
	m_pCollision->SetPos(GetPos());

	Direction();

	CollisionItem();
}

//******************************
// 描画処理
//******************************
void CItem::Draw(void)
{
	CModel::Draw();
}

//******************************
// 向き
//******************************
void CItem::Direction(void)
{
	//int nCount = 0;
	//nCount++;
	//if (nCount <= 360)
	//{
	//	// 向きの設定
	//	m_fRotYDist = D3DXToRadian(nCount);
	//}
	//else
	//{
	//	nCount = 0;
	//}
}

//******************************
// 描画処理
//******************************
void CItem::CollisionItem(void)
{
	switch (m_type)
	{
		//キャンディ
	case CANDY:
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
					//プレイヤーと敵の範囲の当たり判定
					if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
					{
						m_nCandy--;
						
						// 回収率を増やす
						CCollect::Collect();

						Uninit();
						break;
					}
				}
			}
		}
		break;
		//コバン
	case KOBAN:
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
					//プレイヤーと敵の範囲の当たり判定
					if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
					{
						//小判処理
						CScore::AddScore(1000);
						Uninit();
						break;
					}
				}
			}
		}
		break;
		//回復
	case LIFE:
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
					//プレイヤーと敵の範囲の当たり判定
					if (CCollision::CollisionSphere(m_pCollision, pPlayer->GetCollision()))
					{
						Life();
						Uninit();
						break;
					}
				}
			}
		}
	default:
		break;
	}
}

//******************************
// 回復アイテム処理
//******************************
void CItem::Life(void)
{
	CPlayer*pPlayer = CGame::GetPlayer();

	pPlayer->Life(1);
}
