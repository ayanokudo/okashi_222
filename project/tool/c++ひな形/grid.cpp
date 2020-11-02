//===================================================
//
//    グリッドの処理[grid.cpp]
//    Author:筒井　俊稀
//
//====================================================
//**********************************
//インクルード
//**********************************
#include "grid.h"
#include "manager.h"
#include "renderer.h"

//*****************************
// マクロ定義
//*****************************
#define FLOOR_FLOORING_TEXTURE_PATH "./data/Textures/check.png"    //フローリングのテクスチャのパス
#define FLOOR_MAT_TEXTURE_PATH		"./data/Textures/check.png"	   //まっとのテクスチャのパス
#define FLOOR_KITCHEN_TEXTURE_PATH  "./data/Textures/check.png"    //キッチンの床のテクスチャのパス

//==================================
// コンストラクタ
//==================================
LPDIRECT3DTEXTURE9 CGrid::m_apTexture[FLOOR_MAX] = {};
D3DXVECTOR2 CGrid::m_UV[NUM_VERTEX] = {
    { 0.0f * MAX_GRID / 2 ,0.0f * MAX_GRID / 2 },
    { 1.0f * MAX_GRID / 2 ,0.0f * MAX_GRID / 2 },
    { 0.0f * MAX_GRID / 2 ,1.0f * MAX_GRID / 2 },
    { 1.0f * MAX_GRID / 2 ,1.0f * MAX_GRID / 2 }
};
//==================================
// コンストラクタ
//==================================
CGrid::CGrid()
{
	m_type = FLOOR_FLOORING;	//床の種類の初期化
}

//==================================
// デストラクタ
//==================================
CGrid::~CGrid()
{
}

//==================================
// 生成処理
//==================================
CGrid * CGrid::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type)
{
	//CGridのポインタ作成
	CGrid *pFloor;
	//インスタンスを生成
	pFloor = new CGrid;
	//NULLチェック
	if (pFloor != NULL)
	{
		//それぞれの初期化処理
		pFloor->Init();
		pFloor->m_type = type;
		pFloor->SetPos(pos);
		pFloor->SetSize(size);
		pFloor->SetObjType(OBJTYPE_MAP);
	}
	//ポインタを返す
	return pFloor;
}

//==================================
// テクスチャロード処理
//==================================
HRESULT CGrid::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, FLOOR_FLOORING_TEXTURE_PATH, &m_apTexture[FLOOR_FLOORING]);
	D3DXCreateTextureFromFile(pDevice, FLOOR_MAT_TEXTURE_PATH,		&m_apTexture[FLOOR_MAT]);
	D3DXCreateTextureFromFile(pDevice, FLOOR_KITCHEN_TEXTURE_PATH,  &m_apTexture[FLOOR_KITCHEN]);

	return S_OK;
}

//==================================
// テクスチャ破棄
//==================================
void CGrid::Unload(void)
{
	for (int nCntFloor = 0; nCntFloor < FLOOR_MAX; nCntFloor++)
	{
		// テクスチャの解放処理
		if (m_apTexture[nCntFloor] != NULL)
		{
			m_apTexture[nCntFloor]->Release();
			m_apTexture[nCntFloor] = NULL;
		}
	}
}

//==================================
// 初期化処理
//==================================
HRESULT CGrid::Init(void)
{
	CScene3d::Init();
    SetTextureUV(m_UV);
	CScene3d::BindTexture(m_apTexture[m_type]);
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CGrid::Uninit(void)
{
	CScene3d::Uninit();
}

//==================================
// 更新処理
//==================================
void CGrid::Update(void)
{
}

//==================================
// 描画処理
//==================================
void CGrid::Draw(void)
{
	CScene3d::Draw();
}
