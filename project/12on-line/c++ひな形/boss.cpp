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

//*****************************
// マクロ定義
//*****************************
#define BOSS_CARRIER_MODEL_PATH	"./data/Models/cube.x"	//運びネズミのモデル情報
#define ENEMY_SPEED 5
#define ENEMY_MOVE_RATE 0.05f
#define ENEMY_RADIUS  100
#define ENEMY_RANGE_RADIUS 600
#define ENEMY_DIRECTION_RATE 0.1f              // 向きを変えるときの係数

#define ATTACK_BASE 200             // 攻撃するタイミングのベース値

//*****************************
// 静的メンバ変数宣言
//*****************************
LPD3DXMESH   CBoss::m_pMeshModel = {};   	//メッシュ情報へのポインタ
LPD3DXBUFFER CBoss::m_pBuffMatModel = {};	//マテリアル情報へのポインタ
DWORD        CBoss::m_nNumMatModel = {};	//マテリアル情報の数

//******************************
// コンストラクタ
//******************************
CBoss::CBoss() :CModel(OBJTYPE_ENEMY)
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
CBoss::~CBoss()
{

}

//******************************
// クリエイト
//******************************
CBoss * CBoss::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CBoss *pEnemy;
	pEnemy = new CBoss;

	if (pEnemy != NULL)
	{
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
HRESULT CBoss::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	//運びネズミ
	D3DXLoadMeshFromX(BOSS_CARRIER_MODEL_PATH,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CBoss::Unload(void)
{
	//メッシュの破棄
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CBoss::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);

	m_pCollision = CCollision::CreateSphere(GetPos(), ENEMY_RADIUS);

	m_pRadiusColision = CCollision::CreateSphere(GetPos(), ENEMY_RANGE_RADIUS);
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

	CModel::Uninit();
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
}

//******************************
// 描画処理
//******************************
void CBoss::Draw(void)
{
	CModel::Draw();
}

//******************************
// ヒット処理
//******************************
void CBoss::Hit(int nDamage)
{

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
