//=============================================================================
//
// scratchヘッダ [scratch.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _SCRATCH_H_
#define _SCRATCH_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene3d.h"

//*****************************
// マクロ定義
//*****************************
#define SCRATCH_SIZE_PLAYER 180   // サイズ
#define SCRATCH_SIZE_ENEMY 100   // サイズ
#define SCRATCH_COLLISION_SIZE_PLAYER 150


// 当たり判定のサイズ
#define SCRATCH_COLLISION_SIZE_ENEMY 100   // 当たり判定のサイズ
#define SCRATCH_HEIGHT 75 // プレイヤーより高い位置に置く
//*****************************
// 前方宣言
//*****************************
class CCollision;

//*****************************
// クラス定義
//*****************************

 
// 弾クラス
class CScratch : public CScene3d
{
public:
	typedef enum
	{
		SCRATCHUSER_PLAYER,
		SCRATCHUSER_ENEMY,
		SCRATCHUSER_BOSS,
		SCRATCHUSER_MAX,
	}SCRATCHUSER;

	//メンバ関数
	CScratch();
	~CScratch();
	static CScratch *Create(const D3DXVECTOR3 pos, const float fAngle, const  SCRATCHUSER user, const int nPlayerNum);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void CollisionScratch(SCRATCHUSER user);
	void Animation(void);
	// メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[SCRATCHUSER_MAX]; // テクスチャ
	SCRATCHUSER m_user; // バレットユーザー
	CCollision*m_pCollision;    // コリジョンクラスのポインタ
	int m_nPlayerNum;   // どのプレイヤーの攻撃か
	int m_nCntAnim;     // アニメーションカウント
	int m_nAnimX;       // アニメーションX軸
	int m_nAnimY;       // アニメーションY軸
	bool m_bAttackEnemy;
	bool m_bAttackPlayer;
};

#endif