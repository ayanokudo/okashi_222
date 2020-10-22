////////////////////////////////////////////////////
//
//    bulletクラスの処理[bullet.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "game.h"

//*****************************
// マクロ定義
//*****************************
#define BULLET_TEXTURE_PATH "./data/Textures/" //テクスチャのパス

//******************************
// 静的メンバ変数宣言
//******************************
LPDIRECT3DTEXTURE9  CBullet::m_pTexture = NULL; // テクスチャポインタ

//******************************
// コンストラクタ
//******************************
CBullet::CBullet()
{
	// 変数のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_user = BULLETUSER_PLAYER;
}

//******************************
// デストラクタ
//******************************
CBullet::~CBullet()
{
}

//******************************
// クリエイト
//******************************
CBullet * CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const  BULLETUSER user)
{
	// メモリの確保
	CBullet *pBullet;
	pBullet = new CBullet;
	// 初期化
	pBullet->Init();

	// 各値の代入・セット
	pBullet->SetPos(pos);                // 座標
	pBullet->SetObjType(OBJTYPE_BULLET); // オブジェクトタイプ
	pBullet->m_move = move;              // 移動量
	pBullet->m_nLife = nLife;            // 寿命
	pBullet->m_user = user;              // バレットユーザー

	return pBullet;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CBullet::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_PATH, &m_pTexture);


	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CBullet::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//******************************
// 初期化処理
//******************************
HRESULT CBullet::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindTexture(m_pTexture);
	// サイズの設定
	SetSize(D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f));

	return S_OK;
}

//******************************
// 終了処理
//******************************
void CBullet::Uninit(void)
{
	CBillboard::Uninit();
}

//******************************
// 更新処理
//******************************
void CBullet::Update(void)
{
	// 座標の取得
	D3DXVECTOR3 pos = GetPos();
	// 移動量のプラス
	pos += m_move;
	// 座標のセット
	SetPos(pos);

	// 寿命を減らす
	m_nLife--;
	if (m_nLife <= 0)
	{// 寿命が0以下になったとき
		// 消す
		Uninit();
	}

	// 当たり判定
	CollisionBullet(m_user);
}

//******************************
// 描画処理
//******************************
void CBullet::Draw(void)
{
	CBillboard::Draw();
}


//******************************
// 当たり判定
//******************************
void CBullet::CollisionBullet(BULLETUSER user)
{
}
