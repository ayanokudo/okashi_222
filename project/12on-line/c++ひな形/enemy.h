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
#include "model_hierarchy.h"

//*****************************
// 前方宣言
//*****************************
class CCollision;
class CMotion;
class CBillboard;
//*****************************
// クラス定義
//*****************************

// パーティクルクラス
class CEnemy : public CModelHierarchy
{
public:

	// モーション列挙
	typedef enum
	{
		WALK = 0,	  // 歩き
		MOTION_MAX
	}MOTION;

	typedef enum
	{
		ENEMY_CARRIER = 0,		//お菓子運んでる敵
		ENEMY_ESCORT,			//BOSS守ってる敵
		ENEMY_MAX,
	}ENEMY;

	// 状態
	typedef enum
	{
		STATE_NORMAL = 0,	//歩き
		STATE_DAMAGE,		//ダッシュ
		STATE_MAX
	}STATE;

	//メンバ関数
	CEnemy();
	~CEnemy();
	static CEnemy *Create(D3DXVECTOR3 pos, ENEMY type);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Hit(int nDamage);
	CCollision *GetCollision(void) { return m_pCollision; }
private:
	//各敵キャラの動きの処理
	void RangeDecisionCarrier(void);
	void RangeDecisionEscort(void);
	void MotionCarrier(void);
	void MotionEscort(void);
	void Move(void);
	void Direction(void);
	void Sweat(void);
	void CollisionPlayer(void);

	// メンバ変数
	static CModel::Model m_model[ENEMY_MAX][MAX_PARTS_NUM]; // モデル情報
	static int m_nNumModel;                      // モデル数
	static char m_achAnimPath[MOTION_MAX][64];   // アニメーションテキストのパス格納用
	static LPDIRECT3DTEXTURE9 m_pTexture;

	//static LPD3DXMESH m_pMeshModel[ENEMY_MAX];	//メッシュ情報へのポインタ
	//static LPD3DXBUFFER m_pBuffMatModel[ENEMY_MAX];	//マテリアル情報へのポインタ
	//static DWORD m_nNumMatModel[ENEMY_MAX];	//マテリアル情報の数
	//static LPDIRECT3DTEXTURE9 m_apTexture[ENEMY_MAX]; // テクスチャ

	D3DXVECTOR3 m_move;        // 移動量
	D3DXVECTOR3 m_moveDest;
	CCollision *m_pCollision;    // 当たり判定
	CCollision *m_pRadiusColision;
	ENEMY m_type;
	int m_nLife;
	bool m_bRd;
	bool m_bCarrier;
	float m_fRotYDist;
	int m_nCount;
	int m_nCntAttack;
	int m_nCountMotion;
	int m_nCountRand;
	bool m_bRoute;             // 逃げるとき壁ののほうに永遠といかないようにする
	CMotion*m_pMotion[MOTION_MAX];  // アニメーションポインタ
	
	CBillboard*m_pBilboard;
	// アニメーション用
	int m_nCntAnim;       // アニメーションカウント
	int m_nAnimX;         // アニメーションX軸
	int m_nAnimY;         // アニメーションY軸

	int m_nCntState;                // ステート遷移用のカウント
	STATE m_state;                  // 状態
};

#endif