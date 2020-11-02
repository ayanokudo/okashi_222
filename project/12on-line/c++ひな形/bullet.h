//=============================================================================
//
// bulletヘッダ [bullet.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// マクロ定義
//*****************************
#define BULLET_SPEED_PLAYER 25    // 速度(プレイヤーの弾)
#define BULLET_SPEED_ENEMY 20     // 速度(エネミーの弾)
#define BULLET_SIZE 100            // サイズ

//*****************************
// 前方宣言
//*****************************
class CCollision;

//*****************************
// クラス定義
//*****************************

// 弾クラス
class CBullet : public CScene3d
{
public:
	typedef enum
	{
		BULLETUSER_PLAYER,
		BULLETUSER_ENEMY,
		BULLETUSER_MAX,
	}BULLETUSER;

	//メンバ関数
	CBullet();
	~CBullet();
	static CBullet *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const int nLife, const  BULLETUSER user);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
private:
	void CollisionBullet(BULLETUSER user);
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャ
	D3DXVECTOR3 m_move; // 移動量
	int m_nLife;        // 寿命
	BULLETUSER m_user; // バレットユーザー
	CCollision*m_pCollision;    // コリジョンクラスのポインタ
};

#endif