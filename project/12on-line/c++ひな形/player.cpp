////////////////////////////////////////////////////
//
//    playerクラスの処理[player.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "joypad.h"
#include "bullet.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //モデルのパス
#define PLAYER_SPEED 10
#define PLAYER_MOVE_RATE 0.05f

//*****************************
// 静的メンバ変数宣言
//*****************************
LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CPlayer::m_nNumMatModel = 0;	    //マテリアル情報の数

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//******************************
// デストラクタ
//******************************
CPlayer::~CPlayer()
{
}

//******************************
// クリエイト
//******************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	// メモリの確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

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
HRESULT CPlayer::Load(void)
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
void CPlayer::Unload(void)
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
HRESULT CPlayer::Init(void)
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
void CPlayer::Uninit(void)
{

	CModel::Uninit();
}

//******************************
// 更新処理
//******************************
void CPlayer::Update(void)
{
	// 移動
	Move();
	// 攻撃
	Attack();
}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	CModel::Draw();
}

//******************************
// 移動操作
//******************************
void CPlayer::Move(void)
{
	// 移動処理
	// 座標
	D3DXVECTOR3 pos = GetPos();
	//移動量の目標値
	D3DXVECTOR3 moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ジョイスティックの取得
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

	if (CManager::GetKeyboard()->GetKeyPress(DIK_W) || js.lY <= -600)
	{// ↑移動
		moveDest.z = -PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * -PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S) || js.lY >= 600)
	{// ↓移動

		moveDest.z = PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
		{
			moveDest.z = sinf(45) * PLAYER_SPEED;
			moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_A) || js.lX <= -600)
	{// ←移動
		moveDest.x = PLAYER_SPEED;

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_D) || js.lX >= 600)
	{// →移動
		moveDest.x = -PLAYER_SPEED;
	}

	// 慣性
	m_move += (moveDest - m_move) * PLAYER_MOVE_RATE;
	
	// 移動量を足す
	pos += m_move;

	// 座標のセット
	SetPos(pos);

}

//******************************
// 攻撃操作
//******************************
void CPlayer::Attack(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE))
	{// 弾を撃つ
		// プレイヤーの向いている方向の取得
		float fRotY = GetRot().y /*+ D3DXToRadian(90)*/;
		// 移動量
		D3DXVECTOR3 bulletMove;
		bulletMove.x = cosf(fRotY)*BULLET_SPEED_PLAYER;
		bulletMove.y = 0;
		bulletMove.z = sinf(fRotY)*BULLET_SPEED_PLAYER;
		// 弾の生成
		CBullet::Create(GetPos(), bulletMove, 300, CBullet::BULLETUSER_PLAYER)->
			SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}
