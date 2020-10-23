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
#include "scene3d.h"
#include "debug_log.h"
#include "collision.h"

//*****************************
// マクロ定義
//*****************************
#define MODEL_PATH "./data/Models/cat_sakamoto.x"    //モデルのパス
#define PLAYER_SPEED 10                          // 移動スピード
#define PLAYER_MOVE_RATE 0.05f                   // 移動の慣性の係数
#define PLAYER_DIRECTION_RATE 0.1f              // 向きを変えるときの係数
#define PLAYER_RADIUS 100                       // プレイヤーの半径
//*****************************
// 静的メンバ変数宣言
//*****************************
LPD3DXMESH   CPlayer::m_pMeshModel = NULL;   	//メッシュ情報へのポインタ
LPD3DXBUFFER CPlayer::m_pBuffMatModel = NULL;	//マテリアル情報へのポインタ
DWORD        CPlayer::m_nNumMatModel = 0;	    //マテリアル情報の数

//******************************
// コンストラクタ
//******************************
CPlayer::CPlayer():CModel(OBJTYPE_PLAYER)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotYDist = 0.0f;
	m_nPlayerNum = 0;
	m_pCollision = NULL;
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
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, int nPlayerNum)
{
	// メモリの確保
	CPlayer *pPlayer;
	pPlayer = new CPlayer;

	// 初期化
	pPlayer->Init();
	
	// 各値の代入・セット
	pPlayer->SetPos(pos);
	// 各値の代入・セット
	pPlayer->SetObjType(OBJTYPE_PLAYER); // オブジェクトタイプ
	pPlayer->m_nPlayerNum = nPlayerNum;
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
	// 当たり判定の生成
	m_pCollision = CCollision::CreateSphere(GetPos(), PLAYER_RADIUS);
	return S_OK;
}

//******************************
// 終了処理
//******************************
void CPlayer::Uninit(void)
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
void CPlayer::Update(void)
{
	// 目標値の初期化
	m_moveDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 移動（キーボード）
	MoveKeyboard();

	// 移動（コントローラー）
	MoveController();

	// 慣性
	m_move += (m_moveDest - m_move) * PLAYER_MOVE_RATE;

	// 座標
	D3DXVECTOR3 pos = GetPos();
	// 移動量を足す
	pos += m_move;

	// 座標のセット
	SetPos(pos);

	// 向きの管理
	Direction();
	// 攻撃
	Attack();

	// 当たり判定の位置更新
	m_pCollision->SetPos(GetPos());
}

//******************************
// 描画処理
//******************************
void CPlayer::Draw(void)
{
	CModel::Draw();
}

//******************************
// 移動操作(キーボード)
//******************************
void CPlayer::MoveKeyboard(void)
{
	// 移動処理

	// ジョイスティックの取得
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(0);

	if (CManager::GetKeyboard()->GetKeyPress(DIK_W))
	{// ↑移動
		m_moveDest.z = -PLAYER_SPEED;

		// 向きの設定
		m_fRotYDist = D3DXToRadian(0);

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
		{
			// 向きの設定
			m_fRotYDist = D3DXToRadian(-45);

			m_moveDest.z = sinf(45) * -PLAYER_SPEED;
			m_moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
		{
			// 向きの設定
			m_fRotYDist = D3DXToRadian(45);

			m_moveDest.z = sinf(45) * -PLAYER_SPEED;
			m_moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_S))
	{// ↓移動
	
	    // 向きの設定
		m_fRotYDist = D3DXToRadian(180);
		m_moveDest.z = PLAYER_SPEED;

		if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
		{
			// 向きの設定
			m_fRotYDist = D3DXToRadian(225);

			m_moveDest.z = sinf(45) * PLAYER_SPEED;
			m_moveDest.x = cosf(45) * PLAYER_SPEED;
		}
		if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
		{
			// 向きの設定
			m_fRotYDist = D3DXToRadian(135);

			m_moveDest.z = sinf(45) * PLAYER_SPEED;
			m_moveDest.x = cosf(45) * -PLAYER_SPEED;
		}
	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_A))
	{// ←移動
	 
	    // 向きの設定
		m_fRotYDist = D3DXToRadian(-90);

		m_moveDest.x = PLAYER_SPEED;

	}
	else if (CManager::GetKeyboard()->GetKeyPress(DIK_D))
	{// →移動
	 
	    // 向きの設定
		m_fRotYDist = D3DXToRadian(90);

		m_moveDest.x = -PLAYER_SPEED;
	}

	

}
//******************************
// 移動操作(コントローラー)
//******************************
void CPlayer::MoveController(void)
{
	// ジョイスティックの情報の取得
	DIJOYSTATE js = CManager::GetJoypad()->GetStick(m_nPlayerNum);

	// スティックがどれくらい倒されているかでスピードの調整
	float fSpeedX = 0.0f;
	float fSpeedZ = 0.0f;
	if (js.lX < 0)
	{
		fSpeedX = 0 - js.lX;
	}
	else if (js.lX > 0)
	{
		fSpeedX = js.lX - 0;
	}

	if (js.lY < 0)
	{
		fSpeedZ = 0 - js.lY;
	}

	else if (js.lY > 0)
	{
		fSpeedZ = js.lY - 0;
	}

	// スティックが倒されている角度
	float fAngle = atan2f(js.lY, js.lX);
	// スティックが一定以上倒されているとき
	if (js.lX >= 10 || js.lX <= -10 || js.lY >= 10 || js.lY <= -10)
	{
		// 移動量の目標値
		m_moveDest.x = cosf(fAngle) * -fSpeedX / 100;
		m_moveDest.z = sinf(fAngle) * fSpeedZ / 100;
		// 向きの設定
		m_fRotYDist = atan2f(js.lX, -js.lY);
	}

	// 慣性
	m_move += (m_moveDest - m_move) * PLAYER_MOVE_RATE;

	// 座標
	D3DXVECTOR3 pos = GetPos();
	// 移動量を足す
	pos += m_move;

	// 座標のセット
	SetPos(pos);

	
}

//******************************
// キャラクターの向きの設定
//******************************
void CPlayer::Direction(void)
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
	rot.y += (m_fRotYDist - rot.y)*PLAYER_DIRECTION_RATE;
	// 向きの設定
	SetRot(rot);
}

//******************************
// 攻撃操作
//******************************
void CPlayer::Attack(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_SPACE) || CManager::GetJoypad()->GetJoystickTrigger(2, m_nPlayerNum))
	{// 弾を撃つ
		// プレイヤーの向いている方向の取得
		float fRotY = GetRot().y - D3DXToRadian(90);
		// 移動量
		D3DXVECTOR3 bulletMove;
		bulletMove.x = cosf(fRotY)*-BULLET_SPEED_PLAYER;
		bulletMove.y = 0;
		bulletMove.z = sinf(fRotY)*BULLET_SPEED_PLAYER;
		// 弾を撃つ位置の調整
		D3DXVECTOR3 pos = GetPos();
		pos.y += 10;
		// 弾の生成
		CBullet::Create(pos, bulletMove, 300, CBullet::BULLETUSER_PLAYER)->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}
