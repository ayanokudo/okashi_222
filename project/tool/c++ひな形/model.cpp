//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MODEL_RADIUS (50.0f)        // モデルの当たり判定

//=============================================================================
//モデルクラスのコンストラクタ
//=============================================================================
CModel::CModel(int nPriority) :CScene(nPriority)
{
	// 変数のクリア
	m_pBuffMatModel = NULL;
	m_pMeshModel = NULL;
	m_nNumMatModel = 0;
	m_pos = {0.0f,0.0f,0.0f};
	m_rot = {0.0f,0.0f,0.0f};
    m_pCollision = NULL;
}

//=============================================================================
//モデルクラスのデストラクタ
//=============================================================================
CModel::~CModel()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos)
{
	//モデルクラスのポインタ変数
	CModel *pModel = NULL;

	//メモリ確保
	pModel = new CModel(OBJTYPE_NONE);

	//メモリが確保できていたら
	if (pModel != NULL)
	{
		//初期化処理呼び出し
		pModel->m_pos = pos;
		pModel->Init();
	}
	//メモリ確保に失敗したとき
	else
	{
		return NULL;
	}

	return pModel;
}

//=============================================================================
//モデルクラスの初期化処理
//=============================================================================
HRESULT CModel::Init()
{
	//向きの初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_pCollision = CCollision::CreateSphere(m_pos, MODEL_RADIUS);
	return S_OK;
}

//=============================================================================
//モデルクラスの終了処理
//=============================================================================
void CModel::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//=============================================================================
//モデルクラスの更新処理
//=============================================================================
void CModel::Update(void)
{
    // 当たり判定の位置更新
    m_pCollision->SetPos(m_pos);
}

//=============================================================================
//モデルクラスの描画処理
//=============================================================================
void CModel::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;  	//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorldModel, &m_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldModel);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		m_pMeshModel->DrawSubset(nCntMat);
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
//モデルクラスのメッシュ情報の取得
//=============================================================================
LPD3DXMESH CModel::GetMesh(void) const
{
	return m_pMeshModel;
}

//=============================================================================
//モデルクラスの位置情報の設定
//=============================================================================
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

}

//=============================================================================
//モデルクラスの位置情報の取得
//=============================================================================
D3DXVECTOR3 CModel::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//モデルクラスの向きの設定
//=============================================================================
void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//モデルクラスの向きの取得
//=============================================================================
D3DXVECTOR3 CModel::GetRot(void) const
{
	return m_rot;
}

//=============================================================================
// モデルの割り当て
//=============================================================================
void CModel::BindModel(LPD3DXMESH pMeshModel, LPD3DXBUFFER pBuffMatModel, DWORD nNumMatModel)
{
	m_pMeshModel = pMeshModel;
	m_pBuffMatModel = pBuffMatModel;
	m_nNumMatModel = nNumMatModel;
}
