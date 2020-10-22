//=============================================================================
//
// enemyヘッダ [enemy.h]
// Author : 筒井 俊稀
//
//=============================================================================

//二重インクルード防止
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CEnemy : public CModel
{
public:
	typedef enum
	{
		ENEMY_CARRIER,		//お菓子運んでる敵
		ENEMY_ESCORT,		//BOSS守ってる敵
		ENEMY_RARE,			//レアキャラ
		ENEMY_MAX,
	}ENEMY;

	//メンバ関数
	CEnemy();
	~CEnemy();
	static CEnemy *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	// メンバ変数
	static LPD3DXMESH m_pMeshModel;	//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel;	//マテリアル情報へのポインタ
	static DWORD m_nNumMatModel;	//マテリアル情報の数
	static LPDIRECT3DTEXTURE9 m_apTexture[ENEMY_MAX]; // テクスチャ
	D3DXVECTOR3 m_move;        // 移動量
};

#endif