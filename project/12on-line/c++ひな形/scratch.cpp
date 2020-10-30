////////////////////////////////////////////////////
//
//    scratchクラスの処理[scratch.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "scratch.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "enemy.h"

//*****************************
// マクロ定義
//*****************************
#define SCRATCH_TEXTURE_PATH "./data/Textures/scratch.png" //テクスチャのパス
#define SCRATCH_COLOR D3DXCOLOR(1.0f,1.0f,0.3f,1.0f)       // アニメーション速度
#define SCRATCH_ANIM_SPEED 4                               // アニメーション速度
#define SCRATCH_MAX_ANIMATION_X 5                          // アニメーション数 横
#define SCRATCH_MAX_ANIMATION_Y 2                          // アニメーション数 縦
#define SCRATCH_ANIM_PATTERN 8                             // アニメーションのパターン数

//******************************
// 静的メンバ変数宣言
//******************************
LPDIRECT3DTEXTURE9  CScratch::m_pTexture = NULL; // テクスチャポインタ

//******************************
// コンストラクタ
//******************************
CScratch::CScratch() :CScene3d(OBJTYPE_ATTACK)
{
	// 変数のクリア
	m_user = SCRATCHUSER_PLAYER;
	m_pCollision = NULL;
	m_nCntAnim = 0;
	m_nAnimX = 0;
	m_nAnimY = 0;
}

//******************************
// デストラクタ
//******************************
CScratch::~CScratch()
{
}

//******************************
// クリエイト
//******************************
CScratch * CScratch::Create(const D3DXVECTOR3 pos, const float fAngle,  const  SCRATCHUSER user,const int nPlayerNum)
{
	// メモリの確保
	CScratch *pScratch;
	pScratch = new CScratch;
	// 初期化
	pScratch->Init();

	// 各値の代入・セット
	pScratch->SetPos(pos);                             // 座標
	pScratch->SetRot(D3DXVECTOR3(0.0f, fAngle, 0.0f)); // 角度
	pScratch->SetObjType(OBJTYPE_ATTACK);              // オブジェクトタイプ
	pScratch->m_user = user;                           // バレットユーザー
	pScratch->m_nPlayerNum = nPlayerNum;
	// 当たり判定の生成
	pScratch->m_pCollision = CCollision::CreateSphere(D3DXVECTOR3(pos.x, pos.y-SCRATCH_HEIGHT, pos.z), SCRATCH_COLLISION_SIZE);

	return pScratch;
}

//******************************
// テクスチャのロード
//******************************
HRESULT CScratch::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, SCRATCH_TEXTURE_PATH, &m_pTexture);


	return S_OK;
}

//******************************
// テクスチャのアンロード
//******************************
void CScratch::Unload(void)
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
HRESULT CScratch::Init(void)
{
	if (FAILED(CScene3d::Init()))
	{
		return E_FAIL;
	}

	// テクスチャ割り当て
	BindTexture(m_pTexture);
	// サイズの設定
	SetSize(D3DXVECTOR3(SCRATCH_SIZE, 0.0f, SCRATCH_SIZE));

	// UV座標の設定
	D3DXVECTOR2 uv[NUM_VERTEX];
	float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
	float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

	uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
	uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
	uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
	uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

	// UV座標セット
	SetTextureUV(uv);
	// 加算合成にする
	//SetAddMode(true);
	// カラーの設定
	SetColor(SCRATCH_COLOR);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CScratch::Uninit(void)
{
	// コリジョンの終了処理
	if (m_pCollision != NULL)
	{
		m_pCollision->Uninit();
	}

	CScene3d::Uninit();
}

//******************************
// 更新処理
//******************************
void CScratch::Update(void)
{
	// 当たり判定
	CollisionScratch(m_user);
	switch (m_user)
	{
	case SCRATCHUSER_ENEMY:
	{
		// プレイヤーの取得
		CEnemy*pEnemy = CGame::GetEnemy();
		if (pEnemy != NULL)
		{
			// 座標の設定
			D3DXVECTOR3 pos;
			float fRotY = pEnemy->GetRot().y - D3DXToRadian(90);
			pos.x = pEnemy->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE;
			pos.y = pEnemy->GetPos().y + SCRATCH_HEIGHT;
			pos.z = pEnemy->GetPos().z + sinf(fRotY) * SCRATCH_SIZE;
			SetPos(pos);

			// 角度
			SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
			m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
		}
	}
		break;
	case SCRATCHUSER_PLAYER:
	{
		// プレイヤーの取得
		CPlayer*pPlayer = CGame::GetPlayer(m_nPlayerNum);
		if (pPlayer != NULL)
		{
			// 座標の設定
			D3DXVECTOR3 pos;
			float fRotY = pPlayer->GetRot().y - D3DXToRadian(90);
			pos.x = pPlayer->GetPos().x + cosf(fRotY) * -SCRATCH_SIZE;
			pos.y = pPlayer->GetPos().y + SCRATCH_HEIGHT;
			pos.z = pPlayer->GetPos().z + sinf(fRotY) * SCRATCH_SIZE;
			SetPos(pos);

			// 角度
			SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));
			m_pCollision->SetPos(D3DXVECTOR3(pos.x, pos.y - SCRATCH_HEIGHT, pos.z));
		}
	}
	default:
		break;
	}
	// アニメーション*アニメーションが終了したら消える
	Animation();
}

//******************************
// 描画処理
//******************************
void CScratch::Draw(void)
{
	CScene3d::Draw();
}


//******************************
// 当たり判定
//******************************
void CScratch::CollisionScratch(SCRATCHUSER user)
{
	switch (user)
	{
	case SCRATCHUSER_ENEMY:
		break;
	case SCRATCHUSER_PLAYER:
	{
		CEnemy*pEnemy = (CEnemy*)CScene::GetTop(OBJTYPE_ENEMY);
		while (pEnemy != NULL)
		{

			if (CCollision::CollisionSphere(m_pCollision, pEnemy->GetCollision()))
			{
				pEnemy->Uninit();
				//Uninit();
				break;
			}
			pEnemy = (CEnemy*)pEnemy->GetNext();
		}
	}
	default:
		break;
	}
}

//******************************
// アニメーション
//******************************
void CScratch::Animation(void)
{
	// アニメーションカウントを進める
	m_nCntAnim++;

	// アニメーションした数のカウント
	if (m_nCntAnim % SCRATCH_ANIM_SPEED == 0)
	{

		if (m_nCntAnim >= SCRATCH_ANIM_PATTERN*SCRATCH_ANIM_SPEED)
		{
			Uninit();
			return;
		}

		// アニメーションX軸の加算
		m_nAnimX++;

		if (m_nAnimX >= SCRATCH_MAX_ANIMATION_X)
		{
			// アニメーションX軸の初期化
			m_nAnimX = 0;
			m_nAnimY++;
		}

		// UV座標の設定
		D3DXVECTOR2 uv[NUM_VERTEX];
		float fu = 1.0f / SCRATCH_MAX_ANIMATION_X;
		float fv = 1.0f / SCRATCH_MAX_ANIMATION_Y;

		uv[0] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY);
		uv[1] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY);
		uv[2] = D3DXVECTOR2(fu*m_nAnimX, fv*m_nAnimY + fv);
		uv[3] = D3DXVECTOR2(fu*m_nAnimX + fu, fv*m_nAnimY + fv);

		// UV座標セット
		SetTextureUV(uv);
	}
}
