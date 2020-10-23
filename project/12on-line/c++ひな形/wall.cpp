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

//*****************************
// マクロ定義
//*****************************
#define WALL_1_TEXTURE_PATH "./data/Textures/floor000.png"    //フローリングのテクスチャのパス
#define WALL_2_TEXTURE_PATH		"./data/Textures/particle001.png"	 //まっとのテクスチャのパス
#define WALL_3_TEXTURE_PATH  "./data/Textures/particle001.png"    //キッチンの床のテクスチャのパス

//==================================
// コンストラクタ
//==================================
LPDIRECT3DTEXTURE9 CWall::m_apTexture[WALL_MAX] = {};

//==================================
// コンストラクタ
//==================================
CWall::CWall():CScene3d(OBJTYPE_WALL)
{
	m_type = WALL_1;	//床の種類の初期化
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

}

//==================================
// 描画処理
//==================================
void CWall::Draw(void)
{
	CScene3d::Draw();
}
