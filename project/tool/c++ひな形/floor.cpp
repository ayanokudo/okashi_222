//===================================================
//
//    床の処理[floor.cpp]
//    Author:筒井　俊稀
//
//====================================================
//**********************************
//インクルード
//**********************************
#include "floor.h"
#include "manager.h"
#include "renderer.h"

//*****************************
// マクロ定義
//*****************************
#define FLOOR_FLOORING_TEXTURE_PATH "./data/Textures/particle001.png"    //フローリングのテクスチャのパス
#define FLOOR_MAT_TEXTURE_PATH		"./data/Textures/particle001.png"	 //まっとのテクスチャのパス
#define FLOOR_KITCHEN_TEXTURE_PATH  "./data/Textures/particle001.png"    //キッチンの床のテクスチャのパス

//==================================
// コンストラクタ
//==================================
LPDIRECT3DTEXTURE9 CFloor::m_apTexture[FLOOR_MAX] = {};

//==================================
// コンストラクタ
//==================================
CFloor::CFloor()
{
	m_type = FLOOR_FLOORING;	//床の種類の初期化
}

//==================================
// デストラクタ
//==================================
CFloor::~CFloor()
{
}

//==================================
// 生成処理
//==================================
CFloor * CFloor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, FLOOR type)
{
	//CFloorのポインタ作成
	CFloor *pFloor;
	//インスタンスを生成
	pFloor = new CFloor;
	//NULLチェック
	if (pFloor != NULL)
	{
		//それぞれの初期化処理
		pFloor->Init();
		pFloor->m_type = type;
		pFloor->SetPos(pos);
		pFloor->SetSize(size);
		pFloor->SetObjType(OBJTYPE_FLOOR);
	}
	//ポインタを返す
	return pFloor;
}

//==================================
// テクスチャロード処理
//==================================
HRESULT CFloor::Load(void)
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
void CFloor::Unload(void)
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
HRESULT CFloor::Init(void)
{
	CScene3d::Init();
	CScene3d::BindTexture(m_apTexture[m_type]);
	return S_OK;
}

//==================================
// 終了処理
//==================================
void CFloor::Uninit(void)
{
	CScene3d::Uninit();
}

//==================================
// 更新処理
//==================================
void CFloor::Update(void)
{
}

//==================================
// 描画処理
//==================================
void CFloor::Draw(void)
{
	CScene3d::Draw();
}
