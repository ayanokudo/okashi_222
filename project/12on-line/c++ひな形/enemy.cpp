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

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/cube.x"    //モデルのパス
#define ENEMY_SPEED 10
#define ENEMY_MOVE_RATE 0.05f

//*****************************
// 静的メンバ変数宣言
//*****************************
LPD3DXMESH   CEnemy::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CEnemy::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CEnemy::m_nNumMatModel = 0;	    //マテリアル情報の数

//******************************
// コンストラクタ
//******************************
CEnemy::CEnemy()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
CEnemy * CEnemy::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CEnemy *pPlayer;
	pPlayer = new CEnemy;

	// 初期化
	pPlayer->Init();
	pPlayer->SetPos(pos);
	// 各値の代入・セット
	pPlayer->SetObjType(OBJTYPE_MAP); // オブジェクトタイプ

	return pPlayer;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CEnemy::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_PATH,
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
void CEnemy::Unload(void)
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
HRESULT CEnemy::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CEnemy::Uninit(void)
{

	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CEnemy::Update(void)
{
	D3DXVECTOR3 rot = GetRot();

	SetRot(rot);
}

//******************************
// 描画処理
//******************************
void CEnemy::Draw(void)
{
	CModel::Draw();
}
