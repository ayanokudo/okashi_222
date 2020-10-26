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

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //モデルのパス

//*****************************
// 静的メンバ変数宣言
//*****************************
LPD3DXMESH   CItem::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CItem::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CItem::m_nNumMatModel = 0;	    //マテリアル情報の数

//******************************
// コンストラクタ
//******************************
CItem::CItem() :CModel(OBJTYPE_PLAYER)
{
	m_pCollision = NULL;
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
CItem * CItem::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CItem *pItem;
	pItem = new CItem;

	// 初期化
	pItem->Init();

	// 各値の代入・セット
	pItem->SetPos(pos);
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
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CItem::Unload(void)
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
HRESULT CItem::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindModel(m_pMeshModel, m_pBuffMatModel, m_nNumMatModel);
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
}

//******************************
// 描画処理
//******************************
void CItem::Draw(void)
{
	CModel::Draw();
}